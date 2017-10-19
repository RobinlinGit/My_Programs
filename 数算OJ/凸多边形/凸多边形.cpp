#include <iostream>
#include <vector>
using namespace std;
struct Position{
	double x;
	double y;
	bool is_2;
	Position(){ is_2 = false; }
};
//定义坐标结构体

bool whether_2(Position* head, Position* middle, Position* next){
	double x1,y1,x2,y2;
	x1 = middle->x - head->x;
	y1 = middle->y - head->y;
	x2 = next->x - middle->x;
	y2 = next->y - middle->y;
	
	if( (x1*y2 - x2*y1) < 0 )
	{
		middle->is_2 = true;
		return true;
	}
	return false;
}//判断是否凸点，叉积

int main(){
	int pos_num = 0;
	int times = 0;
	cin>>times;
	bool* ok = new bool[times];
	vector<int> pointsStream;
	pointsStream.insert(pointsStream.end(),-1);


	for( int i = 0; i <= times-1; i++) ok[i] = true;
	for( int i = 0; i <= times - 1; i++){
		cin>>pos_num;
		int turns = 0;
		Position* Point = new Position[pos_num];
		for( int j = 0; j <= pos_num-1 ; j++){
			cin>>Point[j].x>>Point[j].y;
		}

		while( turns < pos_num ){
			 if( !whether_2
				( Point + ((pos_num+turns-1)%pos_num),
				  Point + ((pos_num+turns)%pos_num),
				  Point + ((pos_num+turns+1)%pos_num) ) )
				  {
					  ok[i] = false;
			 }
			turns++; 
		}//判断是否凸多边形

		if( !ok[i] ){
			for( int j = 0; j <= pos_num-1; j++)
				if( !Point[j].is_2 )
					pointsStream.insert(pointsStream.end(),j);
			pointsStream.insert(pointsStream.end(),-1);//每段以-1隔开
		}
		
		delete[] Point;
	}

	int count = 0;
	for( int i = 0; i <= times-1; i++){
		if( ok[i] ) cout<<'y';
		else {
			count++;
			while( pointsStream[count] != -1)
				cout<<pointsStream[count++]<<' ';
		}
		cout<<endl;
	}//输出
	getchar();
	getchar();
	return 0;
}
