#include <iostream>
#include <vector>
#include <fstream>

#define MAX 32767
using namespace std;

vector<int> G2B( MAX, 0 );       // G2B[g] Ч мальчик, который назначен девочке "g"
vector< vector<int> > W( MAX );  // W[b] Ч список смежных девочек мальчика "b"

int k;  // мальчик, начина€ с которого мы ищем улучшающий путь
        // и одновременно цвет, в который мы закрашиваем всех мальчиков, до которых
        // мы можем добратьс€ из мальчика k.

vector<int> V(MAX, 0); // цвета вершин-мальчиков

int dfs( int b ) {
    if( V[b] != k ) {
        V[b] = k;
        for( int j = 0; j < W[b].size(); j++ ) {
            if( G2B[ W[b][j] ] == 0 || dfs( G2B[ W[b][j] ] ) ) {
                G2B[ W[b][j] ] = b;
                return 1;
            }
        }
    }
    return 0;
}

void read(int &Ng,int &Nb){
	ifstream fi = ifstream("in.txt");
	int m;
	fi>>Ng>>Nb>>m;
	int *a=new int[m];

	for (int i=1;i<m+1;i++) fi >> a[i];
	for (int i=1;i<=Ng;i++)
	{
		int end=(i==Ng)?m:a[i+1];
		for (int j=a[i];j<end;j++)
		{
			W[a[j]].push_back(i);
		}
		
	}
	fi.close();
}

int main() {
    int Ng, Nb;     // число девочек и число мальчиков
    int g, b, res;
	read(Ng,Nb);
    for(k = 1, res = 0; k <= Nb; k++) {
      res += dfs(k);
   }
	ofstream fo = ofstream("out.txt");
	
    for(g = 1; g < Ng; g++) 
        if( G2B[g] != 0 ) 
			fo<<G2B[g]<<" ";
		else 
			fo<<"0 ";
	if (G2B[Ng]!=0)
		fo<<G2B[Ng];
	else
		fo<<"0";
	fo.close();
    return 0;
}