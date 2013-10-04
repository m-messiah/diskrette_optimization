#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct apex { int n; int c; apex *next;};
struct edge {int v;int w; int c;};
struct knot {edge v; knot* next;};
bool comparator(edge *i,edge *j) {return (i->c<j->c);}
class Queue //Очередь
{
public:
	knot *st;
	Queue ()
		{
		st=0;
		}
	bool is_empty ()
	{
		return st==0;
	}
	void add (edge v)
	{
		knot* us= new knot;
		us->v=v;
		us->next=0;
		if (!st) st=us; 
		else {	knot* r=st;
		while (r->next) r=r->next;
		r->next=us;	
		}
	}
	edge& get ()
	{
		return st->v;
	}
	void del ()
	{
		knot* us = st;
		st=st->next;
		delete us;
	}
	~Queue ()
	{
		while (!is_empty ()) del();
	}
};
class Graph
{
public:	
	apex *graf;
	int m,weight;

	Graph(int N) 
	{m=N; weight=0; graf=new apex [N];}
	Graph(vector<edge*> T)
	{	
		weight=0;
		int max=0;
		for (int i=0;i<abs((int)T.size());i++)
			{	
				if ((T[i]->w)>max) max=T[i]->w;
				if ((T[i]->v)>max) max=T[i]->v;
			}
		m=max;
		graf=new apex [max];
		for (int i=0;i<m;i++) {graf[i].n=i; graf[i].c=-1; graf[i].next=0;}
		for (int j=0;j<m;j++)
		{
			apex *current=&graf[j];
			for (int i=0;i<abs((int)T.size());i++)
			{
				if (((T[i]->v-1)==j) || ((T[i]->w-1)==j))
					{
						apex *temp=new apex;
						if ((T[i]->w-1)==j) temp->n=T[i]->v;
						else temp->n=T[i]->w;
						temp->c=T[i]->c;
						weight+=temp->c;
						T[i]->c=0;
						temp->next=0;
						current->next=temp;
						current=current->next;
					}
			}
		}
	}
	~Graph(){delete [] graf;};
	void sortgraf()
	{
		for (int i=0;i<m;i++)
		{
			bool fl=true;
			while(fl)
			{
				fl=false;
				apex *temp=&graf[i];
				while(temp->next->next) 
				{
					if ((temp->next->n)>(temp->next->next->n)) 
					{
						fl=true;
						int t=temp->next->n;
						temp->next->n=temp->next->next->n;
						temp->next->next->n=t;
						t=temp->next->c;
						temp->next->c=temp->next->next->c;
						temp->next->next->c=t;
					}
					temp=temp->next;
				}
			}
		}
	}
	void readgraf ()
	  {
			int r,k;
			apex *last, *temp;
			ifstream fi("in.txt");
			fi>>k;
			k--;
			int a[32767];
			for (int i = 0; i < k; i++) fi>>a[i];
			int j=0;
			if (a[j]!=m) while(a[j++]!=k+1);
			m=j-1; 
			for (int i=0; i<m; i++)
			{ graf[i].n = i; graf[i].next = 0; }   
			for (int i=0; i<m;i++)
			{
				r=a[i]-1;
				int l;
				if (a[i + 1] !=m+1) { l = a[i + 1]-1; } else { l = k-1; }
				last=&graf[i];
				for (int i=r;i<l; i=i+2)
				{
					temp = new apex();
					temp->n=a[i];
					temp->c=a[i+1];
					weight+=temp->c;
					last->next=temp;
					last=last->next;
				}
			} 
			fi.close();
		}
	void writegraf ()
		{
			apex *temp;
			ofstream fo("out.txt");
			fo<<m<<endl;
			for (int i=0; i<m; i++)
			{
				temp=graf[i].next;
				fo<<i+1<<" ";
				while(temp)
				{	
					fo<<temp->n<<" ";
					temp=temp->next;
				}
				fo<<"0\n";
			}
			fo<<weight;
			fo.close();
		}
	void edges(Queue& E)
	{	
		vector<edge*> sE;
		for (int i=0;i<m;i++)
		{	
			apex *temp=graf[i].next;
			while (temp) 
			{
				if (i+1<temp->n) 
				{   
					edge *e=new edge; 
					e->v=i+1; e->w=temp->n;
					e->c=temp->c;
					sE.push_back(e);

				}
				temp=temp->next;
				
			}
		}
		sort(sE.begin(),sE.end(),comparator);
		for (int i=0;i<abs((int)sE.size());i++) E.add(*sE[i]);
	}

};
//Globals
int *name,*sled,*size,p,q;

void merge(int v, int w)
{
	name[w]=p;	int u=sled[w];
	while(name[u]!=p)
	{
		name[u]=p; u=sled[u];
	}
	size[p]+=size[q];
	int vv=sled[v];	int ww=sled[w];
	sled[v]=ww; sled[w]=vv;
}

int main()
{
	Graph G(30);
	G.readgraf();
	Queue E;
	G.edges(E);
	name=new int[G.m];
	sled=new int[G.m];
	size=new int[G.m];
	for (int v=0;v<=G.m;v++) {name[v]=v; sled[v]=v; size[v]=1;}
	vector<edge*> T;
	while (abs((int)T.size())<(G.m-1))
	{
		edge *e=new edge(E.get()); E.del();
		p=name[e->v]; q=name[e->w];
		if (p!=q) 
		{	
			if (size[p]<size[q]) {swap(p,q); merge(e->w,e->v);}
			else merge(e->v,e->w);
			T.push_back(e);
		}
	}
	Graph GT(T);
	GT.sortgraf();
	GT.writegraf();
	return 0;
}