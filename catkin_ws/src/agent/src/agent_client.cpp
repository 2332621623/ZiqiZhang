#include <ros/ros.h>
#include "agent/Agent.h"

int main(int argc, char** argv)
{
	ros::init(argc, argv, "agent_client");

	ros::NodeHandle node;

	ros::service::waitForService("/agent_feedback");
	ros::ServiceClient agent_client = node.serviceClient<agent::Agent>("/agent_feedback");
	agent::Agent srv;
	srv.request.agentID  = 1;
	srv.request.init_x  = 0;
	srv.request.init_y  = 0;
	srv.request.finl_x  = 5;
	srv.request.finl_y  = 5;

	ROS_INFO("[ID:%d, init_x:%d, init_y:%d, finl_x:%d, finl_y:%d]", 
			 srv.request.agentID, srv.request.init_x, srv.request.init_y, srv.request.finl_x, srv.request.finl_y);

	agent_client.call(srv);

	ROS_INFO("Path : %s", srv.response.path.c_str());

	return 0;
};


