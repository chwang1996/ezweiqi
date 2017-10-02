/* Version 5.0 */
/*
	Add the limitation of contact area ( under 2 )
*/

#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "GameBoard.h"
#include "DistanceMapMove.h"
#include <cmath>
#include <sys/time.h>
using namespace std;

correction_factor center_correct(int chess,int direction,int center)
{
	correction_factor factor;
	switch(chess)
	{
		case 0:
			if(direction == 0)
			{
				factor.x = 0;                           //0		//1		//2		//3
				if(center == 0) factor.y = 0;		    //*     //*     //*     //+
				else if(center == 1) factor.y = 1;      //*     //*     //+     //*
				else if(center == 2) factor.y = 2;      //*     //+     //*     //*
				else if(center == 3) factor.y = 3;      //+     //*     //*     //*
			}
			else if(direction == 1)
			{
				factor.y = 0;
				if(center == 0) factor.x = 0;			//+***
				else if(center == 1) factor.x = -1;		//*+**
				else if(center == 2) factor.x = -2;		//**+*
				else if(center == 3) factor.x = -3;		//***+
			}
			else if(direction == 2)
			{
				factor.x = 0;                            //0	 //1	 //2	 //3
				if(center == 0) factor.y = 0;		     //+     //*     //*     //*
				else if(center == 1) factor.y = -1;      //*     //+     //*     //*
				else if(center == 2) factor.y = -2;      //*     //*     //+     //*
				else if(center == 3) factor.y = -3;      //*     //*     //*     //+
			}
			else if(direction == 3)
			{
				factor.y = 0;
				if(center == 0) factor.x = 0;			//***+
				else if(center == 1) factor.x = 1;		//**+*
				else if(center == 2) factor.x = 2;		//*+**
				else if(center == 3) factor.x = 3;		//+***
			}
			break;
		case 1:
			if(direction == 0)
			{
				if(center == 0)
				{									// +
					factor.x = 0;	factor.y = 0;   //***
				}
				else if(center == 1)
				{									// *
					factor.x = 1;	factor.y = -1;  //+**
				}
				else if(center == 2)
				{									// *
					factor.x = 0;	factor.y = -1;	//*+*
				}
				else if(center == 3)
				{									// *
					factor.x = -1;	factor.y = -1;  //**+
				}
			}
			else if(direction == 1)
			{
				if(center == 0)						//*
				{                                   //*+
					factor.x = 0;	factor.y = 0;   //*
				}
				else if(center == 1)				//+
				{                                   //**
					factor.x = 1;	factor.y = 1;   //*
				}
				else if(center == 2)				//*
				{                                   //+*
					factor.x = 1;	factor.y = 0;   //*
				}
				else if(center == 3)				//*
				{                                   //**
					factor.x = 1;	factor.y = -1;  //+
				}
			}
			else if(direction == 2)
			{
				if(center == 0)						//***
				{                                   // +
					factor.x = 0;	factor.y = 0;
				}
				else if(center == 1)				//+**
				{                                   // *
					factor.x = 1;	factor.y = 1;
				}
				else if(center == 2)				//*+*
				{                                   // *
					factor.x = 0;	factor.y = 1;
				}
				else if(center == 3)				//**+
				{                                   // *
					factor.x = -1;	factor.y = 1;
				}
			}
			else if(direction == 3)
			{
				if(center == 0)						// *
				{                                   //+*
					factor.x = 0;	factor.y = 0;   // *
				}
				else if(center == 1)				// +
				{                                   //**
					factor.x = -1;	factor.y = 1;   // *
				}
				else if(center == 2)				// *
				{                                   //*+
					factor.x = -1;	factor.y = 0;   // *
				}
				else if(center == 3)				// *
				{                                   //**
					factor.x = -1;	factor.y = -1;  // +
				}
			}
			break;
		case 2:
			if(direction == 0)
			{
				if(center == 0)						//   +*
				{                                   //  **
					factor.x = 0;	factor.y = 0;
				}
				else if(center == 1)				//   *+
				{                                   //  **
					factor.x = -1;	factor.y = 0;
				}
				else if(center == 2)				//   **
				{                                   //  +*
					factor.x = 1;	factor.y = -1;
				}
				else if(center == 3)				//   **
				{                                   //  *+
					factor.x = 0;	factor.y = -1;
				}
			}
			else if(direction == 1)
			{
				if(center == 0)						//  *
				{                                   //  *+
					factor.x = 0;	factor.y = 0;   //   *
				}
				else if(center == 1)				//  +
				{                                   //  **
					factor.x = 1;	factor.y = 1;   //   *
				}
				else if(center == 2)				//  *
				{                                   //  +*
					factor.x = 1;	factor.y = 0;   //   *
				}
				else if(center == 3)				//  *
				{                                   //  **
					factor.x = 0;	factor.y = -1;  //   +
				}
			}
			else if(direction == 2)
			{
				if(center == 0)						//   **
				{                                   //  *+
					factor.x = 0;	factor.y = 0;
				}
				else if(center == 1)				//   +*
				{                                   //  **
					factor.x = 0;	factor.y = 1;
				}
				else if(center == 2)				//   *+
				{                                   //  **
					factor.x = -1;	factor.y = 1;
				}
				else if(center == 3)				//   **
				{                                   //  +*
					factor.x = 1;	factor.y = 0;
				}
			}
			else if(direction == 3)
			{
				if(center == 0)						//  *
				{                                   //  +*
					factor.x = 0;	factor.y = 0;   //   *
				}
				else if(center == 1)				//  +
				{                                   //  **
					factor.x = 0;	factor.y = 1;   //   *
				}
				else if(center == 2)				//  *
				{                                   //  *+
					factor.x = -1;	factor.y = 0;   //   *
				}
				else if(center == 3)				//  *
				{                                   //  **
					factor.x = -1;	factor.y = -1;  //   +
				}
			}
			break;
		case 3:
			if(direction == 0)
			{
				if(center == 0)						// *+
				{                                   //  **
					factor.x = 0;	factor.y = 0;
				}
				else if(center == 1)				// +*
				{                                   //  **
					factor.x = 1;	factor.y = 0;
				}
				else if(center == 2)				// **
				{                                   //  +*
					factor.x = 0;	factor.y = -1;
				}
				else if(center == 3)				// **
				{                                   //  *+
					factor.x = -1;	factor.y = -1;
				}
			}
			else if(direction == 1)
			{
				if(center == 0)						//   *
				{                                   //  *+
					factor.x = 0;	factor.y = 0;   //  *
				}
				else if(center == 1)				//   +
				{                                   //  **
					factor.x = 0;	factor.y = 1;   //  *
				}
				else if(center == 2)				//   *
				{                                   //  +*
					factor.x = 1;	factor.y = 0;   //  *
				}
				else if(center == 3)				//   *
				{                                   //  **
					factor.x = 1;	factor.y = -1;  //  +
				}
			}
			else if(direction == 2)
			{
				if(center == 0)						// **
				{                                   //  +*
					factor.x = 0;	factor.y = 0;
				}
				else if(center == 1)				// +*
				{                                   //  **
					factor.x = 1;	factor.y = 1;
				}
				else if(center == 2)				// *+
				{                                   //  **
					factor.x = 0;	factor.y = 1;
				}
				else if(center == 3)				// **
				{                                   //  *+
					factor.x = -1;	factor.y = 0;
				}
			}
			else if(direction == 3)
			{
				if(center == 0)						//   *
				{                                   //  +*
					factor.x = 0;	factor.y = 0;   //  *
				}
				else if(center == 1)				//   +
				{                                   //  **
					factor.x = -1;	factor.y = 1;   //  *
				}
				else if(center == 2)				//   *
				{                                   //  *+
					factor.x = -1;	factor.y = 0;   //  *
				}
				else if(center == 3)				//   *
				{                                   //  **
					factor.x = 0;	factor.y = -1;  //  +
				}
			}
			break;
		case 4:
			if(direction == 0)
			{
				if(center == 0)						//  *
				{                                   //**+
					factor.x = 0;	factor.y = 0;
				}
				else if(center == 1)				//  +
				{                                   //***
					factor.x = 0;	factor.y = 1;
				}
				else if(center == 2)				//  *
				{                                   //+**
					factor.x = 2;	factor.y = 0;
				}
				else if(center == 3)				//  *
				{                                   //*+*
					factor.x = 1;	factor.y = 0;
				}
			}
			else if(direction == 1)
			{
				if(center == 0)						//*
				{                                   //*
					factor.x = 0;	factor.y = 0;   //+*
				}
				else if(center == 1)				//+
				{                                   //*
					factor.x = 0;	factor.y = 2;   //**
				}
				else if(center == 2)				//*
				{                                   //+
					factor.x = 0;	factor.y = 1;   //**
				}
				else if(center == 3)				//*
				{                                   //*
					factor.x = -1;	factor.y = 0;   //*+
				}
			}
			else if(direction == 2)
			{
				if(center == 0)						//+**
				{                                   //*
					factor.x = 0;	factor.y = 0;
				}
				else if(center == 1)				//*+*
				{                                   //*
					factor.x = -1;	factor.y = 0;
				}
				else if(center == 2)				//**+
				{                                   //*
					factor.x = -2;	factor.y = 0;
				}
				else if(center == 3)				//***
				{                                   //+
					factor.x = 0;	factor.y = -1;
				}
			}
			else if(direction == 3)
			{
				if(center == 0)						//*+
				{                                   // *
					factor.x = 0;	factor.y = 0;   // *
				}
				else if(center == 1)				//+*
				{                                   // *
					factor.x = 1;	factor.y = 0;   // *
				}
				else if(center == 2)				//**
				{                                   // +
					factor.x = 0;	factor.y = -1;  // *
				}
				else if(center == 3)				//**
				{                                   // *
					factor.x = 0;	factor.y = -2;  // +
				}
			}
			break;
		case 5:
			if(direction == 0)
			{
				if(center == 0)						//*
				{                                   //+**
					factor.x = 0;	factor.y = 0;
				}
				else if(center == 1)				//+
				{                                   //***
					factor.x = 0;	factor.y = 1;
				}
				else if(center == 2)				//*
				{                                   //*+*
					factor.x = -1;	factor.y = 0;
				}
				else if(center == 3)				//*
				{                                   //**+
					factor.x = -2;	factor.y = 0;
				}
			}
			else if(direction == 1)
			{
				if(center == 0)						//+*
				{                                   //*
					factor.x = 0;	factor.y = 0;   //*
				}
				else if(center == 1)				//*+
				{                                   //*
					factor.x = -1;	factor.y = 0;   //*
				}
				else if(center == 2)				//**
				{                                   //+
					factor.x = 0;	factor.y = -1;  //*
				}
				else if(center == 3)				//**
				{                                   //*
					factor.x = 0;	factor.y = -2;  //+
				}
			}
			else if(direction == 2)
			{
				if(center == 0)						//**+
				{                                   //  *
					factor.x = 0;	factor.y = 0;
				}
				else if(center == 1)				//+**
				{                                   //  *
					factor.x = 2;	factor.y = 0;
				}
				else if(center == 2)				//*+*
				{                                   //  *
					factor.x = 1;	factor.y = 0;
				}
				else if(center == 3)				//***
				{                                   //  +
					factor.x = 0;	factor.y = -1;
				}
			}
			else if(direction == 3)
			{
				if(center == 0)						// *
				{                                   // *
					factor.x = 0;	factor.y = 0;   //*+
				}
				else if(center == 1)				// +
				{                                   // *
					factor.x = 0;	factor.y = 2;   //**
				}
				else if(center == 2)				// *
				{                                   // +
					factor.x = 0;	factor.y = 1;   //**
				}
				else if(center == 3)				// *
				{                                   // *
					factor.x = 1;	factor.y = 0;   //+*
				}
			}
			break;
		case 6:
			if(direction == 0)
			{
				if(center == 0)						//+*
				{                                   //**
					factor.x = 0;	factor.y = 0;
				}
				else if(center == 1)				//*+
				{                                   //**
					factor.x = -1;	factor.y = 0;
				}
				else if(center == 2)				//**
				{                                   //+*
					factor.x = 0;	factor.y = -1;
				}
				else if(center == 3)				//**
				{                                   //*+
					factor.x = -1;	factor.y = -1;
				}
			}
			else if(direction == 1)
			{
				if(center == 0)						//*+
				{                                   //**
					factor.x = 0;	factor.y = 0;
				}
				else if(center == 1)				//+*
				{                                   //**
					factor.x = 1;	factor.y = 0;
				}
				else if(center == 2)				//**
				{                                   //+*
					factor.x = 1;	factor.y = -1;
				}
				else if(center == 3)				//**
				{                                   //*+
					factor.x = 0;	factor.y = -1;
				}
			}
			else if(direction == 2)
			{
				if(center == 0)						//**
				{                                   //*+
					factor.x = 0;	factor.y = 0;
				}
				else if(center == 1)				//+*
				{                                   //**
					factor.x = 1;	factor.y = 1;
				}
				else if(center == 2)				//*+
				{                                   //**
					factor.x = 0;	factor.y = 1;
				}
				else if(center == 3)				//**
				{                                   //+*
					factor.x = 1;	factor.y = 0;
				}
			}
			else if(direction == 3)
			{
				if(center == 0)						//**
				{                                   //+*
					factor.x = 0;	factor.y = 0;
				}
				else if(center == 1)				//+*
				{                                   //**
					factor.x = 0;	factor.y = 1;
				}
				else if(center == 2)				//*+
				{                                   //**
					factor.x = -1;	factor.y = 1;
				}
				else if(center == 3)				//**
				{                                   //*+
					factor.x = -1;	factor.y = 0;
				}
			}
			break;
		case 7:
			factor.x = 0;	factor.y = 0;
			break;
		case 8:
			factor.x = 0;	factor.y = 0;
			break;
	}

	return factor;
}


void set_chess_table(int table[4][12])
{
	//returndata = 10000*x+100*y+10*dir+random_chess;
	table[0][0] = 4*10000  + 4*100  + 1*10 +0; 		// x=4;  y=4;  dir=1; type=0;-
	table[0][1] = 4*10000  + 4*100  + 2*10 +0; 		// x=4;  y=4;  dir=2; type=0;-
	table[0][2] = 5*10000  + 5*100  + 1*10 +1; 		// x=5;  y=5;  dir=1; type=1;-
	table[0][3] = 5*10000  + 5*100  + 2*10 +1; 		// x=5;  y=5;  dir=2; type=1;-
	table[0][4] = 5*10000  + 5*100  + 1*10 +2; 		// x=5;  y=5;  dir=1; type=2;-
	table[0][5] = 4*10000  + 5*100  + 3*10 +2; 		// x=4;  y=5;  dir=3; type=2;-
	table[0][6] = 5*10000  + 4*100  + 0*10 +3; 		// x=5;  y=4;  dir=0; type=3;-
	table[0][7] = 5*10000  + 5*100  + 2*10 +3; 		// x=5;  y=5;  dir=2; type=3;-
	table[0][8] = 5*10000  + 4*100  + 3*10 +4; 		// x=5;  y=4;  dir=3; type=4;-
	table[0][9] = 4*10000  + 6*100  + 1*10 +4; 		// x=4;  y=6;  dir=1; type=4;-
	table[0][10]= 4*10000  + 5*100  + 0*10 +5; 		// x=4;  y=5;  dir=0; type=5;-
	table[0][11]= 6*10000  + 4*100  + 2*10 +5; 		// x=6;  y=4;  dir=2; type=5;-

	table[1][0] =10*10000  + 4*100  + 2*10 +0; 		// x=10; y=4;  dir=2; type=0;-
	table[1][1] =10*10000  + 4*100  + 3*10 +0; 		// x=10; y=4;  dir=3; type=0;-
	table[1][2] = 9*10000  + 5*100  + 2*10 +1; 		// x=9;  y=5;  dir=2; type=1;-
	table[1][3] = 9*10000  + 5*100  + 3*10 +1; 		// x=9;  y=5;  dir=3; type=1;-
	table[1][4] = 9*10000  + 4*100  + 0*10 +2; 		// x=9;  y=4;  dir=0; type=2;-
	table[1][5] = 9*10000  + 5*100  + 2*10 +2; 		// x=9;  y=5;  dir=2; type=2;-
	table[1][6] =10*10000  + 5*100  + 1*10 +3; 		// x=10; y=5;  dir=1; type=3;-
	table[1][7] = 9*10000  + 5*100  + 3*10 +3; 		// x=9;  y=5;  dir=3; type=3;-
	table[1][8] =10*10000  + 5*100  + 0*10 +4; 		// x=10; y=5;  dir=0; type=4;-
	table[1][9] = 8*10000  + 4*100  + 2*10 +4; 		// x=8;  y=4;  dir=2; type=4;-
	table[1][10]= 9*10000  + 4*100  + 1*10 +5; 		// x=9;  y=4;  dir=1; type=5;-
	table[1][11]=10*10000  + 6*100  + 3*10 +5; 		// x=10; y=6;  dir=3; type=5;-

	table[2][0] = 4*10000  +10*100  + 0*10 +0; 		// x=4;  y=10; dir=0; type=0;-
	table[2][1] = 4*10000  +10*100  + 1*10 +0; 		// x=4;  y=10; dir=1; type=0;-
	table[2][2] = 5*10000  + 9*100  + 0*10 +1; 		// x=5;  y=9;  dir=0; type=1;-
	table[2][3] = 5*10000  + 9*100  + 1*10 +1; 		// x=5;  y=9;  dir=1; type=1;-
	table[2][4] = 5*10000  + 9*100  + 0*10 +2; 		// x=5;  y=9;  dir=0; type=2;-
	table[2][5] = 5*10000  +10*100  + 2*10 +2; 		// x=5;  y=10; dir=2; type=2;-
	table[2][6] = 5*10000  + 9*100  + 1*10 +3; 		// x=5;  y=9;  dir=1; type=3;-
	table[2][7] = 4*10000  + 9*100  + 3*10 +3; 		// x=4;  y=9;  dir=3; type=3;-
	table[2][8] = 6*10000  +10*100  + 0*10 +4; 		// x=6;  y=10; dir=0; type=4;-
	table[2][9] = 4*10000  + 9*100  + 2*10 +4; 		// x=4;  y=9;  dir=2; type=4;-
	table[2][10]= 4*10000  + 8*100  + 1*10 +5; 		// x=4;  y=8;  dir=1; type=5;-
	table[2][11]= 5*10000  +10*100  + 3*10 +5; 		// x=5;  y=10; dir=3; type=5;-

	table[3][0] =10*10000  +10*100  + 0*10 +0; 		// x=10; y=10; dir=0; type=0;-
	table[3][1] =10*10000  +10*100  + 3*10 +0; 		// x=10; y=10; dir=3; type=0;-
	table[3][2] = 9*10000  + 9*100  + 0*10 +1; 		// x=9;  y=9;  dir=0; type=1;-
	table[3][3] = 9*10000  + 9*100  + 3*10 +1; 		// x=9;  y=9;  dir=3; type=1;-
	table[3][4] =10*10000  + 9*100  + 1*10 +2; 		// x=10; y=9;  dir=1; type=2;-
	table[3][5] = 9*10000  + 9*100  + 3*10 +2; 		// x=9;  y=9;  dir=3; type=2;-
	table[3][6] = 9*10000  + 9*100  + 0*10 +3; 		// x=9;  y=9;  dir=0; type=3;-
	table[3][7] = 9*10000  +10*100  + 2*10 +3; 		// x=9;  y=10; dir=2; type=3;-
	table[3][8] = 9*10000  +10*100  + 1*10 +4; 		// x=9;  y=10; dir=1; type=4;-
	table[3][9] =10*10000  + 8*100  + 3*10 +4; 		// x=10; y=8;  dir=3; type=4;-
	table[3][10]= 8*10000  +10*100  + 0*10 +5; 		// x=8;  y=10; dir=0; type=5;-
	table[3][11]=10*10000  + 9*100  + 2*10 +5; 		// x=10; y=9;  dir=2; type=5;-
}

float SetDisMap(int board[14][14],int turns,bool limit)
{

	int P1_Map[14][14],P2_Map[14][14];
	int q[200];
	int start=0,end=0;
	for(int i=0;i<200;i++){
		q[i]=0;
	}
	for(int i=0;i<14;i++)
	{
		for(int j=0;j<14;j++)
		{
			P1_Map[i][j] = (board[i][j]==0)?(limit?110:0):board[i][j];
			P2_Map[i][j] = (board[i][j]==0)?(limit?210:0):board[i][j];
			if(board[i][j]==1){
				q[end]=100000*i+1000*j+100;
				end++;
			}
		}
	}
	/* Set P1_Map */
	int x,y,value,s = 0,t=0;
	while(start<end){
		y=q[start]/100000;
		x=(q[start]%100000)/1000;
		value=q[start]%1000;
		if(!(limit && value >=106)){
			if(board[y-1][x]==0 && P1_Map[y-1][x]==0 && y>1){
				q[end]=q[start]-100000+1;
				P1_Map[y-1][x] = value+1;
				end++;
			}
			if(board[y+1][x]==0 && P1_Map[y+1][x]==0 && y<13){
				q[end]=q[start]+100000+1;
				P1_Map[y+1][x] = value+1;
				end++;
			}
			if(board[y][x-1]==0 && P1_Map[y][x-1]==0 && x>1){
				q[end]=q[start]-1000+1;
				P1_Map[y][x-1] = value+1;
				end++;
			}
			if(board[y][x+1]==0 && P1_Map[y][x+1]==0 && x<13){
				q[end]=q[start]+1000+1;
				P1_Map[y][x+1] = value+1;
				end++;
			}
		}
		start++;
	}
/*	cout<<"------------P1----------"<<endl;
	for(int i=1;i<14;i++){
		for(int j=1;j<14;j++){
			cout<<P1_Map[i][j]<<"\t";
		}
		cout<<endl;
	}*/
	/* Set P2_Map */
	start=0,end=0;

	for(int i=0;i<200;i++){
		q[i]=0;
	}
	for(int i=0;i<14;i++)
	{
		for(int j=0;j<14;j++)
		{
			if(board[i][j]==2){
				q[end]=100000*i+1000*j+200;
				end++;
			}
		}
	}
	while(start<end){
		y=q[start]/100000;
		x=(q[start]%100000)/1000;
		value=q[start]%1000;
		if(!(limit && value >=206)){
			if(board[y-1][x]==0 && P2_Map[y-1][x]==0 && y>1){
				q[end]=q[start]-100000+1;
				P2_Map[y-1][x] = value+1;
				end++;
			}
			if(board[y+1][x]==0 && P2_Map[y+1][x]==0 && y<13){
				q[end]=q[start]+100000+1;
				P2_Map[y+1][x] = value+1;
				end++;
			}
			if(board[y][x-1]==0 && P2_Map[y][x-1]==0 && x>1){
				q[end]=q[start]-1000+1;
				P2_Map[y][x-1] = value+1;
				end++;
			}
			if(board[y][x+1]==0 && P2_Map[y][x+1]==0 && x<13){
				q[end]=q[start]+1000+1;
				P2_Map[y][x+1] = value+1;
				end++;
			}
		}
		start++;
	}
/*	cout<<"------------P2----------"<<endl;
	for(int i=1;i<14;i++){
		for(int j=1;j<14;j++){
			cout<<P2_Map[i][j]<<"\t";
		}
		cout<<endl;
	}*/
	if(!limit){
		for(int i=1;i<14;i++)
		{
			for(int j=1;j<14;j++)
			{
				if(P1_Map[i][j]==0)
					P1_Map[i][j] = 1000;
				if(P2_Map[i][j]==0)
					P2_Map[i][j] = 1100;
			}
		}
	}
	/* calculate score */
	float score = 0;
	
	for(int y=1;y<14;y++)
	{
		for(int x=1;x<14;x++)
		{
			if(board[y][x]==0)
			{	
				if(turns == 1){
					if(P2_Map[y][x]>=1000)
						score+=(float)pow((P2_Map[y][x]-200),2)/(pow((P1_Map[y][x]-100),2)+pow((P2_Map[y][x]-200),2))+0.07;
					else score+=(float)pow((P2_Map[y][x]-200),2)/(pow((P1_Map[y][x]-100),2)+pow((P2_Map[y][x]-200),2));
				}
				else if(turns == 2){
					if(P1_Map[y][x]>=1000)
						score+=(float)pow((P1_Map[y][x]-100),2)/(pow((P1_Map[y][x]-100),2)+pow((P2_Map[y][x]-200),2))+0.07;
					else score+=(float)pow((P1_Map[y][x]-100),2)/(pow((P1_Map[y][x]-100),2)+pow((P2_Map[y][x]-200),2));
				}
/*				if(turns == 1)
					score+=(float)pow((P2_Map[y][x]-200),2)/(pow((P1_Map[y][x]-100),2)+pow((P2_Map[y][x]-200),2));
				else if(turns == 2)
					score+=(float)pow((P1_Map[y][x]-100),2)/(pow((P1_Map[y][x]-100),2)+pow((P2_Map[y][x]-200),2));*/
			}
		}
	}
	return score;
}


int* DistanceMapMove(int b[14][14],int turns,bool chess_r[18],vector<MCTNode*> existpos,int type)
{
	int board[14][14],temp[14][14];
	bool chess_remain[18];
	int *bestlist = new int[10];
	int bestvalue[10];

	int index=0;
	for(int i=0;i<14;i++)
	{ 
		for(int j=0;j<14;j++){
			board[i][j]=b[i][j];
			temp[i][j] = b[i][j];
		}
	}
	for(int i=0;i<18;i++) chess_remain[i]=chess_r[i];

	vector< pair<int,int> > cover;
	
	/* Get the position around the turns player's Area */
	Area Pos_around_area;
	Pos_around_area.size = 0;
	for(int y=1;y<14;y++)
	{
		for(int x=1;x<14;x++)
		{
			if(board[y][x] == 0 &&((board[y-1][x] == turns && y>=2)||(board[y][x-1] == turns && x>=2)||(board[y][x+1] == turns && x<=12)||(board[y+1][x] == turns && y<=12)))
			{
				Pos_around_area.x[Pos_around_area.size] = x;
				Pos_around_area.y[Pos_around_area.size] = y;
				Pos_around_area.size++;
			}
		}
	}

	/*	Check first four point	*/
	int first_four_count = 0;

	if(board[4][4] != 0) first_four_count++;
	if(board[4][10] != 0) first_four_count++;
	if(board[10][4] != 0) first_four_count++;
	if(board[10][10] != 0) first_four_count++;

	/* Set first four step score board */
	float score_board[14][14];
	for(int y=0;y<14;y++)
	{
		for(int x=0;x<14;x++)
		{
			if((y==4&&x>=4&&x<=10)||(y==10&&x>=4&&x<=10)||(x==4&&y>=4&&y<=10)||(x==10&&y>=4&&y<=10)) score_board[y][x] = 1;
			else if((y==5&&x>=5&&x<=9)||(y==9&&x>=5&&x<=9)||(x==5&&y>=5&&y<=9)||(x==9&&y>=5&&y<=9)) score_board[y][x] = 1.1;
			else score_board[y][x] = 0;
		}
	}
	
	int chess_remain_num[2];
	chess_remain_num[0] = 0;
	chess_remain_num[1] = 0;
	for(int i=0;i<9;i++) {if(chess_remain[i]) chess_remain_num[0]++;}
	for(int i=0;i<9;i++) {if(chess_remain[9+i]) chess_remain_num[1]++;}

	if(chess_remain_num[turns-1]==0){
		bestlist[0]=999999;
		return bestlist;
	}

	
	
	int returndata = 0;
	
	float MaxValue = 0;
	int MaxDir,Max_pos_x,Max_pos_y,Max_chess;
		int aa=0;

	int chess_type = 0;
	if(first_four_count<4)
	{
		/* Set chess table (4 point ,2 direction*6 type of chess,) */
		int chess_table[4][12];
		int table_value = 0;
		set_chess_table(chess_table);
		
		/* Get random point */
		int random = rand()%(4-first_four_count)+1;
		
		bool ff[4];
		for(int i=0;i<4;i++) ff[i] = false;
		if(board[4][4] != 0) ff[0] = true;
		if(board[4][10] != 0) ff[1] = true;
		if(board[10][4] != 0) ff[2] = true;
		if(board[10][10] != 0) ff[3] = true;
		
		int counter = 0;

		for(int i=0;i<4;i++)
		{
			if(!ff[i]) counter++;
			
			if(counter == random)
			{
				/* Random step */
				int random_step = rand()%12;
				if(!chess_remain[random_step/2 + (turns-1)*9]) 
					random_step = (random_step+2 > 11) ? 8: random_step+2;
				
				table_value = chess_table[i][random_step];
				
				int pos_x = table_value/10000;
				int pos_y = (table_value/100)%100;
				int direction = (table_value/10)%10;
				int ctype = table_value%10;
				
				bool choose_again = false;
				int hold_x,hold_y;
				set_cover(cover,ctype,pos_x,pos_y,direction);
				
				/* Check if cover */
				for(int s=0;s<cover.size();s++)
				{
					hold_x=cover[s].first;
					hold_y=cover[s].second;

					if(hold_x>13||hold_x<1||hold_y>13||hold_y<1) choose_again = true;
					if(board[hold_y][hold_x]!=0)//the cover is chosen before
					{
						choose_again = true;
						break;
					}
				}
				
				if(!choose_again )
				{
					/*for(int s=0;s<cover.size();s++)
					{
						hold_x=cover[s].first;
						hold_y=cover[s].second;
						board[hold_y][hold_x] = turns;//store cover in the board
					}*/
					
					returndata = 10000*pos_x+100*pos_y+10*direction+ctype;
					cover.clear();
				}
				else
				{
					cover.clear();
					random_step = (random_step+2 > 11) ? 9: random_step+2;
					
					returndata = chess_table[i][random_step];
					
				}
				break;
			}
				
		}
		
		
		
		bestlist[index]=returndata;
	}
	else
	{
		for(int chess_counter=0;chess_counter<9;chess_counter++)	// Select chess type
		{
			if(type%2==1){
				do{
					chess_counter = rand()%9;
				}while(!chess_remain[(turns-1)*9+chess_counter]);
			}
			if(!chess_remain[(turns-1)*9+chess_counter]) continue;
			for(int pos_counter=0;pos_counter<Pos_around_area.size;pos_counter++)	// Select position
			{
				for(int direction=0;direction<4;direction++)	// Select direction
				{
					int center_num = (chess_counter==7 || chess_counter ==8) ? 1:4;
					for(int center_counter=1;center_counter<=center_num;center_counter++)	// Select center
					{
						cover.clear();
						correction_factor factor = center_correct(chess_counter,direction,center_counter-1);	//Get correction factor
						
						int pos_x = Pos_around_area.x[pos_counter]+factor.x;
						int pos_y = Pos_around_area.y[pos_counter]+factor.y;
						
						if(pos_x>13 || pos_x<1 ||pos_y>13 || pos_y<1 ||board[pos_y][pos_x] !=0 ) continue;
						
						
						bool choose_again = false;
						bool step_check = set_cover(cover,chess_counter,pos_x,pos_y,direction);	//Get the chess cover on board
						
						int hold_x,hold_y;
						if(step_check)
						{
							int contact_num = 0;
							int contact_edge_num = 0;
							for(int s=0;s<cover.size();s++)
							{
								hold_x=cover[s].first;
								hold_y=cover[s].second;
								
								if(board[hold_y][hold_x-1]==turns && hold_x-1>=1) contact_num++;
								if(board[hold_y][hold_x+1]==turns && hold_x+1<=13) contact_num++;
								if(board[hold_y-1][hold_x]==turns && hold_y-1>=1) contact_num++;
								if(board[hold_y+1][hold_x]==turns && hold_y+1<=13) contact_num++;
								
								if(hold_x == 13 || hold_x == 1) contact_edge_num++;
								if(hold_y == 13 || hold_y == 1) contact_edge_num++;
								
								if(hold_x>13||hold_x<1||hold_y>13||hold_y<1) choose_again = true;
								if(board[hold_y][hold_x]!=0)//the cover is chosen before
								{
									choose_again = true;
									break;
								}
							}
							
							if(contact_num > 2 || contact_edge_num > 2) choose_again = true;
							
							if(!choose_again)
							{
								for(int s=0;s<cover.size();s++)
								{
									hold_x=cover[s].first;
									hold_y=cover[s].second;
									board[hold_y][hold_x] = turns;//store cover in the board
								}
								
								float MapValue = (type==3)?SetDisMap(board,turns,true):SetDisMap(board,turns,false);
								if(1)
								{
									bool exist = false;
									int id = 10000*pos_x+100*pos_y+10*direction+chess_counter;
									for(int i=0;i<existpos.size();i++)
									{
										if(id == existpos[i]->id)
										{
											exist = true;
											break;
										}
									}
									if(!exist){
										MaxValue = MapValue;
										MaxDir = direction;
										Max_chess = chess_counter;
										Max_pos_x = pos_x;
										Max_pos_y = pos_y;
										aa++;
										if(index<10){
											bestvalue[index]=MaxValue;
											bestlist[index]=10000*Max_pos_x+100*Max_pos_y+10*MaxDir+Max_chess;
											index++;
										}else{
											int min=MaxValue,min_index=0;
											for(int i=0;i<10;i++){
												if(MaxValue>bestvalue[i] && min>bestvalue[i]){
													min = bestvalue[i];
													min_index = i;
												}
											}
											bestvalue[min_index]=MaxValue;
											bestlist[min_index]=10000*Max_pos_x+100*Max_pos_y+10*MaxDir+Max_chess;
										}
										
									}
								}
										
								//recover
								for(int s=0;s<cover.size();s++)
								{
									hold_x=cover[s].first;
									hold_y=cover[s].second;
									board[hold_y][hold_x] = 0;//recover to the origin
								}
							}
						}
						cover.clear();
					}
				}
				

			}
			if(type%2==1)break;
		}//		cout<<"aa = "<<aa<<endl;
//		returndata = 10000*Max_pos_x+100*Max_pos_y+10*MaxDir+Max_chess;
		int t;
		for(int i=0;i<10;i++){
			for(int j=i;j<10;j++){
				if(bestvalue[i]<bestvalue[j]){
					t=bestvalue[i];
					bestvalue[i]=bestvalue[j];
					bestvalue[j]=t;
					t=bestlist[i];
					bestlist[i]=bestlist[j];
					bestlist[j]=t;
				}
			}
		}
	}

	//if(type==2) cout<<"aa = "<<aa<<endl;
	
	return bestlist;
}

int* GetDistanceMapMove(int board[14][14],int turns,bool chess_remain[18],vector<MCTNode*> existpos){
	return DistanceMapMove(board,turns,chess_remain,existpos,2);
}
int GetSingleDistanceMapMove(int board[14][14],int turns,bool chess_remain[18],vector<MCTNode*> existpos){
	int *newlist = DistanceMapMove(board,turns,chess_remain,existpos,3);
	return newlist[0];
}
int GetSingleDistanceMapMoveAcc(int board[14][14],int turns,bool chess_remain[18],vector<MCTNode*> existpos){
	int *newlist = DistanceMapMove(board,turns,chess_remain,existpos,1);
	return newlist[0];
}
int rollout(int b[14][14],int turns,bool chess_r[18],int depth,int type){
	
	int board[14][14];
	bool chess_remain[18];
	for(int i=0;i<14;i++){ for(int j=0;j<14;j++)board[i][j]=b[i][j];};
	for(int i=0;i<18;i++) chess_remain[i]=chess_r[i];
	vector< pair<int,int> > data_cover;
	vector<MCTNode*> null;
	
	int chess_remain_num[2];
	chess_remain_num[0] = 0;
	chess_remain_num[1] = 0;
	for(int i=0;i<9;i++) {if(chess_remain[i]) chess_remain_num[0]++;}
	for(int i=0;i<9;i++) {if(chess_remain[9+i]) chess_remain_num[1]++;}
	
	int returndata,direction,pos_x,pos_y,ctype;
	int d=0;
	while(d<depth&&(chess_remain_num[0]>0 || chess_remain_num[1]>0))
	{
		returndata = (type==3)?GetSingleDistanceMapMove(board,turns,chess_remain,null):GetSingleDistanceMapMoveAcc(board,turns,chess_remain,null);
		pos_x = returndata/10000;
		pos_y = (returndata/100)%100;
		direction = (returndata/10)%10;
		ctype = returndata%10;
		
		set_cover(data_cover,ctype,pos_x,pos_y,direction);
		
		int hold_x,hold_y;
		for(int s=0;s<data_cover.size();s++)
		{
			hold_x=data_cover[s].first;
			hold_y=data_cover[s].second;
			board[hold_y][hold_x] = turns;//store cover in the board
		}
		
		chess_remain_num[turns-1]--;
		chess_remain[(turns-1)*9+ctype] = false;
		turns = (turns == 1)?2:1;
		data_cover.clear();
		d++;
	}
	
	GameBoard game(board);
	
	return game.result();
}
