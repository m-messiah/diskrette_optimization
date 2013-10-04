#ifndef STACK_H //Esli imya otsutstvuet v preprocessore, to tekst budet rabotat`
#define STACK_H
#include "graph.h"
struct tknot {apex task; tknot* next;};
void new_null (tknot*& st);
bool check_empty (tknot*& st);
void add_compon (tknot*& st, apex task);
void read_compon (tknot*& st, apex &task);
void del_compon (tknot*& st);
void destr (tknot*& st);
#endif