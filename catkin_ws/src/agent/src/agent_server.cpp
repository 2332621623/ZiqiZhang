#include <ros/ros.h>
#include "agent/Agent.h"
//#include "Planner.cpp"

bool agent_feedback(agent::Agent::Request  &req,
         			agent::Agent::Response &res)
{
    ROS_INFO("agentID:%d init_x:%d init_y:%d finl_x:%d finl_y:%d", req.agentID, req.init_x, req.init_y, req.finl_x, req.finl_y);


	res.path = "agent_path(should be get from planner.cpp, the connection between server and planner has not been completed yet)";/*Astar_Planner(req.init_x, req.init_y, req.finl_x, req.finl_y);
*/
    return true;
}

int main(int argc, char **argv)
{

    ros::init(argc, argv, "agent_status");
    ros::NodeHandle n;
    ros::ServiceServer agent_service = n.advertiseService("/agent_feedback", agent_feedback);

    ROS_INFO("Ready to show informtion.");
    ros::spin();

    return 0;
}




