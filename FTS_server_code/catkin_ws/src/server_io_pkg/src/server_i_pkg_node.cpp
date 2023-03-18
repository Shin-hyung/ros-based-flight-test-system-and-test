#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "std_msgs/UInt8.h"
#include "std_msgs/Time.h"
#include <cmath>

#include <malloc.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <time.h>

#include "VL53L1X_api.h"
#include "VL53L1X_calibration.h"
#include "vl53l1_platform.h"

#define POLLING 1

#define MICRO_WAIT 200000

#define VL53L1_MAX_I2C_XFER_SIZE 256

#define MSG_START "VL53L1X sensor detected\n"
#define MSG_OK "ok\n"
#define MSG_UNKNOWN_CMD "Unknown command\n"
#define MSG_WRONG_VALUE "Warning: Wrong value sent\n"
#define INPUT_BUFFER_SIZE 512

#define ST_TOF_IOCTL_WFI 1

//XAVIER SETTINGS
#define I2C_BUS_NUM 8

char cmd[1024];
int user_cmd_set;
int SensorStateBool;

uint16_t Dev;

int main(int argc, char **argv){
	ros::init(argc, argv, "server_i");
	ros::NodeHandle node;
	ros::Publisher pubDist = node.advertise<std_msgs::Float64>("server_zpos/mesured", 1);
	ros::Publisher pubStat = node.advertise<std_msgs::UInt8>("server_zpos/sensor/state", 1);
	ros::Publisher pubStamp = node.advertise<std_msgs::Time>("server_zpos/sensor/time", 1);
	ros::Rate loop_rate(10);

	int adapter_nr = 0;
    int file = 0;
    int status;
    uint8_t byteData, sensorState = 0;
    uint16_t wordData;
    VL53L1X_Result_t Results;
    uint8_t first_range = 1;
    uint8_t I2cDevAddr = 0x29;

    adapter_nr = I2C_BUS_NUM;

    file = VL53L1X_UltraLite_Linux_I2C_Init(Dev, adapter_nr, I2cDevAddr);
    if (file == -1){
		ROS_ERROR("error to access i2cdev");
		exit(1);
	}

#if !defined(POLLING)
    status = VL53L1X_UltraLite_Linux_Interrupt_Init();
    if (status == -1){
		ROS_ERROR("error to access i2c interrupt");
        exit(1);
	}
#endif

	status = VL53L1_RdByte(Dev, 0x010F, &byteData);
    ROS_INFO("VL53L1X Model_ID: %X\n", byteData);
    status += VL53L1_RdByte(Dev, 0x0110, &byteData);
    ROS_INFO("VL53L1X Module_Type: %X\n", byteData);
    status += VL53L1_RdWord(Dev, 0x010F, &wordData);
    ROS_INFO("VL53L1X: %X\n", wordData);
    while (sensorState == 0) {
        status += VL53L1X_BootState(Dev, &sensorState);
        VL53L1_WaitMs(Dev, 2);
    }
    ROS_INFO("Chip booted\n");

    status = VL53L1X_SensorInit(Dev);
    /* status += VL53L1X_SetInterruptPolarity(Dev, 0); */
    status += VL53L1X_SetDistanceMode(Dev, 1); /* 1=short, 2=long */
    status += VL53L1X_SetTimingBudgetInMs(Dev, 100);
    status += VL53L1X_SetInterMeasurementInMs(Dev, 100);
    status += VL53L1X_StartRanging(Dev);

	while(ros::ok()){
		std_msgs::UInt8 ros_status;
		std_msgs::Float64 ros_distance;

#if defined(POLLING)
		uint8_t dataReady = 0;

		while (dataReady == 0) {
			status = VL53L1X_CheckForDataReady(Dev, &dataReady);
			usleep(1);
		}
#else
		status = VL53L1X_UltraLite_WaitForInterrupt(ST_TOF_IOCTL_WFI);
		if (status) {
			ROS_INFO("ST_TOF_IOCTL_WFI failed, err = %d\n", status);
			return -1;
		}
#endif
		/* Get the data the new way */
		status += VL53L1X_GetResult(Dev, &Results);

		ros_status.data = Results.Status;
		ros_distance.data = Results.Distance;
		//printf("Status = %2d, dist = %5d, Ambient = %2d, Signal = %5d, #ofSpads = %5d\n",	Results.Status, Results.Distance, Results.Ambient, Results.SigPerSPAD, Results.NumSPADs);

        /* trigger next ranging */
		status += VL53L1X_ClearInterrupt(Dev);
		if (first_range) {
			/* very first measurement shall be ignored
			 * thus requires twice call
			 */
			status += VL53L1X_ClearInterrupt(Dev);
			first_range = 0;
		}


		pubDist.publish(ros_distance);
		pubStat.publish(ros_status);

		std_msgs::Time ros_time;
		ros_time.data = ros::Time::now();
		pubStamp.publish(ros_time);

		ros::spinOnce();
		//if you want static dt. uncomment blow
		//loop_rate.sleep();
	}
	return 0;
}
