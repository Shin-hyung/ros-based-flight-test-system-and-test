/* IMPORTANT CHECKLIST					//
* MODEMDEVICE chmod 666 are setted?		//
*										//
/ ***************************************/

#include "ros/ros.h"
#include "std_msgs/UInt8.h"
#include "std_msgs/Float64MultiArray.h"
#include "server_io_pkg/diftorder.h" //for custom message
#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <termios.h>
#include <time.h>
#include <sys/signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <hiredis.h>
#include <tic.hpp>


#define BAUDRATE B115200
#define MODEMDEVICE "/dev/ttyTHS0"

#include "ros/ros.h"
#include "ros/console.h"
#include "server_io_pkg/diftorder.h"
#include "std_msgs/UInt16.h"
#include "std_msgs/Float64.h"
#include "std_msgs/Empty.h"
#include "std_msgs/Float64MultiArray.h"

//statcode
#define VAILED_CELL_DATA 0
#define STATE_HALT 1
#define STATE_OPERATE 2

//response of optbyte
#define _shootHalt_     0
#define _shootLaunch_   1
#define _shootSethome_  3
#define _shootFindhome_ 4
#define _shootDofset_   5
#define _shootPowering_ 7
#define _setAvr_ 8

using namespace std;
//trigger for launch
ros::Publisher publaunch;
//mot address
const char* headgroup = "00390845";
const char* pipegroup = "00339350";

namespace zpos{
	static double center_mass = 7.975, vel = 0, omg;
}
struct{
    bool launched = false;
    bool useExtern = true;
    bool holding = false;
    bool release = false;
    bool rellchan = false;
    double zkgf = 0.0f;
    double bodymass = 3.0f;//kgf
}now;

namespace kim{
        struct{
                const   double  whell   = 0.05f;//'diameter' of whell
                const   int     spa     = 200;// step per revol
                const   int     stpdiv  = 16;// step division
                const   double  sth     = 0.0f;//(spa/stepdiv/360)*2*PI*whell single step to height
                const   double  gpb     = 0.009535f;
                const   double  kpb     = 0.000009535f;//bit to kgf;
                const   double  vdda    = 3.3f;
        }dfl;
};


class SMOT{
    private:
        long dflstpnt = 10000;
        long spindiv = 200;
        long stepdiv = 16; 
        double target_angular = 0.0f;
        long target_stepspeed = 0;
		tic::handle handle;	
    public:
        SMOT(const char* sn = nullptr){
			try{
				handle = open_handle(sn);
			}
			catch(const std::exception & error){
				//std::cerr << "Error: << error.what() << std:endl; return 1;
				ROS_ERROR("Stepper motor connection error");
			}
        }

		tic::handle open_handle(const char * desired_serial_number = nullptr)
		{
		  // Get a list of Tic devices connected via USB.
		  std::vector<tic::device> list = tic::list_connected_devices();

		  // Iterate through the list and select one device.
		  for (const tic::device & device : list)
		  {
			if (desired_serial_number &&
			  device.get_serial_number() != desired_serial_number)
			{
			  // Found a device with the wrong serial number, so continue on to
			  // the next device in the list.
			  continue;
			}

			// Open a handle to this device and return it.
			return tic::handle(device);
		  }

		  throw std::runtime_error("No device found.");
		}
		
        void set_angularad(double angular){
            target_angular = angular;
            target_stepspeed = (long)round((double)(spindiv*stepdiv*dflstpnt)*target_angular*M_1_PI/2);
        }
        void set_halt(bool on){
            if(on){
                //halt set
				handle.halt_and_hold();
            }else{
                //active set
            }
        }
        void set_home(){
			handle.halt_and_set_position(0);
        }
        void set_hold(const char* sn = ""){
			handle.set_target_velocity(0);
        }
        void find_home(void){
		//0이 앞 방향인지 1이 앞 방향인지 모르겠음, 확인 필요.
		//원래 Zpos 값 등을 기준으로 현제 위치에서 이동해야 할 위치 계산해서 간 뒤
		//set_home 하는 코드인데 임시록 아래 코드 삽입.
			handle.go_home(0);
        }
        void put_speedorder(int32_t step){
			handle.set_target_velocity(step);
        }
        void put_speedorder(){
			handle.set_target_velocity((uint32_t)target_stepspeed);
        }
        void put_positionorder(int32_t step){
			handle.set_target_position(step);
        }
        void put_poweringorder(bool on){
            if(on){
			   handle.energize();	
			}else{
			   handle.deenergize();	
            }
        }
        void go_home(const char* sn=""){
			handle.go_home(0);
        }
};

SMOT *hmot, *zmot;


//cast of cmd and sensor
struct {
	struct {
		union {
			uint8_t dlpf:1;
			uint8_t byte;
		};
	}mode;
}cmd;

struct {
    struct {
		timeval time_past;
		timeval time;	
        uint32_t load[3];
    }raw;
}sensor;

class UART{
private:
        struct sigaction saio;           /* signal action의 정의 */
        struct termios oldtio,newtio;
        vector<string> split(string input, char delimiter) {
            vector<string> answer;
            stringstream ss(input);
            string temp;

            while (getline(ss, temp, delimiter)) {
                answer.push_back(temp);
            }

            return answer;
        }
public:
        struct cussig_t{
                bool ok = false;
                bool Valueupdate = false;
                bool isUartdataupdate=false;                    /* when data-parsed ready */
                bool error = false;
        }sig;
        timeval rcvtime;
        int fd, bufflen;
        int isReadytoparse=false;
        char buf[255];
        UART() {
        }
        ~UART() {
                send("AT+R\n",5);//Reset
                tcsetattr(fd,TCSANOW,&oldtio);
        }
        void connect(); 
        bool isValueupdated(){
                bool result = sig.Valueupdate;
                sig.Valueupdate = false;
                return result;
        }
        void send(const char* c) {
                write(fd, c, sizeof(c));
        }
        void send(const char* c, int i) {
                write(fd, c, i);
        }
        void send(char* c, int i) {
                write(fd, c, i);
        }
        void enter(){
                write(fd, "\n", 1);
        }
        int parse(){
                if(!sig.isUartdataupdate) return 0;
                string istr = buf;
                if(istr == "OK\n"){
                        sig.ok=true;
                }
                if(isReadytoparse && (bufflen == 22)){
                        char *ptr = strtok(buf, " ");
                        int i = 0;
                        while(ptr != NULL && i < 3){
                                sensor.raw.load[i] = strtoul((const char*) ptr,NULL,16);
                                ptr = strtok(NULL, " ");
                                i++;
                        }
                        sensor.raw.time.tv_sec = this->rcvtime.tv_sec;
                        sensor.raw.time.tv_usec = this->rcvtime.tv_usec;
                        sig.Valueupdate = true;
                }
                memset(buf, 0, sizeof(buf));
                sig.isUartdataupdate = false;
                return bufflen;
        }
        void ok(){ send("AT+\n", 4); }
        int init();
}uart;
void io_callback (int status) {
        uart.bufflen = read(uart.fd, uart.buf, 255);
        uart.buf[uart.bufflen] = 0;
        uart.sig.error |= !! gettimeofday(&uart.rcvtime, NULL);
        uart.sig.isUartdataupdate = true;
}
void UART::connect(){
		/* Non-blocking 모드로 시리얼 장치를 연다(read 함수 호출 후 즉각 리턴) */
		fd = open(MODEMDEVICE, O_RDWR | O_NOCTTY | O_NONBLOCK);
		if (fd <0) {perror(MODEMDEVICE); exit(-1); }

		/* install the signal handler before making the device asynchronous */
		/* 장치를 비동기 모드로 만들기 전에 signal handler */

		saio.sa_handler = io_callback;
		sigemptyset(&saio.sa_mask);
		saio.sa_flags = 0;
		saio.sa_restorer = NULL;
		sigaction(SIGIO,&saio,NULL);

		/* SIGIO signal을 받을 수 있도록 한다. */
		fcntl(fd, F_SETOWN, getpid());
		/* file descriptor를 비동기로 만든다. (manual page를 보면
		O_APPEND 와 O_NONBLOCK만이 F_SETFL에 사용할 수 있다고 되어 있다.) */
		fcntl(fd, F_SETFL, FASYNC);

		tcgetattr(fd,&oldtio); /* save current port settings */
		/* canonical 입력처리를 위한 포트 세팅 */
		bzero(&newtio, sizeof(newtio));
		newtio.c_cflag = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;
		newtio.c_iflag = IGNPAR | ICRNL;
		newtio.c_oflag = 0;
		newtio.c_lflag = ICANON;
		newtio.c_cc[VMIN]=0;
		newtio.c_cc[VTIME]=1;
		tcflush(fd, TCIFLUSH);
		tcsetattr(fd,TCSANOW,&newtio);
}
int UART::init(){
        uart.send("AT+r\n",5);//refresh
        usleep(500000);
        uart.send("AT+R\n",5);//Reset
        usleep(50000);
        ok();
        usleep(50000);
        ok();
        usleep(50000);
        parse();
        if(sig.ok){
                cout << "AUC connected" << endl;
                isReadytoparse = true;
                return 0;
        }
        else{
                cout << "cannot find AUC" << endl;
                return 1;
        }
}

bool callbackservice(server_io_pkg::diftorder::Request &req, server_io_pkg::diftorder::Response &res){
    std_msgs::Empty msg;
    //ros::Rate cellrate(80);
    //int i = 80*1;//sec
    switch(req.option){
        case 1<<_shootHalt_:
            hmot->set_halt(true);
            zmot->set_halt(true);
            now.launched = false;
        break;
        case 1<<_shootLaunch_:
        case 1<<_shootLaunch_|1<<(_shootLaunch_+1):
            hmot->set_halt(false);
            zmot->set_halt(false);
            now.launched = true;
            publaunch.publish(msg);
            if(req.option & (1<<2)) now.useExtern = true;
            else now.useExtern = false;
        break;
        case 1<<_shootSethome_:
            zmot->set_home();
        break;
        case 1<<_shootFindhome_:
            zmot->find_home();
        break;
        case 1<<_shootDofset_:
        case 1<<_shootDofset_|1<<(_shootDofset_+1):
            if(req.option == 32){
                hmot->put_positionorder(0);
                //now.holding = true;
                //now.rellchan = true;
            }else if(req.option == 96) { //hold release part
                hmot->put_positionorder(-20000);
                //now.release = true;
                //now.rellchan = true;
            }
            break;
        case 1<<_shootPowering_:
        case 1<<_shootPowering_|1<<(_shootPowering_+1):
            if(req.option & (1<<8)){
				zpos::vel = 0;
				zpos::omg = 0;
				hmot->put_poweringorder(true);
				zmot->put_poweringorder(true);
            }else{
				hmot->put_poweringorder(false);
				zmot->put_poweringorder(false);
            }
            break;
        case 1<<_setAvr_:
			zpos::center_mass = - now.zkgf;
			break;
        default:
            break;
    }
    res.state = req.option;
    return true;
}
void update(){
	/*
    ros::Rate cellrate(100);
    if(now.holding){
        now.holding = false;
        int i = 400;//csec
        while(ros::ok()){
            ros::spinOnce();
            if(now.zkgf>0){
				hmot->set_home();
				hmot->set_hold();
                break;
            }
            else; hmot->put_positionorder(2000000);
            i--;
            if(i < 0 || now.rellchan){
                now.rellchan = false;
                break;
            }
            cellrate.sleep();
        }
    }
    if(now.release){
        now.release = false;
        int i = 400;//sec
        while(1){
            ros::spinOnce();
            hmot->put_positionorder(-50000);
            i--;
            if(i < 0 || now.rellchan){
                now.rellchan = false;
                break;
            }
            cellrate.sleep();
        }
    }
	*/
}
double calc_omega_inherit(){
	static ros::Time timestamp;
	ros::Duration duration = ros::Time::now() - timestamp;
    double acc = (now.zkgf+zpos::center_mass)*9.80665/now.bodymass;
	zpos::vel += acc*duration.toSec();
    zpos::omg = -zpos::vel/2.5;//r
	timestamp = timestamp + duration;
	return zpos::omg;
}
void stepperCallback(const std_msgs::Float64::ConstPtr& msg){
    if(now.launched && now.useExtern){
        zmot->set_angularad(msg->data);
        zmot->put_speedorder();
    }
}
/*
void stepperCallback_inherit(const std_msgs::Float64::ConstPtr& msg){
    if(now.launched && !now.useExtern){
        //smot.set_angularad(msg->data);
        //smot.put_speedorder(pipegroup);
    }
}
*/
void stepperCallback_inherit(){
 if(now.launched && !now.useExtern){
        zmot->set_angularad(calc_omega_inherit());
        zmot->put_speedorder();
 }
}
void CmdCallback(const std_msgs::Empty::ConstPtr& msg){
	zpos::vel = 0;
	zpos::omg = 0;
}
void spinner(){
	ros::spinOnce();
	update();
}

int main(int argc, char **argv){
	hmot = new SMOT(headgroup);
	zmot = new SMOT(pipegroup);
	hmot->put_poweringorder(true);
	/*temporal data config*/
	cmd.mode.dlpf = 1;

	uart.connect();
	if(uart.init()) ROS_INFO("UART failure");
	usleep(50000);
    uart.send("AT+H\n",5);
    if(cmd.mode.dlpf){//dlf on(send +D);
        usleep(50000);
        uart.send("AT+D\n",5);
    }   
    usleep(50000);
    uart.send("AT+p\n",5);

	ros::init(argc, argv, "server_io");
	ros::NodeHandle node;
	ros::ServiceServer service = node.advertiseService("/dift_control", callbackservice);
	ros::Subscriber substepo= node.subscribe("Stepper_Omega", 1, stepperCallback);
	//ros::Subscriber substepoi= node.subscribe("Stepper_Omega_inherit", 1, stepperCallback);
	ros::Subscriber subcmd= node.subscribe("/launch_trigger", 1, CmdCallback);
	ros::Publisher pub_loadcell = node.advertise<std_msgs::Float64MultiArray>("/server_loadcells", 1);
	ros::Publisher pub_omega_in =  node.advertise<std_msgs::Float64>("Stepper_Omega_inherit", 1);
	publaunch = node.advertise<std_msgs::Empty>("/launch_trigger",1);
	ROS_INFO("READY");
	while(ros::ok()){
		uart.parse();
		if(uart.isValueupdated()){
			std_msgs::Float64MultiArray msg_loadcell;
			std_msgs::Float64 msg_omega_in;
			msg_loadcell.data.resize(3);
			for(int i=0; i<3; i++) {
				const long centerval = 8388608;
				msg_loadcell.data[i] = (double)(sensor.raw.load[i] - centerval)*kim::dfl.kpb;
			}
			now.zkgf = msg_loadcell.data[2];
			pub_loadcell.publish(msg_loadcell);
			stepperCallback_inherit();
			msg_omega_in.data = zpos::omg;
			pub_omega_in.publish(msg_omega_in);
		}	

		spinner();
	}
	return 0;
}
