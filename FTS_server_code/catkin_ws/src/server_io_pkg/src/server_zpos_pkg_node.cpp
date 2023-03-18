#include "ros/ros.h"
#include "ros/console.h"
#include "server_io_pkg/diftorder.h"
#include "std_msgs/UInt16.h"
#include "std_msgs/Float64.h"
#include "std_msgs/Empty.h"
#include "std_msgs/Float64MultiArray.h"

static double cm = 7.28, bodymass = 2.4, vel = 0;
ros::Publisher pub;
using namespace std;
std_msgs::Float64 omg;
void CmdCallback(const std_msgs::Empty::ConstPtr& msg){
	vel = 0;
	omg.data = 0;
}
void CellCallback(const std_msgs::Float64MultiArray::ConstPtr& msg){
	double acc = (msg->data[2]+cm)/bodymass;
	vel += acc/80;//80hz
	omg.data = -vel/2.5;//r
	pub.publish(omg);
}
int main(int argc, char **argv){
	/*
	ros::init(argc, argv, "server_zpos");
	ros::NodeHandle node;
	ros::Rate r(10);
	ros::Subscriber subcmd= node.subscribe("/launch_trigger", 10, CmdCallback);
	ros::Subscriber subcell= node.subscribe("/server_loadcells", 10, CellCallback);
	pub= node.advertise<std_msgs::Float64>("Stepper_Omega_inherit", 10);
	ROS_INFO("READY");
	omg.data = 0;
	ros::spin();
	*/
	return 0;
}
