#include "Bomb.h"

double Bomb::count_time()
{
	double duration=0;
	clock_t temp=clock();
	//if(bomb_state==bomb)
		duration=(double)((temp-start)/CLOCKS_PER_SEC);//��������ʱ��
//	else 
		//duration=(double)((temp-finish)/CLOCKS_PER_SEC);//���򷵻ر�ըʱ��
	return duration;//����ը��������ʱ��
}


//��ը����Ϊ��ը״̬
void Bomb::Boom()
{
	if(count_time()>=boom_cd)
	{
		finish=clock();//��finish�¶���
		bomb_state=boom_center;
	}

}

void Bomb::vanish()
{
	if(bomb_state==boom_center&&count_time()>(boom_stay+boom_cd))
		bomb_state=boom_dead;
}

