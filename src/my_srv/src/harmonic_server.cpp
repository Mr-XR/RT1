#include "ros/ros.h"
#include "my_srv/Harmonic.h"
#include <math.h>

#define PI 3.14159265358979323846

bool harmonic (my_srv::Harmonic::Request &req, my_srv::Harmonic::Response &res){
	res.vel = 0.1 + 2*sin(PI*req.pos/7 -2*PI/7);
    return true;
}



int main(int argc, char **argv)
{
   ros::init(argc, argv, "harmonic_server");
   ros::NodeHandle n;
   ros::ServiceServer service= n.advertiseService("/harmonic", harmonic);
   ros::spin();

   return 0;
}
