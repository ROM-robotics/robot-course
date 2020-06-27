#include <ros/ros.h> 
#include <visualization_msgs/Marker.h> // need this for publishing markers
#include <geometry_msgs/Point.h> //data type used for markers
#include <string.h>
#include <stdio.h>  
#include <example_rviz_marker/SimpleFloatSrvMsg.h> //a custom message type defined in this package
using namespace std;

//set these two values by service callback, make available to "main"
double g_z_height = 0.0;
bool g_trigger = true;

//a service to prompt a new display computation.
// E.g., to construct a plane at height z=1.0, trigger with: 
// rosservice call rviz_marker_svc 1.0

bool displaySvcCB(example_rviz_marker::SimpleFloatSrvMsgRequest& request,
	example_rviz_marker::SimpleFloatSrvMsgResponse& response) {
    g_z_height = request.request_float32;
    ROS_INFO("example_rviz_marker: received request for height %f", g_z_height);
    g_trigger = true; // inform "main" a new computation is desired
    response.resp=true;
    return true;
}

void init_marker_vals(visualization_msgs::Marker &marker) {
    marker.header.frame_id = "/world"; // reference frame for marker coords
    marker.header.stamp = ros::Time();
    marker.ns = "my_namespace";
    marker.id = 0;
    // use SPHERE if you only want a single marker
    // use SPHERE_LIST for a group of markers
    marker.type = visualization_msgs::Marker::SPHERE_LIST; //SPHERE;
    marker.action = visualization_msgs::Marker::ADD;
    // if just using a single marker, specify the coordinates here, like this:

    //marker.pose.position.x = 0.4;  
    //marker.pose.position.y = -0.4;
    //marker.pose.position.z = 0;
    //ROS_INFO("x,y,z = %f %f, %f",marker.pose.position.x,marker.pose.position.y,   				    
    //        marker.pose.position.z);    
    // otherwise, for a list of markers, put their coordinates in the "points" array, as below

    //whether a single marker or list of markers, need to specify marker properties
    // these will all be the same for SPHERE_LIST
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;
    marker.scale.x = 0.01;
    marker.scale.y = 0.01;
    marker.scale.z = 0.01;

    marker.color.a = 1.0;
         
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "example_rviz_marker");
    ros::NodeHandle nh;
    ros::Publisher r_pub = nh.advertise<visualization_msgs::Marker>("r_topic", 0);
    ros::Publisher g_pub = nh.advertise<visualization_msgs::Marker>("g_topic", 0);
    ros::Publisher b_pub = nh.advertise<visualization_msgs::Marker>("b_topic", 0);
    ros::Publisher t_pub = nh.advertise<visualization_msgs::Marker>("t_topic", 0);
    visualization_msgs::Marker r_marker; // instantiate a marker object
    visualization_msgs::Marker g_marker;
    visualization_msgs::Marker b_marker;

    
    double iteration = 0.0;
    visualization_msgs::Marker text_marker;
    text_marker.header.frame_id = "/world";
    text_marker.header.stamp = ros::Time::now();
    text_marker.ns = "basic_shapes";
    text_marker.id = iteration;
    text_marker.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
    text_marker.action = visualization_msgs::Marker::ADD;

    text_marker.pose.position.x = 0.0 + iteration;
    text_marker.pose.position.y = 0.0;
    text_marker.pose.position.z = 1.7;
    text_marker.pose.orientation.x = 0.0;
    text_marker.pose.orientation.y = 0.0;
    text_marker.pose.orientation.z = 0.0;
    text_marker.pose.orientation.w = 1.0;

    text_marker.text = "ROS MYANMAR";

    text_marker.scale.x = 0.3;
    text_marker.scale.y = 0.3;
    text_marker.scale.z = 0.1;

    text_marker.color.r = 0.0f;
    text_marker.color.g = 0.5f;
    text_marker.color.b = 0.5f;
    text_marker.color.a = 1.0;
    

    geometry_msgs::Point point; // points will be used to specify where the markers go
    
    //set up a service to compute marker locations on request
    ros::ServiceServer service = nh.advertiseService("rviz_marker_svc", displaySvcCB);

    init_marker_vals(r_marker);
    g_marker = r_marker;
    b_marker = r_marker;

    r_marker.color.r = 1.0;
    r_marker.color.g = 0.0;
    r_marker.color.b = 0.0;

    g_marker.color.r = 0.0;
    g_marker.color.g = 1.0;
    g_marker.color.b = 0.0;

    b_marker.color.r = 1.0;
    b_marker.color.g = 1.0;
    b_marker.color.b = 0.0;
    //init_marker_vals(g_marker);
    //init_marker_vals(b_marker);
    
    double z_des;

    // build a wall of markers; set range and resolution
    double x_min = -1.5;
    double x_max = 1.5;
    double y_min = 0.0;
    double y_max = 0.3;
    double dx_des = 0.04;
    double dy_des = 0.04;
    double dz_des = 0.04;

    while (ros::ok()) {
        if (g_trigger) {  // did service get request for a new computation?
            g_trigger = false; //reset the trigger from service
            z_des = g_z_height; //use z-value from service callback
            double z_min = z_des;
            double z_max = z_min + 0.5;
            ROS_INFO("constructing plane of markers at height %f",z_des);
    	    r_marker.header.stamp = ros::Time();
    	    g_marker.header.stamp = ros::Time();
    	    b_marker.header.stamp = ros::Time();
            r_marker.points.clear(); // clear out this vector
            g_marker.points.clear();
            b_marker.points.clear();
            	
			    

                for(double x=0.0;x<3;x+=0.04){
	        		for(double y=0.0;y<0.3;y+=0.04){
	        			for(double z=0.0;z<0.5;z+=0.04){
	        				point.x = x;
	        				point.y = y;
	        				point.z = z;
	        				r_marker.points.push_back(point);
	        			}
	        		}
	        	}  
                for(double x=0.0;x<3;x+=0.04){
                    for(double y=0.0;y<0.3;y+=0.04){
                        for(double z=0.5;z<1.0;z+=0.04){
                            point.x = x;
                            point.y = y;
                            point.z = z;
                            g_marker.points.push_back(point);
                        }
                    }
                }
                for(double x=0.0;x<3;x+=0.04){
                    for(double y=0.0;y<0.3;y+=0.04){
                        for(double z=1.0;z<1.5;z+=0.04){
                            point.x = x;
                            point.y = y;
                            point.z = z;
                            b_marker.points.push_back(point);
                        }
                    }
                }		

            
        }
     ros::Duration(0.1).sleep();
    //ROS_INFO("publishing...");
    r_pub.publish(r_marker);
    

    g_pub.publish(g_marker);
    

    b_pub.publish(b_marker);

    t_pub.publish(text_marker);

    ros::spinOnce();       
    }
    return 0;
}



