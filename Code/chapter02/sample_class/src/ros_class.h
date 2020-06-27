#ifndef ROS_CLASS_H
#define ROS_CLASS_H

#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Float32.h>
#include <std_srvs/Trigger.h>

class RosClass
{
public:
	RosClass(ros::NodeHandle* nodeHandle);
private:
	ros::NodeHandle nh_;
	ros::Publisher pub_;
	ros::Subscriber sub_;
	ros::ServiceServer server_;
	

	void init_subscriber();
	void init_publisher();
	void init_server();

	// callbacks
	void sub_callback(const std_msgs::Float32& msg);
	bool service_callback(std_srvs::TriggerRequest& req,std_srvs::TriggerResponse& res);
};
#endif