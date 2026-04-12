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

void destroy(int j, int &npd)
{
	auto children_copy = PCB[j].children;
	for (int i : children_copy) {
		destroy(i, npd);
	}

	PCB[PCB[j].parent].children.remove(j);
	RL.remove(j);
	for (int r = 0; r < 4; r++;) RCB[r].waitlist.remove(j);
	release_all(j);
	PCB[j] = { false, 0, {}, {} };
	npd++;
}

// Operations on Resources
void request(int r)
{
	int curr_p_index = RL.front();

	if (RCB[r].state == false) {
		RCB[r].state = true;
		PCB[curr_p_index].resources.push_back(r);
		cout << "resource " << r << " allocated" << endl;
	}
	else {
		PCB[curr_p_index].state = false;
		RL.remove(curr_p_index);
		RCB[r].waitlist.push_back(curr_p_index);
		cout << "process " << curr_p_index << " blocked" << endl;
		scheduler();
	}	
}

void release(int r) 
{
	int curr_p_index = RL.front();
	
	PCB[curr_p_index].resources.remove(r);
	if (RCB[r].waitlist.empty()) {
		RCB[r].state = false;
	}
	else {
		int wait_front_i = RCB[r].waitlist.front();
		RCB[r].waitlist.pop_front();
		RL.push_back(wait_front_i);
		PCB[wait_front_i].state = true;
		PCB[wait_front_i].resources.push_back(r);
	}

	cout << "resource " << r << " released" << endl;
}

// Timesharing and the Scheduler
void timeout() 
{
	int running = RL.front();
	RL.pop_front();
	RL.push_back(running);
	scheduler();
}

void scheduler() 
{
	cout << "process " << RL.front() << " running" << endl;
}

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