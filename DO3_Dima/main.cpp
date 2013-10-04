/****************************************
**   DO. Path of max weight.           **
**  This program is published "as is"  **
**  ================================   **
**  Copyleft by Messiah, under GNU GPL **
****************************************/

#include <fstream>
#include <limits> //for inf
using namespace std;
const int inf=numeric_limits<int>::min(); //inf = negative pseudo infinity
struct apex { int n; int c; apex *next;} *net; //NET for PRED
int m,start,finish,nomer;
int *index, *ishod, *D, *parent;
void readnet () {
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
void topol_sort()  //iz tetradi
{
	index = new int [m+1];
	ishod = new int [m+1];
	apex *temp;
	for (int i=1; i<m+1; ishod[i++]=0);
	for (int i=1; i<m+1; i++)
	{
		temp=net[i].next;
		while(temp) 
		{
			ishod[temp->n]++;
			temp=temp->next;
		}
	}
	stack=0;
	nomer=m;
	for (int v=1;v<m+1;v++) if (!ishod[v]) add_compon(stack,v);
	while (stack)
	{
		int v=read_del_compon(stack);
		index[v]=nomer--;
		temp=net[v].next;
		while(temp) 
		{
			ishod[temp->n]--;
			if (!ishod[temp->n]) add_compon(stack,temp->n);
			temp=temp->next;
		}
	}
}
void measurements()   //Определение наименьшего расстояния в б/к сети, 
{					  //модифицирован на поиск наибольшего и с запоминанием предка.
	D=new int [m+1];
	parent = new int [m+1];
	for (int i=1; i<m+1; i++) {D[i]=inf; parent[i]=0;}
	D[index[start]]=0;
	for (int ind=1;ind<m+1;ind++)
	{
		int i;
		for (i=1;i<m+1;i++) if (index[i]==ind) break;
		apex *temp=net[i].next;
		while (temp)
		{
			if (D[i]<D[temp->n]+temp->c)
			{
				D[i]=D[temp->n]+temp->c;
				parent[i]=temp->n;
			}
			temp=temp->next;
		}
	}
}

int main()
{
	readnet();
	topol_sort();
	measurements();
	ofstream fo("out.txt");
	if (D[finish]==inf) fo<<"N";
	else 
	{ fo<<"Y"<<endl;
	int i=finish;
	tknot *par=0;
	add_compon(par,finish);
	while (i!=start)
	{
		add_compon(par,parent[i]);
		i=parent[i];
	}
	fo<<read_del_compon(par);
	while (par)
	{
		fo<<" "<<read_del_compon(par);
	}
	fo<<endl<<D[finish];
	}
	fo.close();
	return 0;
}

/*
         .'@@'.         
       @@@@@@@@@@       
     #@@@@@@@@@@@@#     
    @@@@.      .@@@@    
   @@@;          ;@@@   
  #@@.    .;;`    .@@#  
  @@;   +@@@@@@:   ;@@  
 @@@   @@@@@@@@@#   @@@ 
 @@.  +@@@@,:@@@@,  .@@ 
.@@   @@@.    '@@@   @@.
'@@  .;;;      @@@   @@'
@@@            '@@,  @@@
@@@            '@@,  @@@
'@@  `:::      @@@   @@'
.@@   @@@.    '@@@   @@.
 @@.  +@@@@,:@@@@,  .@@ 
 @@@   @@@@@@@@@#   @@@ 
  @@;   +@@@@@@:   ;@@  
  #@@.    .;;`    .@@#  
   @@@;          ;@@@   
    @@@@.      .@@@@    
     #@@@@@@@@@@@@#     
       @@@@@@@@@@       
         .'@@'.         


*/