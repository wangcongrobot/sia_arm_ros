# include <data_record.h>
char int2char(int num)
{
	 char nnum = '0' + num;
	 return nnum;
}

void sysUsecTime() 
{ 
    gettimeofday(&tv, &tz); 
    //printf("tv_sec:%ld\n",tv.tv_sec); 
    //printf("tv_usec:%ld\n",tv.tv_usec); 
    //printf("tz_minuteswest:%d\n",tz.tz_minuteswest); 
    //printf("tz_dsttime:%d\n",tz.tz_dsttime); 
       
    p = localtime(&tv.tv_sec); 
    shiw[1] = p->tm_min / 10;
	gew[1] = p->tm_min - shiw[1] * 10;
	mmin[0] = int2char(gew[1]);
	mmin[1] = int2char(shiw[1]);


	shiw[2] = p->tm_sec / 10;
	gew[2] = p->tm_sec - shiw[2] * 10;
	ssec[0] = int2char(gew[2]);
	ssec[1] = int2char(shiw[2]);

	shiw[0] = (p->tm_hour+8) / 10;
	gew[0] = (p->tm_hour+8) - shiw[0] * 10;
	hhour[0] = int2char(gew[0]);
	hhour[1] = int2char(shiw[0]);

    //printf("time_now:%d%d%d%d%d%d.%ld\n", 1900+p->tm_year, 1+p->tm_mon, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec, tv.tv_usec); 
}  

void SD_dataRecord(MCMD* a, char j, char b, char c, char d) //记录数据整体 j代表关节 bcd代表时间间隔
{
	char jj = j + '1';
	FILE *fp;
    sysUsecTime();
	char addr[40] = {'D',':','\\','\\',hhour[1],hhour[0],'_',mmin[1],mmin[0],'_',ssec[1],ssec[0],' ','S','D','_','d','a','t','a','_',jj,'_',b,c,d,'.','t','x','t','\0'};
	fp = fopen(addr, "a+");

	if(fp == NULL)
    {
        printf("error");
        exit(1);
    }

	fprintf(fp, "%02d ", p->tm_hour);
	fprintf(fp, "%02d ", p->tm_min);
	fprintf(fp, "%02d.", p->tm_sec);
	fprintf(fp, "%03d ", (int)tv.tv_usec);

	for (int i = 0; i < 6; i++)
	{
		//fprintf(fp, "%04u ", sd_msg[i]);
		fprintf(fp, "%04u ", (a->joint)[i].pos);
	}	
	fprintf(fp, "\n");
	fclose(fp);
}
void RX_dataRecord(MCMD* a, char j, char b, char c, char d) //
{
	char jj = j + '1';
	FILE *fp;
    sysUsecTime();
	char addr[40] = {'D',':','\\','\\',hhour[1],hhour[0],'_',mmin[1],mmin[0],'_',ssec[1],ssec[0],' ','R','X','_','d','a','t','a','_',jj,'_',b,c,d,'.','t','x','t','\0'};
	fp = fopen(addr, "a+");

	if(fp == NULL)
    {
        printf("error");
        exit(1);
    }

	fprintf(fp, "%02d ", p->tm_hour);
	fprintf(fp, "%02d ", p->tm_min);
	fprintf(fp, "%02d.", p->tm_sec);
	fprintf(fp, "%03d ", (int)tv.tv_usec);

	for (int i = 0; i < 6; i++)
	{
		fprintf(fp, "%04u ", (a->joint)[i].pos);
	}	
	fprintf(fp, "\n");
	fclose(fp);
}


