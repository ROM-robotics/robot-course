#!/usr/bin/env python

import rospy
from std_msgs.msg import String

def talker():
	pub = rospy.Publisher('chatter', String,queue_size=10)
	rospy.init_node('talker', anonymous=True)

	rate = rospy.Rate(10)
	msg = String()
	while not rospy.is_shutdown():
		hello_str = "hello world %s" %rospy.get_time()
		rospy.loginfo(hello_str)
		msg.data = hello_str
		pub.publish(msg)
		rate.sleep()

if __name__ == '__main__':		
	try:
		talker()
	except rospy.ROSInterruptException :
		pass
	