#include "main.h"
int j = 5;

double test_Point1[7] = { 0, 50, -45, 0, 10, 0, 0};//{ 0, 0, 0, 0, 0, 0, 0 }; //
double test_Point2[7] = { 0, 90, -90, 0, 45, 0, 0 };
double rad_test[6] = { 0,0,0,0,0,0 };

unsigned short leave[7] = {0x0010,0x00a0,0x0d00,0x0980,0x0600,0x0800,0x0010};
unsigned short ttest[7] = { 0x07a0, 0x0bf8, 3000, 0x0990, 0x0860, 0x0700, 0x0400 };//0904 0984 098e 07c0 09fb 09d9
unsigned short home1[7] = { 0x06e5, 0x006b, 0x0fc8, 0x0909, 0x0ff0, 0x08d3, 0x0110 };//
unsigned short home_calib[7] = { 0x0458, 0x0282, 0x0600, 0x0409, 0x0a5f, 0x0016, 0x0010 };//
unsigned short home_pid1[7] = { 0x05e5, 0x056b, 0x05c8, 0x0709, 0x05f0, 0x05d3, 0x0110 };//
unsigned short home_pid2[7] = { 0x09e5, 0x096b, 0x09c8, 0x0809, 0x09f0, 0x0ad3, 0x0110 };//
//unsigned short home_pid2[7] = { 0x0b58, 0x0982, 0x0e00, 0x0a09, 0x0a5f, 0x0016, 0x0010 };//
unsigned char str[3] = {7,8,9};


int main(int argc, char** argv)
{
    ros::init(argc, argv, "main_serial_port");
   
    ros::NodeHandle nh;

    open_serial();
    
    size_t n = 0;
	flag_RX = 0;
	flag_SD = 0;
	int i = 5;
    while(i--) 
	{
	    Slavor_Init(zero, j);
        
        n = sp.available();
        if((n!=0)&&(flag_SD == 0))
        {
            RX_msg(rx_buffer,  n);
        }
        
	}

	
	int m=0;
    ros::Rate loop_rate(1000);
    while(ros::ok())
    {	
        //获取缓冲区内的字节数
        n = sp.available();
        if((n!=0)&&(flag_SD == 0))
        {
            RX_msg(rx_buffer,  n);
        }

        m=targetPointList.size();
        //ROS_INFO("targetPoint List's size: %d ", m);
		if(m > 0)
		{
			MoveIt_test(targetPointList);
			targetPointList.clear();
		}

        ros::spinOnce();
        loop_rate.sleep();
    } 
    //关闭串口
    sp.close();
    //ros::spin();
	return 0;
}
