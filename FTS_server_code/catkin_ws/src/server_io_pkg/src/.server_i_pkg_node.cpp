#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include <cmath>
#include <stdlib.h>

#include <linux/i2c-dev.h>
#include "a.h"
#include "b.h"
using namespace std;


int main(int argc, char **argv){
	ros::init(argc, argv, "server_i");
	ros::NodeHandle node;
	ros::Publisher pub = node.advertise<std_msgs::Float64>("server_zpos/mesured", 1);
	ros::Rate loop_rate(10);

	dosomething1();
	dosomething2();
	while(ros::ok()){
		std_msgs::Float64 msg;
		msg.data = 0.5f;
		pub.publish(msg);
		ros::spinOnce();
		loop_rate.sleep();
	}
	return 0;
}

void dosomething1(){
	volatile int i = 0;
	i++;
}
void dosomething2(){
	volatile int i = 0;
	i++;
}
