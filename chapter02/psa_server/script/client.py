#!/usr/bin/env python

import sys
from psa_server.srv import *
import rospy

def add_three_inits_client(x,y,z):
	rospy.wait_for_service('blabla')
	try:
		add_three_inits = rospy.ServiceProxy('blabla', ghostsrv)
		res = add_three_inits(x, y, z)
		return res.sum
	except rospy.ServiceException, e:
		print "Service call failed: %s" %e

def usuage():
	return "%s [x,y,z]" %sys.argv[0]

if __name__ == '__main__':
	if len(sys.argv) == 4:
		x = int (sys.argv[1])
		y = int (sys.argv[2])
		z = int (sys.argv[3])
	else:
		print usuage ()
		sys.exit(1)
	print "Requesting %s+%s+%s " %(x,y,z)
	print "%s+%s+%s=%s" %(x,y,z, add_three_inits_client(x,y,z))		
