#include <ros/ros.h>
#include <sample_class/ros_class.h>

int main(int argc,char** argv)
{
	ros::init(argc,argv,"tester_01");
	ros::NodeHandle nh;

	RosClass rc(&nh);
	ros::spin();
	return 0;
}

// Do some implement