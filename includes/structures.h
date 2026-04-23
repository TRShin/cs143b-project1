#pragma once

#include <list>
#include <utility>
using std::list;
using std::pair;

struct process
{
	bool slot_usage;
	bool state;					   // Ready = TRUE, blocked = FALSE
	int parent;
	int priority;
	list<int> children;
	list<int> resources;
};

struct resource
{
	int state;
	int inventory;
	list<pair<int, int>> waitlist; // first = process index, second = number of resources requested
};
