#pragma once
#ifndef MOVE_CONTROL_H_INCLUDED
#define MOVE_CONTROL_H_INCLUDED

#include "data_record.h"
#include "data.h"
#include "sia_7f_arm_control.h"
#include <string.h>
#include <ctime>
#include <stdio.h>
#include <iostream>
#include <list>

const double Pi = 3.14159265358979;
const double EPSINON = 1e-5;

unsigned short limitMin_part[7] = { 0x0410,0x0510,0x0410,0x0500,0x0410,0x0010,0x0010 }; 
unsigned short limitMax_part[7] = { 0x0ae0,0x08e0,0x08e0,0x0a00,0x09e0,0x0fe0,0x0ff0 }; 
//unsigned short limitMin[7] = { 0x0010,0x0010,0x0010,0x0400,0x0010,0x0010,0x0010 }; 
//unsigned short limitMax[7] = { 0x0fe0,0x0fe0,0x0fe0,0x0f00,0x0fe0,0x0fe0,0x0ff0 }; 
unsigned short limitMin[7] = { 172, 111, 110, 3592, 100, 350, 0x0010 }; 
unsigned short limitMax[7] = { 3971, 3986, 4000, 1395, 4000, 3800, 0x0ff0 }; 
double kk[7] = {0,0,0,0,0,0,0};
double bb[7] = {0,0,0,0,0,0,0};

double Frame[7] = { 40.6, 54.8, 54.8, 39.4, 40.6, 56.1, 56.1 }; 
double L0[7] = { 227, 252, 252, 252.1, 227, 227.1, 227.1 }; 
double Theta[7] = { 0.5258, 0.4290, 0.4290, 0.1308, 0.5258, 0.1308, 0.1308 }; 
double Conect_rod[7] = { 261.2, 300.8, 300.8, 305.5, 261.2, 305.5, 305.5 }; 
double Trip[7] = { 70,95,95,95,70,95,95 }; 
double Delte[7] = { 0 }; 
int SFEED_open = 0;
// 118 119.8 114.5 172.2 118.1
double Angle_limitMin[7] = {-60,80, 25, -90, -28, -170, 0x0010 };
double Angle_limitMax[7] = {58,-20,-90,  83,  90,  170, 0x0fff };

double Angle_limitMin_r[7] = {-Pi/3, -Pi/6, -Pi/2, -Pi/2, -Pi/6, -Pi*170.0/180.0, 0x0001 };
double Angle_limitMax_r[7] = {Pi/3, Pi/2, Pi/6, Pi/2, Pi/2, Pi*170.0/180.0, 0x0fff };

double Joint_Angle[7] = { 0 };
unsigned short currentpos[7] = { 0, 0, 0, 0, 0, 0, 0 };
double currentRad[7] = { 0, 0, 0, 0, 0, 0, 0 };
double currentJoint[7] = { 0 };  // get current joint values
char currentJoint_hex[7] = { 0 };  // get current joint values
//0x06b8
unsigned short zero[7] = { 0x07a0, 0x0c24, 0x0360, 0x0990, 0x0360,350, 0x0400 }; //0x0790,0x0c10,0x0380,0x0980,0x0470,0x0010,0x0ff0
unsigned short home[7] = { 0x0380,0x0270,0x0d00,0x0c80,0x0200,0x0600,0x08f0 };// 0x0180,0x0270,0x0d00,0x0c80,0x0200,0x0600,0x08f0  { 0x0f20,0x0020,0x0f80,0x0980,0x0460,0x0a00,0x0ff0 };//{ 0x0f20,0x0020,0x0f80,0x0980,0x0460,0x0a00,0x0ff0 };
double repangle_max[6] = { 60, 40, 20, 45, 40, 90 };
double repangle_min[6] = { -60, -20, -40, -45, -20, -90 };
double angle_home[7] = {0,80,-40,60,-20,-80};//{0, 90, -60, 90, 0, -60, 0x0fff };//{1850,1036,212,x,3932}

double PPoint1[6] = { 14.0160 ,  45.6648  , 10.4048  , -0.2748  , 17.8749 ,0};
double PPoint2[6] = {26.5366  , 31.0389 , -43.7893 ,  -1.0203  ,  2.2067, 0 };//
double PPoint3[6] = {-45 ,  20  ,20  , 0  ,  -20, 0 };//{-26.5827 ,  31.0433  ,-43.9823  , -0.2969  ,  2.6600, 0 }
double PPoint4[6] = {-14.1321  , 44.9926  ,  4.7496  , -0.7512 ,  32.8381, 0 };
double PPoint5[6] = {-0.2745 ,  52.6262 , -36.1360 ,  -2.5485  , 18.7721, 0 };//

double joint_deg2pos[6][4] = { //������������intercepet B1 B2 B3 
								{ 1939.32735, 37.95874, 0.03567, -0.00174 },
								{ 3092.92026, -35.19651, -0.13429, 0.00177 },
								{ 909.71191, -33.3771, 0.18092, 0.00188 },
								{ 2424.94764, 12.29197, 0.0025, -2.09538E-5 },//{-1390.396, 5518.112, -27.9998, 138.47678 }
								{ 765.93178, 31.04001, 0.21765, -0.00194 },
								{ 1808.27824, 12.1544, 0.00274, -7.16078E-6 } };

signed char DM[7] = { -1,-1,1,-1,-1,1,1 };   


extern MCMD mCmd;
extern SFEED sFeed;
extern SPOS  sPos;
extern SFEED  *sfeed;
extern SPOS  *spos;


void Slavor_Init(unsigned short *a,int i);
void Slavor_Init_Freeze(unsigned short *a, int i);
void getCurrentJoint();
void Angle_Test(double* test);//
void Task_Point2Point_deg_all(double* sstart, double* eend, int num, int t);
void repsend(int i, int t, int loop ,unsigned short num);
unsigned short *deg2pos_cal(double* deg, unsigned short *ret);
void Delay(int time); //time*1000 is the seconds you want to delay
void MoveIt_test(std::list<robotState> PPoints);

extern unsigned char rx_buffer[24];
extern unsigned char sd_buffer[24];
extern void SD_msg(uint8_t* sd_msg, int n);
extern void RX_msg(uint8_t* rx_msg, size_t n);
extern void SD_dataRecord(MCMD* a, char j, char b, char c, char d);
extern void RX_dataRecord(MCMD* a, char j, char b, char c, char d);
extern std::list<robotState> targetPointList;	

extern void ArrayRecord(double* a, int b);

extern void AngleRecord(double* a, int b); //记录SFEED包中的角度信息
extern void SPackage_Open();
extern unsigned char CheckRecData();
extern void get_systime();
//extern void IK(double q_current[], double x, double y, double z, int step_num);

extern double ik_deg_desire[7];
extern unsigned short ik_dec_desire[7];
extern double ik_rad_desire[7];
extern unsigned short clamp_desire;

using namespace std;

#endif