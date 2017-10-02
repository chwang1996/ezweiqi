#include "GameBoard.h"
#include <iostream>
#include <vector>
#define PC 2
#define GAMER 1
#define INFINITY 100000
#define AI_depth 3
using namespace std;
/*
chesstype
0.       1.          2.         3.          4.
*			+           +*        *+             *
*          ***         **          **          **+
*
+


5.          6.        7.        8.
*             +*        +           +
+**           **

direction
    0

3        1

    2

board
    1   2   3   4   5   6   7   8   9   10  11  12  13
   ----------------------------------------------------
1 |   |   |   |   |   |   |   |   |   |   |   |   |   |
  |----------------------------------------------------
2 |   |   |   |   |   |   |   |   |   |   |   |   |   |
  |----------------------------------------------------
3 |   |   |   |   |   |   |   |   |   |   |   |   |   |
  |----------------------------------------------------
4 |   |   |   |   |   |   |   |   |   |   |   |   |   |
  |----------------------------------------------------
5 |   |   |   |   |   |   |   |   |   |   |   |   |   |
  |----------------------------------------------------
6 |   |   |   |   |   |   |   |   |   |   |   |   |   |
  |----------------------------------------------------
7 |   |   |   |   |   |   |   |   |   |   |   |   |   |
  |----------------------------------------------------
8 |   |   |   |   |   |   |   |   |   |   |   |   |   |
  |----------------------------------------------------
9 |   |   |   |   |   |   |   |   |   |   |   |   |   |
  |----------------------------------------------------
10|   |   |   |   |   |   |   |   |   |   |   |   |   |
  |----------------------------------------------------
11|   |   |   |   |   |   |   |   |   |   |   |   |   |
  |----------------------------------------------------
12|   |   |   |   |   |   |   |   |   |   |   |   |   |
  |----------------------------------------------------
13|   |   |   |   |   |   |   |   |   |   |   |   |   |
  |----------------------------------------------------
*/
GameBoard::GameBoard()
{
    //board reset
    for(int x=0;x<14;x++)
    {
        for(int y=0;y<14;y++)
            board[x][y]=0;
    }
	for(int i=0;i<18;i++)chess_remain[i]=true;
	chess_remain_num[0]=9;
	chess_remain_num[1]=9;
	p1_score=0;
	p2_score=0;
}
GameBoard::GameBoard(int b[14][14])
{
    //board reset
    for(int x=0;x<14;x++)
    {
        for(int y=0;y<14;y++)
            board[x][y]=b[x][y];
    }
	for(int i=0;i<18;i++)chess_remain[i]=false;
	chess_remain_num[0]=0;
	chess_remain_num[1]=0;
	p1_score=0;
	p2_score=0;
}

GameBoard::GameBoard(GameBoard b,vector<pair<int,int> > cover,int chess,int player)
{
    for(int x=0;x<14;x++)
    {
        for(int y=0;y<14;y++)
        {
            board[x][y] = b.get_value(x,y);
        }
    }	
	for(int i=0;i<cover.size();i++) board[cover[i].second][cover[i].first] = player;
	for(int i=0;i<18;i++) chess_remain[i] = b.chess_remain[i];
	chess_remain_num[0] = b.chess_remain_num[0];
	chess_remain_num[1] = b.chess_remain_num[1];
	p1_score=b.p1_score;
	p2_score=b.p2_score;
}

void GameBoard::set_value(int x,int y,int player)
{
    board[y][x] = player;    //change the store type
}

int GameBoard::get_value(int x,int y)
{
   return board[y][x];
}

void GameBoard::show()
{
    /*
    1   2   3   4   5   6   7   8   9   10  11  12  13
   ----------------------------------------------------
1 |   |   |   |   |   |   |   |   |   |   |   |   |   |
  |----------------------------------------------------
2 |   |   |   |   |   |   |   |   |   |   |   |   |   |
  |----------------------------------------------------
3 |   |   |   |   |   |   |   |   |   |   |   |   |   |
  |----------------------------------------------------
4 |   |   |   |   |   |   |   |   |   |   |   |   |   |
  |----------------------------------------------------
5 |   |   |   |   |   |   |   |   |   |   |   |   |   |
  |----------------------------------------------------
6 |   |   |   |   |   |   |   |   |   |   |   |   |   |
  |----------------------------------------------------
7 |   |   |   |   |   |   |   |   |   |   |   |   |   |
  |----------------------------------------------------
8 |   |   |   |   |   |   |   |   |   |   |   |   |   |
  |----------------------------------------------------
9 |   |   |   |   |   |   |   |   |   |   |   |   |   |
  |----------------------------------------------------
10|   |   |   |   |   |   |   |   |   |   |   |   |   |
  |----------------------------------------------------
11|   |   |   |   |   |   |   |   |   |   |   |   |   |
  |----------------------------------------------------
12|   |   |   |   |   |   |   |   |   |   |   |   |   |
  |----------------------------------------------------
13|   |   |   |   |   |   |   |   |   |   |   |   |   |
  |----------------------------------------------------

    */
    cout<<"    1   2   3   4   5   6   7   8   9   10  11  12  13"<<endl;
    cout<<"   ----------------------------------------------------"<<endl;

    for(int i=1;i<14;i++)  //change the show type
    {
        if(i<10)cout<<i<<" |";
        else cout<<i<<"|";

        for(int j=1;j<14;j++)
        {
            if(board[i][j]==1)cout<<"\033[1;41m "<<board[i][j]<<" \033[0m"<<"|";
            else if(board[i][j]==2)cout<<"\033[1;44m "<<board[i][j]<<" \033[0m"<<"|";
            else
            {
                cout<<"   |";
            }

        }
        cout<<endl;
        cout<<"  |----------------------------------------------------"<<endl;
    }

}

void GameBoard::coloring(int board[14][14],int q[200],int q_size,int reference,int color,int type){
	int temp[14][14];
	int start=0,end=q_size;
	for(int i=0;i<14;i++)
	{
		for(int j=0;j<14;j++)
			temp[i][j]=board[i][j];
	}
	
	int x,y;
	while(start<end){
		y=q[start]/100;
		x=q[start]%100;
		if(temp[y-1][x]==reference && board[y-1][x]==reference && y>1){
			q[end]=q[start]-100;
			board[y-1][x] = color;
			end++;
		}
		if(temp[y+1][x]==reference && board[y+1][x]==reference && y<13){
			q[end]=q[start]+100;
			board[y+1][x] = color;
			end++;
		}
		if(temp[y][x-1]==reference && board[y][x-1]==reference && x>1){
			q[end]=q[start]-1;
			board[y][x-1] = color;
			end++;
		}
		if(temp[y][x+1]==reference && board[y][x+1]==reference && x<13){
			q[end]=q[start]+1;
			board[y][x+1] = color;
			end++;
		}
		//for marking live line
		if(type == 2){
			if(temp[y-1][x-1]==reference && board[y-1][x-1]==reference && y>1 && x>1){
				q[end]=q[start]-101;
				board[y-1][x-1] = color;
				end++;
			}
			if(temp[y+1][x+1]==reference && board[y+1][x+1]==reference && y<13 && x<13){
				q[end]=q[start]+101;
				board[y+1][x+1] = color;
				end++;
			}
			if(temp[y+1][x-1]==reference && board[y+1][x-1]==reference && y<13 && x>1){
				q[end]=q[start]+99;
				board[y+1][x-1] = color;
				end++;
			}
			if(temp[y-1][x+1]==reference && board[y-1][x+1]==reference && y>1  && x<13){
				q[end]=q[start]-99;
				board[y-1][x+1] = color;
				end++;
			}
		}
		start++;
	}
}

void GameBoard::cal_area(){	
	int tempboard[14][14],flag[14][14];
	int q[200],cq[200];
	int start=0,end=0;
	//initial
	for(int i=0;i<200;i++){
		q[i]=0;
		cq[i]=0;
	}
	for(int i=0;i<14;i++)
	{
		for(int j=0;j<14;j++){
			tempboard[i][j]=board[i][j];
			flag[i][j]=board[i][j];
		}
	}
	//Step 1 -- group the zero area by 7 and 8, 7 means it belongs to someone, 8 means unsure the owner
	int check=0,x,y;
	for(int i=1;i<14;i++)
	{
		for(int j=1;j<14;j++){
			if(tempboard[i][j]==0){
				check=0;
				start=0;
				end=0;
				q[end++]=100*i+j;

				while(start<end){
					y=q[start]/100;
					x=q[start]%100;
					
					if(tempboard[y-1][x]==0 && flag[y-1][x]==0 && y>1){
						q[end]=q[start]-100;
						flag[y-1][x]=1;
						end++;
					}else if(tempboard[y-1][x]>0 && tempboard[y-1][x]<3 && y>1){
						if(check==0)check = tempboard[y-1][x];
						else if(check!=tempboard[y-1][x]){
							check=3;
							cq[0]=100*i+j;
							coloring(tempboard,cq,1,0,7,1);
							break;
						}
					}
					if(tempboard[y+1][x]==0 && flag[y+1][x]==0 && y<13){
						q[end]=q[start]+100;
						flag[y+1][x]=1;
						end++;
					}else if(tempboard[y+1][x]>0 && tempboard[y+1][x]<3 && y<13){
						if(check==0)check = tempboard[y+1][x];
						else if(check!=tempboard[y+1][x]){
							check=3;
							cq[0]=100*i+j;
							coloring(tempboard,cq,1,0,7,1);
							break;
						}
					}
					if(tempboard[y][x-1]==0 && flag[y][x-1]==0 && x>1){
						q[end]=q[start]-1;
						flag[y][x-1]=1;
						end++;
					}else if(tempboard[y][x-1]>0 && tempboard[y][x-1]<3 && x>1){
						if(check==0)check = tempboard[y][x-1];
						else if(check!=tempboard[y][x-1]){
							check=3;
							cq[0]=100*i+j;
							coloring(tempboard,cq,1,0,7,1);
							break;
						}
					}
					if(tempboard[y][x+1]==0 && flag[y][x+1]==0 && x<13){
						q[end]=q[start]+1;
						flag[y][x+1]=1;
						end++;
					}else if(tempboard[y][x+1]>0 && tempboard[y][x+1]<3 && x<13){
						if(check==0)check = tempboard[y][x+1];
						else if(check!=tempboard[y][x+1]){
							check=3;
							cq[0]=100*i+j;
							coloring(tempboard,cq,1,0,7,1);
							break;
						}
					}
					start++;
				}
				if(check!=3){
					
					cq[0]=100*i+j;
					coloring(tempboard,cq,1,0,8,1);
				}
			}
		}
	}
	
	//Step 2 -- derive the live line which is hitting edge
	int count=0;
	while(++count<=4){
		int temp[14][14],s[30],top=1,x_i,y_i,target,x,y,mark=0;
		for(int i=0;i<14;i++){
			for(int j=0;j<14;j++)
				temp[i][j]=0;
		}
		if(count==1) s[0]=404;
		else if(count==2) s[0]=410;
		else if(count==3) s[0]=1004;
		else if(count==4) s[0]=1010;
		x_i=s[0]%100;
		y_i=s[0]/100;
		target = board[y_i][x_i];
		if(target>2)continue;
		while(top>0){
			top--;
			x=s[top]%100;
			y=s[top]/100;
			if(temp[y][x])continue;
			if(x==1||y==1||x==13||y==13){//reach the boundary
				if(((x==1||x==13) && ((!temp[y-1][x]&&(y>1))&&(!temp[y+1][x]&&(y<13)))) ||
				   ((y==1||y==13) && ((!temp[y][x-1]&&(x>1))&&(!temp[y][x+1]&&(x<13))))){
					   if(y>1 && board[y-1][x]==target && !temp[y-1][x]) temp[y-1][x]=1;
					   if(y<13 && board[y+1][x]==target && !temp[y+1][x]) temp[y+1][x]=1;
					   if(x>1 && board[y][x-1]==target && !temp[y][x-1]) temp[y][x-1]=1;
					   if(x<13 && board[y][x+1]==target && !temp[y][x+1]) temp[y][x+1]=1;
					   mark++;
				   }
			}			
			else{
				if(board[y-1][x]==target && !temp[y-1][x] && y>1){ //up
					s[top]=100*y+x-100;
					top++;
				}
				if(board[y+1][x]==target && !temp[y+1][x] && y<13){ //down
					s[top]=100*y+x+100;
					top++;
				}
				if(board[y][x-1]==target && !temp[y][x-1] && x>1){ //left
					s[top]=100*y+x-1;
					top++;
				}
				if(board[y][x+1]==target && !temp[y][x+1] && x<13){ //right
					s[top]=100*y+x+1;
					top++;
				}
				if(board[y-1][x-1]==target && !temp[y-1][x-1] && x>1 && y>1){ //up and left
					s[top]=100*y+x-101;
					top++;
				}
				if(board[y-1][x+1]==target && !temp[y-1][x+1] && x<13 && y>1){ //up and right
					s[top]=100*y+x-99;
					top++;
				}
				if(board[y+1][x-1]==target && !temp[y+1][x-1] && x>1 && y<13){ //down and left
					s[top]=100*y+x+99;
					top++;
				}
				if(board[y+1][x+1]==target && !temp[y+1][x+1] && x<13 && y<13){ //down and right
					s[top]=100*y+x+101;
					top++;
				}
			}
			if(mark>1)break; //have an area
			temp[y][x]=1;			
		}
		if(mark>1){
			q[0]=s[0];
			coloring(board,q,1,target,target+2,2);
		}
	}
	//Step 3 -- derive the live line which has true area
	end=0;
	for(int i=1;i<14;i++){
		for(int j=1;j<14;j++){
			if(tempboard[i][j]==8 && tempboard[i-1][j]<3 && i>1){
				q[0]=100*i+j-100;
				coloring(board,q,1,tempboard[i-1][j],tempboard[i-1][j]+2,2);
			}
			else if(tempboard[i][j]==0 && tempboard[i+1][j]<3 && i<13){
				q[0]=100*i+j+100;
				coloring(board,q,1,tempboard[i+1][j],tempboard[i+1][j]+2,2);
			}
			else if(tempboard[i][j]==0 && tempboard[i][j-1]<3 && j>1){
				q[0]=100*i+j-1;
				coloring(board,q,1,tempboard[i][j-1],tempboard[i][j-1]+2,2);
			}
			else if(tempboard[i][j]==0 && tempboard[i][j+1]<3 && j<13){
				q[0]=100*i+j+1;
				coloring(board,q,1,tempboard[i][j+1],tempboard[i][j+1]+2,2);
			}
		}
	}
	//expand the live chess, to get the real area
	for(int i=1;i<14;i++)
	{
		for(int j=1;j<14;j++){
			if(board[i][j]<3)
				tempboard[i][j]=0;
			else
				tempboard[i][j]=board[i][j];
		}
	}

	end=0;
	for(int i=1;i<14;i++){
		for(int j=1;j<14;j++){
			if(board[i][j]==3){
				q[end]=100*i+j;
				end++;
			}
		}
	}
	coloring(tempboard,q,end,0,5,1);
	end=0;
	for(int i=1;i<14;i++){
		for(int j=1;j<14;j++){
			if(board[i][j]==4){
				q[end]=100*i+j;
				end++;
			}
		}
	}
	coloring(tempboard,q,end,0,6,1);
	//if both side reach the same area, then this area doesn't belong to anyone
	end=0;
	for(int i=1;i<14;i++){
		for(int j=1;j<14;j++){
			if(board[i][j]==4){
				q[end]=100*i+j;
				end++;
			}
		}
	}
	coloring(tempboard,q,end,5,0,1);
	//Step 5 -- calculate the score
	int p1=0,p2=0;
	for(int i=1;i<14;i++){
		for(int j=1;j<14;j++){
			if(tempboard[i][j]==5){p1++;}
			if(tempboard[i][j]==6){p2++;}
			if(tempboard[i][j]==5 && board[i][j]==2)p1++;
			if(tempboard[i][j]==6 && board[i][j]==1)p2++;
		}
	}
	p1_score = p1;
	p2_score = p2;
}
int GameBoard::get_score(int player)
{
	return player==1?p1_score:p2_score;
}


int GameBoard::result()
{
	cal_area();
	int player1_score=p1_score;
	int player2_score=p2_score;
	return (player1_score>=player2_score)?1:2;
}
int GameBoard::final_result()
{
	cal_area();
	int player1_score=p1_score;
	int player2_score=p2_score;
	cout<<"Player1's score : "<<player1_score<<endl;
	cout<<"Player2's score : "<<player2_score<<endl;
	if(player1_score>player2_score) cout<<"Player1 wins!!"<<endl;
	else cout<<"Player2 wins!!"<<endl;
	return (player1_score>=player2_score)?1:2;
}
void GameBoard::show_result(){
	int r = final_result();
	cout<<"Result:"<<endl;
	switch(r){
		case 1:
			cout<<"player 1 wins"<<endl;
			break;
		case 2:
			cout<<"player 2 wins"<<endl;
			break;
		case 3:
			cout<<"player 2 wins"<<endl;
			break;
	}
}
bool set_cover(vector< pair<int,int> > &cover,int chess,int position_x,int position_y,int direction)
{
    if(chess==0)
	{
	    if(direction==0)
        {
			if(position_y-3 < 1)return false;
			else
			{
				cover.push_back(make_pair(position_x,position_y));      //*
				cover.push_back(make_pair(position_x,position_y-1));    //*
				cover.push_back(make_pair(position_x,position_y-2));    //*
				cover.push_back(make_pair(position_x,position_y-3));    //+
				return true;
			}
        }
        if(direction==1)
		{
			if(position_x+3 > 13)return false;
			else
			{
				cover.push_back(make_pair(position_x,position_y));      //+***
				cover.push_back(make_pair(position_x+1,position_y));
				cover.push_back(make_pair(position_x+2,position_y));
				cover.push_back(make_pair(position_x+3,position_y));
				return true;
			}
		}
        if(direction==2)
		{
			if(position_y+3 > 13)return false;
			else
			{
				cover.push_back(make_pair(position_x,position_y));      //+
				cover.push_back(make_pair(position_x,position_y+1));    //*
				cover.push_back(make_pair(position_x,position_y+2));    //*
				cover.push_back(make_pair(position_x,position_y+3));    //*
				return true;
			}
		}
        if(direction==3)
		{
			if(position_x-3 < 1)return false;
			else
			{
				cover.push_back(make_pair(position_x,position_y));      //***+
				cover.push_back(make_pair(position_x-1,position_y));
				cover.push_back(make_pair(position_x-2,position_y));
				cover.push_back(make_pair(position_x-3,position_y));
				return true;
			}
		}
	}
    else if(chess==1)
    {
        if(direction==0)
		{
			if(position_x-1<1||position_x+1>13||position_y+1>13)return false;
			else
			{
				cover.push_back(make_pair(position_x,position_y));          // +
				cover.push_back(make_pair(position_x-1,position_y+1));      //***
				cover.push_back(make_pair(position_x,position_y+1));
				cover.push_back(make_pair(position_x+1,position_y+1));
				return true;
			}
		}
        if(direction==1)
		{

			if(position_x-1<1||position_y-1<1||position_y+1>13)return false;
			else
			{
				cover.push_back(make_pair(position_x,position_y));
				cover.push_back(make_pair(position_x-1,position_y-1));  //*
				cover.push_back(make_pair(position_x-1,position_y));    //*+
				cover.push_back(make_pair(position_x-1,position_y+1));  //*
				return true;
			}
		}
        if(direction==2)
        {
			if(position_x-1<1||position_x+1>13||position_y-1<1)return false;
			else
			{
				cover.push_back(make_pair(position_x,position_y));       //***
				cover.push_back(make_pair(position_x-1,position_y-1));   // +
				cover.push_back(make_pair(position_x,position_y-1));
				cover.push_back(make_pair(position_x+1,position_y-1));
				return true;
			}
		}
		if(direction==3)
		{
			if(position_x+1>13||position_y+1>13||position_y-1<1)return false;
			else
			{
				cover.push_back(make_pair(position_x,position_y));          // *
				cover.push_back(make_pair(position_x+1,position_y-1));      //+*
				cover.push_back(make_pair(position_x+1,position_y));        // *
				cover.push_back(make_pair(position_x+1,position_y+1));
				return true;
			}
		}
	}
    else if(chess==2)
    {
        if(direction==0)
        {
            if(position_x+1>13||position_x-1<1||position_y+1>13)return false;
            else
            {
                cover.push_back(make_pair(position_x,position_y));              //   +*
				cover.push_back(make_pair(position_x+1,position_y));            //  **
				cover.push_back(make_pair(position_x,position_y+1));
				cover.push_back(make_pair(position_x-1,position_y+1));
				return true;
            }
        }
        if(direction==1)
        {
            if(position_x-1<1||position_y+1>13||position_y-1<1)return false;
            else
            {
                cover.push_back(make_pair(position_x,position_y));              //  *
				cover.push_back(make_pair(position_x-1,position_y-1));          //  *+
				cover.push_back(make_pair(position_x-1,position_y));            //   *
				cover.push_back(make_pair(position_x,position_y+1));
				return true;
            }
        }
        if(direction==2)
        {
            if(position_x+1>13||position_x-1<1||position_y-1<1)return false;
            else
            {
                cover.push_back(make_pair(position_x,position_y));          //   **
				cover.push_back(make_pair(position_x-1,position_y));        //  *+
				cover.push_back(make_pair(position_x,position_y-1));
				cover.push_back(make_pair(position_x+1,position_y-1));
				return true;
            }
        }
        if(direction==3)
        {
            if(position_x+1>13||position_y+1>13||position_y-1<1)return false;
            else
            {
                cover.push_back(make_pair(position_x,position_y));           //  *
				cover.push_back(make_pair(position_x+1,position_y+1));       //  +*
				cover.push_back(make_pair(position_x+1,position_y));         //   *
				cover.push_back(make_pair(position_x,position_y-1));
				return true;
            }
        }
    }
    else if(chess==3)
	{
        if(direction==0)
        {
            if(position_x-1<1||position_x+1>13||position_y+1>13)return false;
            else
            {
                cover.push_back(make_pair(position_x,position_y));           // *+
				cover.push_back(make_pair(position_x+1,position_y+1));       //  **
				cover.push_back(make_pair(position_x-1,position_y));
				cover.push_back(make_pair(position_x,position_y+1));
				return true;
            }
        }
        if(direction==1)
        {
            if(position_x-1<1||position_y+1>13||position_y-1<1)return false;
            else
            {
                cover.push_back(make_pair(position_x,position_y));           //   *
				cover.push_back(make_pair(position_x,position_y-1));         //  *+
				cover.push_back(make_pair(position_x-1,position_y));         //  *
				cover.push_back(make_pair(position_x-1,position_y+1));
				return true;
            }
        }
        if(direction==2)
        {
            if(position_x-1<1||position_x+1>13||position_y-1<1)return false;
            else
            {
                cover.push_back(make_pair(position_x,position_y));           // **
				cover.push_back(make_pair(position_x-1,position_y-1));       //  +*
				cover.push_back(make_pair(position_x,position_y-1));
				cover.push_back(make_pair(position_x+1,position_y));
				return true;
            }
        }
        if(direction==3)
        {
            if(position_x+1>13||position_y+1>13||position_y-1<1)return false;
            else
            {
                cover.push_back(make_pair(position_x,position_y));           //   *
				cover.push_back(make_pair(position_x+1,position_y-1));       //  +*
				cover.push_back(make_pair(position_x+1,position_y));         //  *
				cover.push_back(make_pair(position_x,position_y+1));
				return true;
            }
        }
    }
    else if(chess==4)
	{
        if(direction==0)
        {
            if(position_x-2<1||position_y-1<1)return false;
            else
            {
                cover.push_back(make_pair(position_x,position_y));       //  *
				cover.push_back(make_pair(position_x-2,position_y));     //**+
				cover.push_back(make_pair(position_x-1,position_y));
				cover.push_back(make_pair(position_x,position_y-1));
				return true;
            }
        }
        if(direction==1)
        {
            if(position_y-2<1||position_x+1>13)return false;
            else
            {
                cover.push_back(make_pair(position_x,position_y));       //*
				cover.push_back(make_pair(position_x,position_y-2));     //*
				cover.push_back(make_pair(position_x,position_y-1));     //+*
				cover.push_back(make_pair(position_x+1,position_y));
				return true;
            }
        }
        if(direction==2)
        if(position_x+2>13||position_y+1>13)return false;
            else
            {
                cover.push_back(make_pair(position_x,position_y));       //+**
				cover.push_back(make_pair(position_x+2,position_y));     //*
				cover.push_back(make_pair(position_x+1,position_y));
				cover.push_back(make_pair(position_x,position_y+1));
				return true;
            }
        if(direction==3)
        {
            if(position_y+2>13||position_x-1<1)return false;
            else
            {
                cover.push_back(make_pair(position_x,position_y));       //*+
				cover.push_back(make_pair(position_x,position_y+2));     // *
				cover.push_back(make_pair(position_x,position_y+1));     // *
				cover.push_back(make_pair(position_x-1,position_y));
				return true;
            }
        }
    }
    else if(chess==5)
	{
        if(direction==0)
        {
            if(position_x+2>13||position_y-1<1)return false;
            else
            {
                cover.push_back(make_pair(position_x,position_y));       //*
				cover.push_back(make_pair(position_x+2,position_y));     //+**
				cover.push_back(make_pair(position_x+1,position_y));
				cover.push_back(make_pair(position_x,position_y-1));
				return true;
            }
        }
        if(direction==1)
        {
            if(position_y+2>13||position_x+1>13)return false;
            else
            {
                cover.push_back(make_pair(position_x,position_y));       //+*
				cover.push_back(make_pair(position_x,position_y+2));     //*
				cover.push_back(make_pair(position_x,position_y+1));     //*
				cover.push_back(make_pair(position_x+1,position_y));
				return true;
            }
        }
        if(direction==2)
        if(position_x-2<1||position_y+1>13)return false;
            else
            {
                cover.push_back(make_pair(position_x,position_y));       //**+
				cover.push_back(make_pair(position_x-2,position_y));     //  *
				cover.push_back(make_pair(position_x-1,position_y));
				cover.push_back(make_pair(position_x,position_y+1));
				return true;
            }
        if(direction==3)
        {
            if(position_y-2<1||position_x-1<1)return false;
            else
            {
                cover.push_back(make_pair(position_x,position_y));       // *
				cover.push_back(make_pair(position_x,position_y-2));     // *
				cover.push_back(make_pair(position_x,position_y-1));     //*+
				cover.push_back(make_pair(position_x-1,position_y));
				return true;
            }
        }
    }
    else if(chess==6)
	{
        if(direction==0)
        {
            if(position_y+1>13||position_x+1>13)return false;
            else
            {
                cover.push_back(make_pair(position_x,position_y));       //+*
				cover.push_back(make_pair(position_x,position_y+1));     //**
				cover.push_back(make_pair(position_x+1,position_y));
				cover.push_back(make_pair(position_x+1,position_y+1));
				return true;
            }
        }
        if(direction==1)
        {
            if(position_y+1>13||position_x-1<1)return false;
            else
            {
                cover.push_back(make_pair(position_x,position_y));       //*+
				cover.push_back(make_pair(position_x,position_y+1));     //**
				cover.push_back(make_pair(position_x-1,position_y));
				cover.push_back(make_pair(position_x-1,position_y+1));
				return true;
            }
        }
        if(direction==2)
        {
            if(position_y-1<1||position_x-1<1)return false;
            else
            {
                cover.push_back(make_pair(position_x,position_y));       //**
				cover.push_back(make_pair(position_x,position_y-1));     //*+
				cover.push_back(make_pair(position_x-1,position_y));
				cover.push_back(make_pair(position_x-1,position_y-1));
				return true;
            }
        }
        if(direction==3)
        {
            if(position_y-1<1||position_x+1>13)return false;
            else
            {
                cover.push_back(make_pair(position_x,position_y));       //**
				cover.push_back(make_pair(position_x,position_y-1));     //+*
				cover.push_back(make_pair(position_x+1,position_y));
				cover.push_back(make_pair(position_x+1,position_y-1));
				return true;
            }
        }
    }
    else if(chess==7)
	{
        cover.push_back(make_pair(position_x,position_y));
        return true;
    }
    else if(chess==8)
	{
        cover.push_back(make_pair(position_x,position_y));
        return true;
    }
}

void show_chesstype()
{
    cout<<"chesstype"<<endl;
    cout<<"0.       1.          2.         3.          4."      <<endl;
    cout<<"*         +           +*        *+             *"    <<endl;
    cout<<"*        ***         **          **          **+"    <<endl;
    cout<<"*"<<endl;
	cout<<"+"<<endl;
	cout<<endl;
    cout<<"5.          6.        7.        8."                  <<endl;
    cout<<"*             +*        +           +"               <<endl;
    cout<<"+**           **"                                    <<endl;
    cout<<endl;
}