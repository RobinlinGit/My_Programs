#pragma once
#include"init_All.h"
#include <graphics.h>
#include "Bomb.h"

class Map
{
private:
	int map[map_width][map_length];
	int bomb_num;
public:
	void draw();//��ͼ�����������飬���ݴ��������
	
	void attribute_prop(int,int);//�������

	int get_type(int i,int j){return map[i][j];}

	bool whether_can_move(QQT_Position center,int direction,int speed);//�ڵ�ͼ���Ƿ�ɹ�����
	bool whether_can_enter(QQT_Position);
	void produce_bomb(QQT_Position);//����һ��ը��
	void BOOM(QQT_Position,int);//����һ��ը�����������౬ըЧ��
	int get_bomb_num(){return bomb_num;}
	bool zombie_hurt(QQT_Position);

	void fresh_map(QQT_Position,int state);//����
	//void fresh_map();//���µ�ͼ�ϵı�ը���������
	void fresh_map(Bomb* chain);//��ը������ֱ�Ӵ���



	Map(const int map_type[map_width][map_length])
	{
		for(int i=0;i<=map_width-1;i++)
			for(int j=0;j<=map_length-1;j++)
				map[i][j]=map_type[i][j];
		bomb_num=0;
		//��ɸ�ֵ
	}
};