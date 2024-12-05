#include<fstream>
#include<iostream>
#include<string>
#include<unordered_map>
#include <vector>

using namespace std;


int main() {
    ifstream data("input.txt");
    int total = 0;
    
    unordered_map<string, vector<string>> ordermap;
    string line;
    while (getline(data, line) && line != "") {
        ordermap[line.substr(0, 2)].push_back(line.substr(3, 5));
    }

    while (getline(data, line)) {
        int start = 0;
        bool good = true;
        while (start < line.size()) {
            string curr = line.substr(start, start + 2);
            int dummy = start + 3;
            while (dummy < line.size()) {
                if (ordermap.count(line.substr(dummy, dummy + 2))) {
                    vector<string> contvec = ordermap[line.substr(dummy, dummy + 2)];
                    if (find(contvec.begin(), contvec.end(), curr) != contvec.end()) {
                        good = false;
                        break;
                    }
                }
            }
            if (!good) {
                break;
            }
        }
    }

    cout << total << '\n';

    return 0;
}
