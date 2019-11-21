#ifndef rob_comm_H
#define rob_comm_H

#include "ros/ros.h"
#include "std_msgs/String.h"

#include <stdio.h>
#include <string.h>
#include <sstream>

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

#endif