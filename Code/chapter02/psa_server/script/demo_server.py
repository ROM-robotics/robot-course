#!/usr/bin/env python

import rospy
import actionlib

from psa_server.msg import demoAction

class DemoServer:
	def __init__(self):
		self.server = actionlib.SimpleActionServer('demo_action', demoAction,self.execute,False)
		self.server.start()

	def execute(self, goal):
		rospy.loginfo("I got %d",goal.count)
		self.server.set_succeeded()

if __name__ == '__main__':
	rospy.init_node('demo_server')
	server = DemoServer()
	rospy.spin()