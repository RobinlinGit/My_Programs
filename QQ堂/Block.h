#pragma once
#include <graphics.h>
#include <stdio.h>
#include "init_all.h"
class QQT_Block
{
protected:
	QQT_Position position;
	int shape;//形状
	int state_boom;//是否可炸开
	int state_through;//是否可通过
public:
	void draw();
	//初始化函数
	QQT_Block(int x,int y,int type):shape(type){position.x=x;position.y=y;state_boom=boom_state[type];state_through=through_state[type];}

};
