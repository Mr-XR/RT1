#include "ros/ros.h"
#include "my_srv/Randpos.h"


/** This program is conceived to work as a service server that gives back random coordinates between the specified range */   
   

double randMToN(double M, double N)
 {
/** This function just creates and returns a random number between the minimum and maximum boundaries specified*/
     return M+(rand()/ (RAND_MAX/(N-M)));
 }

bool position (my_srv::Randpos::Request &req, my_srv::Randpos::Response &res)
 {
 /** This function provides de service for generating random coordenates by 
   *calling the function randMToN to get random coordenates in x and y. It also prints them in the screen*/
   res.x= randMToN(req.min, req.max);
               
   res.y= randMToN(req.min, req.max);
   ROS_INFO("Target position srv [%f, %f]", res.x, res.y);
   return true;
 }

int main(int argc, char **argv)
{  
  ros::init(argc, argv, "randpos_server");
/**
   * The ros::init() function needs to see argc and argv so that it can perform
   * any ROS arguments and name remapping that were provided at the command line.*/
   
  ros::NodeHandle n;
/**
   * NodeHandle is the main access point to communications with the ROS system.*/
   
  ros::ServiceServer service = n.advertiseService("/randpos", position);
/**
  * The service is created and advertised over ros*/

  ros::spin();
/**
   * ros::spin() will enter a loop*/
   
  return 0;
}
