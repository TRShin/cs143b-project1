#include list;

struct process
{
	bool state;
	int parent;
	list<int> children;
	list<int> resources;
};

struct resource
{
	bool state;
	list<int> waitlist;
};