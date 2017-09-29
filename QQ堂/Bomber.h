#pragma once
#include "init_All.h"

class Bomber
{
private:
	int mode;
	int blood;//Ѫ��
	int speed;//�ٶ�
	int bomb_carry_num;//ը�����������������ը������
	int max_carry_bomb;//ը�������������Ե��߶���
	int bomb_power;//ը������
	QQT_Position center_position;//��ͼ��������λ��(���ĵ�)
	QQT_Position pixel_position;//ͼƬʵ��������ʼ��
	QQT_Position Game_coordinate;//��Ϸ�����������
	int state;//ͼƬ״̬
public:
	Bomber()
	{
		center_position.x=(int)(0.5*map_length*block_size);
		center_position.y=(int)0.5*(map_width*block_size);
		//��ɳ�ʼ��λ��
		blood=normal_life;
		speed=basic_speed;
		bomb_carry_num=1;
		state=down;
		init_position();
		bomb_power=1;
		max_carry_bomb=1;
		mode=walk;
	}//���һ��������Ĵ���

	void draw();//��ͼ
	void move( );//�ƶ�����
	void move_to_side(int direction);//�������ϰ�ʱ���ƶ�
	void init_position();//�������ص�����������
	void eat_prop(int);//�Ե��߼ӳ�
	void put_bomb();//��ը��
	void recycle_bomb();//����ը��
	int change_state(char);//�޸�״̬������״̬
	void get_attack(int );//�յ���ʬ����

	//���·���һЩ����
	int get_power(){return bomb_power;}
	int get_bomb_carry_num(){return bomb_carry_num;}
	QQT_Position get_coordinate(){return Game_coordinate;}
	QQT_Position get_center(){return center_position;}
	int getSpeed(){return speed;}//�����ٶ�ֵ
	int get_life(){return blood;}

};