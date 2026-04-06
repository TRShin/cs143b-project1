#include "operations.h"

// Declare all DS
process PCB[n];
resource RCB[n];
list<int> RL;

// Operations on Processes
void create() {}

void destroy(process j);

// Operations on Resources
void request(resource r);
void release(resource r);

// Timesharing and the Scheduler
void timeout();
void scheduler();

// Initialize
void init()
{
	for (int i = 1; i < n - 1; i++) {}
	for (int i = 0; i < n - 1; i++) {}
}