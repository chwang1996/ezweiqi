#ifndef __DISTANCEMAPMOVE_H__
#define __DISTANCEMAPMOVE_H__

#include <iostream>
#include <vector>
#include "ezweiqiAI.h"
using namespace std;
struct correction_factor{
	int x;
	int y;
};

struct Area{
	int x[196];
	int y[196];
	int size;
};
float SetDisMap(int board[14][14],int turns,bool limit);
correction_factor center_correct(int chess,int direction,int center);
int* DistanceMapMove(int board[14][14],int turns,bool chess_remain[18],vector<MCTNode*>,int type);
int* GetDistanceMapMove(int board[14][14],int turns,bool chess_remain[18],vector<MCTNode*> existpos);
int GetSingleDistanceMapMove(int board[14][14],int turns,bool chess_remain[18],vector<MCTNode*> existpos);
int GetSingleDistanceMapMoveAcc(int board[14][14],int turns,bool chess_remain[18],vector<MCTNode*> existpos);
int rollout(int board[14][14],int turns,bool chess_remain[18],int depth,int type);//type for different AIs PK
#endif