/* IMPORTANT CHECKLIST					//
* MODEMDEVICE chmod 666 are setted?		//
*										//
/ ***************************************/

#include "ros/ros.h"
#include "std_msgs/UInt8.h"
#include "std_msgs/Float64MultiArray.h"
//#include "server_io_pkg/data.h" //for custom message
#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <termios.h>
#include <sys/signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BAUDRATE B115200
#define MODEMDEVICE "/dev/ttyTHS0"


//statcode
#define VAILED_CELL_DATA 0
#define STATE_HALT 1
#define STATE_OPERATE 2

using namespace std;
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

int main(int argc, char **argv){
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
	ROS_INFO("READY");
	ros::init(argc, argv, "server_io");
	ros::NodeHandle node;
	ros::Publisher pub_loadcell = node.advertise<std_msgs::Float64MultiArray>("/server_loadcells", 1);

	while(ros::ok()){
		uart.parse();

		if(uart.isValueupdated()){
			std_msgs::Float64MultiArray msg_loadcell;
			msg_loadcell.data.resize(3);
			for(int i=0; i<3; i++) {
				const long centerval = 8388608;
				msg_loadcell.data[i] = (double)(sensor.raw.load[i] - centerval)*kim::dfl.kpb;
			}
			pub_loadcell.publish(msg_loadcell);
		}	
	}
	return 0;
}
