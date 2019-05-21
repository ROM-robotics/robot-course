#!/usr/bin/env python

import rospy
import tf
from nav_msgs.msg import Odometry
from geometry_msgs.msg import Point, Pose, Quaternion, Twist, Vector3, TransformStamped

import math
from math import sin, cos, pi

class odomPub():
	def __init__(self):
		self.x=0.0
		self.y=0.0
		self.th=0.0
		self.vx=0.0
		self.vy=0.0
		self.vth=0.0
		rospy.init_node('myrobot1_odom',anonymous=True)
		self.sub=rospy.Subscriber('cmd_vel',Twist,self.callback)
		self.odom_publisher	=rospy.Publisher('odom',Odometry,queue_size=50)
		self.odom_broadcaster=tf.TransformBroadcaster()


		current_time=rospy.Time.now()
		last_time	=rospy.Time.now()

		rate=10
		r=rospy.Rate(rate)

		while not rospy.is_shutdown():
			current_time=rospy.Time.now()
			dt=(current_time - last_time).to_sec()
			delta_x=(self.vx * cos(self.th) - self.vy * sin(self.th)) * dt
			delta_y=(self.vx * sin(self.th) + self.vy * cos(self.th)) * dt
			delta_th=self.vth * dt

			self.x += delta_x
			self.y += delta_y
			self.th+= delta_th

			odom_quat=tf.transformations.quaternion_from_euler(0,0,self.th)

			self.odom_broadcaster.sendTransform(
				(self.x , self.y, 0.),
				odom_quat,
				current_time,
				"base_link",
				"odom"
			)

			odom=Odometry()
			odom.header.stamp=current_time
			odom.header.frame_id="odom"

			#set the position
			odom.pose.pose=Pose(Point(self.x, self.y, 0.0), Quaternion(*odom_quat))

			#set the velocity
			odom.child_frame_id="base_link"
			odom.twist.twist=Twist(Vector3(self.vx, self.vy, 0.0), Vector3(0, 0, self.vth))

			#publish the message
			self.odom_publisher.publish(odom)

			last_time=current_time
			r.sleep()

	def callback(self,data):
		self.vx=data.linear.x
		self.vy=data.linear.y
		self.vth=data.angular.z


if __name__=='__main__':
	try:
		odomPub()
	except rospy.ROSInterruptException:
		pass