#include <fstream>
#include <iostream>
using namespace std;

int AB_d, N;
int capacity,consumption;
float money, *D;
int *parent, *index;
const int inf=numeric_limits<int>::max(); //inf = pseudo infinity

struct gas_st { float c;//cost
		int d;//distance 
		int n; //number
		gas_st *next;
		 } *net_next, *net;
void reading()
{
	ifstream f("in.txt");
	f>>AB_d>>capacity>>consumption;
	f>>money;
	f>>N;
	net_next=new gas_st[N+2];
	for (int i=1; i<N+1;i++)
		f>>net_next[i].d>>net_next[i].c;
	f.close();
}
void net_next_create()
{
	net_next[0].d=0;
	net_next[0].c=money/capacity;
	net_next[N+1].d=AB_d;
	net_next[N+1].next=0;
	net_next[N+1].n=N+1;
	net_next[N+1].c=0;
	float s=capacity*consumption;
	for (int j=0;j<N+1;j++)
	{
		net_next[j].next=0;
		gas_st *last=&net_next[j];
		for (int i=j+1; i<N+2;i++)
			if ((net_next[i].d-net_next[j].d)<=s)
				if (((net_next[i].d-net_next[j].d)*1.0/consumption)>=(capacity*1.0/2))
				{
					gas_st *temp=new gas_st;
					temp->d=net_next[i].d;
					temp->c=net_next[i].c;
					temp->n=i;
					temp->next=0;
					last->next=temp;
					last=last->next;
				}
	}
}

void net_next2last()
{
	net = new gas_st[N+2];
	for (int i=0;i<N+2; net[i].n=i++) net[i].next=0;
	for (int i=0; i<N+2;i++)
	{
		gas_st *last=net_next[i].next;
		while (last)
		{
			gas_st *temp=&net[last->n];
			while (temp->next) { temp=temp->next;}
			temp->next=new gas_st;
			temp->next->n=i;
			temp->next->d=last->d-net_next[i].d;
			if (last->c) temp->next->c=floor((20+(last->c)*(temp->next->d*1.0/consumption))*10+0.5)/10;
			else temp->next->c=0;
			temp->next->next=0;
			last=last->next;
		}
	}
}

void find_path()
{
	D=new float [N+2];
	parent = new int [N+2];
	for (int i=1; i<N+2; i++) {D[i]=inf; parent[i]=0;}
	D[0]=0;
	for (int i=1;i<N+2;i++)
	{	gas_st *temp=net[i].next;
		while (temp)
		{
			if ((D[temp->n]!=inf) && (D[i]>D[temp->n]+temp->c))
			{
			D[i]=D[temp->n]+temp->c;
			parent[i]=temp->n;
			}
			temp=temp->next;
		}
	}
}

struct tknot {int v; tknot* next;} *stack; //STACK for topol_sort
void add_compon (tknot*& st, int v)
{
	tknot* us = new tknot;
	us->v=v;
	us->next=st;
	st=us;
}
int read_del_compon(tknot *& st)
{
	int v=st->v;
	tknot *temp=st;
	st=st->next;
	delete temp;
	return v;
}

int main()
{
	reading();
	net_next_create();
	net_next2last();
	find_path();
	int i=N+1;
	tknot *par=0;
	ofstream fo("out.txt");
	while (parent[i]!=0)
	{
		add_compon(par,parent[i]);
		i=parent[i];
	}
	fo.precision(2);
	fo<<fixed<<D[N+1]+money<<endl;
	fo<<read_del_compon(par);
	while (par)
	{
		fo<<" "<<read_del_compon(par);
	}
	fo.close();
return 0;
}
