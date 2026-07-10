
    #include <iostream>
    #include <string>
    #include <vector>
	#include <fstream>
    using namespace std;
    struct transaction {
    	int user_id;
    	long value;
    };

    istream& operator>>(istream& in, transaction& trans) {
    	return (in >> trans.user_id >> trans.value);
    }

    int main() {
    	int result = 0;
    	vector<transaction> chunk;
    	transaction temp;
		ifstream fs;
		fs.open("./input");
    	while(fs >> temp) {
    		chunk.push_back(temp);
    	}
	
    	cout << chunk.size();
	    return 0;
    }


