#include <ros/ros.h>
#include <ros/time.h>
#include <tf/tf.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/String.h>
#include <math.h>
#include <stdio.h>

using namespace std;

void Shutdown();
float normalize_angle(float angle);

int main(int argc,char** argv)
{
	ros::init(argc,argv,"odom_out_and_back");
	ros::NodeHandle n;
	ros::Publisher cmd_vel=n.advertise<geometry_msgs::Twist>("cmd_vel",10);

	int rate=10;
	float linear_speed=0.2;
	float goal_distance=1.0;
	float angular_speed=0.5;
	float angular_tolarance=0.0175; //rad for 1 degree
	float goal_angle=1.5708;  //90 degree
	ros::Rate r(rate);

	tf::TransformListener tf_listener;
	tf::StampedTransform transform;

	//Give tf some time to fill its buffer
	ros::Duration(2).sleep();

	string odom_frame="odom";
	string base_frame;

	
	try
	{
		tf_listener.waitForTransform(odom_frame,"base_link",ros::Time(),ros::Duration(1.0));
		base_frame="base_link";
	}
	catch(tf::LookupException ex)
	{
		ROS_INFO("cannot find transform between /odom and /base_link or /base_footprint");
	}

	for(int i=0;i<4;i++)
	{
		geometry_msgs::Twist move_cmd;
		move_cmd.linear.x=linear_speed;
		move_cmd.angular.z=0.0;
		try
		{
			tf_listener.lookupTransform(odom_frame,base_frame,ros::Time(0),transform);
		}
		catch(tf::TransformException ex)
		{
			ROS_ERROR("%s",ex.what());
			ros::Duration(1.0).sleep();
		}
		
		float x_start=transform.getOrigin().x();
		float y_start=transform.getOrigin().y();
		float distance=0;
		while(distance < goal_distance)
		{
			cmd_vel.publish(move_cmd);
			r.sleep();
			try
			{
				tf_listener.lookupTransform(odom_frame,base_frame,ros::Time(0),transform);
			}
			catch(tf::TransformException ex)
			{
				ROS_ERROR("%s",ex.what());
				ros::Duration(1.0).sleep();
			}
			distance=sqrt(pow(transform.getOrigin().x()-x_start,2)+
						  pow(transform.getOrigin().y()-y_start,2));
		}
		

		cmd_vel.publish(geometry_msgs::Twist());
		ros::Duration(1.0).sleep();

		move_cmd.linear.x=0.0;
		move_cmd.angular.z=angular_speed;
		tf::Matrix3x3 m(transform.getRotation());
		double roll,pitch,yaw;
		m.getRPY(roll,pitch,yaw);
		double last_angle=yaw;
		double turn_angle=0;
		while(abs(turn_angle+angular_tolarance) < abs(goal_angle))
		{
			cmd_vel.publish(move_cmd);
			r.sleep();
			try
			{
				tf_listener.lookupTransform(odom_frame,base_frame,ros::Time(0),transform);
			}
			catch(tf::TransformException ex)
			{
				ROS_ERROR("%s",ex.what());
				ros::Duration(1.0).sleep();
			}
			tf::Matrix3x3 m(transform.getRotation());
			m.getRPY(roll,pitch,yaw);
			double rotation=yaw;
			double delta_angle=normalize_angle(rotation - last_angle);
			turn_angle += delta_angle;
			last_angle = rotation;
		}

		cmd_vel.publish(geometry_msgs::Twist());
		ros::Duration(1.0).sleep();
	}

	cmd_vel.publish(geometry_msgs::Twist());
	ros::Duration(1.0).sleep();
}

float normalize_angle(float angle)
{
	float res=angle;
	while(res > 3.1416)
	{
		res -= 2.0 * 3.1416;
	}

	while(res < -3.1416)
	{
		res += 2.0 * 3.1416;
	}
	return res;
}
