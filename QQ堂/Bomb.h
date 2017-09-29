#pragma once
#include "init_All.h"



class Bomb
{
private:
	int power;//ը������
	int bomb_state;
	QQT_Position bomb_coordinate;
	clock_t start,finish,boom_finish;//ը�����ɣ���ը���Լ���ը����
	int low_x,low_y,high_x,high_y;

public:
	Bomb* next;//��һ��ը����λ��
	Bomb(){power=0;bomb_coordinate.x=-1;bomb_coordinate.y=-1;next=NULL;bomb_state=blank;low_x=high_x=bomb_coordinate.x;
	low_y=high_y=bomb_coordinate.y;}
	Bomb(int in_power,QQT_Position temp){power=in_power;bomb_coordinate.x=temp.x;bomb_coordinate.y=temp.y;next=NULL;start=clock();low_x=high_x=bomb_coordinate.x;
	low_y=high_y=bomb_coordinate.y;bomb_state=bomb;}//���캯��


	void delete_bomb();//ɾ��ը��ָ��
	double count_time();
	void Boom();
	void vanish();
	void strength_power(){power++;}

	//��ȡ��Ϣ�ຯ��
	QQT_Position get_Pos(){return bomb_coordinate;}
	int get_Power(){return power;}
	int get_State(){return bomb_state;}

	void record_lo_x(int x){low_x=x;}
	void record_hi_x(int x){high_x=x;}
	void record_lo_y(int y){low_y=y;}
	void record_hi_y(int y){high_y=y;}
	int get_low_x(){return low_x;}
	int get_high_x(){return high_x;}
	int get_low_y(){return low_y;}
	int get_high_y(){return high_y;}
};
