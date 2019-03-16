#include<bits/stdc++.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
using namespace std;
class board
{
	public:
	char **a;
	void give_size()
	{
		int i;
		a=new char*[40];
		for(i=0;i<40;i++)
		{
			a[i]=new char[80];
		}
	}
	void initialise_board()
	{
		int i,j;
		for(i=0;i<40;i++)
		{	
			for(j=0;j<80;j++)
			{
				if(i==0||j==0||i==39||j==79)
				{
					a[i][j]='*';
				}
				else
				{
					a[i][j]=' ';
				}
			}
		}
	}
};
class player
{
	public:
	char pvalue;
	int px;
	int py;
	player()
	{
		pvalue='P';
		px=36;
		py=39;
	}
	player(char ch)
	{
		px=1;
		py=rand()%77+1;
		pvalue=ch;
	}
	player(int x,int y,char ch)
	{
		px=x;
		py=y;
		pvalue=ch;
	}
	void on_board(board &b)
	{
		b.a[px][py]=pvalue;
	}
	int update_player(board &b,char ch)
	{
		if(ch=='w')
		{
			b.a[px][py]=' ';
			px--;
		}
		else if(ch=='s')
		{
			b.a[px][py]=' ';
			px++;
		}
		else if(ch=='d')
		{
			b.a[px][py]=' ';
			py++;
		}
		else if(ch=='a')
		{
			b.a[px][py]=' ';
			py--;
		}
		b.a[px][py]=pvalue;
		if(px==39||px==0||py==0||py==79)
			return 1;
		return 0;
	}
	void increase_enemy(vector<player> &enemy,board &b)
	{
		player p('|');
		enemy.push_back(p);
		b.a[1][p.py]=p.pvalue;
	}
	void print(board b)
	{
		int i,j;
		for(i=0;i<40;i++)
		{
			for(j=0;j<80;j++)
			{
				cout<<b.a[i][j];
			}
			cout<<endl;
		}
	}
	int update_enemy(vector<player> &enemy,board &b)
	{
		if(enemy[0].px==38)
		{
			if(px==38&&py==enemy[0].py)
			{
				b.a[px][py]='E';
				return 1;
			}
			b.a[38][enemy[0].py]=' ';
			enemy.erase(enemy.begin());
		}
		int i;
		for(i=0;i<enemy.size();i++)
		{
			if((px==enemy[i].px||px==enemy[i].px+1)&&py==enemy[i].py)
			{
				b.a[px][py]='E';
				b.a[px-1][py]=' ';
				return 1;
			}
			b.a[enemy[i].px][enemy[i].py]=' ';
			enemy[i].px++;
			b.a[enemy[i].px][enemy[i].py]=enemy[i].pvalue;
		}
		return 0;
	}
	void add_goli(board &b,vector<player> &goli,vector<player> &enemy)
	{
		player p(px-1,py,'"');
		goli.push_back(p);
		b.a[p.px][p.py]='"';
	}
	void update_goli(board &b,vector<player> &goli,vector<player> &enemy)
	{
		int i,j;
		for(i=0;i<goli.size();i++)
		{
			for(j=0;j<enemy.size();j++)
			{
				if(goli.size()!=0&&(goli[i].px==enemy[j].px||goli[i].px+1==enemy[j].px)&&(goli[i].py==enemy[j].py))
				{
					b.a[goli[i].px][goli[i].py]=' ';
					goli.erase(goli.begin()+i);
					enemy.erase(enemy.begin()+j);
				}
			}
		}
		if(goli.size()!=0&&goli[0].px==1)
		{
			b.a[1][goli[0].py]=' ';
			goli.erase(goli.begin());
		}
		for(i=0;i<goli.size();i++)
		{
			b.a[goli[i].px][goli[i].py]=' ';
			goli[i].px--;
			b.a[goli[i].px][goli[i].py]='"';
		}
	}
};
int main()
{
	int t=0;
	char ch;
	board b;
	b.give_size();
	b.initialise_board();
	player p;
	p.on_board(b);
	vector<player> enemy;
	vector<player> goli;
	p.increase_enemy(enemy,b);
	while(1)
	{
		p.update_goli(b,goli,enemy);
		if(kbhit())
		{
			ch=getch();
			if(ch=='w'||ch=='s'||ch=='d'||ch=='a')
			{
				if(p.update_player(b,ch))
				{
					p.print(b);
					break;
				}
			}
			else if(ch==' ')
			{
				p.add_goli(b,goli,enemy);
			}
		}
		if(p.update_enemy(enemy,b))
		{
			p.print(b);
			break;
		}
		t++;
		if(t==5)
		{
			p.increase_enemy(enemy,b);
			t=0;
		}
		p.print(b);
		system("CLS");
	}
	cout<<"game over";
}