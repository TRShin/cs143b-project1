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
		args >> a1;

		if (a1 == "in") {
			init();
		}
		else if (a1 == "cr") {
			
		} 
		else if (a1 == "de") {

		}
		else if (a1 == "rq") {

		}
		else if (a1 == "rl") {

		}
		else if (a1 == (a1 == "to") {
		}
		else {}

	return 0;
}