# Research track 1: First Assignment
This code aims to control a simulated robot using ROS. The robot should autonomously reach a target between the coordinates (6,-6) in both 
x and y axis. The project uses two nodes, the one coded in the file **first.cpp** (in the folder src/assignment/src) that properly controlls the robot and makes it reach the target, and the server coded in the file **Radndpos_server.cpp** (in the folder 
/src/my_srv/src) that uses the messages of **randpos.srv** to send a random position for the robot to reach.

## Running the code
In order to properly run the code, one should open 3 shells and through the command cd reach the workspace folder where the files of this git repository are located. Before that, one should as well run the command "roscore &" to start using ROS. In the workspace folder, the 
command "catkin_make" should be run in order to be able to execute the program. 
Next, one should run the command "rosrun stage_ros stageros $(rospack find assignment1)/world/exercise.world" to initialize the world where
the robot will work, "rosrun my_srv randpos_server" to run the server and finally "rosrun assignment first" to run the robot controller.
Once done this, one could observe the vehaviour of the robot in the environment, moving towards a random position and requesting another 
goal once it is reached.

## Relational graph
! [relational graph] (images/Graph.png)

## Nodes
There are two nodes as stated before:

 1. The "first" node: it serves as the control algorithm for the robot, it receives a random position from the server (explained next) 
 using the service Randpos. Then, reads de current position of the robot through the topic /odom and computes the velocity required to
 reach the target, which is then published in the /cmd_vel topic. As specified by the requirements, the velocity is computed as a
 function: velocity= k*(target position- current position), where k is a constant left to the choice of the programmer (in this case, 
 it has been chosen to be 1 for simplicity´s sake). Every time the target is reached, the Randpos service is recalled to obtain a new
 position.
 
 2. The "randpos_service" service node: The only purpose of this node is to serve as a service server for the "first" node by providing
 each time that is requested a random number between the specified coordinates. 
 
## Custom Services and Messages
There is only one service created and no custom messages. 
The service created is the Randpos service (Randpos.srv), composed by two floats specifying the maximum and minimum coordinates between
 which the random position will be located sended by the "first" node, and two other floats containing the random coordenates offered by
 the server in the x and y axis.
 
