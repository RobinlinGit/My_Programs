#pragma once
//位置参数
#include <graphics.h>
#include <time.h>
struct QQT_Position
{
	int x;
	int y;
};//位置


//炸弹人参数
#define dead 0			//死亡
#define normal_life 5	//正常生命
#define max_carry_num 8	//最大携带炸弹量
#define max_speed  12
#define basic_speed 4
#define max_carry 9
#define walk 10086
#define bubble 12306



//Block的各个参量
#define pass_boom    -1 //没有炸这回事
#define no_boom 0		//不可炸开
#define already_boom 12314
#define can_boom 1		//是否可炸开
#define can_thr  2		//可穿过
#define no_thr   3		//不可穿过


#define boom_cd 2.789	//爆炸时间
#define boom_stay 0.2 //爆炸停留时间
#define max_power 8     //最大炸药威力


//方块类型
#define block 0
#define bomb 1			//炸弹	
#define wood 2			//木块
#define rock 3			//岩石
#define floor 4
//道具类型
#define shoe 5
#define medicine 6		//加强炸弹强度
#define powder 7		//加强炸弹数量

#define diaosu 8		//雕塑


#define boom   9        //炸弹爆炸时的效果

//保持道具的存在而设常量
#define boom_shoe  10
#define boom_medicine 11
#define boom_power    12
#define boom_prop     13   //代表需要道具分配方块
#define boom_center    14
#define boom_dead     2018



//各方块的state表
const int boom_state[15]={pass_boom,no_boom,can_boom,can_boom,pass_boom,pass_boom,pass_boom,pass_boom,no_boom,
	already_boom,already_boom,already_boom,already_boom,already_boom,already_boom};//定义是否可被爆炸
const int through_state[9]={no_thr,no_thr,no_thr,no_thr,can_thr,can_thr,can_thr,can_thr,no_thr};//定义是否可过的表


//道具的时间
#define props_time 8

//地图界面的绘画
#define block_size 49
#define map_length 15
#define map_width  13

//地图对于人物中心位置的界限
#define up_side 30
#define down_side (map_width*block_size-30)
#define right_side (map_length*block_size-20)
#define left_side 20

//定义初始化的所有方块
const int MAP1[13][15]={
	3,3,3,3,4,4,4,4,4,4,4,3,3,3,3,
	3,4,3,4,2,2,2,4,2,2,2,4,3,3,3,
	3,3,4,2,4,3,4,2,4,3,4,2,4,3,3,
	3,4,2,4,3,3,3,3,3,3,3,4,2,4,3,
	3,4,2,3,3,3,3,3,3,3,3,3,2,4,3,
	3,4,2,4,3,3,8,8,8,3,3,4,2,4,3,
	3,4,2,3,3,3,8,8,8,3,3,3,2,4,3,
	3,3,4,2,4,3,8,8,8,3,4,2,4,3,3,
	3,3,3,4,2,3,3,3,3,3,2,4,3,3,3,
	3,3,3,3,4,2,4,3,4,2,4,3,3,3,3,
	3,3,4,3,3,4,2,2,2,4,3,3,4,3,3,
	3,4,4,3,3,3,4,4,4,3,3,3,4,4,3,
	3,4,4,3,3,3,3,3,3,3,3,3,4,4,3,
};//地图1的各个数据

//bomber的移动指令集
#define up 2001
#define down 2002
#define right 2003
#define left 2004
#define blank 0

#define zombie_alive 2019
#define zombie_dead  2020

#define easy 1111
#define middle 2222
#define hard   3333

const QQT_Position zombie_Pos[4]={{70,40},{(int)12.5*block_size,(int)2.5*block_size},
								{(int)2*block_size,(int)10*block_size},{(int)13*block_size,(int)10*block_size}};

