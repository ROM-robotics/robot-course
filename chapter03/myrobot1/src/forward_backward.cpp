#include <ros/ros.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Twist.h>
#define pi 3.147

int main(int argc, char** argv)
{
	ros::init(argc,argv,"forward_backward");

	ros::NodeHandle n;
	ros::Publisher pub=n.advertise<geometry_msgs::Twist>("cmd_vel",10);

	int rate=10;
	float linear_velocity=0.2;
	float goal_distance=1.0;
	float linear_time_duration;
	float angular_velocity=0.2;
	float goal_angle=pi;
	float angular_time_duration;
	int ticks;

	linear_time_duration=goal_distance/linear_velocity;
	angular_time_duration=goal_angle/angular_velocity;

	geometry_msgs::Twist move_cmd;

	ros::Rate r(rate);

	for(int i=0;i<2;i++)
	{
		ticks=rate*linear_time_duration;
		move_cmd.linear.x=linear_velocity;
		move_cmd.angular.z=0;

		for(int i=0;i<ticks;i++)
		{
			pub.publish(move_cmd);
			r.sleep();
		}

		move_cmd.linear.x=0.0;
		move_cmd.angular.z=0.0;
		pub.publish(move_cmd);
		ros::Duration(1).sleep();
	
		ticks=rate*angular_time_duration;
		move_cmd.linear.x=0.0;
		move_cmd.angular.z=angular_velocity;

		for(int i=0;i<ticks;i++)
		{
			pub.publish(move_cmd);
			r.sleep();
		}

		move_cmd.linear.x=0.0;
		move_cmd.angular.z=0.0;
		pub.publish(move_cmd);
		ros::Duration(1).sleep();
	}
}