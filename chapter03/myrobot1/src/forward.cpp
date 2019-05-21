#include <ros/ros.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Twist.h>

int main(int argc, char** argv)
{
	ros::init(argc,argv,"forward");

	ros::NodeHandle n;
	ros::Publisher pub=n.advertise<geometry_msgs::Twist>("cmd_vel",10);

	int rate=10;
	float linear_velocity=0.2;
	float goal_distance=1.0;
	float time_duration;
	int ticks;
	
	time_duration=goal_distance/linear_velocity;
	ticks=rate*time_duration;

	geometry_msgs::Twist move_cmd;
	move_cmd.linear.x=linear_velocity;

	ros::Rate r(rate);

	for(int i=0;i<ticks;i++)
	{
		pub.publish(move_cmd);
		r.sleep();
	}

	move_cmd.linear.x=0.0;
	pub.publish(move_cmd);
	ros::Duration(1).sleep();
}