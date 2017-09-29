#include "Process.h"


//总过程
void Process::process()
{
	while(bomber.get_life()>0&&zombie_num!=0)
	{
		delay_fps(60);
		cleardevice();
		action_bomber();//炸弹人的行为判断，包括掉血，吃道具，移动
		action_zombie();//僵尸移动，死亡，攻击玩家
		action_bomb();//全场炸弹处理，包括爆炸，威力
		action_prop();
		action_map();//全场地图信息处理
		draw();
	}
	if(bomber.get_life()<=0)
	{
		setfont(50,0,"微软雅黑");
		outtextxy(6*block_size,4*block_size,"失败");
	}
	else if(zombie_num==0)
	{
		setfont(18,0,"微软雅黑");
		outtextxy(6*block_size,4*block_size,"胜利！");
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
	//吃道具加血量判断
}

//对于整个游戏界面的绘制
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




//接受键盘信息后bomber做出的反应//还有死亡判定啥的还没写
void Process::action_bomber()
{
	



	char k=' ';
	if((GetKeyState('a')<0)||(GetKeyState('A')<0))k='a';
	else if((GetKeyState('d')<0)||(GetKeyState('D')<0))k='d';
	else if((GetKeyState('w')<0)||(GetKeyState('W')<0))k='w';
	else if((GetKeyState('s')<0)||(GetKeyState('S')<0))k='s';
	//获取键盘被按下情况

	if(k=='w'||k=='s'||k=='a'||k=='d'||k=='W'||k=='S'||k=='A'||k=='D')
		move_bomber(k);
	
	
	
}

//炸弹人的移动，基本正确
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
		||(Game_map.whether_can_move(bomber.get_center(),direction,bomber.getSpeed())))//如果下个方块是可穿过的或者距离还未到穿过
	{
		bomber.move();
	}
	else bomber.move_to_side(direction);//否则只能限制在方格内//待测试

}





//接受键盘信息与时间信息后的有光炸弹信息的反馈
void Process::action_bomb()
{
	create_bomb();//判断是否下弹
	boom_bomb();
					

}


//根据炸弹人位置来制造炸弹
void Process::create_bomb()
{
	if(GetKeyState(' ')<0)//若空格被按下
	{	
		int type=Game_map.get_type(bomber.get_coordinate().y,bomber.get_coordinate().x);
		if(bomber.get_bomb_carry_num()>0&&type!=bomb&&type!=rock&&type!=wood&&type!=diaosu)
		{
			bomber.put_bomb();
			Game_map.produce_bomb(bomber.get_coordinate());

			Bomb* new1=new Bomb(bomber.get_power(),bomber.get_coordinate());//构造一个炸弹

			class_bomb_num++;
			Bomb* p=&bomb_chain_head;
			while(p->next!=NULL)p=p->next;
			p->next=new1;//链表操作,为末尾添加一个
		}
	}
}



//对炸弹的处理
void Process::boom_bomb()
{
	Bomb* bomb_on_field=bomb_chain_head.next;//赋值，第一个炸弹
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
		
		//while循环结束

	
}


//僵尸行为
void Process::action_zombie()
{
	zombie_living(&zombie_on_field);
	zombie_attack(&zombie_on_field);
	zombie_move(&zombie_on_field);
}


//判定是否死亡
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

//位置如果重合，则减血
void Process::zombie_attack(Zombie* head)
{
	for(int i=0;i<=3;i++)
	{
		if((head->get_State()==zombie_alive)&&(head->get_coordinate().x==bomber.get_coordinate().x&&head->get_coordinate().y==bomber.get_coordinate().y))//如果位置相同
		{
			bomber.get_attack(head->get_Attack());
		}
		//if(head->next!=NULL)
			head=head->next;
	}
}

//僵尸移动，采用随机情况
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
				head->random_walk_mod();//给其随机赋予一个方向
			}
			
		}
		if(head->next!=NULL)
			head=head->next;
	}
}
void Process::action_map()
{
	//先使炸弹的状态改变
	Bomb *temp= &bomb_chain_head;
	Game_map.fresh_map(temp);
}

