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
	getimage(start,"��ʼ����.png");
	putimage(0,0,800,600,start,0,0,800,600);
	setfontbkcolor(NULL);
	setfont(30,0,"΢���ź�");
	outtextxy(50,50,"1����ʼ��Ϸ");
	outtextxy(50,100,"2���˳�(����ѡ���س�ȷ��)");
	delimage(start);
}
void second_pic()
{
		initgraph(1024,768);
		PIMAGE new_pic=newimage();
		getimage(new_pic,"�¿�ʼ����.png");
		putimage(0,0,1024,768,new_pic,0,0,1024,768);
		setfont(32,0,"΢���ź�");
		setfontbkcolor(NULL);
		outtextxy(400,50,"ѡ���Ѷ�:");
		outtextxy(400,100,"1/��");
		outtextxy(400,150,"2/�е�");
		outtextxy(400,200,"3/����");
		delimage(new_pic);
}
int main()
{

	start();
	Sleep(1000);
	char choice[10];
	inputbox_getline("����ѡ��","���뵥�����ֺ�س�",choice,9);
	while(choice[0]!='1'&&choice[0]!='2')
		inputbox_getline("��������ѡ��","���뵥�����ֺ�س�",choice,9);
	while(choice[0]=='1')
	{

		closegraph();
		second_pic();//�ڶ�����

		char temp[10];
		inputbox_getline("��������ѡ��:","���ֻ����һ������",temp,9);
		while(temp[0]!='1'&&temp[0]!='2'&&temp[0]!='3')
		{
			inputbox_getline("������������ѡ��:","���ֻ����һ������",temp,1);
		}
		int rank=0;
		switch (temp[0])
		{
		case '1':rank=easy;break;
		case '2':rank=middle;break;
		case '3':rank=hard;break;
		default:
			break;
		}//����ģʽ�Ѷ�
		outtextxy(450,380,"���ڽ�����Ϸ,wasd�ƶ����ո񰲷�ը��");
		outtextxy(450,430,"�����ݣ������ΧԲȦ����ʱ)������");
		Sleep(2000);

		closegraph();

		initgraph(map_length*block_size,map_width*block_size);//��ʼ������
		Process Pro(MAP1,rank);
		Pro.process();
		getch();
		closegraph();

		//ѭ����ʼ����
		start();
		inputbox_getline("����ѡ��","���뵥�����ֺ�س�",choice,9);
		while(choice[0]!='1'&&choice[0]!='2')
			inputbox_getline("��������ѡ��","���뵥�����ֺ�س�",choice,9);
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