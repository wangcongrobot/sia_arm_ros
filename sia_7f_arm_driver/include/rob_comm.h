/**********************************************************************************************************************
* Copyright (c) Shenyang Institute of Automation, Chinese Academy of Sciences. All rights reserved.
* FileName: robot_abstract.h
* Contact:  
* Version:  V0.1
*
* LICENSING TERMS:
*
* History:
* <author>      <time>      <version>      <desc>
*
* Description:
**********************************************************************************************************************/

#ifndef ROB_COMM_H
#define ROB_COMM_H

#include <stdio.h>
#include <string.h>
#include <sstream>

#include "ros/ros.h"
#include "std_msgs/String.h"

class RobComm {
public:
	RobComm(){};
   ~RobComm(){};

	//bool flagDoComm;
	int nrOfJoints;   
    float Rx_buf[6];                  
	float Tx_buf[12];

	//void Init(std::string robotType);
	void SetJoints(float * j)
    {
        return;
    }
	void GetJoints(float * j);

};

#endif // ROB_COMM_H