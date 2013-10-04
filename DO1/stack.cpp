#include "stack.h"
//struct tknot {int x; tknot* next};
void new_null (tknot*& st)
{
	st=0;
}
bool check_empty (tknot*& st)
{
	return st==0;
}
void add_compon (tknot*& st, apex task)
{
	tknot* us = new tknot;
	us->task=task;
	us->next=st;
	st=us;

}
void read_compon (tknot*& st, apex &task)
{
	task=st->task;
}
void del_compon (tknot*& st)
{
	tknot* us = st;
	st=st->next;
	delete us;
}
void destr (tknot*& st)
{
	while (!check_empty (st)) del_compon(st);
}