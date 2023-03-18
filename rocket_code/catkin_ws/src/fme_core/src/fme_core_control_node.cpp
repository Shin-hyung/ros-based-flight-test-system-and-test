//ROS compoenets
#include "ros/ros.h"
#include "std_srvs/Empty.h"
#include "std_srvs/SetBool.h"
#include "sensor_msgs/Imu.h"
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/Quaternion.h"
#include "geometry_msgs/Point.h"
#include "geometry_msgs/Vector3.h"
#include "sensor_msgs/Imu.h"
#include "std_msgs/Empty.h"

//Standard libs
#include <cmath>
#include <math.h>
#include <string>
#include <sstream>
#include <functional>
#include <numeric>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

//UART Serial lib
#include "serial/serial.h"
//Servo moter dirver lib
#include <tic.hpp>

#define _USE_MATH_DEFINES
#define GEE 9.80665

//DFLT SENSOR ANGLE
#define ADJUST_ROLL_DEG 0
#define ADJUST_PITCH_DEG 0
#define ADJUST_YAW_DEG 0

//Creat UART COM for IMU
serial::Serial uart;
ros::Publisher euler_angle;
ros::Publisher euler_angle_error;
ros::Publisher euler_angle_target;
ros::Publisher target_pose_pub;
bool request_set_zro = false;
bool request_launch = false;
#define _USE_MATH_DEFINES
#define FIN_AREA 0.01125 //m2
#define FIN_RAD_PER_CL 0.15901323359947 //rad/cl
#define FIN_ALPHA_LIMIT 0.785398//45도, cl 꺽이는 지점
#define FIN_ADJUST_ANG 0.015708//0.9도
#define AIRSPEED 15//m/s
double RAD2DEG (double a  ){
	return a * 180.0/3.141592;

}

using namespace std;

geometry_msgs::Quaternion Q_E();
geometry_msgs::Quaternion Q_E(geometry_msgs::Quaternion t, geometry_msgs::Quaternion c);
geometry_msgs::Vector3 Q2E(geometry_msgs::Quaternion q);
geometry_msgs::Vector3 Q2E(geometry_msgs::Quaternion q, bool deg);
geometry_msgs::Quaternion Q_Inv(geometry_msgs::Quaternion o);
geometry_msgs::Quaternion E2Q(geometry_msgs::Vector3 u);
geometry_msgs::Quaternion E2Q(geometry_msgs::Point u);
double inp(std::vector<double> a, std::vector<double> b);
void setTarget(double r, double p, double y);

std::vector<double> finangle{M_PI/2,0,-M_PI/2,0};
std::vector<double> alpha{0,0,0,0};
std::vector<double> angle{0,0,0};
std::vector<double> zndo = {0, 0, 0};	

struct{
	std::vector<std::vector<double>>k
	{	//	 P I D
	  
			{0,0,0},//X
			{0,0,0},//Y
			{0,0,0},//Z
	
			{30,10,20},//R
			{30,10,20},//P
			{30,10,20},//Y
	};//xyz-rpy
	bool data_changed=false;
}controller;

//Sensor valuse
struct{
	sensor_msgs::Imu imu;
	geometry_msgs::Pose zro;
	//Air data
	struct{
		double density = 1.2;//kg/m3
		geometry_msgs::Vector3 size;//xyz cord, m/s
	}air;
	//Body data
	struct{
		double weight = 3;//kg
		double length = 2.8;//m
		double diameter = 0.1;//m
		double CG_D[3] = {0.08, 0.8, 0.8};
		double Inerthia[3]={//Ix,Iy,Iz at pridict
			weight*diameter*diameter/8,
			weight*length*length/12,
			weight*length*length/12};
	}body;
	bool data_changed=false;
}sensor;

//Control values
struct{
	geometry_msgs::Pose pose;
	geometry_msgs::Pose poserror;
        bool request_set_zro = true;
        bool request_set_start = false;
	bool pid_rst_trigger = false;
	bool request_toggle_energize[2] = {false, false};//set unset
	bool contorol = false;
}target;

/// @brief Fin class, manage stepper motor
class Fin{
	//wing data
	double radpcl = FIN_RAD_PER_CL;
	double finarea = FIN_AREA;
	double alpha_limit = FIN_ALPHA_LIMIT;
	//stepper moter data
	long div = 128;
	double rad2p = (double)div*100/M_PI;
	long maxspeed = 256000000;//25600.0000 p/s
	long maxaccel = 25600000;//25600.0000 p/s
	long maxangle = 12800;//25600.0000 p/s
	tic::handle htic;
	public:
	double adjust_angle = FIN_ADJUST_ANG;
	
	/// @brief Setup Fin API
	/// @param in_id pololu driver id
	Fin(const char* in_id){
		//pololu API USB;
		try{
			htic = open_handle(in_id);
		}
		catch(const std::exception & error){
			ROS_ERROR("%s", error.what());
		}
		this->energize(false);
	};
	/// @brief Power on/off to motor
	/// @param set on/off value
	void energize(bool set){
		if(set){
			htic.energize();
		}else{
			htic.deenergize();
		}
	};
	/// @brief Get required angle of attack from cl table and airspeed
	/// @param force required force
	/// @param airspeed current airspeed
	/// @return angle of attack
	double get_alpha(double force, double airspeed){
		geometry_msgs::Vector3 air; air.x = airspeed;
		double v = sqrt(air.x*air.x + air.y*air.y + air.z*air.z);
		return radpcl*(force/(0.5*sensor.air.density*v*v*finarea));
	};
	double get_alpha(double force){//get airspeed from default sensor
		geometry_msgs::Vector3 air = sensor.air.size;
		double v = sqrt(air.x*air.x + air.y*air.y + air.z*air.z);
		return radpcl*(force/(0.5*sensor.air.density*v*v*finarea));
	};
	double get_angle_limited(double force, double airspeed){//applied angle limite
		double result = this->get_alpha(force,airspeed);
		if(result>alpha_limit){
			result = alpha_limit;
		}
		if(result<-alpha_limit){
			result = -alpha_limit;
		}
		return result;
	}
	double get_angle_limited(double force){//get airspped form default sensor and applied angle limit
		double result = this->get_alpha(force);
		if(result>alpha_limit){
			result = alpha_limit;
		}
		if(result<-alpha_limit){
			result = -alpha_limit;
		}
		return result;
	}
	/// @brief Set angle to motor driver
	/// @param angle 
	void set_angle(double angle){
		int32_t setpoint = round(angle*rad2p + this->adjust_angle*rad2p); //
		htic.exit_safe_start();
		htic.set_target_position(setpoint);
	}
	tic::handle open_handle(const char* serial){
		std::vector<tic::device> list = tic::list_connected_devices();
		for(const tic::device & device : list){
			if(serial && device.get_serial_number() != serial){
				continue;
			}
			return tic::handle(device);
		}
		throw std::runtime_error("No device found");
	}
};

/// @brief Process callback to change target position from ROS
/// @param msg rosmsg
void target_pose_update_callback(const geometry_msgs::Pose::ConstPtr& msg){
	target.pose.orientation.x = msg->orientation.x;
	target.pose.orientation.y = msg->orientation.y;
	target.pose.orientation.z = msg->orientation.z;
	target.pose.orientation.w = msg->orientation.w;
	target.poserror.orientation = Q_E();
	sensor.data_changed=true;
	geometry_msgs::Vector3 euler_angle_target_msg = Q2E(target.pose.orientation,true);
	euler_angle_target.publish(euler_angle_target_msg);
	geometry_msgs::Vector3 euler_angle_error_msg = Q2E(target.poserror.orientation,true);
	euler_angle_error.publish(euler_angle_error_msg);
}
void sensor_pose_update(sensor_msgs::Imu msg){
	sensor.imu.header.seq = msg.header.seq;
	sensor.imu.header.stamp = msg.header.stamp;
	sensor.imu.header.frame_id = msg.header.frame_id;
	sensor.imu.linear_acceleration.x = msg.linear_acceleration.x;
	sensor.imu.linear_acceleration.y = msg.linear_acceleration.y;
	sensor.imu.linear_acceleration.z = msg.linear_acceleration.z;
	sensor.imu.angular_velocity.x = msg.angular_velocity.x;
	sensor.imu.angular_velocity.y = msg.angular_velocity.y;
	sensor.imu.angular_velocity.z = msg.angular_velocity.z;
	sensor.imu.orientation.x = msg.orientation.x;
	sensor.imu.orientation.y = msg.orientation.y;
	sensor.imu.orientation.z = msg.orientation.z;
	sensor.imu.orientation.w = msg.orientation.w;
	target.poserror.orientation = Q_E();
	geometry_msgs::Vector3 euler_angle_error_msg = Q2E(target.poserror.orientation,true);
	euler_angle_error.publish(euler_angle_error_msg);
	sensor.data_changed=true;
}
/// @brief Process callback if get Imu data from ROS
/// @param msg 
void sensor_pose_update_callback(const sensor_msgs::Imu::ConstPtr& msg){
	sensor.imu.header.seq = msg->header.seq;
	sensor.imu.header.stamp = msg->header.stamp;
	sensor.imu.header.frame_id = msg->header.frame_id;
	sensor.imu.linear_acceleration.x = msg->linear_acceleration.x;
	sensor.imu.linear_acceleration.y = msg->linear_acceleration.y;
	sensor.imu.linear_acceleration.z = msg->linear_acceleration.z;
	sensor.imu.angular_velocity.x = msg->angular_velocity.x;
	sensor.imu.angular_velocity.y = msg->angular_velocity.y;
	sensor.imu.angular_velocity.z = msg->angular_velocity.z;
	sensor.imu.orientation.x = msg->orientation.x;
	sensor.imu.orientation.y = msg->orientation.y;
	sensor.imu.orientation.z = msg->orientation.z;
	sensor.imu.orientation.w = msg->orientation.w;
	target.poserror.orientation = Q_E();
	geometry_msgs::Vector3 euler_angle_error_msg = Q2E(target.poserror.orientation,true);
	euler_angle_error.publish(euler_angle_error_msg);
	sensor.data_changed=true;
}


/// @brief ROS service request process from flight test system
/// @param msg 
void launch_callback(const std_msgs::Empty::ConstPtr& msg){
	request_launch = true;	
}


/// @brief ROS service request process from rocket console
/// @param req ros required data
/// @param res ros result data
/// @return true
bool zro_callback(std_srvs::Empty::Request& req, std_srvs::Empty::Response& res){
        ROS_INFO("zro");
        target.request_set_zro = true;
	request_set_zro = true;
        return true;
}
bool start_callback(std_srvs::SetBool::Request& req, std_srvs::SetBool::Response& res){
        ROS_INFO("start");
	if(req.data){
		target.request_set_start = true;
		target.pid_rst_trigger = true;
	}else{
		target.request_set_start = false;
	}
        return true;
}
bool energize_callback(std_srvs::SetBool::Request& req, std_srvs::SetBool::Response& res){
	target.request_toggle_energize[req.data] = true;
	return true;
}

//Math
//Dot product
double inp(std::vector<double> a, std::vector<double> b){//dot product
	return std::inner_product(a.begin(), a.end(), b.begin(),0);
}
//Cross product of3
std::vector<double> oup3(std::vector<double> a, std::vector<double> b){//cross product of 3
	std::vector<double> c{a[1]*b[2]-a[2]*b[1], a[2]*b[0]-a[0]*b[2], a[0]*b[1]-a[1]*b[0]};
	return c;
}
//Vector merge
std::vector<double> vep(std::vector<double> a, std::vector<double> b){//vector add
	std::transform (a.begin(), a.end(), b.begin(), a.begin(), std::plus<>{});
	return a;
}
//Vector schlar product
std::vector<double> slp(double a, std::vector<double> b){//schlar mult
	std::transform (b.begin(), b.end(), b.begin(), std::bind2nd(std::plus<double>(), a));
	return b;
}
//Process calcuate error on rotation quaternion space with sensor and target attitude
geometry_msgs::Quaternion Q_E(){
	geometry_msgs::Quaternion t, c, e;
	c.x = sensor.imu.orientation.x;
	c.y = sensor.imu.orientation.y;
	c.z = sensor.imu.orientation.z;
	c.w = sensor.imu.orientation.w;
	t.x = target.pose.orientation.x;
	t.y = target.pose.orientation.y;
	t.z = target.pose.orientation.z;
	t.w = target.pose.orientation.w;

	std::vector<double> t_v{t.x, t.y, t.z};
	std::vector<double> c_v{c.x, c.y, c.z};
	std::vector<double> e_v;
	e_v = vep(vep(slp(-t.w, c_v),slp(c.w, t_v)), oup3(t_v,c_v));//벡터항 계산

	e.x=e_v[0];
	e.y=e_v[1];
	e.z=e_v[2];
	e.w = t.w*c.w - inp(t_v,c_v);//스칼라항 계산
	return e;
} 
//Process calcuate different with two rotation quaternions
geometry_msgs::Quaternion Q_E(geometry_msgs::Quaternion t, geometry_msgs::Quaternion c){
	geometry_msgs::Quaternion e;

	std::vector<double> t_v{t.x, t.y, t.z};
	std::vector<double> c_v{c.x, c.y, c.z};
	std::vector<double> e_v;
	e_v = vep(vep(slp(-t.w, c_v),slp(c.w, t_v)), oup3(t_v,c_v));//벡터항 계산

	e.x=e_v[0];
	e.y=e_v[1];
	e.z=e_v[2];
	e.w = t.w*c.w - inp(t_v,c_v);//스칼라항 계산
	return e;
} 
//Convert rotation quaternion to euler
geometry_msgs::Vector3 Q2E(geometry_msgs::Quaternion q, bool deg=false) {
	geometry_msgs::Vector3 angles;

	// roll (x-axis rotation)
	double sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
	double cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
	angles.x = std::atan2(sinr_cosp, cosr_cosp);

	// pitch (y-axis rotation)
	double sinp = 2 * (q.w * q.y - q.z * q.x);
	if (std::abs(sinp) >= 1){
	angles.y = std::copysign(M_PI / 2, sinp); // use 90 degrees if out of range
	}else{
	angles.y = std::asin(sinp);
	}

	// yaw (z-axis rotation)
	double siny_cosp = 2 * (q.w * q.z + q.x * q.y);
	double cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
	angles.z = std::atan2(siny_cosp, cosy_cosp);

	if(deg){
		angles.x = angles.x*180.0/M_PI;
		angles.y = angles.y*180.0/M_PI;
		angles.z = angles.z*180.0/M_PI;
	}
	return angles;
}
//Convert Euler angle to Quaternion, Point in
geometry_msgs::Quaternion E2Q(geometry_msgs::Point u){
	geometry_msgs::Vector3 a;
	a.x = u.x;
	a.y = u.y;
	a.z = u.z;
	return E2Q(a);
}
//Convert Euler angle to Quaternion, Vector3 in
geometry_msgs::Quaternion E2Q(geometry_msgs::Vector3 u){
	geometry_msgs::Quaternion q;
	double r = u.x, p = u.y, y = u.z;
	q.w = cos(y/2)*cos(p/2)*cos(r/2) + sin(y/2)*sin(p/2)*sin(r/2);
	q.x = cos(y/2)*cos(p/2)*sin(r/2) - sin(y/2)*sin(p/2)*cos(r/2);
	q.y = cos(y/2)*sin(p/2)*cos(r/2) + sin(y/2)*cos(p/2)*sin(r/2);
	q.z = sin(y/2)*cos(p/2)*cos(r/2) - cos(y/2)*sin(p/2)*sin(r/2);
	return q;
}
//Quaternion inverse
geometry_msgs::Quaternion Q_Inv(geometry_msgs::Quaternion o){
	geometry_msgs::Quaternion r;
	double size2 = o.x*o.x + o.y*o.y + o.z*o.z + o.w*o.w;
	r.x = -o.x/size2;
	r.y = -o.y/size2;
	r.z = -o.z/size2;
	r.w = o.w/size2;
	return r;
}

//Vector quaternion protuct to vector
geometry_msgs::Vector3 VQV(geometry_msgs::Vector3 o, geometry_msgs::Quaternion q){
	geometry_msgs::Vector3 r;
	r.x = 	  o.x*(q.w*q.w + q.x*q.x - q.y*q.y - q.z*q.z)
		+ o.y*(q.x*q.y - q.w*q.z)*2
		+ o.z*(q.x*q.z + q.w*q.y)*2
	;
	r.y = 	  o.x*(q.x*q.y + q.w*q.z)*2
		+ o.y*(q.w*q.w - q.x*q.x + q.y*q.y - q.z*q.z)
		+ o.z*(q.y*q.z - q.w*q.x)*2
	;
	r.z =	  o.x*(q.x*q.z - q.w*q.y)*2
		+ o.y*(q.y*q.z + q.w*q.x)*2
		+ o.z*(q.w*q.w - q.x*q.x - q.y*q.y + q.z*q.z)
	;
	return r;
}

/// @brief PID controller
class PID{
	double kp, ki, kd;
	double toterror, prerror, pred;
	ros::Time stamp;
	public:
	double ifanceval = 10000000;
	double Nval = 5;
	double hpfintg=0;

	/// @brief Constructor
	/// @param kp initial gain of p
	/// @param ki initial gain of i
	/// @param kd initial gain of d 
	PID(double kp, double ki, double kd){
		this->kp = kp;
		this->ki = ki;
		this->kd = kd;
		toterror = 0;
		prerror = 0;
		pred = 0;
		stamp = ros::Time::now();
	};	
	private:
	/// @brief Intgrate limiter
	/// @param value 
	void ifance(double value){
		ifanceval = value;
	}
	void ifance(){
		if(this->toterror>ifanceval)
			this->toterror = ifanceval;
		if(this->toterror<-ifanceval)
			this->toterror = -ifanceval;
	}
	public:
	/// @brief Pid update
	/// @param e input error
	/// @param der input error different
	/// @param stamp time stamp
	/// @param dfilter derivate filter
	/// @return controller out
	double run(double e, double der, ros::Time stamp, bool dfilter=true){
		double P, I, D;
		double dt = stamp.toSec() - this->stamp.toSec();
		toterror += dt*e;
		ifance();

		P = kp*e;
		I = ki*toterror;
		if(dfilter){
			D = (kd*der - hpfintg)*Nval;
			hpfintg += (D * prerror)*dt/2.0f;
		}else{
			D = kd*(der-prerror);
		}

		this->prerror = der;
		this->stamp = stamp;

		return P+I+D;
	}
	double run(double e, ros::Time stamp, bool dfilter=true){
		double P, I, D;
		double dt = stamp.toSec() - this->stamp.toSec();
		double de = e - this->prerror;
		toterror += dt*e;
		ifance();

		P = kp*e;
		I = ki*toterror;
		D = (1/(1+Nval*dt))*this->pred + (1/(1+Nval*dt))*kd*de;

		this->pred = D;
		this->prerror = e;
		this->stamp = stamp;

		return P+I+D;
	}
	void rst(){
		this->toterror = 0;
		this->prerror= 0;
		stamp = ros::Time::now();
	}
};


//Programmed movement input(experimental schedule process);
void update(){
	double delay = 10, max_angle = 5;
	double start_at_i = 2, start_at_j = 0;
	bool start_at = false;
	static bool program_running = false;
	static int i = 0, j = 0, step = 0;
	static double r = 0, p = 0, y = 0;
	static ros::Time stamp, tamp;
	static double elapsed_time = 0;

	if(request_launch){
		request_launch = false;
		stamp = ros::Time::now();
		program_running=true;
		step = 0;
		elapsed_time = 0;
		i = -max_angle;
		j = -max_angle;
		
		if(start_at){
			i = start_at_i;
			j = start_at_j;
		}
		setTarget(0,0,0);
	}
	if(program_running){
		tamp = ros::Time::now();
		double dt = tamp.toSec() - stamp.toSec();
		//elapsed_time += dt;
		if(dt> delay){
			/* 1. progam sheet 
			stamp = ros::Time::now();
			if(elapsed_time<10) setTarget(0,-10,0);
			else if(elapsed_time<15) setTarget(0,0,0);
			else if(elapsed_time<25) setTarget(0,10,0);
			else if(elapsed_time<30) setTarget(0,0,0);
			else program_running=false;
			 2. stepped program */	
			if(step % 2){
				setTarget(0,0,0);
				if(j+0.1>max_angle+1){
					program_running=false;
					step = 0;
				}
			}else{
				setTarget(0,i,j);
				i++;
				if(i+0.1 > max_angle+1){
					i = -max_angle;
					j++;
				}
			}
			step++;
			stamp = tamp;
		}
	}
}


/// @brief Target set function for attitude, euler angle in
/// @param r roll
/// @param p pitch
/// @param y yaw 
void setTarget(double r, double p, double y){//deg in
	geometry_msgs::Pose out;
	geometry_msgs::Vector3 in;
	in.x = r*M_PI/180.0;
	in.y = p*M_PI/180.0;
	in.z = y*M_PI/180.0;
	out.orientation = E2Q(in);
	target_pose_pub.publish(out);
}

/// @brief NDO frame for future work
/// @param zndo NDO state value integrated by z_ndodot
/// @param A value of disturbance
/// @param C value of coffecient of disturbance model 
/// @param n gain of distubance
/// @param x the state value
/// @param u contorl input
/// @param I gain of input
/// @return extimated disturbance
double z_ndodot(double zndo, double A, double C, double n, double x, double u, double I){
	// tau = a_acc*I + d
	return (A-n*C)*zndo + A*n*x - n*(C*n*x + I*u);
}



/// @brief Main fucntion
/// @param argc 
/// @param argv 
/// @return 0
int main(int argc, char **argv){
	std::string arg;
	sensor_msgs::Imu imu_msg; // senser msg 선언;
	//ros node 초기화;
	ros::init(argc, argv, "rocket_fcc");
	//ros ndoe 실행;
	ros::NodeHandle node;
	//uart 연결 시도
	try{
		uart.setPort("/dev/ttyUSB0");
		uart.setBaudrate(115200);
		serial::Timeout tot = serial::Timeout::simpleTimeout(1000);
		uart.setTimeout(tot);
		uart.open();
		uart.write("ss=0\n");
		uart.readline();
	}catch(serial::IOException& e){// uart 연결 실패시(누가 사용하는 경우 등);
		ROS_ERROR("Unable to port");
		return -1;
	}
	
	if(uart.isOpen()){// uart 연결 성공시;
		ROS_INFO("Serial Port initiaized");
	}else{
		return -1;
	}

	//ros node로부터 imu publisher 관리자 실행;
	ros::Publisher imu_pub = node.advertise<sensor_msgs::Imu>("sensors/imu",10);
	target_pose_pub = node.advertise<geometry_msgs::Pose>("target/pose", 1);
	euler_angle = node.advertise<geometry_msgs::Vector3>("target/euler/pose",10);
	euler_angle_error = node.advertise<geometry_msgs::Vector3>("target/euler/error",10);
	euler_angle_target = node.advertise<geometry_msgs::Vector3>("target/euler/target",10);
	//ros zro 서비스를 위한 srv 관리자 실행;
	ros::Subscriber target_pose_sub = node.subscribe("target/pose", 10, target_pose_update_callback);
	//ros::Subscriber sensor_pose_sub = node.subscribe("sensors/imu", 10, sensor_pose_update_callback);
	ros::Publisher target_poserror_pub = node.advertise<geometry_msgs::Pose>("target/error", 10);
	ros::Publisher target_pose_pub = node.advertise<geometry_msgs::Pose>("target/pose", 10);
	ros::Publisher fin_pose_pub = node.advertise<geometry_msgs::Pose>("target/fins", 10);
	ros::ServiceServer zro_srv = node.advertiseService("target/srv/zro", zro_callback);	
	ros::ServiceServer start_srv = node.advertiseService("target/srv/start", start_callback);	
	ros::ServiceServer energize_srv = node.advertiseService("target/srv/energize", energize_callback);	
	//launch trigger 구독
	ros::Subscriber launch_trigger = node.subscribe("/launch_trigger", 1, launch_callback);
	

	target.pose.orientation.x = 0;
	target.pose.orientation.y = 0;
	target.pose.orientation.z = 0;
	target.pose.orientation.w = 1;
	target.pose.position.x = 0;
	target.pose.position.y = 0;
	target.pose.position.z = 0;
	target_pose_pub.publish(target.pose);


	sensor.zro.orientation.x = 0;
	sensor.zro.orientation.y = 0;
	sensor.zro.orientation.z = 0;
	sensor.zro.orientation.w = 1;
	sensor.zro.position.x = ADJUST_ROLL_DEG * M_PI/180.0;
	sensor.zro.position.y = ADJUST_PITCH_DEG * M_PI/180.0;
	sensor.zro.position.z = ADJUST_YAW_DEG * M_PI/180.0;

	sensor.air.size.x =AIRSPEED;//m/s
	sensor.air.size.y =0;
	sensor.air.size.z =0;

	Fin fins[4] = {"00390833\0","00390839\0","00390840\0","00339447\0"};
	fins[1].adjust_angle *=2;

	PID pid[3] = {
			{	
				controller.k[0][0],	       
				controller.k[0][1],
				controller.k[0][2]
			},
			{	
				controller.k[1][0],	       
				controller.k[1][1],
				controller.k[1][2]
			},
			{	
				controller.k[2][0],	       
				controller.k[2][1],
				controller.k[2][2]
			},
			{	
				controller.k[3][0],	       
				controller.k[3][1],
				controller.k[3][2]
			},
			{	
				controller.k[4][0],	       
				controller.k[4][1],
				controller.k[4][2]
			},
			{	
				controller.k[5][0],	       
				controller.k[5][1],
				controller.k[5][2]
			}
	};

	ros::Rate loop_rate(20);
	//Running code
	while(ros::ok()){
		//Get ros event
		ros::spinOnce();
		update();
		double angle_x, angle_y, angle_z;
		double r,p,y;
		int data_ready = 0;
		double dt;
		//Get sensor data from imu
		uart.write("acc\n");
		arg= uart.readline();
		//Get message and parsing
		std::string::difference_type length_data;
		length_data = std::count(arg.begin(), arg.end(), '.');//읽어들인 데이터 포멧 길이 계산;
		if(length_data==3 && arg.find("acc")!=std::string::npos){//읽어들인 데이터 포멧 프레임 확인;
			arg.erase(0,arg.find("=")+1);
			std::string::size_type sz = 0; // arg 파싱용 문자 길이 선언 및 초기화;
			//가속도계와 각속도계 파싱 저장;
			imu_msg.linear_acceleration.x = std::stod(arg.erase(0,sz), &sz)*GEE;
			imu_msg.linear_acceleration.y = std::stod(arg.erase(0,sz), &sz)*GEE;
			imu_msg.linear_acceleration.z = std::stod(arg.erase(0,sz), &sz)*GEE;
			data_ready++;
			uart.write("gyr\n");
			arg= uart.readline(); // '\n'문자 수신될 때까지 수신;
			length_data = std::count(arg.begin(), arg.end(), '.');//읽어들인 데이터 포멧 길이 계산;
		}
		if(length_data==3 && arg.find("gyr")!=std::string::npos){//읽어들인 데이터 포멧 프레임 확인;
			arg.erase(0,arg.find("=")+1);
			std::string::size_type sz = 0; // arg 파싱용 문자 길이 선언 및 초기화;
			//가속도계와 각속도계 파싱 저장;
			imu_msg.angular_velocity.x = std::stod(arg.erase(0,sz), &sz) * M_PI/180.0; 
			imu_msg.angular_velocity.y = std::stod(arg.erase(0,sz), &sz) * M_PI/180.0; 
			imu_msg.angular_velocity.z = std::stod(arg.erase(0,sz), &sz) * M_PI/180.0; 
			data_ready++;
			uart.write("ang\n");
			arg= uart.readline(); // '\n'문자 수신될 때까지 수신;
			length_data = std::count(arg.begin(), arg.end(), '.');//읽어들인 데이터 포멧 길이 계산;
		}

		imu_msg.header.stamp = ros::Time::now(); // 수신완료 시점 기준 시간 기록;
	
		if(length_data==3 && arg.find("ang")!=std::string::npos){//읽어들인 데이터 포멧 프레임 확인;
			arg.erase(0,arg.find("=")+1);
			std::string::size_type sz = 0; // arg 파싱용 문자 길이 선언 및 초기화;
			//오일러각 파싱;
			angle_x = std::stod(arg.erase(0,sz), &sz) * M_PI/180.0;//rad
			angle_y = std::stod(arg.erase(0,sz), &sz) * M_PI/180.0;
			angle_z = std::stod(arg.erase(0,sz), &sz) * M_PI/180.0;
			r = angle_x - sensor.zro.position.x;
			p = angle_y - sensor.zro.position.y;
		       	y = angle_z - sensor.zro.position.z;
			//쿼터니언 변환 및 저장;
			geometry_msgs::Vector3 euler_angle_msg;
			euler_angle_msg.x = r*180.0/M_PI;
			euler_angle_msg.y = p*180.0/M_PI;
			euler_angle_msg.z = y*180.0/M_PI;
			euler_angle.publish(euler_angle_msg);

			//E2Q;
			imu_msg.orientation.w = cos(y/2)*cos(p/2)*cos(r/2) + sin(y/2)*sin(p/2)*sin(r/2);
			imu_msg.orientation.x = cos(y/2)*cos(p/2)*sin(r/2) - sin(y/2)*sin(p/2)*cos(r/2);
			imu_msg.orientation.y = cos(y/2)*sin(p/2)*cos(r/2) + sin(y/2)*cos(p/2)*sin(r/2);
			imu_msg.orientation.z = sin(y/2)*cos(p/2)*cos(r/2) - cos(y/2)*sin(p/2)*sin(r/2);
			data_ready++;
		}
		if(data_ready==3){
			static ros::Time stamp;
			sensor_pose_update(imu_msg);
			imu_pub.publish(imu_msg);
			dt = imu_msg.header.stamp.toSec()-stamp.toSec();
			stamp =	imu_msg.header.stamp; 
		}
		else uart.flush();
		if(request_set_zro)	{
			request_set_zro = false;
			sensor.zro.position.x = angle_x;
			sensor.zro.position.y = angle_y;
			sensor.zro.position.z = angle_z;
			sensor.zro.orientation = E2Q(sensor.zro.position);
			uart.write("zro\n");
			uart.readline();
		}
		//End get data

		if(sensor.data_changed){
			//after pid requset set zro;
			if(target.request_set_zro){
				target.request_set_zro=false;
				for(int i=0; i<finangle.size(); i++){
					finangle[i] = 0;
					finangle[i] = 0;
				}
			}
			if(target.pid_rst_trigger){
				target.pid_rst_trigger = false;
				for(int i = 0; i < 3; i++){
					pd[i].rst();
					pi[i].rst();
					pid[i].rst();
					zndo[i] = 0;
				}
			}
			/*
			//Non linear observer distribution for future work

			std::vector<double> dist = {0, 0, 0};	
			std::vector<double> dist_c = {1, 1, 1};	
			std::vector<double> Ac = {0.5, 0.5, 0.5};	
			std::vector<double> nu = {10, 10, 10};	
			//r *= -1;
			//p *= -1;
			//y *= -1;
			
			//err.y 방향 맞는지 확인필요
			zndo[0] += z_ndodot(zndo[0], Ac[0], dist_c[0], nu[0], err.x, E_pid.x, sensor.body.Inerthia[0])*dt;
			zndo[1] += z_ndodot(zndo[1], Ac[1], dist_c[1], nu[1], err.y, E_pid.y, sensor.body.Inerthia[1])*dt;
			zndo[2] += z_ndodot(zndo[2], Ac[2], dist_c[2], nu[2], err.z, E_pid.z, sensor.body.Inerthia[2])*dt;
			dist[0] = zndo[0] + nu[0]*err.x;
			dist[1] = zndo[1] + nu[1]*err.y;
			dist[2] = zndo[2] + nu[2]*err.z;
			
			//for ndob enable
			dist[0] = dist[0]*dist_c[0];
			dist[1] = dist[1]*dist_c[1];
			dist[2] = dist[2]*dist_c[2];
			*/

			//Calculation of control input as angle. accel.
			geometry_msgs::Vector3 E_pid;
			E_pid.x = pid[3].run(target.poserror.orientation.x, sensor.imu.header.stamp);
			E_pid.y = pid[4].run(target.poserror.orientation.y, sensor.imu.header.stamp);
			E_pid.z = pid[5].run(target.poserror.orientation.z, sensor.imu.header.stamp);

			//Euler error for interface
			geometry_msgs::Vector3 err = Q2E(target.poserror.orientation);

			//Get wind_direction
			//get air direction from orientation and velocity vec;
			geometry_msgs::Quaternion w, y = Q_Inv(sensor.imu.orientation);
			//Fixed for experiment
			w.x = 0;
			w.y = 0;
			w.z = 0;
			w.w = 1;//방위각 기준
			//sensor.air.velocity = fixed for experiment;

			geometry_msgs::Vector3 wind = VQV(sensor.air.size, y);
			double w_n = sqrt(wind.x*wind.x + wind.y*wind.y + wind.z*wind.z);

			//Get Correction angle
			geometry_msgs::Vector3 angle = Q2E(Q_E(w,sensor.imu.orientation));


			//Calculation angle of attack of control wings
			double req_force[3];
			//M = rf, f = M/r. M = Ia
			req_force[0] = E_pid.x*sensor.body.Inerthia[0]/sensor.body.CG_D[0];
			req_force[1] = E_pid.y*sensor.body.Inerthia[1]/sensor.body.CG_D[1];
			req_force[2] = E_pid.z*sensor.body.Inerthia[2]/sensor.body.CG_D[2];
		
			req_force[1] /= cos(angle.y);
			req_force[2] /= cos(angle.z);

			//Merge wiht wind direction(angle + angle of attack).
			//roll rotate use 4 pin, pitch and yaw use 2 pin
			//change by coordinate
			finangle[0] =  angle.y + fins[0].get_angle_limited(req_force[0]/4 - req_force[1]/2);	//+Y
			finangle[1] =  angle.z + fins[1].get_angle_limited(req_force[0]/4 + req_force[2]/2);	//+Z
			finangle[2] = -angle.y + fins[2].get_angle_limited(req_force[0]/4 + req_force[1]/2);	//-Y
			finangle[3] = -angle.z + fins[3].get_angle_limited(req_force[0]/4 - req_force[2]/2);	//-Z
			
			//Update for interface
			geometry_msgs::Pose finspose;
			finspose.orientation.x = finangle[0];
			finspose.orientation.y = finangle[1];
			finspose.orientation.z = finangle[2];
			finspose.orientation.w = finangle[3];
			
			//Data publish to ROS message network
			target.poserror.position.x = RAD2DEG(err.x);
			target.poserror.position.y = RAD2DEG(err.y);
			target.poserror.position.z = RAD2DEG(err.z);
			target_poserror_pub.publish(target.poserror);
			target_poserror_pub.publish(target.poserror);
			fin_pose_pub.publish(finspose);
		}

		//safty functions
		if(target.request_toggle_energize[0] || target.request_toggle_energize[1]){
		       	for(int i=0; i<finangle.size(); i++){
				if(target.request_toggle_energize[0]){
					fins[i].energize(false);
				}else{
					fins[i].energize(true);
				}
			}
			target.request_toggle_energize[0] = false;
			target.request_toggle_energize[1] = false;
		}
		if(target.request_set_start){
			for(int i=0; i<finangle.size(); i++){
				fins[i].set_angle(finangle[i]);
			}
		}else{
			fins[0].set_angle(M_PI/2);
			fins[1].set_angle(0);
			fins[2].set_angle(-M_PI/2);
			fins[3].set_angle(0);
		}
		loop_rate.sleep();
	}
	for(int i=0; i<finangle.size(); i++){
		fins[i].energize(false);
	}
	return 0;

}



