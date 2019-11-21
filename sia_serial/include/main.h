#define _CRT_SECURE_NO_WARNINGS
#pragma once
#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include<cstdlib>
#include <ros/ros.h>
//#include <thread>
//#include <conio.h>
#include <stdio.h>
#include <iostream>
#include <list>
#include "move_control.h"
#include "sia_7f_arm_control.h"



using namespace std;
extern void Slavor_Init(unsigned short *a,int i);//从手初始化，开始执行时被调用一次即可
extern void Slavor_Init_Freeze(unsigned short *a, int i);//从手初始化，开始执行时被调用一次即可
extern void Angle_Test(double* test);//
extern void SD_dataRecord(MCMD* a, char j, char b, char c, char d);
extern void Task_Point2Point_deg_all(double* sstart, double* eend, int num, int t);

extern void MoveIt_test(std::list<robotState> PPoints);
extern std::list<robotState> targetPointList;

extern double ik_deg_desire[7];
extern unsigned short ik_dec_desire[7];
extern double ik_rad_desire[7];
extern void end_cartsian_pool(unsigned char* input);

#endif
