#include "data.h"
# include <stdio.h>
# include <fstream>
# include <sys/time.h>
# include <time.h>
# include <ros/ros.h>
# include <serial/serial.h>
# include <iostream>
struct timeval    tv; 
struct timezone   tz;      
struct tm         *p;
char hhour[2] = { 0,0 }, mmin[2] = { 0,0 }, ssec[2] = { 0,0 };
int  shiw[3] = { 0,0,0 }, gew[3] = { 0,0,0 };
int flag_SD = 0;//0代表没有发送 1代表正在发送
int flag_RX = 0;//0代表没有接受 1代表正在接受

uint8_t rx_buffer[24];
uint8_t sd_buffer[24] = {0x4d, 0x01, 0xa0, 0x07, 0x24, 0x0c, 0x60, 0x03, 0x90, 0x09, 0x60, 0x03, 0x5e, 
                         0x01, 0x00, 0x04, 0x14, 0x00, 0x00, 0x2a, 0x13, 0x2c, 0x0d, 0x0a};
void SD_msg(uint8_t* sd_msg, int n);
void RX_msg(uint8_t* rx_msg, size_t n);
//创建一个serial类
serial::Serial sp;

int open_serial();

void SD_dataRecord(MCMD* a, char j, char b, char c, char d);
void RX_dataRecord(MCMD* a, char j, char b, char c, char d);
void sysUsecTime(); 
char int2char(int num);