#!/usr/bin/env python
import rospy
from std_msgs.msg import Float64

rospy.init_node("min_pub")
pub = rospy.Publisher("topic1", Float64, queue_size=1)

rate = rospy.Rate(1)
msg = Float64()
msg.data = 0.0

while not rospy.is_shutdown():
	pub.publish(msg)
	msg.data = msg.data + 0.1
	rate.sleep()

	