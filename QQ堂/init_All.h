#pragma once
//λ�ò���
#include <graphics.h>
#include <time.h>
struct QQT_Position
{
	int x;
	int y;
};//λ��


//ը���˲���
#define dead 0			//����
#define normal_life 5	//��������
#define max_carry_num 8	//���Я��ը����
#define max_speed  12
#define basic_speed 4
#define max_carry 9
#define walk 10086
#define bubble 12306



//Block�ĸ�������
#define pass_boom    -1 //û��ը�����
#define no_boom 0		//����ը��
#define already_boom 12314
#define can_boom 1		//�Ƿ��ը��
#define can_thr  2		//�ɴ���
#define no_thr   3		//���ɴ���


#define boom_cd 2.789	//��ըʱ��
#define boom_stay 0.2 //��ըͣ��ʱ��
#define max_power 8     //���ըҩ����


//��������
#define block 0
#define bomb 1			//ը��	
#define wood 2			//ľ��
#define rock 3			//��ʯ
#define floor 4
//��������
#define shoe 5
#define medicine 6		//��ǿը��ǿ��
#define powder 7		//��ǿը������

#define diaosu 8		//����


#define boom   9        //ը����ըʱ��Ч��

//���ֵ��ߵĴ��ڶ��賣��
#define boom_shoe  10
#define boom_medicine 11
#define boom_power    12
#define boom_prop     13   //������Ҫ���߷��䷽��
#define boom_center    14
#define boom_dead     2018



//�������state��
const int boom_state[15]={pass_boom,no_boom,can_boom,can_boom,pass_boom,pass_boom,pass_boom,pass_boom,no_boom,
	already_boom,already_boom,already_boom,already_boom,already_boom,already_boom};//�����Ƿ�ɱ���ը
const int through_state[9]={no_thr,no_thr,no_thr,no_thr,can_thr,can_thr,can_thr,can_thr,no_thr};//�����Ƿ�ɹ��ı�


//���ߵ�ʱ��
#define props_time 8

//��ͼ����Ļ滭
#define block_size 49
#define map_length 15
#define map_width  13

//��ͼ������������λ�õĽ���
#define up_side 30
#define down_side (map_width*block_size-30)
#define right_side (map_length*block_size-20)
#define left_side 20

//�����ʼ�������з���
const int MAP1[13][15]={
	3,3,3,3,4,4,4,4,4,4,4,3,3,3,3,
	3,4,3,4,2,2,2,4,2,2,2,4,3,3,3,
	3,3,4,2,4,3,4,2,4,3,4,2,4,3,3,
	3,4,2,4,3,3,3,3,3,3,3,4,2,4,3,
	3,4,2,3,3,3,3,3,3,3,3,3,2,4,3,
	3,4,2,4,3,3,8,8,8,3,3,4,2,4,3,
	3,4,2,3,3,3,8,8,8,3,3,3,2,4,3,
	3,3,4,2,4,3,8,8,8,3,4,2,4,3,3,
	3,3,3,4,2,3,3,3,3,3,2,4,3,3,3,
	3,3,3,3,4,2,4,3,4,2,4,3,3,3,3,
	3,3,4,3,3,4,2,2,2,4,3,3,4,3,3,
	3,4,4,3,3,3,4,4,4,3,3,3,4,4,3,
	3,4,4,3,3,3,3,3,3,3,3,3,4,4,3,
};//��ͼ1�ĸ�������

//bomber���ƶ�ָ�
#define up 2001
#define down 2002
#define right 2003
#define left 2004
#define blank 0

#define zombie_alive 2019
#define zombie_dead  2020

#define easy 1111
#define middle 2222
#define hard   3333

const QQT_Position zombie_Pos[4]={{70,40},{(int)12.5*block_size,(int)2.5*block_size},
								{(int)2*block_size,(int)10*block_size},{(int)13*block_size,(int)10*block_size}};

