#include list;

struct process
{
	int state;
	int parent;
	list<int> children;
	list<int> resources;
};

struct resource
{
	int state;
	list<int> waitlist;
};

// Move to operations.
process PCB[12];
resource RCB[12];