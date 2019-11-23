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

#ifndef ROBOT_ABSTRACT_H
#define ROBOT_ABSTRACT_H

class RobotAbstract
{
private:
    /* data */

public:
    RobotAbstract(/* args */);
    ~RobotAbstract();

public:

    /* data */

	unsigned short limitMin_part[7]; 
	unsigned short limitMax_part[7]; 
	//unsigned short limitMin[7]; 
	//unsigned short limitMax[7]; 
	unsigned short limitMin[7]; 
	unsigned short limitMax[7];
	double kk[7];
	double bb[7];

	double Frame[7]; 
	double L0[7]; 
	double Theta[7]; 
	double Conect_rod[7]; 
	double Trip[7]; 
	double Delte[7]; 
	int SFEED_open;
	// 118 119.8 114.5 172.2 118.1
	double Angle_limitMin[7];
	double Angle_limitMax[7];

	double Angle_limitMin_r[7];
	double Angle_limitMax_r[7];

	double Joint_Angle[7];
	unsigned short currentpos[7];
	double currentRad[7];
	double currentJoint[7];  // get current joint values
	char currentJoint_hex[7];  // get current joint values
	//0x06b8
	unsigned short zero[7]; //0x0790,0x0c10,0x0380,0x0980,0x0470,0x0010,0x0ff0
	unsigned short home[7];// 0x0180,0x0270,0x0d00,0x0c80,0x0200,0x0600,0x08f0  { 0x0f20,0x0020,0x0f80,0x0980,0x0460,0x0a00,0x0ff0 };//{ 0x0f20,0x0020,0x0f80,0x0980,0x0460,0x0a00,0x0ff0 };
	double repangle_max[6];
	double repangle_min[6];
	double angle_home[7];//{0, 90, -60, 90, 0, -60, 0x0fff };//{1850,1036,212,x,3932}

	double PPoint1[6];
	double PPoint2[6];//
	double PPoint3[6];//{-26.5827 ,  31.0433  ,-43.9823  , -0.2969  ,  2.6600, 0 }
	double PPoint4[6];
	double PPoint5[6];//

	double joint_deg2pos[6][4];

	signed char DM[7]; 

};

#endif // ROBOT_ABSTRACT_H