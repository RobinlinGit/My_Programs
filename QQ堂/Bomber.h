#pragma once
#include "init_All.h"

class Bomber
{
private:
	int mode;
	int blood;//血量
	int speed;//速度
	int bomb_carry_num;//炸弹承载数量，随放置炸弹而变
	int max_carry_bomb;//炸弹最高数量，随吃道具而变
	int bomb_power;//炸弹威力
	QQT_Position center_position;//地图中所处的位置(中心点)
	QQT_Position pixel_position;//图片实际像素起始点
	QQT_Position Game_coordinate;//游戏中人物的坐标
	int state;//图片状态
public:
	Bomber()
	{
		center_position.x=(int)(0.5*map_length*block_size);
		center_position.y=(int)0.5*(map_width*block_size);
		//完成初始化位置
		blood=normal_life;
		speed=basic_speed;
		bomb_carry_num=1;
		state=down;
		init_position();
		bomb_power=1;
		max_carry_bomb=1;
		mode=walk;
	}//完成一个新人物的创建

	void draw();//绘图
	void move( );//移动函数
	void move_to_side(int direction);//在遇到障碍时的移动
	void init_position();//根据像素点来更新坐标
	void eat_prop(int);//吃道具加成
	void put_bomb();//放炸弹
	void recycle_bomb();//回收炸弹
	int change_state(char);//修改状态并返回状态
	void get_attack(int );//收到僵尸攻击

	//以下返回一些数据
	int get_power(){return bomb_power;}
	int get_bomb_carry_num(){return bomb_carry_num;}
	QQT_Position get_coordinate(){return Game_coordinate;}
	QQT_Position get_center(){return center_position;}
	int getSpeed(){return speed;}//返回速度值
	int get_life(){return blood;}

};