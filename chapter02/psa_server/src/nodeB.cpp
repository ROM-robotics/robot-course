#include "ros/ros.h"
#include "psa_server/ghostsrv.h"

int main(int argc, char ** argv)
{
	ros::init(argc,argv, "add_intenger_client");
	ros::NodeHandle nh();
	ros::ServiceClient client = nh.serviceClient<psa_server::ghostsrv> ("add_3_ints");

	psa_server::ghostsrv srv;
	srv.request.A = 1;
	srv.request.B = 2;
	srv.request.C = 3;

	if (client.call(srv))
	{
		ROS_INFO("Sum: %d", (int)srv.response.sum);
	}	
	else
	{
		ROS_INFO("Fail to call service add_3_ints");
		return 1;
	}	

	return 0;

}	