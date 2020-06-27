#include <ros/ros.h>
#include <std_msgs/Float64.h>

void myCallback(const std_msgs::Float64& msg){

	ROS_INFO("Receive = %f ", msg.data);
}

int main (int argc,char**argv){

	ros::init(argc,argv, "minimal_subscriber");
	ros::NodeHandle n;

	ros::Subscriber sub = n.subscribe("topic1", 1,myCallback);

	ros::spin();
	return 0;
}