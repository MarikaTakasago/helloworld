#include "my_turtlesim_controller/my_turtlesim_controller.h"

MyTurtlesimController::MyTurtlesimController():private_nh("")
{
    private_nh.param("hz",hz,{10});

    sub_pose = nh.subscribe("/turtle1/pose",10,&MyTurtlesimController::pose_callback,this);

    pub_cmd_vel = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",1);
}

void MyTurtlesimController::pose_callback(const turtlesim::Pose::ConstPtr &msg)
{
    old_x = current_pose.x;
    old_y = current_pose.y;
    old_theta = current_pose.theta;

    current_pose = *msg;

    dx = current_pose.x - old_x;
    dy = current_pose.y - old_y;
    dtheta = current_pose.theta - old_theta;
    if(dx<0)
    {
        dx = -dx;
    }
    if(dy<0)
    {
        dy = -dy;
    }
    if(dtheta>M_PI)
    {
        dtheta -= M_PI;
    }

}

void MyTurtlesimController::go_straight()
{
    std::cout<<current_pose<<std::endl;
    geometry_msgs::Twist cmd_vel;
    cmd_vel.linear.x = 0.5;
    pub_cmd_vel.publish(cmd_vel);
}

void MyTurtlesimController::draw_square(int i)
{
      std::cout<<current_pose<<std::endl;
      geometry_msgs::Twist cmd_vel;

      if(i==10)
      {
          sum_x = 0;
          sum_y = 0;
          sum_theta = 0;
          //old_x = current_pose.x;
          //old_y = current_pose.y;
          //old_theta = current_pose.theta;
      }

      //sum_x += (current_pose.x - old_x)*10;
      //sum_theta += (current_pose.theta - old_theta);

      std::cout<<old_x<<std::endl;
      std::cout<<old_y<<std::endl;

      if(sum_x >= 4 || sum_y >=4)
      {
          //kaiten
          cmd_vel.linear.x = 0.0;
          cmd_vel.angular.z = 0.1;
          sum_theta += dtheta;

      }

      /*if(sum_y >= 2)
      {
          cmd_vel.linear.x = 0.0;
          cmd_vel.angular.z = 0.1;
          sum_theta += dtheta;

      }*/

      if(sum_theta >= 0.25)
      {
          cmd_vel.angular.z = 0.0;
          sum_x = 0.0;
          sum_y = 0.0;
          sum_theta = 0.0;

      }

      if(sum_x < 4 && sum_y < 4)
      {
          cmd_vel.linear.x = 0.5;
          cmd_vel.angular.z = 0.0;
          sum_x += dx*10;
          sum_y += dy*10;
      }

      std::cout<<sum_x<<std::endl;
      std::cout<<sum_y<<std::endl;
      std::cout<<sum_theta<<std::endl;
      std::cout<<current_pose.theta<<std::endl;

      /*if(current_pose.x - old_x <= 2)
      {
          //chokusin
          cmd_vel.angular.z = 0.0;
          cmd_vel.linear.x = 0.5;
          old_theta = current_pose.theta;

      }*/

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
