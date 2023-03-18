#include "ros/ros.h"
#include "ros/console.h"
#include "server_io_pkg/diftorder.h"
#include "std_msgs/UInt16.h"
#include "std_msgs/Float64.h"
//idconfig => 107

const char* headgroup = "-d 00339447";
const char* pipegroup = "-d 00339350";

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

class SMOT{
	private:
		long dflstpnt = 10000;
		long spindiv = 200;
		long stepdiv = 16;
		double target_angular = 0.0f;
		long target_stepspeed = 0;
		char order_buff[512];
		
	public:
		SMOT(){
		}
		void set_angularad(double angular){
			target_angular = angular;
			target_stepspeed = (long)round((double)(spindiv*stepdiv*dflstpnt)*target_angular*M_1_PI/2);
		}
		void set_halt(bool on){
			if(on){
				//halt set
				sprintf(order_buff, "sudo ticcmd --halt-and-hold");
			}else{
				//active set
			}
			system(order_buff);
		}
		void set_home(const char* sn = ""){
			sprintf(order_buff, "sudo ticcmd %s --halt-and-set-position 0", sn);
			system(order_buff);
		}
		void find_home(const char* sn = ""){
			sprintf(order_buff, "sudo ticcmd %s --home fwd", sn);
			system(order_buff);
		}
		void put_speedorder(long step, const char* sn = ""){
			sprintf(order_buff, "sudo ticcmd %s --exit-safe-start -y %ld\n", sn, step);
			system(order_buff);
		}
		void put_speedorder(const char* sn=""){
			sprintf(order_buff, "sudo ticcmd %s --exit-safe-start -y %ld\n", sn, target_stepspeed);
			system(order_buff);
		}
		void put_posistionorder(long step, const char* sn=""){
			sprintf(order_buff, "sudo ticcmd %s --exit-safe-start -p %ld\n", sn, step);
			system(order_buff);
		}
		void put_poweringorder(bool on, const char* sn=""){
			if(on){
				sprintf(order_buff, "sudo ticcmd %s --energize", sn);
			}else{
				sprintf(order_buff, "sudo ticcmd %s --deenergize", sn);
			}
			system(order_buff);
		}
}smot;

//response of optbyte
#define _shootHalt_     0
#define _shootLaunch_   1
#define _shootSethome_  3
#define _shootFindhome_ 4
#define _shootDofset_   5
#define _shootPowering_   7
struct{
	bool launched = false;
	bool useExtern = true;
}now;
bool callbackservice(server_io_pkg::diftorder::Request &req, server_io_pkg::diftorder::Response &res){

	switch(req.option){
		case 1<<_shootHalt_:
			smot.set_halt(true);
			now.launched = false;
		break;
		case 1<<_shootLaunch_:
		case 1<<_shootLaunch_|1<<(_shootLaunch_+1):
			smot.set_halt(false);
			  now.launched = true;
			  if(req.option & (1<<2)) now.useExtern = true;
			  else now.useExtern = false;
		break;
		case 1<<_shootSethome_:
			smot.set_home(pipegroup);
		break;
		case 1<<_shootFindhome_:
			smot.find_home(pipegroup);
		break;
		case 1<<_shootDofset_:
		case 1<<_shootDofset_|1<<(_shootDofset_+1):
			if(req.option & (1<<6)){
				smot.put_posistionorder(-33000, headgroup);
			}else { //hold
				smot.put_posistionorder(0, headgroup);
			}
			break;
		case 1<<_shootPowering_:
		case 1<<_shootPowering_|1<<(_shootPowering_+1):
			if(req.option & (1<<8)){
				smot.put_poweringorder(true, pipegroup);
			}else{
				smot.put_poweringorder(false, pipegroup);
			}
			break;
		default:
			break;
	}
	res.state = req.option;
	return true;
}
void stepperCallback(const std_msgs::Float64::ConstPtr& msg){
	if(now.launched && now.useExtern){
		smot.set_angularad(msg->data);
		smot.put_speedorder(pipegroup);
	}
}
void stepperCallback_inherit(const std_msgs::Float64::ConstPtr& msg){
	if(now.launched && !now.useExtern){
		smot.set_angularad(msg->data);
		smot.put_speedorder(pipegroup);
	}
}

int main(int argc, char **argv){
	ros::init(argc, argv, "server_o");
	ros::NodeHandle node;
	ros::ServiceServer service = node.advertiseService("dift_control", callbackservice);
	ros::Subscriber sub1= node.subscribe("Stepper_Omega", 10, stepperCallback);
	ros::Subscriber sub2= node.subscribe("Stepper_Omega_inherit", 10, stepperCallback_inherit);
	ROS_INFO("READY");
	ros::spin();

	return 0;
}
