#include "Bomber.h"

void Bomber::draw()
{
	PIMAGE image_bomber;
	image_bomber=newimage();
	getimage(image_bomber,"走图.png");
	switch (state)
	{
	case left:putimage_withalpha(NULL,image_bomber,pixel_position.x,pixel_position.y,0,100,100,100);break;
	case right:putimage_withalpha(NULL,image_bomber,pixel_position.x,pixel_position.y,0,200,100,100);break;
	case up:putimage_withalpha(NULL,image_bomber,pixel_position.x,pixel_position.y,0,300,100,100);break;
	case down:putimage_withalpha(NULL,image_bomber,pixel_position.x,pixel_position.y,0,0,100,100);break;
	default:
		break;
	}
	if(mode==bubble)
	{
		circle(center_position.x,center_position.y,16+(5-blood)*3);
	}
	delimage(image_bomber);
}
//确定方块格
void Bomber::init_position()
{
	pixel_position.x=center_position.x-50;
	pixel_position.y=center_position.y-75;//实际图片像素描绘起始点
	Game_coordinate.x=(int)center_position.x/block_size;
	Game_coordinate.y=(int)center_position.y/block_size;//描述人物在游戏中的坐标
}

//移动画图函数
void Bomber::move()
{
	
	switch (state)
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

void Bomber::move_to_side(int direction)
{
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
}//只能运动值边界的情况下


void Bomber::eat_prop(int prop_type)
{
	switch (prop_type)
	{
	case shoe:if(speed<=max_speed)speed+=1;break;
	case powder:if(bomb_power<=max_power)bomb_power++;break;
	case medicine:if(bomb_carry_num<=max_carry){bomb_carry_num++;max_carry_bomb++;}break;
	case boom:blood--;mode=bubble;break;
	case boom_center:blood--;mode=bubble;break;
	case boom_shoe:blood--;mode=bubble;break;
	case boom_medicine:blood--;mode=bubble;break;
	case boom_power:blood--;mode=bubble;break;
	case boom_prop:blood--;mode=bubble;break;
	default:
		break;
	}
}//完成对吃入道具后的数据修改

void Bomber::put_bomb()
{
	if(bomb_carry_num>0)bomb_carry_num--;
}//放置炸弹后对本身数据的影响

void Bomber::recycle_bomb()
{
	if(bomb_carry_num<max_carry_bomb)
		bomb_carry_num++;
}
//炸弹爆炸后的回收

int Bomber::change_state(char in_ch)
{
	switch (in_ch)
	{
	case 'w':state=up;break;
	case 's':state=down;break;
	case 'a':state=left;break;
	case 'd':state=right;break;
	case 'W':state=up;break;
	case 'S':state=down;break;
	case 'A':state=left;break;
	case 'D':state=right;break;
	default:
		break;
	}
	return state;
}//修改状态

void Bomber::get_attack(int _attack)
{
	blood-=_attack;
}