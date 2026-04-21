#include "operations.h"
#include "helpers.h"
#include <iostream>

using namespace std;

// Declare all DS
process PCB[16];
resource RCB[4];
list<int> RL[3];

// Operations on Processes
void create(int p)
{
	int index;

	// Find next process to be created
	auto it = find_if(begin(PCB), end(PCB), [](const auto& e) {
		return e.state == false;
		});
	if (it != end(PCB)) {
		index = it - begin(PCB);
	}
	else {
		cout << "error" << endl;
		return;
	}

	// Check who the parent is, update parent
	int parent_index = get_running(RL);
	PCB[parent_index].children.push_back(index);

	// Allocate new pcb[index]
	PCB[index] = { true, parent_index, p, {}, {} };

	// Push back onto RL
	RL[p].push_back(index);

	cout << "Process " << index << " created" << endl;

	scheduler();
}

void destroy(int j, int &npd)
{
	if (j != 0)
	{
		auto children_copy = PCB[j].children;
		for (int i : children_copy) {
			destroy(i, npd);
		}

		PCB[PCB[j].parent].children.remove(j);
		RL[PCB[j].priority].remove(j);

		for (int r = 0; r < 4; r++) {
			RCB[r].waitlist.remove_if([j](const std::pair<int, int>& p) { return p.first == j; });
		}
		release_all(j);
		PCB[j] = { false, 0, 0, {}, {} };
		npd++;
	}
}

// Operations on Resources
void request(int r, int num_rq)
{
	int curr_p_index = get_running(RL);

	if (num_rq > RCB[r].inventory) {
		cout << "error" << endl;
		return;
	}

	if (RCB[r].state >= num_rq) {
		RCB[r].state -= num_rq;
		PCB[curr_p_index].resources.push_back(r);
		cout << "resource " << r << " allocated" << endl;
	}
	else {
		PCB[curr_p_index].state = false;
		RL[PCB[curr_p_index].priority].remove(curr_p_index);
		RCB[r].waitlist.emplace_back(curr_p_index, num_rq);
		cout << "process " << curr_p_index << " blocked" << endl;
		scheduler();
	}	
}

void release(int r, int num_rq) 
{
	int curr_p_index = get_running(RL);
	for (int i = 0; i < num_rq; i++) {
		PCB[curr_p_index].resources.remove_if([](const pair<int, int>& p) { return p.first == j; });
	PCB[curr_p_index].resources.remove(r);
	RCB[r].state += num_rq;

	while (!RCB[r].waitlist.empty() && RCB[r].state >= RCB[r].waitlist.front().second) {
		auto wait_entry = RCB[r].waitlist.front();
		int wait_front_i = wait_entry.first;
		int wait_req = wait_entry.second;

		// Remove from waitlist, add to ready queue
		RCB[r].waitlist.pop_front();
		RL[PCB[wait_front_i].priority].push_back(wait_front_i);
		PCB[wait_front_i].state = true;

		// Assign correct num of resources
		RCB[r].state -= num_rq;
		PCB[wait_front_i].resources.push_back(r);
	}

	scheduler();
	cout << "resource " << r << " released" << endl;
}

// Timesharing and the Scheduler
void timeout() 
{
	int running = get_running(RL);
	RL[PCB[running].priority].pop_front();
	RL[PCB[running].priority].push_back(running);
	scheduler();
}

void scheduler() 
{
	int highest_priority = get_running(RL);
	cout << "process " << highest_priority << " running" << endl;
}

// Initialize
void init()
{
	for (auto &i : RL) { 
		i.clear();
	}

	/*
	 * Process Control Block Init
	 * false = blocked, true = ready
	 */
	PCB[0] = { true, 0, 0, {}, {} };
	for (int i = 1; i < 16; i++) {
		PCB[i] = { false, 0, 0, {}, {} };
	}

	// Add process 0 to the Ready List, lowest level
	RL[0].push_front(0);

	/*
	 * Resource Control Block Init
	 * false = free
	 */
	RCB[0] = { 1, 1, {} };
	RCB[1] = { 1, 1, {} };
	RCB[2] = { 2, 2, {} };
	RCB[3] = { 3, 3, {} };
}