#include "Bomber.h"
#include "Block.h"
#include "Bomb.h"
#include "Map.h"
#include "Zombie.h"
#include <WinUser.h>

class Process
{
private:
	Map Game_map;
	Bomber bomber;
	Zombie zombie_on_field;
	Bomb bomb_chain_head;
	int mode;
	int zombie_num;
	int class_bomb_num;

public:
	void process();//总过程
	void action_bomber();//炸弹人处理
	void action_zombie();//僵尸处理
	void action_bomb( );//炸弹行为处理
	void action_map();//地图行为处理
	void action_prop();//道具行为处理

	void draw();//绘图,包含各种绘图
	void move_bomber(char);//炸弹人的移动
	void create_bomb();//创造炸弹
	void boom_bomb();//炸弹爆炸


	void zombie_living(Zombie*);//判断僵尸是否死亡，死亡的话删除
	void zombie_attack(Zombie*);//僵尸进攻
	void zombie_move(Zombie*);//僵尸移动
	



	Process(const int map_type[map_width][map_length],int mod):Game_map(map_type),zombie_on_field(mod,zombie_Pos[0]),mode(mod)
	{
		class_bomb_num=0;
		zombie_num=4;
		Zombie *temp=new Zombie(mode,zombie_Pos[1]);
		Zombie *temp2=new Zombie(mode,zombie_Pos[2]);
		Zombie *temp3=new Zombie(mode,zombie_Pos[3]);
		zombie_on_field.next=temp;
		temp->next=temp2;
		temp2->next=temp3;
	};

	
};