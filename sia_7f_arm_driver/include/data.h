/**********************************************************************************************************************
* Copyright (c) Shenyang Institute of Automation, Chinese Academy of Sciences. All rights reserved.
* FileName: data.h
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

#ifndef DATA_H
#define DATA_H

#include<stdio.h>

typedef struct
{
	unsigned short pos : 12;//
	unsigned short mode : 3;//
	unsigned short frz : 1;//
} MSJOINT; //

typedef struct
{
	unsigned char head;//'M'
	unsigned char id;//

					 //
	MSJOINT joint[7];//
					 //MSJOINT Azimuth;
					 //MSJOINT Shoulder;
					 //MSJOINT ELbowPi;
					 //MSJOINT ForeArm;
					 //MSJOINT WristPi;
					 //MSJOINT WristRo;
					 //MSJOINT JawClamp;

	unsigned char Frz : 2;//
	unsigned char Hydro : 1;//
	unsigned char DynMod : 1;//
	unsigned char MoveRatio : 4;//

	unsigned char JawSpd : 2;//
	unsigned char Res1 : 6;//
						   //
	unsigned char key : 3;//
	unsigned char index : 5;//
							//
	unsigned char asterisk;//'*'
	unsigned short checksum;//
	unsigned short END;//"\r\n"
} MCMD; //

typedef struct
{
	unsigned short pos : 12;//
	unsigned short ctrlErr : 1;//
	unsigned short contiErr : 1;//
	unsigned short overErrA : 1;//
	unsigned short overErrB : 1;//
} SMJOINT; //
typedef struct
{
	unsigned char head;//'S'
	unsigned char id;//

	SMJOINT joint[7];//
					
	unsigned char timeoutErr : 1;//
	unsigned char telemErr : 7;//
							 
	unsigned char res1;//
	unsigned char echo;//
					   //
	unsigned char asterisk;//'*'
	unsigned short checksum;//
	unsigned short END;//"\r\n"
} SFEED; //

typedef struct
{
	unsigned char head;//'S'
	unsigned char id;//

	unsigned short scmdPos[7];//

	unsigned char timeoutErr : 1;//
	unsigned char telemErr : 7;//

	unsigned char res1;//
	unsigned char res2;//
	unsigned char asterisk;//'*'
	unsigned short checksum;//
	unsigned short END;//"\r\n"
} SPOS; //


typedef struct
{
	unsigned char head;//'M' or 'S'
	unsigned char id;//
	unsigned short para[8];//
	unsigned char index;//
	unsigned char asterisk;//'*'
	unsigned short checksum;//
	unsigned short END;//"\r\n"
} PARAINFO; //

//extern const double Pi;
//extern unsigned char Ccom5_RXBuff[24];
//void data_print(unsigned char* buffer, int len);
//void deg2rad(double* orig, double* dest, int i);
//unsigned char CheckRecData();
void data_print(unsigned char* buffer, int len);
MCMD mCmd;
SFEED sFeed;
SPOS sPos;
SFEED *sfeed;
SPOS *spos;

#endif // DATA_H