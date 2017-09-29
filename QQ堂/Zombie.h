#pragma once
#include "Bomber.h"

class Zombie
{
private:
	int blood;
	int speed;
	int attack;
	int state;//��ʬ״̬
	int pic_state;//ͼƬ״̬
	QQT_Position center_position;//��ͼ��������λ��(���ĵ�)
	QQT_Position pixel_position;//ͼƬʵ��������ʼ��
	QQT_Position Game_coordinate;//��Ϸ�����������

	


public:
	Zombie(int mode,QQT_Position Pos);//����ģʽ����ʼ����ʬ
	Zombie* next;

	void init_position();
	int  random_walk_mod();//�������ģʽ,Ĭ��Ϊ�����1Ϊ��������
	void move(int direction);//���߷���
	void move_to_side(int direction);
	void search_mod();//׷��ģʽ��AI
	void vanish();//��������
	void draw();

	int get_Blood(){return blood;}
	QQT_Position get_coordinate(){return Game_coordinate;}
	int get_Attack(){return attack;}
	int get_State(){return state;}
	int get_Pic_state(){return pic_state;}
	QQT_Position get_center(){return center_position;}
	int get_Speed(){return speed;}


};