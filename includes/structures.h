#pragma once

#include <list>
#include <utility>
using std::list, std::pair;

struct process
{
	bool state;				// Ready = TRUE, blocked = FALSE
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