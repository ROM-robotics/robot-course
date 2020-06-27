#include <ros/ros.h>
#include "ros_class.h"

int main(int argc,char** argv)
{
	ros::init(argc,argv, "ros_class_example");
	ros::NodeHandle nh;

	RosClass rc(&nh);
	ros::spin();
	return 0;
};

RosClass::RosClass(ros::NodeHandle* nodeHandle) : nh_(*nodeHandle)
{
	init_publisher();
	init_subscriber();
	init_server();
}
void RosClass::init_publisher()
{
	pub_ = nh_.advertise<std_msgs::Float32>("publisher_1",1,true);
}
void RosClass::init_subscriber()
{
	sub_ = nh_.subscribe("subscriber_1",1,&RosClass::sub_callback,this);
}
void RosClass::init_server()
{
	server_ = nh_.advertiseService("server_1",&RosClass::service_callback,this);
}
void RosClass::sub_callback(const std_msgs::Float32& msg)
{
	ROS_INFO_STREAM("I got "<< msg.data << ".");
	std_msgs::Float32 output_msg;
	output_msg.data = msg.data;
	pub_.publish(output_msg);
}
bool RosClass::service_callback(std_srvs::TriggerRequest& req,std_srvs::TriggerResponse& res)
{
	ROS_INFO_STREAM("Server is running");
}