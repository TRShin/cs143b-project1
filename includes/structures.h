#pragma once

#include <list>
using std::list;

struct process
{
	bool state;				// Ready = TRUE, blocked = FALSE
	int parent;
	list<int> children;
	list<int> resources;
};

struct resource
{
	bool state;				// Allocated = TRUE, else FALSE
	list<int> waitlist;
};