#include "operations.h"

using namespace std;

// Declare all DS
process PCB[16];
resource RCB[4];
list<int> RL;

// Operations on Processes
void create()
{
	int index;

	// Find next process to be created
	auto it = find_if(begin(PCB), end(PCB), [](const auto& p) {
		return p.state == false;
		});
	if (it != end(PCB)) {
		index = it - begin(PCB);
	}
	else {
		cout << "error" << endl;
		return;
	}

	// Check who the parent is, update parent
	int parent_index = RL.front();
	PCB[parent_index].children.push_back(index);

	// Allocate new pcb[index]
	PCB[index] = { true, parent_index, {}, {} };

	// Push back onto RL
	RL.push_back(index);

	cout << "Process " << index << " created" << endl;
}

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
	for (int i = 1; i < 15; i++) {
		PCB[i] = { false, 0, {}, {} };
	}

	// Add process 0 to the Ready List
	RL.push_front(0);

	/*
	 * Resource Control Block Init
	 * false = free
	 */
	for (int i = 0; i < 3; i++) {
		RCB[i] = { false, {} };
	}
}