
#include <data_record.h>


int open_serial()
{
    
    serial::Timeout to = serial::Timeout::simpleTimeout(20);
    //设置要打开的串口名称
    sp.setPort("/dev/ttyUSB0");
    //设置串口通信的波特率
    sp.setBaudrate(19200);

    sp.setParity(serial::parity_none);

    sp.setBytesize(serial::eightbits);

    sp.setStopbits(serial::stopbits_one);
    //串口设置timeout
    sp.setTimeout(to);
    

    try
    {
        //打开串口
        sp.open();
    }
    //catch(serial::IOExce+9ption& e)
    catch(serial::IOException& e)
    {
        ROS_ERROR_STREAM("Unable to open port.");
        return -1;
    }
    
    //判断串口是否打开成功
    if(sp.isOpen())
    {
        ROS_INFO_STREAM("/dev/ttyUSB0 is opened.");
    }
    else
    {
        return -1;
    }
}
/*
int main(int argc, char** argv)
{ 
    ros::init(argc, argv, "serial_port");
    //创建句柄（虽然后面没用到这个句柄，但如果不创建，运行时进程会出错）
    ros::NodeHandle n;
    

    //创建timeout
    serial::Timeout to = serial::Timeout::simpleTimeout(100);
    //设置要打开的串口名称
    sp.setPort("/dev/ttyUSB0");
    //设置串口通信的波特率
    sp.setBaudrate(19200);
    //串口设置timeout
    sp.setTimeout(to);
    

    try
    {
        //打开串口
        sp.open();
    }
    catch(serial::IOException& e)
    {
        ROS_ERROR_STREAM("Unable to open port.");
        return -1;
    }
    
    //判断串口是否打开成功
    if(sp.isOpen())
    {
        ROS_INFO_STREAM("/dev/ttyUSB0 is opened.");
    }
    else
    {
        return -1;
    }
    SD_msg(sd_buffer,24);
    SD_dataRecord(sd_buffer,6,'0','5','0');
    ros::Rate loop_rate(50);
    while(ros::ok())
    {
        //获取缓冲区内的字节数
        size_t n = sp.available();
        if((n!=0)&&(flag_SD == 0))
        {
            RX_msg(rx_buffer,  n);
            flag_SD = 0;
        }
        
        loop_rate.sleep();
    } 
    //关闭串口
    sp.close();
 
}
*/

void SD_msg(uint8_t* sd_msg, int n)
{
    if(flag_RX == 1)
    {
        ROS_INFO_STREAM("serial is receiving data");
        return;
    }
    else
    {
        flag_SD = 1;   
        //jiao yan he
        unsigned short* pt = (unsigned short*) sd_msg;
        unsigned short checksum = pt[0];
        for(int i=1;i<10;i++)
        {
            checksum^=pt[i];
        }
        pt[10] = checksum;
        sp.write(sd_msg, n);
        flag_SD = 0;
    }
    
}

void RX_msg(uint8_t* rx_msg, size_t n)
{
        flag_RX = 1;       
        if(n!=0)
        {
            //uint8_t buffer[1024];
            //校验并读出数据
            n = sp.read(rx_buffer, n);
            if(rx_buffer[0] == 0x53)
            {
                for(int i=0; i<n; i++)//16进制的方式打印到屏幕
                {
                    if( (rx_buffer[i] & 0xff) > 0x0f)
                    {
                        std::cout << "0x" << std::hex << (rx_buffer[i] & 0xff) << " ";
                    }
                    else
                    {
                        std::cout << "0x0" << std::hex << (rx_buffer[i] & 0xff) << " ";
                    }
                }
                std::cout << std::endl;
                ROS_INFO_STREAM("confirm successfully");
            }
            else
            {
                for(int i=0; i<n; i++)//16进制的方式打印到屏幕
                {
                    if( (rx_buffer[i] & 0xff) > 0x0f)
                    {
                        std::cout << "0x" << std::hex << (rx_buffer[i] & 0xff) << " ";
                    }
                    else
                    {
                        std::cout << "0x0" << std::hex << (rx_buffer[i] & 0xff) << " ";
                    }
                }
                std::cout << std::endl;
                ROS_INFO_STREAM("confirm failed.");
            }
            
        }
}



