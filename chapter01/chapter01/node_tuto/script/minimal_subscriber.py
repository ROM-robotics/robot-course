#!/usr/bin/env python
import rospy
from std_msgs.msg import Float64

def callback(data):
	rospy.loginfo("I receive : %f",data,data)

def listener():
	rospy.init_node("minimal_subscriber")
	rospy.Subscriber("topic1", Float64, callback)
	rospy.spin()