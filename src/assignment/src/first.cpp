#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "nav_msgs/Odometry.h"
#include "my_srv/Randpos.h"

/** This program receives a random position and controlls the velocity of the robot to reach said target */


ros::Publisher chatter_pub; /** Publisher for the velocity of the robot */
ros::ServiceClient client;  /** Client for receiving the random targer */
my_srv::Randpos rec_randpos; /** Message type received from the server */

float vel_x, vel_y,randpos_x, randpos_y; /**due to the election of K=1 as velocity constant, vel_x and vel_y are both the velocity of the robot and the distance with the target; while randpos_x and _randpos_y are the target random positions*/

geometry_msgs::Twist msg_sent; /** Message type twist for the velocity*/

void positionCallback(const nav_msgs::Odometry::ConstPtr& msg)
{ 
  /** In this callback the actual position of the robot is updated with every loop.
   *  This position is compared with the target position and if the target hasn´t been reached beyond the 
   *  stablished boundaries, the velocity is set. Else, the robot is stopped by setting a velocity of 0 and 
   *  a new target position is requested. With this, the loop is reestarted
  */
  
  ROS_INFO("Target position [%f, %f]", randpos_x, randpos_y);
  ROS_INFO("Robot position [%f, %f]", msg->pose.pose.position.x, msg->pose.pose.position.y);
  
  
  vel_x= 1*(randpos_x - msg->pose.pose.position.x); 
  vel_y= 1*(randpos_y - msg->pose.pose.position.y);
  ROS_INFO("Robot distance [%f, %f]", vel_x, vel_y);
  /** Here the distance/ velocity of the robot is computed for every loop and then printed in the screen.
    * As the specification of the constant k was let to the programmer, in order to do the coding easier it has been defined as 1, 
    * like  that, both distance and velocity remain equal*/
     
  
    
  if (vel_x>0.1 || vel_x<-0.1){
   msg_sent.linear.x = vel_x;
  }
  else {
    msg_sent.linear.x= 0;
  }
  if (vel_y>0.1 || vel_y<-0.1){  
    msg_sent.linear.y = vel_y;
  }
  else{
    msg_sent.linear.y = 0;
  }
  chatter_pub.publish(msg_sent);
  /** In this section of the code, there are 2 kind of "ifs", the ones concerning the X coordinate and the ones regarding the Y 
    * coordinate.
    * With this code, it is verified if the distance between the robot and the target coordinates are outside the boundaries or not, 
    * and depending on it the velocity is set with the given formula or is set to 0 respectively. Then the velocity is published for
    * the robot to start moving */  
  
  if ((vel_x<0.1 && vel_x>-0.1) && ((vel_y<0.1 && vel_y>-0.1)))
  {
    ROS_INFO("Target reached!");
    
    rec_randpos.request.min = -6;
    rec_randpos.request.max = 6;
  
    client.call (rec_randpos);
  
    randpos_x = rec_randpos.response.x;
    randpos_y = rec_randpos.response.y;
  }
  /** In this section of the code, it is verified if the target has been reached, and if so, a new random position is requested (called)
    * sending the maximum and minimum boundaries for the random number, and receiving said number in the variables randpos_x and 
    * randpos_y */ 
  
}




int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "mover");
   /**
   * The ros::init() function needs to see argc and argv so that it can perform
   * any ROS arguments and name remapping that were provided at the command line.*/
   
  ros::NodeHandle n;
  /**
   * NodeHandle is the main access point to communications with the ROS system.*/
   
  client = n.serviceClient<my_srv::Randpos>("/randpos");
  /** Here the client is created over getting a random position over the /randpos service*/
  
  chatter_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);
  /** Here it is signaled that the program will publish the velocity on the topic /cmd_vel*/
  

  /** In order to get a first random position and start moving the robot, before the subscribe is made, the random position is 
    * requested once. It is the same logic as explained in the end of the callback function*/
  rec_randpos.request.min = -6;
  rec_randpos.request.max = 6;
  
  client.call (rec_randpos);
  
  randpos_x = rec_randpos.response.x;
  randpos_y = rec_randpos.response.y;
  ROS_INFO("Target position first do [%f, %f]", randpos_x, randpos_y);
  ROS_INFO("Target position first do [%f, %f]", rec_randpos.response.x, rec_randpos.response.y);
  

  
   ros::Subscriber sub = n.subscribe("/odom", 1000, positionCallback);
   /** Here you are declaring the subscription to the topic /odom and calling the callback*/
   
   ros::spin();
 /**
   * ros::spin() will enter a loop, pumping callbacks.*/

 

  return 0;
}
