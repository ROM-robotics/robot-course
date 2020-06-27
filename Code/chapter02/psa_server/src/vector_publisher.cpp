 #include <ros/ros.h>
#include "psa_server/vec.h"

int main(int argc, char ** argv)
{
	ros::init(argc,argv, "vector_publisher");
	ros::NodeHandle n;
	ros::Publisher my_publisher_object = n.advertise<psa_server::vec>("vec_topic",1);

	psa_server::vec vec_msg;
	double counter=0;
	ros::Rate naptime(1.0);

	vec_msg.x.resize(3);

	vec_msg.x[0]=1.414;
	vec_msg.x[1]=2.71828;
	vec_msg.x[2]=3.1416;

	vec_msg.x.push_back(counter);
	while(ros::ok()){
		counter+=1.0;
		my_publisher_object.publish(vec_msg);
		naptime.sleep();
	}
}	