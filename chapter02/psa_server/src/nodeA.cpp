#include "ros/ros.h"
#include "psa_server/ghostsrv.h"

bool add(psa_server::ghostsrv::Request &req,
		 psa_server::ghostsrv::Response &res)
{
	res.sum = req.A + req.B +req.C;
	ROS_INFO("SENT!");
	ROS_INFO("Sum is [%d]", (int)res.sum);

	return true;
}

int main(int argc, char ** argv)
{
	ros::init(argc,argv, "add_intenger_server");
	ros::NodeHandle nh;
	ros::ServiceServer service = nh.advertiseService ("add_3_ints",add);
	
	ROS_INFO("Ready to add!");
	ros::spin();
	

}	