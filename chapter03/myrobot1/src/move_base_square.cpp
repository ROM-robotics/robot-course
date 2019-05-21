#include <ros/ros.h>
#include <std_msgs/String.h>
#include <actionlib_msgs/GoalID.h>
#include <actionlib_msgs/GoalStatus.h>
#include <actionlib_msgs/GoalStatusArray.h>
#include <actionlib/client/simple_action_client.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/Twist.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <move_base_msgs/MoveBaseGoal.h>
#include <visualization_msgs/Marker.h>
#include <math.h>
#include <stdio.h>

#define pi 3.1417

using namespace std;

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> move_base;

static geometry_msgs::Quaternion createQuaternionFromRPY(double roll, double pitch, double yaw);

int main(int argc,char** argv)
{
	ros::init(argc,argv,"nav_test");
	ros::NodeHandle n;
	int rate=10;
	double square_size=1.0;
	n.getParam("square_size",square_size);

	geometry_msgs::Quaternion quaternions[4];
	double euler_angles[4]={pi/2,pi,3*pi/2,0};

	for(int i=0;i<4;i++)
	{
		quaternions[i]=createQuaternionFromRPY(0,0,euler_angles[i]);
	}

	geometry_msgs::Pose waypoints[4];

	waypoints[0].position.x=square_size;
	waypoints[0].position.y=0.0;
	waypoints[0].position.z=0.0;
	waypoints[0].orientation.x=quaternions[0].x;
	waypoints[0].orientation.y=quaternions[0].y;
	waypoints[0].orientation.z=quaternions[0].z;
	waypoints[0].orientation.w=quaternions[0].w;

	waypoints[1].position.x=square_size;
	waypoints[1].position.y=square_size;
	waypoints[1].position.z=0.0;
	waypoints[1].orientation.x=quaternions[1].x;
	waypoints[1].orientation.y=quaternions[1].y;
	waypoints[1].orientation.z=quaternions[1].z;
	waypoints[1].orientation.w=quaternions[1].w;

	waypoints[2].position.x=0.0;
	waypoints[2].position.y=square_size;
	waypoints[2].position.z=0.0;
	waypoints[2].orientation.x=quaternions[2].x;
	waypoints[2].orientation.y=quaternions[2].y;
	waypoints[2].orientation.z=quaternions[2].z;
	waypoints[2].orientation.w=quaternions[2].w;

	waypoints[3].position.x=0.0;
	waypoints[3].position.y=0.0;
	waypoints[3].position.z=0.0;
	waypoints[3].orientation.x=quaternions[3].x;
	waypoints[3].orientation.y=quaternions[3].y;
	waypoints[3].orientation.z=quaternions[3].z;
	waypoints[3].orientation.w=quaternions[3].w;
	ROS_INFO("Testing..Server");

	visualization_msgs::Marker markers;
	markers.header.frame_id="odom";
	markers.header.stamp=ros::Time();
	markers.ns="waypoints";
	markers.id=0;
	markers.type=visualization_msgs::Marker::CUBE_LIST;
	markers.action=visualization_msgs::Marker::ADD;
	markers.scale.x=0.2;
	markers.scale.y=0.2;
	markers.color.r=1.0;
	markers.color.g=0.7;
	markers.color.b=1.0;
	markers.color.a=1.0;
	markers.points.resize(4);  //resize function is important. for memory core damped

	for(int i=0;i<4;i++)
	{
		markers.points[i]=waypoints[i].position;
	}
	ROS_INFO("Testing..Server1");
	
	ros::Publisher cmd_vel_pub=n.advertise<geometry_msgs::Twist>("cmd_vel",5);
	ros::Publisher marker_pub=n.advertise<visualization_msgs::Marker>("waypoint_markers",5);
	move_base move_base("move_base",true);

	ROS_INFO("Waiting for move_base action server...");

	move_base.waitForServer(ros::Duration(60));

	ROS_INFO("Connected to move base server");
	ROS_INFO("Starting navigation test");

	int i=0;
	while(i<4)
	{
		marker_pub.publish(markers);
		move_base_msgs::MoveBaseGoal goal;
		goal.target_pose.header.frame_id="map";
		goal.target_pose.header.stamp=ros::Time::now();
		goal.target_pose.pose=waypoints[i];
		
		move_base.sendGoal(goal);
		bool finished_within_time=move_base.waitForResult(ros::Duration(60));

		if(!finished_within_time)
		{
			move_base.cancelGoal();
			ROS_INFO("Time out achieving goal");
		}
		else
		{
			if(move_base.getState()==actionlib::SimpleClientGoalState::SUCCEEDED)
			{
				ROS_INFO("Goal succeeded!");
			}
		}

		i+=1;
	}
	/*
	*/
	//ros::shutdown();
}

static geometry_msgs::Quaternion createQuaternionFromRPY(double roll, double pitch, double yaw) 
{   
    geometry_msgs::Quaternion q;
    double t0 = cos(yaw * 0.5);
    double t1 = sin(yaw * 0.5);
    double t2 = cos(roll * 0.5);
    double t3 = sin(roll * 0.5);
    double t4 = cos(pitch * 0.5);
    double t5 = sin(pitch * 0.5);
    q.w = t0 * t2 * t4 + t1 * t3 * t5;
    q.x = t0 * t3 * t4 - t1 * t2 * t5;
    q.y = t0 * t2 * t5 + t1 * t3 * t4;
    q.z = t1 * t2 * t4 - t0 * t3 * t5;
    return q;
}
