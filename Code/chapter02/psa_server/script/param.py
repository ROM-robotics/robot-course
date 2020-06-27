
import rospy

global_name = rospy.get_param("/global_name")
relative_name = rospy.get_param("relative_name")
private_param = rospy.get_param('~private_name')
default_param = rospy.get_param('default_param' , 'default_value')

gains = rospy.get_param('gains')
p,i,d + gains['P'], gains[ ' I '], gains['D']


rospy.setParam('a_string','baz')
rospy.setParam('~private_int','2')
rospy.setParam('list_of _floats' , "[1., 2., 3., 4.,")
rospy.setParam('bool_True', True)
rospy.setParam('gains',"{p:1, i:2, d:3")

rospy.set_param_raw('a_string','baz')
rospy.set_param_raw('~private_int', 2)
rospy.set_param_raw('list_of_floats',[1., 2., 3., 4.,])
rospy.setParam('bool_True', True)
rospy.setParam('gains',"{p:1, i:2, d:3")

rospy.get_param('gains/P')

if rospy.has_param('to_delete'):
	rospy.delete_param('to_delete')