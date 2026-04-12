#include "structure.h"

// Operations on Processes
void create();
void destroy(process j, int &npd);

// Operations on Resources
void request(resource r);
void release(resource r);

// Timesharing and the Scheduler
void timeout();
void scheduler();

// Initialize
void init();