#include "structure.h"

// Operations on Processes
void create();
void destroy(int j, int &npd);

// Operations on Resources
void request(int r);
void release(int r);

// Timesharing and the Scheduler
void timeout();
void scheduler();

// Initialize
void init();