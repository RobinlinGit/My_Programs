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
	void process();//�ܹ���
	void action_bomber();//ը���˴���
	void action_zombie();//��ʬ����
	void action_bomb( );//ը����Ϊ����
	void action_map();//��ͼ��Ϊ����
	void action_prop();//������Ϊ����

	void draw();//��ͼ,�������ֻ�ͼ
	void move_bomber(char);//ը���˵��ƶ�
	void create_bomb();//����ը��
	void boom_bomb();//ը����ը


	void zombie_living(Zombie*);//�жϽ�ʬ�Ƿ������������Ļ�ɾ��
	void zombie_attack(Zombie*);//��ʬ����
	void zombie_move(Zombie*);//��ʬ�ƶ�
	



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