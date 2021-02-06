#ifndef MY_TURTULESIM_CONTROLLER_H
#define MY_TURTULESIM_CONTROLLER_H

#include <ros/ros.h>
#include "turtlesim/Pose.h"
#include "geometry_msgs/Twist.h"


class MyTurtlesimController
{
public:
    MyTurtlesimController();
    void process();

private:
    //method
    void pose_callback(const turtlesim::Pose::ConstPtr &);
    void go_straight();

    //parameter
    int hz;

    //member
    ros::NodeHandle nh;
    ros::NodeHandle private_nh;
    ros::Subscriber sub_pose;
    ros::Publisher pub_cmd_vel;
    turtlesim::Pose current_pose;
};
#endif
