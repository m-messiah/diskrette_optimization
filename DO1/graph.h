#ifndef GRAPH_H
#define GRAPH_H
#include <fstream>
using namespace std;
struct apex {int n; apex* next;};
//apex graf[maxn];
void readgraf (ifstream & fi,  apex* graf, int& m);
void writegraf (ofstream& fo, apex* graf, int m);
#endif