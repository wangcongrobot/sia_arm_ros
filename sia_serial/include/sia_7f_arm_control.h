#ifndef sia_7f_arm_control_H
#define sia_7f_arm_control_H

#include <termios.h>
#include <signal.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <list>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose.h>
#include <sensor_msgs/JointState.h>
#include <std_msgs/String.h>
#include <actionlib/server/simple_action_server.h>//header is the standard action library to implement an action server node
#include <control_msgs/FollowJointTrajectoryAction.h>////The header is generated from the stored action files
#include "rob_comm.h"



struct robotState
{
	double j[6];		// joint position
	double duration;	// duration for motion; needed for actionServer
};

namespace sia_7f_arm_robots
{

	// the struct stores information about the current robots state:
	// joint positions, cartesian position and error code

	class sia_7f_arm_control
	{

		private:

			bool flag_stop_requested;

			robotState setPointState;
			robotState targetState;

			int nrOfJoints; /* 6 */
			double cycleTime; /* in ms */

			//control data def	
			float controlData[6];	/* final control data */
			float executeData[6];
			float executeData_old[6];

			RobComm Comm;

			ros::NodeHandle n;
			sensor_msgs::JointState msgJointsCurrent;	/* the current joints */
			ros::Publisher  pubJoints; /* publishes the current joint positions  */

			void MotionGeneration();
			void CommunicationHW();
			void CommunicationROS();

			
			
		public:
			~sia_7f_arm_control();
			void init();
			void mainLoop();				
	};

}

std::list<robotState> targetPointList;		// list of points to move to

#endif