#include "operations.h"
#include "helpers.h"
#include <iostream>
#include <algorithm>

using namespace std;

// Declare all DS
process PCB[16];
resource RCB[4];
list<int> RL[3];

// Operations on Processes
void create(int p)
{
	int index;

	if (count_if(begin(PCB), end(PCB), [](const auto& p) {return p.slot_usage;}) >= 16) {
		cout << "-1 ";
		return;
	}

	// Find next process to be created
	auto it = find_if(begin(PCB), end(PCB), [](const auto& e) {
		return e.slot_usage == false;
	});
	if (it != end(PCB)) {
		index = static_cast<int>(it - begin(PCB));
	}
	else {
		cout << "-1 " << endl;
		return;
	}

	// Check who the parent is, update parent
	int parent_index = get_running(RL);
	PCB[parent_index].children.push_back(index);

	// Allocate new pcb[index]
	PCB[index] = { true, true, parent_index, p, {}, {} };

	// Push back onto RL
	RL[p].push_back(index);

	scheduler();
}

void destroy(int j, int &npd)
{
	if (j != 0 && PCB[j].slot_usage == true)
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
		PCB[j] = { false, false, 0, 0, {}, {} };
		npd++;
	}
}

// Operations on Resources
void request(int r, int num_rq)
{
	int curr_p_index = get_running(RL);

	if (curr_p_index == 0) {
		cout << "-1 ";
		return;
	}

	if (num_rq + count_resource_r(PCB[curr_p_index].resources, r) > RCB[r].inventory) {
		cout << "-1 " << endl;
		return;
	}

	if (RCB[r].state >= num_rq) {
		RCB[r].state -= num_rq;
		PCB[curr_p_index].resources.push_back(r);
		scheduler();
	}
	else {
		PCB[curr_p_index].state = false;
		RL[PCB[curr_p_index].priority].remove(curr_p_index);
		RCB[r].waitlist.emplace_back(curr_p_index, num_rq);
		scheduler();
	}
}

void release(int r, int num_rq) 
{
	int curr_p_index = get_running(RL);

	if (count_resource_r(PCB[curr_p_index].resources, r) < num_rq) {
		cout << "-1 ";
		return;
	}

	int num_requested = 0;
	auto it = PCB[curr_p_index].resources.begin();
	while (it != PCB[curr_p_index].resources.end() && num_requested < num_rq) {
		if (*it == r) {
			it = PCB[curr_p_index].resources.erase(it);
			num_requested++;
		}
		else {
			++it;
		}
	}
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
		RCB[r].state -= wait_req;
		for (int i = 0; i < wait_req; i++) {
			PCB[wait_front_i].resources.push_back(r);
		}
	}

	scheduler();
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
	cout << get_running(RL) << " ";
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
	PCB[0] = { true, true, 0, 0, {}, {} };
	for (int i = 1; i < 16; i++) {
		PCB[i] = { false, false, 0, 0, {}, {} };
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

	static bool first = true;
	if (!first) 
		cout << "\n";
	first = false;
	cout << "0 ";
}
