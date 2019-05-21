#!/usr/bin/env python

import rospy
from std_msgs.msg import String
from geometry_msgs.msg import Twist

class Forward():
	def __init__(self):
		rospy.init_node('forward',anonymous=True)
		self.pub=rospy.Publisher('cmd_vel',Twist,queue_size=10)
		rate=10
		r=rospy.Rate(rate)

		linear_velocity=0.2
		goal_distance=1
		time_duration=goal_distance/linear_velocity

		move_cmd=Twist()
		move_cmd.linear.x=linear_velocity
		ticks=int(rate*time_duration)
		for t in range(ticks):
			self.pub.publish(move_cmd)
			r.sleep()

		move_cmd=Twist()
		self.pub.publish(move_cmd)
		rospy.sleep(1)

if __name__=='__main__':
	try:
		Forward()
	except rospy.ROSInterruptException:
		rospy.loginfo("shutdown")