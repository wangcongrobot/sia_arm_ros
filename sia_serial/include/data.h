#pragma once
#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

#include<stdio.h>

typedef struct
{
	unsigned short pos : 12;//�������� λ��
	unsigned short mode : 3;//�˶�ģʽ
	unsigned short frz : 1;//����״̬
} MSJOINT; //���ָ����ֵĹؽ���Ϣ

typedef struct
{
	unsigned char head;//'M'
	unsigned char id;//����ָʾ�ð����ݵĺ���

					 //һ��7�����е�2�����߶�������ܻᱻ����
	MSJOINT joint[7];//�����ڶ� ��۸��� ��ؽڸ��� ǰ����ת ��ؽڸ��� ��ؽ���ת ��ǯ�г�
					 //MSJOINT Azimuth;//�����ڶ�
					 //MSJOINT Shoulder;//��۸���
					 //MSJOINT ELbowPi;//��ؽڸ���
					 //MSJOINT ForeArm;//ǰ����ת û�м���λ
					 //MSJOINT WristPi;//��ؽڸ���
					 //MSJOINT WristRo;//��ؽ���ת û�м���λ ��תģʽ �ٶ�-λ��
					 //MSJOINT JawClamp;//��ǯ�г� ��ǯģʽ λ��-����-�н�-����

	unsigned char Frz : 2;//���ּ���-����-����
	unsigned char Hydro : 1;//Һѹ����-�ض�
	unsigned char DynMod : 1;//��̬���� ����-����
	unsigned char MoveRatio : 4;//�˶����� 10%-20%��100%��

	unsigned char JawSpd : 2;//��ǯ�ٶ� ����-����-����-���
	unsigned char Res1 : 6;//�����չ
						   //��19���ֽ� ��������ʱʹ��
	unsigned char key : 3;//���µ����Ǹ���
	unsigned char index : 5;//��ǰ��Ӧ�Ĳ�����ţ��վ�ʱΪ0��
							//��20���ֽ�
	unsigned char asterisk;//'*'
	unsigned short checksum;//У��� ǰ�������ֵ����^
	unsigned short END;//"\r\n"�س�����
} MCMD; //���ַ���������Ϣ

typedef struct
{
	unsigned short pos : 12;//�ؽڷ���ֵ λ��
	unsigned short ctrlErr : 1;//���ƴ���
	unsigned short contiErr : 1;//���������Դ���
	unsigned short overErrA : 1;//���޴���
	unsigned short overErrB : 1;//���޴���
} SMJOINT; //���ָ����ֵĹؽ���Ϣ
typedef struct
{
	unsigned char head;//'S'
	unsigned char id;//����ָʾ�ð����ݵĺ���

	SMJOINT joint[7];//�����ڶ� ��۸��� ��ؽڸ��� ǰ����ת ��ؽڸ��� ��ؽ���ת ��ǯ�г�
					
	unsigned char timeoutErr : 1;//�����������ݳ�ʱ
	unsigned char telemErr : 7;//�͹ؽ�ʧȥ��ϵ �о�û��Ҫ
							 
	unsigned char res1;//����
	unsigned char echo;//����
					   //��20�ֽ�
	unsigned char asterisk;//'*'
	unsigned short checksum;//У��� ǰ�������ֵ����^
	unsigned short END;//"\r\n"�س�����
} SFEED; //���ַ�����Ϣ ������ϴ�Լ��Ҫ12����

typedef struct
{
	unsigned char head;//'S'
	unsigned char id;//����ָʾ�ð����ݵĺ���

	unsigned short scmdPos[7];//�����ڶ� ��۸��� ��ؽڸ��� ǰ����ת ��ؽڸ��� ��ؽ���ת ��ǯ�гֿ�������Ϣ

	unsigned char timeoutErr : 1;//�����������ݳ�ʱ
	unsigned char telemErr : 7;//�͹ؽ�ʧȥ��ϵ �о�û��Ҫ

	unsigned char res1;//����
	unsigned char res2;//����
	unsigned char asterisk;//'*'
	unsigned short checksum;//У��� ǰ�������ֵ����^
	unsigned short END;//"\r\n"�س�����
} SPOS; //����λ�÷�����Ϣ ������ϴ�Լ��Ҫ12����

		//������� ����������ýṹ
		//����ṹ
typedef struct
{
	unsigned char head;//'M' or 'S'
	unsigned char id;//����ָʾ�ð����ݵĺ��� ��Ŵ�100��ʼ
	unsigned short para[8];//7����Ư 7����Сλ�� 7�����λ�� 16*7�����·��ֵ
	unsigned char index;//����
	unsigned char asterisk;//'*'
	unsigned short checksum;//У��� ǰ�������ֵ����^
	unsigned short END;//"\r\n"�س�����
} PARAINFO; //����������Ϣ

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
#endif