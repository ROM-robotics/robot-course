#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>

int main(int argc, char ** argv)
{
	ros::init(argc,argv, "publisher_node");
	ros::NodeHandle n;
	ros::Publisher pub = n.advertise<std_msgs::String>("message",1000);

	ros::Rate r (10);

	while(ros::ok())
	{
		std_msgs::String msg;
		std::stringstream ss;
		ss<<"I am Publisher node !";
		msg.data=ss.str();

		ROS_INFO("i sent %s", msg.data.c_str());
		pub.publish(msg);

		ros::spinOnce();
		r.sleep();

	}
	return 0;
}