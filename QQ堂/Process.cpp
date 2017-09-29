#include "Process.h"


//�ܹ���
void Process::process()
{
	while(bomber.get_life()>0&&zombie_num!=0)
	{
		delay_fps(60);
		cleardevice();
		action_bomber();//ը���˵���Ϊ�жϣ�������Ѫ���Ե��ߣ��ƶ�
		action_zombie();//��ʬ�ƶ����������������
		action_bomb();//ȫ��ը������������ը������
		action_prop();
		action_map();//ȫ����ͼ��Ϣ����
		draw();
	}
	if(bomber.get_life()<=0)
	{
		setfont(50,0,"΢���ź�");
		outtextxy(6*block_size,4*block_size,"ʧ��");
	}
	else if(zombie_num==0)
	{
		setfont(18,0,"΢���ź�");
		outtextxy(6*block_size,4*block_size,"ʤ����");
	}
}


void Process::action_prop()
{
	int stand_type=Game_map.get_type(bomber.get_coordinate().y,bomber.get_coordinate().x);
	if(stand_type==shoe||stand_type==medicine||stand_type==powder||
		stand_type==boom_center||stand_type==boom||
		stand_type==boom_shoe||stand_type==boom_medicine||stand_type==boom_power)
	{
		bomber.eat_prop(stand_type);
		Game_map.fresh_map(bomber.get_coordinate(),floor);
	}
	//�Ե��߼�Ѫ���ж�
}

//����������Ϸ����Ļ���
void Process::draw()
{
	
	Game_map.draw();
	bomber.draw();
	Zombie* temp=&zombie_on_field;
	for(int i=0;i<=3;i++)
	{
		if(temp->get_State()==zombie_alive)
			temp->draw();
		temp=temp->next;
	}
	delete temp;
}




//���ܼ�����Ϣ��bomber�����ķ�Ӧ//���������ж�ɶ�Ļ�ûд
void Process::action_bomber()
{
	



	char k=' ';
	if((GetKeyState('a')<0)||(GetKeyState('A')<0))k='a';
	else if((GetKeyState('d')<0)||(GetKeyState('D')<0))k='d';
	else if((GetKeyState('w')<0)||(GetKeyState('W')<0))k='w';
	else if((GetKeyState('s')<0)||(GetKeyState('S')<0))k='s';
	//��ȡ���̱��������

	if(k=='w'||k=='s'||k=='a'||k=='d'||k=='W'||k=='S'||k=='A'||k=='D')
		move_bomber(k);
	
	
	
}

//ը���˵��ƶ���������ȷ
void Process::move_bomber(char k)
{
	int direction=bomber.change_state(k);
	QQT_Position next=bomber.get_coordinate();
	switch (direction)
	{
	case up:next.y--;break;
	case down:next.y++;break;
	case left:next.x--;break;
	case right:next.x++;break;
	default:
		break;
	}
	
	if(Game_map.whether_can_enter(next)
		||(Game_map.whether_can_move(bomber.get_center(),direction,bomber.getSpeed())))//����¸������ǿɴ����Ļ��߾��뻹δ������
	{
		bomber.move();
	}
	else bomber.move_to_side(direction);//����ֻ�������ڷ�����//������

}





//���ܼ�����Ϣ��ʱ����Ϣ����й�ը����Ϣ�ķ���
void Process::action_bomb()
{
	create_bomb();//�ж��Ƿ��µ�
	boom_bomb();
					

}


//����ը����λ��������ը��
void Process::create_bomb()
{
	if(GetKeyState(' ')<0)//���ո񱻰���
	{	
		int type=Game_map.get_type(bomber.get_coordinate().y,bomber.get_coordinate().x);
		if(bomber.get_bomb_carry_num()>0&&type!=bomb&&type!=rock&&type!=wood&&type!=diaosu)
		{
			bomber.put_bomb();
			Game_map.produce_bomb(bomber.get_coordinate());

			Bomb* new1=new Bomb(bomber.get_power(),bomber.get_coordinate());//����һ��ը��

			class_bomb_num++;
			Bomb* p=&bomb_chain_head;
			while(p->next!=NULL)p=p->next;
			p->next=new1;//�������,Ϊĩβ���һ��
		}
	}
}



//��ը���Ĵ���
void Process::boom_bomb()
{
	Bomb* bomb_on_field=bomb_chain_head.next;//��ֵ����һ��ը��
	Bomb* head=&bomb_chain_head;

	
		for(int i=0;i<=class_bomb_num-1;i++)
		{
			switch(bomb_on_field->get_State())
			{
			case bomb:
				{
					if(bomb_on_field->count_time()>boom_cd)
					{
						bomb_on_field->Boom();
						head=bomb_on_field;
						bomb_on_field=bomb_on_field->next;
						bomber.recycle_bomb();
					}
			    }break;
			case boom_center:
				{
					if(bomb_on_field->count_time()>boom_cd+boom_stay)
					{
						bomb_on_field->vanish();
						head=bomb_on_field;
						bomb_on_field=bomb_on_field->next;
					}
				}break;
			case boom_dead:
				{
					Game_map.fresh_map(bomb_on_field->get_Pos(),floor);
					head->next=bomb_on_field->next;
					Bomb *temp= bomb_on_field;
					bomb_on_field=head->next;
					delete temp;
					class_bomb_num--;
				}
			}
		}
		
		//whileѭ������

	
}


//��ʬ��Ϊ
void Process::action_zombie()
{
	zombie_living(&zombie_on_field);
	zombie_attack(&zombie_on_field);
	zombie_move(&zombie_on_field);
}


//�ж��Ƿ�����
void Process::zombie_living(Zombie* head)
{
	for(int i=0;i<=3;i++)
	{
		QQT_Position temp=head->get_coordinate();
		
		if(Game_map.zombie_hurt(head->get_coordinate()))
		{	head->vanish();if(head->get_State()==zombie_dead)zombie_num--;}
			head=head->next;
	}
}

//λ������غϣ����Ѫ
void Process::zombie_attack(Zombie* head)
{
	for(int i=0;i<=3;i++)
	{
		if((head->get_State()==zombie_alive)&&(head->get_coordinate().x==bomber.get_coordinate().x&&head->get_coordinate().y==bomber.get_coordinate().y))//���λ����ͬ
		{
			bomber.get_attack(head->get_Attack());
		}
		//if(head->next!=NULL)
			head=head->next;
	}
}

//��ʬ�ƶ�������������
void Process::zombie_move(Zombie* head)
{
	for(int i=0;i<=3;i++)
	{
		QQT_Position next_Pos=head->get_coordinate();
		if(head->get_State()==zombie_alive)
		{
			switch (head->get_Pic_state())
			{
			case up:next_Pos.y--;break;
			case down:next_Pos.y++;break;
			case left:next_Pos.x--;break;
			case right:next_Pos.x++;break;
			default:
				break;
			}
			if(Game_map.whether_can_enter(next_Pos)||Game_map.whether_can_move(head->get_center(),head->get_Pic_state(),head->get_Speed()))
				{head->move(head->get_Pic_state());}
			else 
			{
				head->move_to_side(head->get_Pic_state());
				head->random_walk_mod();//�����������һ������
			}
			
		}
		if(head->next!=NULL)
			head=head->next;
	}
}
void Process::action_map()
{
	//��ʹը����״̬�ı�
	Bomb *temp= &bomb_chain_head;
	Game_map.fresh_map(temp);
}

