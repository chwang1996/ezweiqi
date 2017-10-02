#ifndef __GAMEBOARD_H__
#define __GAMEBOARD_H__

#include <iostream>
#include <vector>
using namespace std;

class GameBoard
{
private:
	void coloring(int board[14][14],int q[200],int q_size,int reference,int color,int type);
public:
    GameBoard();
	GameBoard(int board[14][14]);
	GameBoard(GameBoard,vector<pair<int,int> >,int,int);
    void set_value(int,int,int);
    int get_value(int,int);
    void show();
	int get_score(int);
	void cal_area();
	int result();
	int final_result();
	void show_result();
	
    int board[14][14];
	bool chess_remain[18];
	int chess_remain_num[2];
	int p1_score,p2_score;
};
bool set_cover(vector< pair<int,int> > &cover,int chess,int position_x,int position_y,int direction);
void show_chesstype();
#endif
