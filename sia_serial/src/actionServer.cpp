#include <sia_7f_arm_control.h>
#include "rob_comm.h"
#include <list>

//#include "armplaning_client.h"

using namespace std;

typedef actionlib::SimpleActionServer<control_msgs::FollowJointTrajectoryAction> TrajectoryServer;

double deg2rad = 3.14159/180.0;
double rad2deg = 180.0/3.14159;

//***************************************************************************
// Processing and JointTrajectoryAction
void sia_executeTrajectory(const control_msgs::FollowJointTrajectoryGoalConstPtr& _goal, TrajectoryServer* _as)
{
  //double rad2deg = 180.0 / 3.141;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
  
  robotState rs;
  double lastDuration = 0.0;

  int nrOfPoints = _goal->trajectory.points.size();		// Number of points to add                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
  for(int i=0; i<nrOfPoints; i++)
  {
	  rs.j[0] = _goal->trajectory.points[i].positions[0]*rad2deg;	// ros values come in rad, internally we work in degree
	  rs.j[1] = _goal->trajectory.points[i].positions[1]*rad2deg;
	  rs.j[2] = _goal->trajectory.points[i].positions[2]*rad2deg;
	  rs.j[3] = _goal->trajectory.points[i].positions[3]*rad2deg;
	  rs.j[4] = _goal->trajectory.points[i].positions[4]*rad2deg;
      rs.j[5] = _goal->trajectory.points[i].positions[5]*rad2deg;
	  
	  float dtmp = _goal->trajectory.points[i].time_from_start.toSec();
	  rs.duration = dtmp - lastDuration;// time_from_start is adding up, these values are only for the single motion
	  lastDuration = dtmp;

	  targetPointList.push_back(rs);//push_back()
  }
  _as->setSucceeded();
  int m=0;
  m = targetPointList.size();
  //debug msg
  ROS_INFO("targetPoint List's size: %d ", targetPointList.size()); 
  ROS_INFO("arm recv: %f %f %f %f %f %f ,duration: %f", rs.j[0],rs.j[1],rs.j[2],rs.j[3],rs.j[4],rs.j[5],rs.duration);
 
}
//*************************************************************************
void quit(int sig)
{
  ros::shutdown();
  exit(0);
}

//******************** MAIN ************************************************
int main(int argc, char** argv)
{
	ros::init(argc, argv, "sia_7f_arm_joints_punlisher1");
	ros::NodeHandle n2;

	//Start the ActionServer for JointTrajectoryActions and GripperCommandActions from MoveIT
	TrajectoryServer tserver(n2, "sia_7f_arm/follow_joint_trajectory", boost::bind(&sia_executeTrajectory, _1, &tserver), false);
  	ROS_INFO("TrajectoryActionServer: Starting");
  	tserver.start();

	ros::spin();
    
	sia_7f_arm_robots::sia_7f_arm_control robot;
	robot.init();	
	robot.mainLoop();		//spinning is done inside the main loop			

  	signal(SIGINT,quit);	
	return(0);
}

namespace sia_7f_arm_robots{
	//*************************************************************************************
	sia_7f_arm_control::~sia_7f_arm_control(){}
	//*************************************************************************************
	void sia_7f_arm_control::init(){
		ROS_INFO("...initing...");

		flag_stop_requested = false;
		//this deside the control msg send frequency 
        cycleTime = 10.0;// in ms
		nrOfJoints = 6;

		setPointState.j[0] =  0.0;	// values are initialized with 6 field to be usable for rob right arm 
		setPointState.j[1] =  0.0;
		setPointState.j[2] =  0.0;
		setPointState.j[3] =  0.0;
        setPointState.j[4] =  0.0;
        setPointState.j[5] =  0.0;
		setPointState.duration = 0;

		// when starting up (or when reading the HW joint values) the target position has to be aligned with the setPoint position
		for(int i=0; i<nrOfJoints; i++)
		{
			targetState.j[i] = setPointState.j[i];
		}
			
        targetState.duration = 0.0;//init the timeStamp


		for(int j=0;j<6;j++)
		{
			controlData[j] = 0;
		}

		msgJointsCurrent.header.stamp = ros::Time::now();
		msgJointsCurrent.name.resize(6);
		msgJointsCurrent.position.resize(6);
		msgJointsCurrent.name[0] ="sia_7f_arm_joint1";
		msgJointsCurrent.position[0] = 0.0;
		msgJointsCurrent.name[1] ="sia_7f_arm_joint2";
		msgJointsCurrent.position[1] = 0.0;
        msgJointsCurrent.name[2] ="sia_7f_arm_joint3";
		msgJointsCurrent.position[2] = 0.0;
        msgJointsCurrent.name[3] ="sia_7f_arm_joint4";
		msgJointsCurrent.position[3] = 0.0;
		msgJointsCurrent.name[4] ="sia_7f_arm_joint5";
		msgJointsCurrent.position[4] = 0.0;
        msgJointsCurrent.name[5] ="sia_7f_arm_gripper";
		msgJointsCurrent.position[5] = 0.0;

		// Publish the current joint states
		pubJoints = n.advertise<sensor_msgs::JointState>("/joint_states", 1);

	}
	//*************************************************************************************
	void sia_7f_arm_control::mainLoop()
	{
  		ROS_INFO("Starting Mover Main Loop");
		
		//output angle data to a txt file
		int i = 0;
  		
 	 	for(;;)
  		{
			MotionGeneration();			// Generate the joint motion 
			CommunicationHW();			// Forward the new setpoints to the hardware

			if(flag_stop_requested)
				break;

			ros::spinOnce();
			ros::Duration(cycleTime/1000.0).sleep();		// main loop with 20 Hz.(50/1000=0.05s=50ms)
						
  		}

		ROS_INFO("Closing Mover Main Loop");

	} 
	//************************************************************************************
	//
	void sia_7f_arm_control::MotionGeneration()
	{
		int i=0;
		int j=0;

		//printf("r_targetPointList.size() = %ld \n",r_targetPointList.size());
       
		if(targetPointList.size() > 0)
		{
			targetState = targetPointList.front();
			targetPointList.pop_front();

			for(int i=0; i<nrOfJoints; i++)
			{
				setPointState.j[i] = targetState.j[i];
			}
			setPointState.duration = targetState.duration;
			
			for(j=0;j<6;j++)
			{
				controlData[j] = setPointState.j[j];
			}
			controlData[6] = setPointState.duration;
		}

	}
	//************************************************************************************
	// Forward the new setpoints to the hardware

	void sia_7f_arm_control::CommunicationHW()
	{

		int i = 0;
		for(i=0;i<7;i++)//write right arm control data
		{
			executeData[i] = controlData[i];
		}

		if(executeData[0]!=executeData_old[0] && executeData[1]!=executeData_old[1])
		{
			
			//add send mesage command here	
			//************************************

			Comm.SetJoints(executeData);//send new target angle 

			//************************************

			ROS_INFO("arm MSG [%f][%f][%f][%f][%f][%f][%f]", executeData[0],executeData[1],executeData[2],executeData[3],executeData[4],executeData[5],executeData[6]);

			//save the date to old
			for (int i=0;i<7;i++)
			{
				executeData_old[i] = executeData[i];
			}

			CommunicationROS();			// Publish the joint states and error info
		}
	}
	//************************************************************************************
	// forward the current joints to RViz etc
	void sia_7f_arm_control::CommunicationROS()
	{
		msgJointsCurrent.header.stamp = ros::Time::now();
		msgJointsCurrent.position[0] = executeData[0]*deg2rad;		// Robot SER communication works in degree
		msgJointsCurrent.position[1] = executeData[1]*deg2rad;
		msgJointsCurrent.position[2] = executeData[2]*deg2rad;
		msgJointsCurrent.position[3] = executeData[3]*deg2rad;
        msgJointsCurrent.position[4] = executeData[4]*deg2rad;
        msgJointsCurrent.position[5] = executeData[5]*deg2rad;
		pubJoints.publish(msgJointsCurrent);	// ROS communication works in Radian

	}
	
}