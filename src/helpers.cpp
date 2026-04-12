#include "helpers.h"
#include "operations.h"

void release_all(int j)
{
	auto r_copy = PCB[j].resources;
	for (auto i : r_copy) {
		if (RCB[i].waitlist.empty()) {
			RCB[i].state = false;
		}
		else {
			int wait_front_i = RCB[i].waitlist.front();
			RCB[i].waitlist.pop_front();
			RL.push_back(wait_front_i);
			PCB[wait_front_i].state = true;
			PCB[wait_front_i].resources.push_back(i);
		}
	}
}