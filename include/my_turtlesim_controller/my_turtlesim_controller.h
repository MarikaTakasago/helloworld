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
    void draw_square(int);

    //parameter
    int hz;

    double old_x;
    double old_y;
    double old_theta;
    double sum_x;
    double sum_y;
    double sum_theta;
    double dx;
    double dy;
    double dtheta;

    //member
    ros::NodeHandle nh;
    ros::NodeHandle private_nh;
    ros::Subscriber sub_pose;
    ros::Publisher pub_cmd_vel;
    turtlesim::Pose current_pose;
};
#endif
