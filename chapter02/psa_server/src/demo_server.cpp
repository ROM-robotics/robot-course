#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include <actionlib/server/simple_action_server.h>
#include "psa_server/demoAction.h"
#include <iostream>
#include <sstream>

class GhostMan{
protected:
	ros::NodeHandle nh;
	actionlib::SimpleActionServer<psa_server::demoAction> as;

	psa_server::demoFeedback feedback;
	psa_server::demoResult result;

	std::string action_name;
	int goal;
	int progress;
public:
	GhostMan(std::string name) : as(
		nh,
		name,
		boost::bind(&GhostMan::executeCB,this,_1),
		false),
	action_name(name)
	{
		as.registerPreemptCallback(boost::bind(&GhostMan::preemptCB,this));
		as.start();
	}

	void preemptCB()
	{
		ROS_WARN("%s got preempted!", action_name.c_str());
		result.final_count=progress;
		as.setPreempted(result,"I got Preempted");
	}
	void executeCB(const psa_server::demoGoalConstPtr &goal)
	{
		if(!as.isActive() || as.isPreemptRequested()) return;

		ros::Rate r(5);
		ROS_INFO("%s is processing the goal %d",action_name.c_str(),goal->count);

		for(progress =1;progress<=goal->count;progress++)
		{
			if(!ros::ok())
			{
				result.final_count = progress;
				as.setAborted(result,"I fail");
				ROS_INFO("%s shutting dodwn",action_name.c_str());
				break;
			}
			if(!as.isActive() || as.isPreemptRequested() ) return;

			if(goal->count<=progress)
			{
				result.final_count = progress;
				as.setSucceeded(result);

			}
			else{
				feedback.current_count = progress;
				as.publishFeedback(feedback);
			}
			r.sleep();
		}
	}

};


int main(int argc,char** argv)
{
	ros::init(argc,argv,"demo_server");
	ROS_INFO("Starting Action server");
	//GhostMan gm(ros::this_node::getName());
	GhostMan gm("demo_action");
	ros::spin();
	return 0;
}