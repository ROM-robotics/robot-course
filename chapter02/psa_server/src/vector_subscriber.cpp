#include <ros/ros.h>
#include "psa_server/vec.h"

void callback(const psa_server::vec &msg)
{
	std::vector <double> vec_of_doubles = msg.x;
	int nvals = vec_of_doubles.size();
	for (int i=0; i<nvals; i++){

		ROS_INFO("vec [%d] = %f",i, vec_of_doubles[i]);
	}
	ROS_INFO("\n");
}
int main(int argc, char ** argv)
{
	ros::init(argc, argv, "vector_subscriber");
	ros::NodeHandle n;
	ros::Subscriber my_subscriber_object = n.subscribe("vec_topic",1,callback);

	ros::spin();
	return 0;
	
}