#include "operations.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main(int argc, char* argv[])
{
	init();

	string line;
	while (getline(cin, line)) {
		if (line.emmpty()) continue;

		stringstream args(line);
		string a1;
		int val;
		args >> a1;

		if (a1 == "in") {
			init();
		}

		else if (a1 == "cr") {
			create();
		}

		else if (a1 == "de") {
			int val, num_p_dest = 0;
			if (args >> val) {
				destroy(val, num_p_dest);
				cout << num_p_dest << " processes destroyed" << end;
			}
			else continue;
		}

		else if (a1 == "rq") {
			int val;
			if (args >> val) {
				request(val)
			}
			else continue;
		}

		else if (a1 == "rl") {
			int val;
			if (args >> val) {
				release(val);
			}
			else continue;
		}

		else if (a1 == "to") {
			timeout();
		}
	}

	return 0;
}