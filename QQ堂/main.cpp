#include <iostream>
#include <stdio.h>
#include "init_All.h"
#include "Process.h"

using namespace std;
void start()
{
	initgraph(800,600);
	PIMAGE start;
	start=newimage();
	getimage(start,"开始画面.png");
	putimage(0,0,800,600,start,0,0,800,600);
	setfontbkcolor(NULL);
	setfont(30,0,"微软雅黑");
	outtextxy(50,50,"1、开始游戏");
	outtextxy(50,100,"2、退出(输入选项后回车确认)");
	delimage(start);
}
void second_pic()
{
		initgraph(1024,768);
		PIMAGE new_pic=newimage();
		getimage(new_pic,"新开始画面.png");
		putimage(0,0,1024,768,new_pic,0,0,1024,768);
		setfont(32,0,"微软雅黑");
		setfontbkcolor(NULL);
		outtextxy(400,50,"选择难度:");
		outtextxy(400,100,"1/简单");
		outtextxy(400,150,"2/中等");
		outtextxy(400,200,"3/困难");
		delimage(new_pic);
}
int main()
{

	start();
	Sleep(1000);
	char choice[10];
	inputbox_getline("输入选项","输入单个数字后回车",choice,9);
	while(choice[0]!='1'&&choice[0]!='2')
		inputbox_getline("重新输入选项","输入单个数字后回车",choice,9);
	while(choice[0]=='1')
	{

		closegraph();
		second_pic();//第二界面

		char temp[10];
		inputbox_getline("输入数字选项:","务必只输入一个数字",temp,9);
		while(temp[0]!='1'&&temp[0]!='2'&&temp[0]!='3')
		{
			inputbox_getline("重新输入数字选项:","务必只输入一个数字",temp,1);
		}
		int rank=0;
		switch (temp[0])
		{
		case '1':rank=easy;break;
		case '2':rank=middle;break;
		case '3':rank=hard;break;
		default:
			break;
		}//输入模式难度
		outtextxy(450,380,"正在进入游戏,wasd移动，空格安放炸弹");
		outtextxy(450,430,"当泡泡（玩家周围圆圈过大时)，死亡");
		Sleep(2000);

		closegraph();

		initgraph(map_length*block_size,map_width*block_size);//初始化背景
		Process Pro(MAP1,rank);
		Pro.process();
		getch();
		closegraph();

		//循环开始界面
		start();
		inputbox_getline("输入选项","输入单个数字后回车",choice,9);
		while(choice[0]!='1'&&choice[0]!='2')
			inputbox_getline("重新输入选项","输入单个数字后回车",choice,9);
	}	


	if(choice[0]=='2')
	{
		outtextxy(300,200,"ByeBye!");
		Sleep(2000);
		closegraph();
	}
	


	
	return 0;
}



/*	QQT_Position temp={7,7};
	Bomb test(12,temp);
	Bomb test_head;
	test_head.next=&test;
	Map game(MAP1);
	while(1)
	{
		if(test.count_time()>(boom_cd+boom_stay))
			test.vanish();
		else if(test.count_time()>boom_cd)
			test.Boom();
		game.fresh_map(&test_head);
		game.draw();
		
	}*/