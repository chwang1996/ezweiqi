#ifndef __MOVE_H__
#define __MOVE_H__

#include <iostream>
#include <vector>
using namespace std;
class Move{
public:
	int x;
	int y;
	int dir;
	int chess_type;
	int getID(){return 10000*x+100*y+10*dir+chess_type;}
	void show(){cout<<"m = "<<x<<","<<y<<","<<dir<<","<<chess_type<<endl;}
	void setMove(int id){chess_type=id%10; dir=(id%100)/10; y=(id%10000)/100; x=id/10000;}
	void setMove(int x,int y,int dir,int chess_type){this->x=x; this->y=y; this->dir=dir; this->chess_type=chess_type;}
	Move(){x=0;y=0;dir=0;chess_type=0;}
	Move(int x,int y,int dir,int chess_type){this->x=x; this->y=y; this->dir=dir; this->chess_type=chess_type;}
	Move(int id){setMove(id);};
};
#endif