#!/usr/bin/env python

import rospy
import actionlib

from psa_server.msg import demoAction, demoGoal

if __name__ == '__main__':
	rospy.init_node('demo_client')
	client = actionlib.SimpleActionClient('demo_action', demoAction)
	client.wait_for_server()

	goal = demoGoal()

	goal.count = 1000

	client.send_goal(goal)
	client.wait_for_result(rospy.Duration.from_sec(50.0))