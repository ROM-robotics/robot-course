#include "ros/ros.h"
#include "std_msgs/Int32.h"

int main(int argc, char ** argv)
{
	ros::init(argc,argv, "publisher_node");
	ros::NodeHandle n;
	ros::Publisher pub = n.advertise<std_msgs::Int32>("message",1000);

	ros::Rate r(10);
	
	std_msgs::Int32 msg;

	int x=0;

	while(ros::ok())
	{
		
		msg.data = x;

		ROS_INFO("i sent %d", msg.data);
		
		pub.publish(msg);
		x +=1;

		ros::spinOnce();
		r.sleep();

	}
	return 0;
}