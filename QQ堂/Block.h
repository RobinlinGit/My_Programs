#pragma once
#include <graphics.h>
#include <stdio.h>
#include "init_all.h"
class QQT_Block
{
protected:
	QQT_Position position;
	int shape;//��״
	int state_boom;//�Ƿ��ը��
	int state_through;//�Ƿ��ͨ��
public:
	void draw();
	//��ʼ������
	QQT_Block(int x,int y,int type):shape(type){position.x=x;position.y=y;state_boom=boom_state[type];state_through=through_state[type];}

};
