#include "ros/ros.h"
#include "psa_server/ghost.h"


int main(int argc, char ** argv)
{
	ros::init(argc,argv, "publisher_custom_msg_node");
	ros::NodeHandle n;
	ros::Publisher pub = n.advertise<psa_server::ghost>("int_message",1000);

	ros::Rate r (10);

	while(ros::ok())
	{
		psa_server::ghost msg;

		msg.A = 4;
		msg.B = 7;
		msg.C = 9;
		pub.publish(msg);

		ros::spinOnce();
		r.sleep();

	}
	return 0;
}