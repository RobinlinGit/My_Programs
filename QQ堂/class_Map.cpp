#include "Map.h"
#include <stdlib.h>
#include <time.h>

//��ͼ����
void Map::draw()
{
	PIMAGE image[9];
	for(int i=0;i<=8;i++)
		image[i]=newimage();
	getimage(image[bomb-1],"ը��.png");
	getimage(image[wood-1],"ľ��.png");
	getimage(image[rock-1],"rock.png");
	getimage(image[floor-1],"��Դ.png");
	getimage(image[shoe-1],"Ь.png");
	getimage(image[medicine-1],"ҩ.png");
	getimage(image[powder-1],"ǿ��ҩ.png");
	getimage(image[diaosu-1],"����.png");
	getimage(image[boom-1],"��ը.png");
	//��ʼ������ͼ��
	
	for(int i=0;i<=map_width-1;i++)
		for(int j=0;j<=map_length-1;j++)
		{
			if(map[i][j]==wood)
			{
				putimage(j*block_size,i*block_size,block_size,block_size,image[wood-1],0,0,55,66);//����Ӧλ�÷�ľ��
			}
			else if(map[i][j]==rock)
			{
				putimage(j*block_size,i*block_size,block_size,block_size,image[rock-1],0,0,41,46);//rock
			}
			else if(map[i][j]==floor)
			{
				putimage(j*block_size,i*block_size,block_size,block_size,image[floor-1],57*2,0,57,57);
			}//��ʱû��û�ʲô
			else if(map[i][j]==shoe)
			{
				putimage(j*block_size,i*block_size,block_size,block_size,image[floor-1],57*2,0,57,57);
				putimage_withalpha(NULL,image[shoe-1],j*block_size,i*block_size,0,0,36,36);
			}
			else if(map[i][j]==medicine)
			{
				putimage(j*block_size,i*block_size,block_size,block_size,image[floor-1],57*2,0,57,57);
				putimage_withalpha(NULL,image[medicine-1],j*block_size,i*block_size,0,0,36,36);
			}
			else if(map[i][j]==powder)
			{
				putimage(j*block_size,i*block_size,block_size,block_size,image[floor-1],57*2,0,57,57);
				putimage_withalpha(NULL,image[powder-1],j*block_size,i*block_size,0,0,32,64);
			}
			else if(map[i][j]==bomb)
			{
				putimage(j*block_size,i*block_size,block_size,block_size,image[floor-1],57*2,0,57,57);
				putimage_withalpha(NULL,image[bomb-1],j*block_size,i*block_size,0,0,36,36);
			}
			else if(map[i][j]==diaosu)
			{
				putimage(j*block_size,i*block_size,block_size,block_size,image[floor-1],57*2,0,57,57);
			}
			else if(map[i][j]==boom
				||map[i][j]==boom_medicine
				||map[i][j]==boom_shoe
				||map[i][j]==boom_power
				||map[i][j]==boom_prop
				||map[i][j]==boom_center)
			{
				
				putimage(j*block_size,i*block_size,block_size,block_size,image[boom-1],0,0,160,160);
			}
			
			//putimage(6*block_size,5*block_size,3*block_size,2*block_size,image[diaosu-1],0,0,147,140);
			//��ɻ�ͼ
			
		}
		putimage_withalpha(NULL,image[diaosu-1],6*block_size,5*block_size,0,0,147,140);
		for(int i=0;i<=8;i++)delimage(image[i]);
}




//�ж��¸������Ƿ��������
bool Map::whether_can_enter(QQT_Position coordinate)
{
	if(coordinate.x>=map_length*block_size)return false;
	else if(coordinate.x<0)return false;
	else if(coordinate.y<0)return false;
	else if(coordinate.y>=map_width*block_size)return false;
	else 
	{
	int type=map[coordinate.y][coordinate.x];
	if(through_state[type]==no_thr)return false;
	else return true;
	}
}


//����Ӧλ�ò���ը��
void Map::produce_bomb(QQT_Position coordinate)
{
	if(map[coordinate.y][coordinate.x]==floor||map[coordinate.y][coordinate.x]==shoe||map[coordinate.y][coordinate.x]==medicine||map[coordinate.y][coordinate.x]==powder)
	{
		map[coordinate.y][coordinate.x]=bomb;
		bomb_num++;
	}
}



//Ԥ�ƶ��ж�,ֻ����Ҫ�жϱ߽�ʱʹ��
bool Map::whether_can_move(QQT_Position center,int direction,int speed)
{
	QQT_Position coordinate;
	coordinate.x=(int)center.x/block_size;
	coordinate.y=(int)center.y/block_size;

	QQT_Position next;

	if(direction==up)
	{
		next.y=center.y-speed;
		next.x=center.x;
		if(next.y<(coordinate.y*block_size+30))return false;
		else return true;
	}
	else if(direction==down)
	{
		next.y=center.y+speed;
		next.x=center.x;
		if(next.y>((coordinate.y+1)*block_size-30))return false;
		else return true;
	}
	else if(direction==left)
	{
		next.x=center.x-speed;
		next.y=center.y;
		if(next.x<(coordinate.x*block_size+20))return false;
		else return true;
	}
	else if(direction==right)
	{
		next.y=center.y;
		next.x=center.x+speed;
		if(next.x>((coordinate.x+1)*block_size-20))return false;
		else return true;
	}
	else return false;
}


//ը����ը

void Map::fresh_map(QQT_Position Pos,int state)
{
	map[Pos.y][Pos.x]=state;
}

//����ͼ���£���Ҫ���ڱ�ը����
void Map::fresh_map(Bomb* chain)
{
	Bomb* head=chain,* second=chain->next;
	//��ֵ

	while(second!=NULL)
	{
		if(second->get_State()==bomb)
			fresh_map(second->get_Pos(),second->get_State());
		else if(second->get_State()==boom_center)
		{
			fresh_map(second->get_Pos(),second->get_State());
			int power=second->get_Power();
			QQT_Position center=second->get_Pos();
			bool found_limit=false;
			//����һЩ����

			for(int i=center.x-1;i>=center.x-power&&i>=0&&(!found_limit);i--)
			{
				switch (boom_state[map[center.y][i]])
				{
				case no_boom:found_limit=true;break;
				case can_boom:{found_limit=true;map[center.y][i]=boom_prop;}break;
				case pass_boom:map[center.y][i]=boom;break;
				case already_boom:break;
				default:
					break;
				}
				second->record_lo_x(i);
			}//��ɺ��������޸�
			

			found_limit=false;
			for(int i=center.x+1;i<=center.x+power&&i<map_length&&(!found_limit);i++)
			{
				switch (boom_state[map[center.y][i]])
				{
					case no_boom:found_limit=true;break;
					case can_boom:{found_limit=true;map[center.y][i]=boom_prop;}break;
					case pass_boom:map[center.y][i]=boom;break;
					case already_boom:break;
					default:
						break;
				}
				second->record_hi_x(i);
			}

			found_limit=false;
			for(int j=center.y-1;(j>=0)&&(j>=center.y-power)&&(!found_limit);j--)
			{
				switch (boom_state[map[j][center.x]])
				{

				
					case can_boom:{found_limit=true;map[j][center.x]=boom_prop;}break;
					case no_boom:found_limit=true;break;
					
					case pass_boom:map[j][center.x]=boom;break;
					case already_boom:break;
					default:
						break;
				}
				second->record_lo_y(j);
			}

			found_limit=false;
			for(int j=center.y+1;j<map_width&&j<=center.y+power&&(!found_limit);j++)
			{
				switch (boom_state[map[j][center.x]])
				{
					case no_boom:found_limit=true;break;
					case can_boom:{found_limit=true;map[j][center.x]=boom_prop;}break;
					case pass_boom:map[j][center.x]=boom;break;
					case already_boom:break;
					default:
						break;
				}
				second->record_hi_y(j);
			}//���ը����ը�Է���Ӱ��
		}
		
		//����Ϊ����������ը���Ĵ���
		else if(second->get_State()==boom_dead)
		{
			fresh_map(second->get_Pos(),floor);
			QQT_Position center=second->get_Pos();

			for(int i=second->get_low_x();i<=second->get_high_x();i++)
			{
				switch (map[center.y][i])
				{
				case boom:map[center.y][i]=floor;break;
				case boom_shoe:map[center.y][i]=shoe;break;
				case boom_medicine:map[center.y][i]=medicine;break;
				case boom_power:map[center.y][i]=powder;break;
				case boom_prop:attribute_prop(center.y,i);break;
				default:
					break;
				}
			}
			for(int j=second->get_low_y();j<=second->get_high_y();j++)
			{
				switch (map[j][center.x])
				{
				case boom:map[j][center.x]=floor;break;
				case boom_shoe:map[j][center.x]=shoe;break;
				case boom_medicine:map[j][center.x]=medicine;break;
				case boom_power:map[j][center.x]=powder;break;
				case boom_prop:attribute_prop(j,center.x);break;
				default:
					break;
				}
			}
			//ѭ����͵�

			
		}
		second=second->next;
		head=head->next;
	}
}



//�������,�Ѵﵽ���Ч��
void Map::attribute_prop(int i,int j)
{
	int randly_num=0;
	srand(i*(-20123)+j*2017+(short)time(NULL));
	randly_num=(rand()%(powder-floor+1))+floor;

		map[i][j]=randly_num;
	
}

bool Map::zombie_hurt(QQT_Position coor)
{
	if(map[coor.x][coor.y]==boom||
		map[coor.x][coor.y]==boom_center||
		map[coor.x][coor.y]==boom_medicine||
		map[coor.x][coor.y]==boom_shoe||
		map[coor.x][coor.y]==boom_power||
		map[coor.x][coor.y]==boom_prop
		)
		return true;
	else 
		return false;

}