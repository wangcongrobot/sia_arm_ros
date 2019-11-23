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

#ifndef MOTION_PLANNER_H
#define MOTION_PLANNER_H

// C++ STL
#include <string.h>
#include <ctime>
#include <stdio.h>
#include <iostream>
#include <list>

// custom
#include "data_record.h"
#include "data.h"
#include "sia_7f_arm_control.h"

using namespace std;

const double Pi = 3.14159265358979;
const double EPSINON = 1e-5;

class MotionPlanner
{

public:

	MCMD mCmd;
	SFEED sFeed;
	SPOS  sPos;
	SFEED  *sfeed;
	SPOS  *spos;

	unsigned char rx_buffer[24];
	unsigned char sd_buffer[24];

	double ik_deg_desire[7];
	unsigned short ik_dec_desire[7];
	double ik_rad_desire[7];
	unsigned short clamp_desire;

public:

	/** \brief Constructor */
	MotionPlanner();

	/** \brief Destructor */
	~MotionPlanner();

	// data




	// function

	/**
	 * \brief 
	 * \param 
	 * \param 
	 * \return 
	*/
	void Slavor_Init(unsigned short *a,int i);

	/**
	 * \brief 
	 * \param 
	 * \param 
	 * \return 
	*/
	void Slavor_Init_Freeze(unsigned short *a, int i);

	/**
	 * \brief 
	 * \param 
	 * \param 
	 * \return 
	*/
	void getCurrentJoint();

	/**
	 * \brief 
	 * \param 
	 * \param 
	 * \return 
	*/
	void Angle_Test(double* test);//

	/**
	 * \brief 
	 * \param 
	 * \param 
	 * \return 
	*/
	void Task_Point2Point_deg_all(double* sstart, double* eend, int num, int t);

	/**
	 * \brief 
	 * \param 
	 * \param 
	 * \return 
	*/
	void repsend(int i, int t, int loop ,unsigned short num);

	/**
	 * \brief 
	 * \param 
	 * \param 
	 * \return 
	*/
	unsigned short *deg2pos_cal(double* deg, unsigned short *ret);

	/**
	 * \brief 
	 * \param 
	 * \param 
	 * \return 
	*/
	void Delay(int time); //time*1000 is the seconds you want to delay

	/**
	 * \brief 
	 * \param 
	 * \param 
	 * \return 
	*/
	void MoveIt_test(std::list<robotState> PPoints);


	/**
	 * \brief 
	 * \param 
	 * \param 
	 * \return 
	*/
	void SD_msg(uint8_t* sd_msg, int n);

	/**
	 * \brief 
	 * \param 
	 * \param 
	 * \return 
	*/
	void RX_msg(uint8_t* rx_msg, size_t n);

	/**
	 * \brief 
	 * \param 
	 * \param 
	 * \return 
	*/
	void SD_dataRecord(MCMD* a, char j, char b, char c, char d);

	/**
	 * \brief 
	 * \param 
	 * \param 
	 * \return 
	*/
	void RX_dataRecord(MCMD* a, char j, char b, char c, char d);

	/**
	 * \brief 
	 * \param 
	 * \param 
	 * \return 
	*/
	std::list<robotState> targetPointList;	

	/**
	 * \brief 
	 * \param 
	 * \param 
	 * \return 
	*/
	void ArrayRecord(double* a, int b);

	/**
	 * \brief 
	 * \param 
	 * \param 
	 * \return 
	*/
	void AngleRecord(double* a, int b); //记录SFEED包中的角度信息

	/**
	 * \brief 
	 * \param 
	 * \param 
	 * \return 
	*/
	void SPackage_Open();

	/**
	 * \brief 
	 * \param 
	 * \param 
	 * \return 
	*/
	char CheckRecData();

	/**
	 * \brief 
	 * \param 
	 * \param 
	 * \return 
	*/
	void get_systime();

	//extern void IK(double q_current[], double x, double y, double z, int step_num);



}

#endif // MOTION_PLANNER_H_