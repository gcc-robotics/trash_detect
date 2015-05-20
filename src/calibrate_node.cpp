#include <iostream>
#include <stdio.h>

#include "ros/ros.h"
#include "calibrate.cpp"

int main(int argc, char **argv)
{
	// Start Node
	ROS_INFO("Starting calibrate_node");

	ros::init(argc, argv, "calibrate");
	ros::NodeHandle node;

	// Start trash detector
	Calibrate c = Calibrate(node);
	ROS_INFO("Press Ctrl-C to kill node.");

	// Spin
	// ros::Rate loopRate(10); // 10 hz

	// while(ros::ok())
	// {
	// 	// Do other things?

	// 	// ROS Spin & Sleep
	// 	ros::spinOnce();
	// 	loopRate.sleep();
	// }

	ros::spin();

	ros::shutdown();

	return 0;
}
