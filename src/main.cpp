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
		if (line.empty()) continue;

		stringstream args(line);
		string a1;
		int val;
		args >> a1;

		if (a1 == "in") {
			init();
		}

		else if (a1 == "cr") {
			if (args >> val && val >= 0 && val < 3) {
				create(val);
			}
			else continue;
		}

		else if (a1 == "de") {
			int val, num_p_dest = 0;
			if (args >> val) {
				destroy(val, num_p_dest);
				scheduler();
				cout << num_p_dest << " processes destroyed" << endl;
			}
			else continue;
		}

		else if (a1 == "rq") {
			int val;
			if (args >> val && val >= 0 && val < 4) {
				request(val);
			}
			else continue;
		}

		else if (a1 == "rl") {
			int val;
			if (args >> val && val >= 0 && val < 4) {
				release(val);
			}
			else continue;
		}

		else if (a1 == "to") {
			timeout();
		}

		else {
			cout << "error" << endl;
		}
	}

	return 0;
}