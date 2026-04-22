#include "helpers.h"
#include "operations.h"

int count_resource_r(list<int> list, int r) 
{
	int count = 0;
	auto it = list.begin();
	while (it != list.end()) {
		if (*it == r) { count++; it++; }
		else { it++; }
	}

	return count;
}

void release_all(int j)
{
	int holding_resources[4] = {0};
	for (int r : PCB[j].resources) {
		holding_resources[r]++;
	}

	for (int r = 0; r < 4; r++) {
		if (holding_resources[r] != 0) {
			int num_requested = 0;
			auto it = PCB[j].resources.begin();
			while (it != PCB[j].resources.end() && num_requested < holding_resources[r]) {
				if (*it == r) {
					it = PCB[j].resources.erase(it);
					num_requested++;
				}
				else {
					++it;
				}
			}
			RCB[r].state += holding_resources[r];

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
		}
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