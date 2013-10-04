#include "graph.h"
//struct apex {int n; apex* next;};
void readgraf (ifstream & fi,  apex* graf, int& m)
{
	int r;
	apex *last, *temp;
	fi>>m;
	for (int i=0; i<m; i++)
	{ graf[i].n=i; graf[i].next=0;}
	for (int i=0; i<m; i++)
	{
		last=&graf[i];
		do 
		{ fi>>r;
		if(r) {temp=new apex;
		temp->n=r-1;
		temp->next=0;
		last->next=temp;
		last=temp;}
		} while (r);
	}
}
void writegraf (ofstream& fo, apex* graf, int m)
{
	apex *temp;
	bool fl=false;
	fo<<m<<endl;
	for (int i=0; i<m; i++)
	{
		temp=graf[i].next;
		while (temp) 
		{	
			fo<<temp->n+1<<" ";
			temp=temp->next;
		}
		fo<<"0\n";
	}
}