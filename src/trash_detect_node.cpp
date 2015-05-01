#include <iostream>
#include <stdio.h>

#include "ros/ros.h"
#include "TrashDetector.cpp"

int main(int argc, char **argv)
{
	// Start Node
	ROS_INFO("Starting trash_detect_node");

	ros::init(argc, argv, "trash_detect");
	ros::NodeHandle node;

	// Start trash detector
	TrashDetector trash = TrashDetector(node);
	//ROS_INFO(sodacans.at(0).getDistance());
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
