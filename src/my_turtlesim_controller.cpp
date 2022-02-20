#include "my_turtlesim_controller/my_turtlesim_controller.h"

MyTurtlesimController::MyTurtlesimController():private_nh("~")
{
    private_nh.getParam("hz",hz);
    private_nh.getParam("N",N);
    private_nh.getParam("len",len);

    sub_pose = nh.subscribe("/turtle1/pose",10,&MyTurtlesimController::pose_callback,this);

    pub_cmd_vel = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",1);

}

void MyTurtlesimController::pose_callback(const turtlesim::Pose::ConstPtr &msg)
{
    outside = double(2*M_PI/N);
    old_pose = current_pose;
    current_pose = *msg;
    if(!pose_checker) old_pose = current_pose;

    dx = fabs(current_pose.x - old_pose.x);
    dy = fabs(current_pose.y - old_pose.y);
    dl = sqrt(dx*dx + dy*dy);
    if(current_pose.theta * old_pose.theta < 0) dtheta = 0;
    else dtheta = fabs(current_pose.theta - old_pose.theta);
    pose_checker = true;
}

void MyTurtlesimController::go_straight()
{
    // std::cout<<current_pose<<std::endl;
    geometry_msgs::Twist cmd_vel;
    cmd_vel.linear.x = 0.5;
    pub_cmd_vel.publish(cmd_vel);
    l += dl;
    std::cout<<"l="<<l<<std::endl;
    if(l >= len/10) theta_sum = 0;
}
void MyTurtlesimController::turn()
{
    geometry_msgs::Twist cmd_vel;
    cmd_vel.angular.z = 0.1;
    pub_cmd_vel.publish(cmd_vel);
    theta_sum += dtheta*2*M_PI;
    std::cout<<"theta_sum="<<theta_sum<<std::endl;
    if(theta_sum >= outside) l=0;
}

void MyTurtlesimController::square()
{
    if(l >= len/10) turn();
    else go_straight();
}

void MyTurtlesimController::process()
{
    ros::Rate loop_rate(hz);
    while(ros::ok())
    {
        //go_straight();
        square();
        ros::spinOnce();
        loop_rate.sleep();
    }
}

int main(int argc,char**argv)
{
    ros::init(argc,argv,"my_turtlesim_controller");
    MyTurtlesimController my_turtlesim_controller;
    my_turtlesim_controller.process();
    return 0;
}
