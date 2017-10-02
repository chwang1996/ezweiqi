#ifndef __EZWEIQIAI_H__
#define __EZWEIQIAI_H__

#include <iostream>
#include <vector>
#include "Move.h"
using namespace std;
class MCTNode
{
public:
	MCTNode();
	MCTNode(int);
	MCTNode(MCTNode* p,int i,int pid,Move m);
	MCTNode* parent;
	vector<MCTNode*> children;
	int wins;
	int visits;
	int id,player_id;
	int board[14][14];
	bool chess_remain[18];
	int chess_remain_num[2];
	int *cachelist,cache_index;
	
};

class MCTS
{	
private:
	class UCT{
		public:
		double coeff;
		int wi;
		int ni;
		int total;		
		double calculate(int w_i,int n_i,int total_i);
		UCT();
	};
	void deletion(MCTNode* node);
public:
	MCTNode* root;
	MCTS();
	MCTS(int);
	void selection(int);
	void expansion(MCTNode*);
	void simulation(MCTNode*);
	void backpropagation(MCTNode*,bool);
	Move getBestPos();
	void show();
	void move(Move m);
	int player_id;
	Move best_move;
};

class ezweiqiAI
{
private:
	MCTS* mcts;
public:
	ezweiqiAI();
	ezweiqiAI(int);
	void update(Move m);
	void think();
	void show();
	Move move();
};
#endif
