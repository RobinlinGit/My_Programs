#include "Bomb.h"

double Bomb::count_time()
{
	double duration=0;
	clock_t temp=clock();
	//if(bomb_state==bomb)
		duration=(double)((temp-start)/CLOCKS_PER_SEC);//返回生成时间
//	else 
		//duration=(double)((temp-finish)/CLOCKS_PER_SEC);//否则返回爆炸时间
	return duration;//返回炸弹持续的时间
}


//将炸弹改为爆炸状态
void Bomb::Boom()
{
	if(count_time()>=boom_cd)
	{
		finish=clock();//给finish下定义
		bomb_state=boom_center;
	}

}

void Bomb::vanish()
{
	if(bomb_state==boom_center&&count_time()>(boom_stay+boom_cd))
		bomb_state=boom_dead;
}

