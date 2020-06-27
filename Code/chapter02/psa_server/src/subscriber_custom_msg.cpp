#include "ros/ros.h"
#include "psa_server/ghost.h"

void callback(const psa_server::ghost::ConstPtr &msg)
{
	ROS_INFO("I Heard [%d],[%d], [%d]", (int)msg->A, (int)msg->B, (int)msg->C);
}

int main(int argc, char ** argv)
{
	ros::init(argc, argv, "subscriber_custom_msg_node");
	ros::NodeHandle n;
	ros::Subscriber sub = n.subscribe("int_message",1000,callback);

	ros::spin();

	
}