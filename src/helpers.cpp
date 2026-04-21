#include "helpers.h"
#include "operations.h"

void release_all(int j)
{
	auto r_copy = PCB[j].resources;
	for (auto i : r_copy) {
		if (RCB[i].waitlist.empty()) {
			RCB[i].state = RCB[i].inventory;
		}
		else {
			auto wait_entry = RCB[i].waitlist.front();
			RCB[i].waitlist.pop_front();
			int wait_front_i = wait_entry.first;
			int wait_req = wait_entry.second;
			RL[PCB[wait_front_i].priority].push_back(wait_front_i);
			PCB[wait_front_i].state = true;
			PCB[wait_front_i].resources.push_back(i);
		}
		PCB[j].resources.remove(i);
	}
}

int get_running(list<int> RL[])
{
	if (!RL[2].empty()) {
		return RL[2].front();
	}
	else if (!RL[1].empty()) {
		return RL[1].front();
	}
	else {
		return RL[0].front();
	}
}