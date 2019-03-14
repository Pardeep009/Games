#include<bits/stdc++.h>
#include<conio.h>
using namespace std;
void intialise_board(char **board)
{
	int cnt=1;
	int i,j;
	for(i=0;i<5;i++)
	{
		for(j=0;j<5;j++)
		{
			if(i==1||i==3)
				board[i][j]='_';
			else if(j==1||j==3)
				board[i][j]='|';
			else
			{
				board[i][j]=cnt+'0';
				cnt++;
			}
		}
	}
}
void print_board(char **board)
{
	int i,j;
	for(i=0;i<5;i++)
	{
		for(j=0;j<5;j++)
		{
			cout<<board[i][j];
		}
		cout<<endl;
	}
}
int check_move(char **board,int p,int q)
{
	int i,j;
	for(i=2;i<5;i=i+2)
	{
		if(board[i-2][q]!=board[i][q])
			break;
		if(i==4)
			return 1;
	}
	for(i=2;i<5;i=i+2)
	{
		if(board[p][i-2]!=board[p][i])
			break;
		if(i==4)
			return 1;
	}
	if(p==q)
		for(i=2;i<5;i=i+2)
		{
			if(board[i-2][i-2]!=board[i][i])
				break;
			if(i==4)
				return 1;
		}
	else
	{
		j=4;
		for(i=0;i<3;i=i+2)
		{
			if(board[i+2][j-2]!=board[i][j])
				break;
			if(i==2)
				return 1;
			j=j-2;
		}
	}
	if(p==2&&q==2)
	{
		j=4;
		for(i=0;i<3;i=i+2)
		{
			if(board[i+2][j-2]!=board[i][j])
				break;
			if(i==2)
				return 1;
			j=j-2;
		}
	}
	return 0;
}
int update_board(char **board,int p,int f)
{
	int i,j,k;
	for(i=0;i<5;i++)
	{
		for(j=0;j<5;j++)
		{
			if(board[i][j]==p+'0')
			{
				if(f%2==0)
					board[i][j]='O';
				else
					board[i][j]='X';
				k=check_move(board,i,j);
				return k;
			}
		}
	}
	
}
int main()
{
	int i,p,f=0,k;
	int h[10];
	for(i=0;i<10;i++)
		h[i]=0;
	char **board;
	board=new char*[5];
	for(i=0;i<5;i++)
	{
		board[i]=new char[5];
	}
	intialise_board(board);
	print_board(board);
	i=0;
	while(i<9)
	{
		cout<<"Enter position"<<endl;
		cout<<"Player "<<i%2+1<<" turn"<<endl;
		cin>>p;
		while(h[p])
		{
			cout<<"Enter new place,previously filled place cannot be filled again\n"<<endl;
			cin>>p;
		}
		h[p]=1;
		k=update_board(board,p,i);
		if(k==1)
		{
			print_board(board);
			cout<<"Player "<<i%2+1<<" is the winner";
			break;
		}
		i++;
		system("CLS");
		print_board(board);
	}
	if(i==9)
		cout<<"match drawn";
}
