#include <iostream>
#include <vector>
#include "GameBoard.h"
#include "ezweiqiAI.h"
#include "Move.h"
#include "sys/time.h"
#include <unistd.h>
#include "DistanceMapMove.h"
//#define PC 2
#define GAMER 1
#define INFINITY 100000
/*int main(){
	int board[14][14];
	for(int i=0;i<14;i++){
		for(int j=0;j<14;j++){
			if(i==0 || j == 0)board[i][j]=0;
			else cin>>board[i][j];			
		}
	}
	for(int i=0;i<14;i++){
		for(int j=0;j<14;j++){
			cout<<board[i][j]<<" ";
		}
		cout<<endl;
	}
	GameBoard game(board);
	struct timeval start,end;
	int sec,usec;
	gettimeofday(&start,0);
	SetDisMap(board,1,false);
	//game.show_result();
	//SetDisMap(board,1);
	gettimeofday(&end,0);
	sec = end.tv_sec - start.tv_sec;
	usec = end.tv_usec - start.tv_usec;
	float t = (sec*1000+(usec/1000.0));
	cout<<"Total time = "<<t<<" ms."<<endl;

	return 0;
}*/
/*
int main(){
	int times=10,p1_wins=0,p2_wins=0;
	int count=times;
	cout<<"compete "<<times<<" times."<<endl;
		 
	while(count-- >0){
		cout<<"compete "<<(times-count)<<endl;
		GameBoard gameboard;
		ezweiqiAI P1(1),P2(2);
		int c=9;
		char a;
		vector<pair<int,int> > cover;
		Move m;
		while(gameboard.chess_remain_num[0]>0){
			cout<<"P1 turn:"<<endl;
			cout<<"P1 think"<<endl;
			P1.think();
			cout<<"P1 move"<<endl;
			m = P1.move();
			cout<<"P1 m = "<<m.x<<","<<m.y<<","<<m.dir<<","<<m.chess_type<<endl;
			set_cover(cover,m.chess_type,m.x,m.y,m.dir);
			for(int i=0;i<cover.size();i++)gameboard.board[cover[i].second][cover[i].first]=1;
			gameboard.chess_remain_num[0]--;
			gameboard.chess_remain[m.chess_type]=false;
			P2.update(m);
			cout<<"P2 update"<<endl<<endl;
			gameboard.show();
			cover.clear();

			cout<<"P2 turn:"<<endl;
			P2.think();
			m = P2.move();
			cout<<"P2 m = "<<m.x<<","<<m.y<<","<<m.dir<<","<<m.chess_type<<endl;
			set_cover(cover,m.chess_type,m.x,m.y,m.dir);
			for(int i=0;i<cover.size();i++)gameboard.board[cover[i].second][cover[i].first]=2;
			gameboard.chess_remain_num[1]--;
			gameboard.chess_remain[m.chess_type+9]=false;
			P1.update(m);
			cout<<"P1 update"<<endl<<endl;
			cover.clear();
			gameboard.show();
			cout<<"------------------------------"<<endl;
		}
		gameboard.show_result();
		if(gameboard.result()==1)p1_wins++;
		else if(gameboard.result()==2)p2_wins++;
		cout<<"p1 win rate = "<<(float)p1_wins/(float)(times-count)<<endl;
		cout<<"p2 win rate = "<<(float)p2_wins/(float)(times-count)<<endl;

	}
	cout<<"Result:"<<endl;
	cout<<"p1 win rate = "<<(float)p1_wins/(float)times<<endl;
	cout<<"p2 win rate = "<<(float)p2_wins/(float)times<<endl;
	return 0;
}
*/
bool first_four_step = true;


int main()
{
    string player1="player1",player2="player2";  //player name

    GameBoard gameboard;
	cout<<"Test Test Test"<<endl;
	ezweiqiAI AI(2);
	
    vector<pair<int,int> > cover;  //each turn the chosen cover on the board

    int hold_x,hold_y;
    int recover_x,recover_y;
	Move m;

    int turn_who = 1;
    int chess_chosen,position_x,position_y,direction_chosen;
    //bool first_four_step = true;

    while(gameboard.chess_remain_num[0]>0||gameboard.chess_remain_num[1]>0)  //two player's chess are all used, the game is over
    {
        if(gameboard.chess_remain_num[0]+gameboard.chess_remain_num[1]<=14)first_four_step = false;


        show_chesstype();
        //show remain chess
        cout<<player1<<" chess remain: ";
        for(int i=0;i<9;i++)if(gameboard.chess_remain[i])cout<<i;

        cout<<endl;

        cout<<player2<<" chess remain: ";
        for(int i=0;i<9;i++)if(gameboard.chess_remain[9+i])cout<<i;

        cout<<endl;

        if(turn_who == 1)cout<<"Turn to "<<player1<<endl;
        else if(turn_who == 2)cout<<"Turn to "<<player2<<endl;


        cout<<endl;
        gameboard.show();

        cout<<"Choose chess ,position and direction from the remains"<<endl;

        //choose chess and store on the board
        if(first_four_step)
        {
            bool step_check;

            while(1)
            {
                bool cover_origin = false;  //if the player's chosen didn't cover the original four position, choose again
                bool choose_again = false;  //if the player chosen the position which isn't match the rule, choose again

                cout<<"You need to cover the (4,4)(10,4)(4,10)(10,10) at first four step"<<endl;
                cout<<"Input type: (Chess_chosen,position_x,position_y,direction)"<<endl;
                cin>>chess_chosen>>position_x>>position_y>>direction_chosen;
				cover.clear();
                //not follow the type
                if(position_x<1||position_x>13||position_y<1||position_y>13||direction_chosen<0||direction_chosen>3)continue;
                if(turn_who == 1&&!gameboard.chess_remain[chess_chosen])continue;
                else if(turn_who == 2&&!gameboard.chess_remain[9+chess_chosen])continue;

                step_check = set_cover(cover,chess_chosen,position_x,position_y,direction_chosen);    //check the chosen exceed the board or not
				m.setMove(position_x,position_y,direction_chosen,chess_chosen);
                if(step_check)
                {
                    for(int i=0;i<cover.size();i++)
                    {

                        hold_x=cover[i].first;
                        hold_y=cover[i].second;
                        cout<<"("<<hold_x<<","<<hold_y<<")"<<endl;
						
                        if(gameboard.get_value(hold_x,hold_y)!=0)//the cover is chosen before
                        {
                            choose_again = true;
                            cout<<"you cover the chess chosen before"<<endl;
                            break;
                        }

                       gameboard.set_value(hold_x,hold_y,turn_who);//store cover in the board

                        if((hold_x==4&&hold_y==4)||(hold_x==4&&hold_y==10)||(hold_x==10&&hold_y==4)||(hold_x==10&&hold_y==10))cover_origin = true;

                        if(i==cover.size()-1&&!cover_origin) choose_again = true;
                    }
                }
                else
                {
                    cover.clear();
                    continue; //exceed the board, choose again
                }

                if(choose_again)
                {

                    for(int i=0;i<cover.size();i++) //return to origin
                    {
                        recover_x=cover[i].first;
                        recover_y=cover[i].second;
                        if(recover_x!=hold_x ||recover_y!=hold_y)  gameboard.set_value(recover_x,recover_y,0);
                        else break;
                    }
                    cover.clear();
                    continue;
                }
                cover.clear();
                break;
            }

        }
        else  //not the first four step
        {
            bool step_check;

            while(1)
            {
                bool connect_chosen = false;  //if the player's chosen didn't connect the chess on the board, choose again
                bool choose_again = false;  //if the player chosen the position which isn't match the rule, choose again

                cout<<"Your step and the your chess on the board need connect together"<<endl;
                cout<<"Input type: (Chess_chosen,position_x,position_y,direction)"<<endl;
                cin>>chess_chosen>>position_x>>position_y>>direction_chosen;
				cover.clear();
                //not follow the type
                if(position_x<1||position_x>13||position_y<1||position_y>13||direction_chosen<0||direction_chosen>3)continue;

                step_check = set_cover(cover,chess_chosen,position_x,position_y,direction_chosen);    //check the chosen exceed the board or not
				m.setMove(position_x,position_y,direction_chosen,chess_chosen);
                if(step_check)
                {
                    for(int i=0;i<cover.size();i++)
                    {
                        hold_x=cover[i].first;
                        hold_y=cover[i].second;
                        if(gameboard.get_value(hold_x,hold_y)!=0)//the cover is chosen before
                        {
                            cout<<"you cover the chess chosen before"<<endl;
                            choose_again = true;
                            break;
                        }


                        //store cover in the board
                        //(the different from this step and the previous step, use 3 as temp, if this step is match the rule, it would turn to the player's ID)
                        gameboard.set_value(hold_x,hold_y,3);


                        //if connect
                        if((gameboard.get_value(hold_x+1,hold_y)==turn_who)||(gameboard.get_value(hold_x-1,hold_y)==turn_who)||(gameboard.get_value(hold_x,hold_y+1)==turn_who)||
                           (gameboard.get_value(hold_x,hold_y-1)==turn_who)) connect_chosen = true;


                        if(i==cover.size()-1&&!connect_chosen) choose_again = true;
                    }
                }
                else
                {
                    cover.clear();
                    continue; //exceed the board, choose again
                }

                if(choose_again)
                {
                    for(int i=0;i<cover.size();i++) //return to origin
                    {
                        recover_x=cover[i].first;
                        recover_y=cover[i].second;
                        if(recover_x!=hold_x ||recover_y!=hold_y)  gameboard.set_value(recover_x,recover_y,0);
                        else break;
                    }
                    cover.clear();
                    continue;
                }
                else //set the temp to the player's ID
                {
                    for(int i=0;i<cover.size();i++)
                    {
                        hold_x=cover[i].first;
                        hold_y=cover[i].second;
                        gameboard.set_value(hold_x,hold_y,turn_who);
                    }
                }
                cover.clear();
                break;
            }
        }
		gameboard.show();
		AI.update(m);
       //turn to another player
        if(turn_who == 1)
        {
            gameboard.chess_remain[chess_chosen] = false;
            gameboard.chess_remain_num[0]--;
            turn_who = 2;
        }
        else if(turn_who == 2)
        {
            gameboard.chess_remain[9+chess_chosen] = false;
            gameboard.chess_remain_num[1]--;
            turn_who = 1;
        }
		cout<<"------Ai turn------"<<endl;
		while(1){
			AI.think();
			m = AI.move();
			cout<<"In main m = "<<m.x<<","<<m.y<<","<<m.dir<<","<<m.chess_type<<endl;
			cover.clear();
			bool step_check = set_cover(cover,m.chess_type,m.x,m.y,m.dir);    //check the chosen exceed the board or not
			if(step_check)break;
		}
		for(int i=0;i<cover.size();i++){
			hold_x=cover[i].first;
			hold_y=cover[i].second;
			gameboard.set_value(hold_x,hold_y,turn_who);//store cover in the board	
		}
        if(turn_who == 1)
        {
            gameboard.chess_remain[m.chess_type] = false;
            gameboard.chess_remain_num[0]--;
            turn_who = 2;
        }
        else if(turn_who == 2)
        {
            gameboard.chess_remain[9+m.chess_type] = false;
            gameboard.chess_remain_num[1]--;
            turn_who = 1;
        }
        cout<<"------------------------------------------------------------"<<endl;
        gameboard.show();
        cout<<"------------------------------------------------------------"<<endl;
        cout<<"p1 chess remain = "<<gameboard.chess_remain_num[0]<<endl;
        cout<<"p2 chess remain = "<<gameboard.chess_remain_num[1]<<endl;
    }
	gameboard.final_result();
    return 0;
}
