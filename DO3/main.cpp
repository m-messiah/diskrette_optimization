#include <fstream>
#include <limits>
using namespace std;

struct apex { int n; int c; apex *next;};
apex *net;
int *A, *D,*parent;
int m,start,finish;
const int inf=numeric_limits<int>::max();
void readnet ()
	  {
			int r,k;
			apex *last, *temp;
			ifstream fi("in.txt");
			fi>>m;
			net=new apex [m+1];
			for (int i=1; i<m+1;i++)
			{
				net[i].n=i;
				net[i].c=0;
				net[i].next=0;
				last=&net[i];
				do{
					fi>>r;
					if (r) {fi>>k;
							temp = new apex();
							temp->n=r;
							temp->c=k;
							last->next=temp;
							last=last->next;
							}
				}while(r);
			} 
			fi>>start>>finish;
			fi.close();
		}
void matrix_weight()
{
	A=new int [(m+1)*(m+1)];
	for (int i=1;i<m+1;i++) 
		{ 
		for (int j=1;j<m+1;j++)	A[i*(m+1) + j]=inf;	
		A[i*(m+1) + i]=0;
		}
	for (int i=1;i<m+1;i++)
	{
		apex *temp=net[i].next;
		while(temp)
		{
			A[i*(m+1) + temp->n]=temp->c;
			temp=temp->next;
		}
	}

}

void fill_D()
{
	D = new int [m+1];
	parent = new int [m+1];
	D[start]=0;
	for (int v=1;v<m+1;v++)	if (v!=start)	{D[v]=A[start*(m+1) + v]; parent[v]=start;}
	for (int k=2;k<m;k++)
		for (int v=1;v<m+1;v++) if(v!=start)
			for (int w=1;w<m+1;w++)
				if (D[v]>(D[w]+(A[w*(m+1) + v]==inf?(A[w*(m+1) + v]-D[w]):A[w*(m+1) + v])))
					{ D[v]=D[w]+A[w*(m+1) + v]; parent[v]=w;}
}

struct tknot {int v; tknot* next;} *stack;
void add_compon (tknot*& st, int v)
{
	tknot* us = new tknot;
	us->v=v;
	us->next=st;
	st=us;
}
void fill_stack()
{
	stack=0;
	add_compon(stack,finish);
	int v=finish;
	while (v!=start) {v=parent[v]; add_compon(stack,v);}
}

int main()
{
	readnet();
	matrix_weight();
	fill_D();
	fill_stack();
	tknot *temp=stack->next;
	ofstream fo("out.txt");
	if (D[finish]==inf) fo<<"N";
	else { fo<<"Y\n"<<start;
		while(temp) { fo<<" "<<temp->v; temp=temp->next;}
		fo<<"\n"<<D[finish];
	}
	fo.close();
	return 0;
}