#pragma once
#include "Bomber.h"

class Zombie
{
private:
	int blood;
	int speed;
	int attack;
	int state;//僵尸状态
	int pic_state;//图片状态
	QQT_Position center_position;//地图中所处的位置(中心点)
	QQT_Position pixel_position;//图片实际像素起始点
	QQT_Position Game_coordinate;//游戏中人物的坐标

	


public:
	Zombie(int mode,QQT_Position Pos);//根据模式来初始化僵尸
	Zombie* next;

	void init_position();
	int  random_walk_mod();//随机行走模式,默认为随机，1为记忆行走
	void move(int direction);//行走方向
	void move_to_side(int direction);
	void search_mod();//追踪模式，AI
	void vanish();//受伤消亡
	void draw();

	int get_Blood(){return blood;}
	QQT_Position get_coordinate(){return Game_coordinate;}
	int get_Attack(){return attack;}
	int get_State(){return state;}
	int get_Pic_state(){return pic_state;}
	QQT_Position get_center(){return center_position;}
	int get_Speed(){return speed;}


};