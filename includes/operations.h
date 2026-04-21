#pragma once
#include "structures.h"
#include <list>
using std::list;

extern process PCB[16];
extern resource RCB[4];
extern list<int> RL[3];

void create(int p);
void destroy(int j, int& npd);
void request(int r, int num_rq);
void release(int r, int num_rq);
void timeout();
void scheduler();
void init();