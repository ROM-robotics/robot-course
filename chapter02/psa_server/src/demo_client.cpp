#include <ros/ros.h>
#include <iostream>
#include <actionlib/client/simple_action_client.h>
#include <psa_server/demoAction.h>
#include <actionlib/client/terminal_state.h>

int main(int argc,char** argv)
{
	ros::init(argc,argv,"demo_client");
	if(argc != 3)
	{
		ROS_WARN("Usage: rosrun psa_server demo_client <goal> <time_to_preempt>");
		return -1;
	}
	actionlib::SimpleActionClient<psa_server::demoAction> ac("demo_action",true);

	ROS_INFO("Waiting for action server ...");

	ac.waitForServer();
	psa_server::demoGoal goal;
	goal.count=atoi(argv[1]);

	ROS_INFO("Sending goal %d and preempt time of %d",goal.count,atoi(argv[2]) );
	
	ac.sendGoal(goal);

	bool status = ac.waitForResult(ros::Duration(atoi(argv[2])));
	ac.cancelGoal();

	if(status)
	{
		actionlib::SimpleClientGoalState state = ac.getState();
		ROS_INFO("Action finished %s",state.toString().c_str());
		ac.cancelGoal();
	}
	else{
		ROS_INFO("Action did not finish before the time out");
	}

}
