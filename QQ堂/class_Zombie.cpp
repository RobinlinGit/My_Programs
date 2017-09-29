#include "Zombie.h"

Zombie::Zombie(int mode,QQT_Position Pos)
{
	next=NULL;
	center_position=Pos;
	init_position();
	state=zombie_alive;
	pic_state=down;
	

	if(mode==easy)
	{
		blood=1;
		attack=1;
		speed=basic_speed;
	}
	else if(mode==middle)
	{
		blood=2;
		attack=2;
		speed=basic_speed+3;
	}
	else if(mode==hard)
	{
		blood=3;
		attack=5;
		speed=max_speed;
	}
}

void Zombie::init_position()
{
	pixel_position.x=center_position.x-50;
	pixel_position.y=center_position.y-75;//实际图片像素描绘起始点
	Game_coordinate.x=(int)center_position.x/block_size;
	Game_coordinate.y=(int)center_position.y/block_size;//描述人物在游戏中的坐标
}
void Zombie::draw()
{
	PIMAGE image_zombie;
	image_zombie=newimage();
	getimage(image_zombie,"恶魔.png");
	switch (pic_state)
	{
	case left:putimage_withalpha(NULL,image_zombie,pixel_position.x,pixel_position.y,0,100,100,100);break;
	case right:putimage_withalpha(NULL,image_zombie,pixel_position.x,pixel_position.y,0,200,100,100);break;
	case up:putimage_withalpha(NULL,image_zombie,pixel_position.x,pixel_position.y,0,300,100,100);break;
	case down:putimage_withalpha(NULL,image_zombie,pixel_position.x,pixel_position.y,0,0,100,100);break;
	default:
		break;
	}
	delimage(image_zombie);
}//绘图

void Zombie::move(int direction)
{
	pic_state=direction;
	switch (pic_state)
	{
	case up:center_position.y=center_position.y-speed>=up_side?center_position.y-speed:up_side;break;
	case down:center_position.y=center_position.y+speed<=down_side?center_position.y+speed:down_side;break;
	case left:center_position.x=center_position.x-speed>=left_side?center_position.x-speed:left_side;break;
	case right:center_position.x=center_position.x+speed<=right_side?center_position.x+speed:right_side;break;
	default:
		break;
	}
	init_position();//由此更新所有的位置数据
}

void Zombie::move_to_side(int direction)
{
	pic_state=direction;
	switch (direction )
	{
	case up:center_position.y=Game_coordinate.y*block_size+30;break;
	case down:center_position.y=(Game_coordinate.y+1)*block_size-30;break;
	case left:center_position.x=(Game_coordinate.x)*block_size+30;break;
	case right:center_position.x=(Game_coordinate.x+1)*block_size-30;break;
	default:
		break;
	}
	init_position();
}

void Zombie::vanish()
{
	if(blood>0)blood--;
	if(blood<=0)state=zombie_dead;
}

int Zombie::random_walk_mod()
{
	int i=center_position.x,j=center_position.y;
	int random_num=i*2013-j*2018;
	srand((short)time(NULL)+random_num);
	random_num=(rand()%(left-up+1))+up;
	pic_state=random_num;
	return random_num;
}