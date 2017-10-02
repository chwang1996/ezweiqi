#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include "DistanceMapMove.h"
//#include "RandomMove.h"
#include "ezweiqiAI.h"
#include "GameBoard.h"
#include <time.h>
#include <stdlib.h>
#include <cmath>
#include <sys/time.h>
#include <thread>

using namespace std;
int ts=0;
MCTNode::MCTNode()
{
	wins=0;
	visits=0;
	id=0;
	player_id=1;
	for(int i=0;i<14;i++){ for(int j=0;j<14;j++)board[i][j]=0;};
	for(int i=0;i<18;i++)chess_remain[i]=true;
	chess_remain_num[0]=9;
	chess_remain_num[1]=9;
	parent=NULL;
	cache_index=0;
}
MCTNode::MCTNode(int pid)
{
	wins=0;
	visits=0;
	id=0;
	player_id=pid;
	for(int i=0;i<14;i++){ for(int j=0;j<14;j++)board[i][j]=0;};
	for(int i=0;i<18;i++)chess_remain[i]=true;
	chess_remain_num[0]=9;
	chess_remain_num[1]=9;
	parent=NULL;
	cache_index=0;
}
MCTNode::MCTNode(MCTNode* p,int i,int pid,Move m)
{
	wins=0;
	visits=0;
	id=i;
	player_id=(pid==1)?2:1;
	for(int i=0;i<14;i++){ for(int j=0;j<14;j++)board[i][j]=p->board[i][j];};
	for(int i=0;i<18;i++)chess_remain[i]=p->chess_remain[i];

	vector< pair<int,int> > cover;
	cover.clear();
	set_cover(cover,m.chess_type,m.x,m.y,m.dir);
	for(int i=0;i<cover.size();i++)board[cover[i].second][cover[i].first]=pid;
	chess_remain[m.chess_type+(pid-1)*9]=false;
	chess_remain_num[0]=p->chess_remain_num[0];
	chess_remain_num[1]=p->chess_remain_num[1];
	chess_remain_num[pid-1]--;
	parent=p;
	cover.clear();
	cache_index=0;
}

MCTS::UCT::UCT()
{
	coeff=sqrt(2.0);
	wi=0;
	ni=0;
	total=0;
}
double MCTS::UCT::calculate(int w_i,int n_i,int total_i)
{
	double a,b;
	try{
		if(w_i<0 || n_i<0 || total_i<=0)
			throw "Uct wrong!!";
		a=(double)w_i/(double)n_i;
		b=sqrt((log((double)total_i)/(double)n_i));
		return a+b*coeff;
	}
	catch(const char* message){
		cout<<message<<endl;
		exit(1);
	}
}
MCTS::MCTS()
{
	srand(time(NULL));//since rollout will be called many times, the time seed will be the same in 1 sec; so srand(time(NULL)) at first to avoid the same random result
	root = new MCTNode();
	player_id=1;
}
MCTS::MCTS(int pid)
{
	srand(time(NULL));//since rollout will be called many times, the time seed will be the same in 1 sec; so srand(time(NULL)) at first to avoid the same random result
	root = new MCTNode(1);
	player_id=pid;

}
void MCTS::deletion(MCTNode* node)
{
	MCTNode *parent=node,*current;
	if(node->children.size()>0)current=node->children[0];
	else{
		delete node;
		return;
	}
	while(node->children.size()>0){
		if(current->children.size()>0){
			parent=current;
			current=current->children[0];
		}else{
			parent->children.erase(parent->children.begin());
			delete current;
			if(parent->children.size()>0){
				current=parent->children[0];
			}else{
				current=parent;
				if(parent->parent==root)break;
				parent=parent->parent;
			}
		}
	}
	delete node;
}
void MCTS::selection(int simulation_count)
{
	int n_total=simulation_count,count;
	double uct_max,uct_visit;
	UCT uct;
//	MCTNode *target,*current,*parent;
	vector<int> childcount;
	MCTNode *target=root,*current=root;
	while(simulation_count--){
		current=root;
		target=current;
		while(current->children.size()>0){
			n_total=current->visits+1;
			uct_max=0;
			for(int i=0;i<current->children.size();i++){
				uct_visit=uct.calculate(current->children[i]->wins,current->children[i]->visits+1,n_total);
				if(uct_max<uct_visit){
					target=current->children[i];
					uct_max=uct_visit;
				}
			}
			if(root->children.size()<8)break;
			else if(current->children.size()<5)break;
			current=target;
		}
		expansion(current);
	}
	
/*	while(simulation_count--){
		current=root;
		target=current;
		if(root->children.size()<100){
			target = root;
		}else{
			while(current->children.size()>0){
				n_total=current->visits+1;
				uct_max=0;
				for(int i=0;i<current->children.size();i++){
					uct_visit=uct.calculate(current->children[i]->wins,current->children[i]->visits+1,n_total);
					if(uct_max<uct_visit ){
						target=current->children[i];
						uct_max=uct_visit;
					}
				}
				current=target;
			}
		}
		expansion(target);
	}*/
//	cout<<simulation_count<<" Before simulation root id = "<<root->id<<", children = ";
//	for(int i=0;i<root->children.size();i++) cout<<root->children[i]->id<<" ";
//	cout<<endl;
//----------------------------------------------------------------------------------	
//	cout<<"After, children = ";
//	for(int i=0;i<root->children.size();i++) cout<<root->children[i]->id<<" ";
//	cout<<endl;
/*	while(simulation_count--){
		//initial
		//n_total=root->visits+1;
		uct_max=0;
		count=root->children.size();
		if(count>20){
			parent = root;
			current = root;
			childcount.push_back(count);
		}else current = root;
		target = current;
		//traversal
		cout<<"-------------- "<<simulation_count<<" -----------"<<endl;
		while(childcount.size()>0){
			
			if(childcount.back()==0){//no child or its children finish calcuation
				//calculate 
				uct_visit=uct.calculate(current->wins,current->visits+1,n_total);
				cout<<current->id<<" : "<<uct_visit<<endl;
				if(uct_max<=uct_visit){
					target=current;
					uct_max=uct_visit;
				}
				//change to its parent
				childcount.pop_back();
				if(childcount.size()==0)break;
				count = childcount.back()-1;
				childcount.back() = count;
				current = parent;
				if(parent->parent)
					parent = parent->parent;
			}else{//have children, choose the rightest child to be the current node
				parent = current;
				current = current->children[count-1];
				count=current->children.size();
				childcount.push_back(current->children.size());
			}
		}
		//expansion
		if(target->parent)
		cout<<"target = "<<target->id<<", parent = "<<target->parent->id<<" --> ";
		expansion(target);
	}*/
}
void MCTS::expansion(MCTNode* current)
{
	Move m;
	int id;
//	int *bestlist,best_index=0;
	if(current->chess_remain_num[current->player_id-1]>7){
		 id=GetSingleDistanceMapMove(current->board,current->player_id,current->chess_remain,current->children);
	}
	else{
		if(current->cache_index==0){
			current->cachelist=GetDistanceMapMove(current->board,current->player_id,current->chess_remain,current->children);
		}
		id=current->cachelist[current->cache_index];
		if(id!=999999){
			if(current->cache_index<8)current->cache_index++;
		}
	}
	char a;
	if(id==999999||id>140000||id<10100){
	/*	cout<<"return from illegal = "<<id<<endl;
		cout<<"current board = "<<current->id<<current->cache_index<<endl;
		cout<<"current child["<<current->cache_index<<"] = "<<current->cachelist[current->cache_index]<<endl;
		cin>>a;*/
		return;
	}
	bool randomagain=false;
	MCTNode* child;
//	while(1){
    	randomagain=false;
		for(int i=0;i<current->children.size();i++){
			if(id == current->children[i]->id){
				randomagain=true;
				child=current->children[i];
				break;
			}
		}
/*		if(!randomagain)break;
		else id=getRandomMove(current->board,current->player_id,current->chess_remain);
	}*/
	if(!randomagain){
		m.setMove(id);
		child = new MCTNode(current,id,current->player_id,m);
		current->children.push_back(child);
	}	
	ts++;
	simulation(child);
}
void rollout_M(int b[14][14],int turns,bool chess_r[18],int depth,int* winner,int type){
	*winner = rollout(b,turns,chess_r,depth,type);
}
void MCTS::simulation(MCTNode* current)
{/*	struct timeval start,end;
	int sec,usec;
	gettimeofday(&start,0);*/
	int winner[4];
	int depth=(current->player_id == 2)?10:11;
	bool win = false;
//	win = rollout(current->board,current->player_id,current->chess_remain,depth)==player_id ? true : false;
//	backpropagation(current,win);
	if(player_id == 2){
//		win = rollout(current->board,current->player_id,current->chess_remain,depth,1)==player_id ? true : false;
//		backpropagation(current,win);
		thread MT0(bind(&rollout_M,current->board,current->player_id,current->chess_remain,depth,winner,3));
		thread MT1(bind(&rollout_M,current->board,current->player_id,current->chess_remain,depth,winner+1,3));
		thread MT2(bind(&rollout_M,current->board,current->player_id,current->chess_remain,depth,winner+2,3));
		thread MT3(bind(&rollout_M,current->board,current->player_id,current->chess_remain,depth,winner+3,3));

		MT0.join();
		MT1.join();
		MT2.join();
		MT3.join();
		for(int i=0;i<4;i++){
			win = winner[0]==player_id? true:false;
			backpropagation(current,win);
		}		

	}
	else //win = randomRollout(current->board,current->player_id,current->chess_remain)==player_id ? true : false;
	{
	
		thread MT0(bind(&rollout_M,current->board,current->player_id,current->chess_remain,depth,winner,1));
		thread MT1(bind(&rollout_M,current->board,current->player_id,current->chess_remain,depth,winner+1,1));
		thread MT2(bind(&rollout_M,current->board,current->player_id,current->chess_remain,depth,winner+2,1));
		thread MT3(bind(&rollout_M,current->board,current->player_id,current->chess_remain,depth,winner+3,1));

		MT0.join();
		MT1.join();
		MT2.join();
		MT3.join();
		for(int i=0;i<4;i++){
			win = winner[0]==player_id? true:false;
			backpropagation(current,win);
		}		
	}

/*	thread MT0(bind(&rollout_M,current->board,current->player_id,current->chess_remain,depth,winner));
	thread MT1(bind(&rollout_M,current->board,current->player_id,current->chess_remain,depth,winner+1));
	thread MT2(bind(&rollout_M,current->board,current->player_id,current->chess_remain,depth,winner+2));
	thread MT3(bind(&rollout_M,current->board,current->player_id,current->chess_remain,depth,winner+3));

	MT0.join();
	MT1.join();
	MT2.join();
	MT3.join();
	for(int i=0;i<4;i++){
		win = winner[0]==player_id? true:false;
		backpropagation(current,win);
	}*/
/*	gettimeofday(&end,0);
	sec = end.tv_sec - start.tv_sec;
	usec = end.tv_usec - start.tv_usec;
	float t = (sec*1000+(usec/1000.0));*/
//	printf("simulation time = %f\n",t);
}

void MCTS::backpropagation(MCTNode* target,bool win)
{
	MCTNode* current=target;
	while(target != root){
		if(win)
			target->wins++;
		target->visits++;
		target=target->parent;
	}
	if(win)
		target->wins++;
	target->visits++;
}
void MCTS::show()
{
	cout<<"root = "<<root->id<<endl;
	GameBoard game(root->board);
	game.show();
	int n_total,count;
	double uct_max,uct_visit;
	UCT uct;
	MCTNode *target,*current,*parent;
	vector<int> childcount;
	//initial
	n_total=root->visits+1;
	uct_max=0;
	count=root->children.size();
	if(count>0){
		parent = root;
		current = root;
		childcount.push_back(count);
	}else current = root;
	target = current;
	
	//traversal
	while(childcount.size()>0){
		if(childcount.back()==0){//no child or its children finish calcuation
			//show
			cout<<"Current = "<<current->id<<", parent = "<<parent->id<<" --> ";
			for(int i = 0;i<current->children.size();i++)
				cout<<current->children[i]->id<<" ";
			cout<<endl;
				//change to its parent
				childcount.pop_back();
				if(childcount.size()==0)break;
				count = childcount.back()-1;
				childcount.back() = count;
				current = parent;
				if(parent->parent)
					parent = parent->parent;
		}else{//have children, choose the rightest child to be the current node
			parent = current;
			current = current->children[count-1];
			count=current->children.size();
			childcount.push_back(count);
		}
	}
	
}
Move MCTS::getBestPos()
{
	MCTNode *target=root->children[0]; 
	double uct_max=0,uct_visit;
	for(int i=0;i<root->children.size();i++){
		uct_visit=(double)root->children[i]->wins/(double)root->children[i]->visits;
		if(uct_max<uct_visit){
			target=root->children[i];
			uct_max=uct_visit;
		}
	}
	
	Move m(target->id);
	cout<<endl;
	return m;
}
void MCTS::move(Move m)
{
	MCTNode* current = root,*newroot=NULL;
	int id = m.getID();
	for(int i=0;i<current->children.size();i++){
		if(id != current->children[i]->id)deletion(current->children[i]);
		else newroot=current->children[i];
	}
	current->children.clear();
	if(newroot == NULL)	newroot = new MCTNode(root,id,root->player_id,m);
	//delete current;
	root=newroot;
}
ezweiqiAI::ezweiqiAI()
{
	mcts = new MCTS();
	int id,t=18;
	MCTNode*  newroot=mcts->root;
	while(t--){
		cin>>id;
		Move m(id);
		m.show();
		newroot = new MCTNode(newroot,id,newroot->player_id,m);		
		mcts->simulation(newroot);
	}
}
ezweiqiAI::ezweiqiAI(int pid){
	mcts = new MCTS(pid);
}
void ezweiqiAI::update(Move m)
{
	mcts->move(m);
}
void ezweiqiAI::show()
{
	mcts->show();
}

void ezweiqiAI::think()
{
	struct timeval start,end;
	int sec,usec;
	float limit=3000.0f,sum=0;
	int c=0;
	ts=0;
	while(sum<limit){
		gettimeofday(&start,0);
		int simulation_count =10;//(mcts->player_id == 1)?1000:250;
		mcts->selection(simulation_count);
		gettimeofday(&end,0);
		sec = end.tv_sec - start.tv_sec;
		usec = end.tv_usec - start.tv_usec;
		float t = (sec*1000+(usec/1000.0));
		sum+=t;
		if(simulation_count/t>100);//cout<<"! "<<c<<endl;
		else		c++;
		//printf("Total time = %f, average time per sec= %f\n",t,1000*simulation_count/t);
	}
	cout<<"c = "<<ts<<endl;
}
Move ezweiqiAI::move()
{
	Move m = mcts->getBestPos();
	mcts->move(m);
	return m;
}