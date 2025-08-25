#include <iostream>
#include <regex>
#include <string>
#include <fstream>

using namespace std;

regex pat (R"([[:digit:]]+)");

int main()
{
	ifstream file("may_be_nums");
	string line;

	if (file.is_open()) {
		while (getline(file, line)) {
			smatch matches;
			if (regex_search(line, matches, pat))
			{
				for (sregex_iterator it(line.begin(), line.end(), pat), end_it; it != end_it; ++it) 
				{
					std::cout << "Found: " << it->str() << std::endl;
				}
			}
		}

		file.close();
	}

	return 0;
}
