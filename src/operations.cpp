#include "operations.h"

// Declare all DS
process PCB[16];
resource RCB[4];
list<int> RL;

// Operations on Processes
void create() {}
void destroy(process j) {}

// Operations on Resources
void request(resource r) {}
void release(resource r) {}

// Timesharing and the Scheduler
void timeout() {}
void scheduler() {}

// Initialize
void init()
{
	// Potentially release resources

	/*
	 * Process Control Block Init
	 * false = blocked, true = ready
	 */
	PCB[0] = { false, 0, {}, {} }
	for (int i = 1; i < 16 - 1; i++) {
		PCB[i] = { false, 0, {}, {} };
	}

	// Add process 0 to the Ready List
	RL.push_front(0);

	/*
	 * Resource Control Block Init
	 * false = free
	 */
	for (int i = 0; i < 4 - 1; i++) {
		RCB[i] = { false, {} };
	}
}