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
	void draw();//绘图，按各个方块，根据传入的数组
	
	void attribute_prop(int,int);//分配道具

	int get_type(int i,int j){return map[i][j];}

	bool whether_can_move(QQT_Position center,int direction,int speed);//在地图上是否可过方块
	bool whether_can_enter(QQT_Position);
	void produce_bomb(QQT_Position);//产生一个炸弹
	void BOOM(QQT_Position,int);//减少一个炸弹，附带其余爆炸效果
	int get_bomb_num(){return bomb_num;}
	bool zombie_hurt(QQT_Position);

	void fresh_map(QQT_Position,int state);//重载
	//void fresh_map();//更新地图上的爆炸并分配道具
	void fresh_map(Bomb* chain);//将炸弹链表直接传入



	Map(const int map_type[map_width][map_length])
	{
		for(int i=0;i<=map_width-1;i++)
			for(int j=0;j<=map_length-1;j++)
				map[i][j]=map_type[i][j];
		bomb_num=0;
		//完成赋值
	}
};