#include "ros/ros.h"
#include "std_msgs/Int32.h"

void callback(const std_msgs::Int32 &msg)
{
	ROS_INFO("I Heard [%d]", msg.data);
}

int main(int argc, char ** argv)
{
	ros::init(argc, argv, "subscriber_node");
	ros::NodeHandle n;
	ros::Subscriber sub = n.subscribe("message",1000,callback);

	ros::spin();

	
}