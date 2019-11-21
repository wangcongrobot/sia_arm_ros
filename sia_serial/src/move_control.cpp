#include "move_control.h"

void cov_send(int t)
{
	::memcpy(sd_buffer, &mCmd, sizeof(MCMD));
	SD_msg(sd_buffer, sizeof(MCMD)); 
	Delay(t);
}
void cov_send_record(int t, int j)
{
	::memcpy(sd_buffer, &mCmd, sizeof(MCMD));
	SD_msg(sd_buffer, sizeof(MCMD));
	SD_dataRecord((MCMD*)sd_buffer, j, '0', '5', '0');
	Delay(t);
}

void Slavor_Init(unsigned short *a,int i)
{
	mCmd.head = 'M';
	mCmd.END = 0x0A0D;   
	mCmd.asterisk = '*';
	mCmd.Frz = 0;   
	mCmd.Hydro = 1;       
	//mCmd.joint[6].pos = 0x0100;
	mCmd.MoveRatio = 1;	  
	mCmd.id = 0x01;           
	for (int i = 0; i<6; i++)
	{
		mCmd.joint[i].frz = 0;    
		mCmd.joint[i].mode = 0;   
	}
	//mCmd.joint[5].frz = 0;        
	//mCmd.joint[5].mode = 1;   
	mCmd.joint[6].frz = 0;        
	mCmd.joint[6].mode = 0;   
 
							  // 6f3 e3 da2 9f8 d39 72f 0
	for (int i = 0; i<7; i++)
	{
		mCmd.joint[i].pos = a[i];//home[i]; 
	}

	  ::memcpy(sd_buffer, &mCmd, sizeof(MCMD));
	  SD_msg(sd_buffer,24);
	  if (flag_SD == 1)
	  {
		  SD_dataRecord((MCMD*)sd_buffer, i, '1', '0', '0');
	  }
	  data_print(sd_buffer, 24);
	  //dataRecord(sd_buffer, 24);

	Delay(500);     
	//mCmd.Frz = 1;    

	//printf("\nSlavor Initial Successfully!\n");
}


void Slavor_Init_Freeze(unsigned short *a, int i)
{
	mCmd.head = 'M';
	mCmd.END = 0x0A0D;   
	mCmd.asterisk = '*';
	mCmd.Frz = 1;   
	mCmd.Hydro = 0;      
	//mCmd.joint[6].pos = 0x0100;
	mCmd.MoveRatio = 1;	  
	mCmd.id = 0x01;           
	for (int i = 0; i<6; i++)
	{
		mCmd.joint[i].frz = 1;    
		mCmd.joint[i].mode = 0;   
	}
	//mCmd.joint[5].frz = 0;        
	//		mCmd.joint[5].mode = 1;   
	mCmd.joint[6].frz = 1;        
	mCmd.joint[6].mode = 0;   

	// 6f3 e3 da2 9f8 d39 72f 0
	for (int i = 0; i<7; i++)
	{
		mCmd.joint[i].pos = a[i];//home[i]; 
	}

	::memcpy(sd_buffer, &mCmd, sizeof(MCMD));
	SD_msg(sd_buffer, sizeof(MCMD));
	if (flag_SD == 1)
	{
		SD_dataRecord((MCMD*)sd_buffer, i, '1', '0', '0');
	}
	//data_print(sd_buffer, 24);
	//dataRecord(sd_buffer, 24);

	Delay(500);                           
	//mCmd.Frz = 1;    

	//printf("\nSlavor Initial Successfully!\n");
}


void getCurrentJoint()
{
	double c;
	for (int i = 0; i<7; i++) 
	{
		if ((i == 0) || (i == 1) || (i == 2) || (i == 4)) 
		{
			c = Trip[i] + L0[i] - ((double)(spos->scmdPos[i] - limitMin[i])) / ((double)(limitMax[i] - limitMin[i]))*Trip[i];
			currentJoint[i] = acos((pow(Frame[i], 2) + pow(Conect_rod[i], 2) - pow(c, 2)) / (2 * Frame[i] * Conect_rod[i])) - Theta[i];
			//cout << "currentJoint" << i << "  " << currentJoint[i] * 180.0 / Pi << endl;
			//cout << "currentJoint " << i << "  :" << currentJoint[i] << endl;
		}
		else if (i == 3)
		{
			currentJoint[i] = ((double)(spos->scmdPos[i] - limitMin[i])) / ((double)(limitMax[i] - limitMin[i]))*Pi;
			//cout << "currentJoint" << i << "  " << currentJoint[i] << endl;
			//cout << "currentJoint" << i << "  " << currentJoint[i] * 180.0 / Pi << endl;
		}
		else if (i == 6)
		{
			//
			currentJoint[i] = spos->scmdPos[i];
			
		}
		else // (i==5)
		{
			currentJoint[i] = ((double)(spos->scmdPos[i] - limitMin[i])) / ((double)(limitMax[i] - limitMin[i]))*(170.0 / 180.0*Pi * 2);
			//cout << "currentJoint" << i << "  " << currentJoint[i] << endl;
			//cout << "currentJoint" << i << "  " << currentJoint[i] * 180.0 / Pi << endl;
		}
	}
	// convert
	currentJoint[0] = (currentJoint[0] - Pi / 3) * DM[0];
	currentJoint[1] = (currentJoint[1] - Pi / 6) * DM[1];
	currentJoint[2] = (currentJoint[2] - Pi / 2) * DM[2];
	currentJoint[3] = (currentJoint[3] - Pi / 2) * DM[3];
	currentJoint[4] = (currentJoint[4] - Pi / 2) * DM[4];
	currentJoint[5] = (currentJoint[5] - Pi*170.0 / 180.0) * DM[5]; //�������ؽ�340������ת
	currentJoint[6] = currentJoint[6];
	/*
	for (int i = 0; i<7; i++)
	{
		cout << "currentJoint " << i << "  " << currentJoint[i] * 180.0 / Pi << endl;
	}
	*/

	for (int i = 0; i<7; i++)
	{
		if (currentJoint[i] - Angle_limitMin_r[i] <= EPSINON)
		{
			currentJoint[i] = Angle_limitMin_r[i];
			//cout << "currentJoint" << " < " << "Angle_limitMin_r i=" << i << endl;
		}
		else if (currentJoint[i] - Angle_limitMax_r[i] >= EPSINON)
		{
			currentJoint[i] = Angle_limitMax_r[i];
			//cout << "currentJoint" << " > " << "Angle_limitMax_r i=" << i << endl;
		}
	}
	/*
	for (int i = 0; i<6; i++)
	{
		cout << "actual currentJoint" << i << "  " << currentJoint[i] * 180.0 / Pi << endl;		
	}
	*/
	printf("\n\n********get current joint values successfully!**********\n\n");
	//get_current_joint_flag = 1;
	//printf("get_current_joint_flag=1\n");
	//test(currentJoint);
}


void Angle_Test(double* test)//
{
	unsigned short trans_angle[7] = {0x0000,0x0000,0x0000,0x0000,0x0000,0x0010,0x0010};
	flag_RX = 1;
	mCmd.head = 'M';
	mCmd.END = 0x0A0D;   
	mCmd.asterisk = '*';
	mCmd.Frz = 0;   
	mCmd.Hydro = 1;       
	mCmd.joint[6].pos = 0x0f00;
	mCmd.MoveRatio = 1;	 
	mCmd.id = 0x01;       
	for (int i = 0; i<6; i++)
	{
		mCmd.joint[i].frz = 0;  
		mCmd.joint[i].mode = 0; 
	}
	mCmd.joint[6].frz = 0;     
	mCmd.joint[6].mode = 1;  							 

	deg2pos_cal(test,trans_angle);
	//trans_angle[3] = 12.17*PPoint3[3]+2480.48;

	for (int i = 0; i<7; i++)
	{
		mCmd.joint[i].pos = trans_angle[i]; 
	}

	  ::memcpy(sd_buffer, &mCmd, sizeof(MCMD));
	  SD_msg(sd_buffer, 24);
	  //SD_msg(sd_buffer,sizeof(MCMD));
	 if (flag_SD == 1)
	  {
		  SD_dataRecord((MCMD*)sd_buffer, 7, '0', '0', '0');
	  }
	  //ROS_INFO("arm recv: %f %f %f %f %f %f ,duration: %f", rs.j[0],rs.j[1],rs.j[2],rs.j[3],rs.j[4],rs.j[5],rs.duration);
	  data_print(sd_buffer, 24);
	  

	Delay(100);      
	mCmd.Frz = 1;   
}


void MoveIt_test(std::list<robotState> PPoints)
{
	int n = 0;
	if(n = PPoints.size()<=0)
		return;
	else
	{
		for(std::list<robotState>::iterator it=PPoints.begin();it!=PPoints.end();++it)
		{
			Angle_Test((*it).j);
		}
	}
}

/*
void currentJoint_get()
{
	int caltime = 0;
	for (int i = 0; i < 15; i++)
	{
		Slavor_Init(ik_dec_desire, 6);

		if (SFEED_open == 1)
		{

			for (int j = 0; j < 7; j++)
			{
				currentpos[j] += spos->scmdPos[j];
			}
			caltime++;
			printf("Get SFEED Package: %d\n", caltime);
		}
		else
		{
			printf("Don't get SFEED Package!!!\n");
		}
	}
	for (int j = 0; j < 7; j++)
	{
		currentpos[j] = currentpos[j] / caltime;
	}
	//pos2deg_cal(currentpos, currentJoint);
	for (int j = 0; j < 7; j++)
	{
		currentRad[j] = currentJoint[j] / 180 * 3.1415926;
	}
}
*/

/*
y = Intercept + B1*x + B2*x^2 + B3*x^3
*/
unsigned short *deg2pos_cal(double* deg, unsigned short *ret)
{
	for (int i = 0; i < 6; i++)
	{
		ret[i] = joint_deg2pos[i][0] + joint_deg2pos[i][1] * deg[i] + joint_deg2pos[i][2] * pow(deg[i], 2) + joint_deg2pos[i][3] * pow(deg[i], 3);
	}
	return ret;
}
void Delay(int time)
{
	clock_t now = clock();
	while(clock() - now<time);
}
