#include "my_turtlesim_controller/my_turtlesim_controller.h"

MyTurtlesimController::MyTurtlesimController():private_nh("")
{
    private_nh.param("hz",hz,{10});

    sub_pose = nh.subscribe("/turtle1/pose",10,&MyTurtlesimController::pose_callback,this);

    pub_cmd_vel = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",1);
}

void MyTurtlesimController::pose_callback(const turtlesim::Pose::ConstPtr &msg)
{
    current_pose = *msg;
}

void MyTurtlesimController::go_straight()
{
    std::cout<<current_pose<<std::endl;
    geometry_msgs::Twist cmd_vel;
    cmd_vel.linear.x = 0.5;
    pub_cmd_vel.publish(cmd_vel);
}

void turn()
{
    for(int i=0;i<16;i++)
    {
        cmd_vel.angular.z = 0.1;
    }

}

void MyTurtlesimController::draw_square(int i)
{
      std::cout<<current_pose<<std::endl;
      geometry_msgs::Twist cmd_vel;

      if(i==10)
      {
          X = current_pose.x;
          Y = current_pose.y;
      }

      std::cout<<X<<std::endl;
      std::cout<<Y<<std::endl;

      turn;
      go_straight();

/*      if(current_pose.theta < 0)
      {
          current_pose.theta += 2*M_PI;
      }

      if(current_pose.theta >= M_PI/2)
      {
          cmd_vel.angular.z = 0.0;
          cmd_vel.linear.x = 0.5;
          if(current_pose.y-Y >= 2)
          {
              cmd_vel.linear.x = 0.0;
              cmd_vel.angular.z = 0.1;
              if(current_pose.theta >= M_PI)
              {
                  cmd_vel.angular.z = 0.0;
                  cmd_vel.linear.x = 0.5;
                  if(X-current_pose.x >= 2)
                  {
                      cmd_vel.linear.x = 0.0;
                      cmd_vel.angular.z = 0.1;
                      if(current_pose.theta >= 3/2*M_PI)
                      {
                          cmd_vel.angular.z = 0.0;
                          cmd_vel.linear.x = 0.5;

                      }
                  }
              }

          }

      }

//
//      th = current_pose.theta;
//      turn = th + M_PI/2;
//
//      cmd_vel.angular.z = 0.1;
//      if(current_pose.theta > turn)
//      {
//          cmd_vel.linear.x = 0.5;
//      }
*/

      pub_cmd_vel.publish(cmd_vel);


}


void MyTurtlesimController::process()
{
    ros::Rate loop_rate(hz);
    int i=0;
    while(ros::ok())
    {
        //go_straight();
        draw_square(i);
        ros::spinOnce();
        loop_rate.sleep();
        i++;
    }
}

int main(int argc,char**argv)
{
    ros::init(argc,argv,"my_turtlesim_controller");
    MyTurtlesimController my_turtlesim_controller;
    my_turtlesim_controller.process();
    return 0;
}
