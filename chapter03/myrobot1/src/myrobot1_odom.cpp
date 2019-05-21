#include <ros/ros.h>
#include <ros/time.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/Vector3.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>

float vx=0.0;
float vy=0.0;
float vth=0.0;
float x=0.0;
float y=0.0;
float th=0.0;

void vel_callback(const geometry_msgs::Twist& vel)
{
	//geometry_msgs::Vector3 linear=vel.linear;
	//geometry_msgs::Vector3 angular=vel.angular;
	vx=float(vel.linear.x);
	vy=float(vel.linear.y);
	vth=float(vel.angular.z);
}

int main(int argc, char** argv)
{
	ros::init(argc,argv,"myrobot1_odom");
	ros::NodeHandle n;
	ros::Subscriber sub=n.subscribe("cmd_vel",50,vel_callback);
	ros::Publisher odom_publisher=n.advertise<nav_msgs::Odometry>("odom",50);
	tf::TransformBroadcaster odom_broadcaster;
	ros::Time current_time,last_time;
	current_time=ros::Time::now();
	ros::Rate r(100);
	
	while(n.ok())
	{
		ros::spinOnce();
		current_time=ros::Time::now();
		float dt=(current_time-last_time).toSec();
		float delta_x=(vx*cos(th)-vy*sin(th))*dt;
		float delta_y=(vx*sin(th)+vy*cos(th))*dt;
		float delta_th=vth*dt;
		x+=delta_x;
		y+=delta_y;
		th+=delta_th;
		geometry_msgs::Quaternion odom_quat=tf::createQuaternionMsgFromYaw(th);

		geometry_msgs::TransformStamped odom_trans;
		odom_trans.header.stamp=current_time;
		odom_trans.header.frame_id="odom";
		odom_trans.child_frame_id="base_link";

		odom_trans.transform.translation.x=x;
		odom_trans.transform.translation.y=y;
		odom_trans.transform.translation.z=0.0;
		odom_trans.transform.rotation=odom_quat;

		odom_broadcaster.sendTransform(odom_trans);

		nav_msgs::Odometry odom;
		odom.header.stamp=current_time;
		odom.header.frame_id="odom";

		odom.pose.pose.position.x=x;
		odom.pose.pose.position.y=y;
		odom.pose.pose.position.z=0.0;
		odom.pose.pose.orientation=odom_quat;

		odom.child_frame_id="base_link";
		odom.twist.twist.linear.x=vx;
		odom.twist.twist.linear.y=vy;
		odom.twist.twist.angular.z=vth;

		odom_publisher.publish(odom);
		last_time=current_time;
		r.sleep();
	}	

}