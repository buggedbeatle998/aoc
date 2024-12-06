#include<fstream>
#include<iostream>
#include<string>
#include<unordered_map>
#include<vector>
#include<algorithm>

using namespace std;


int main() {
    ifstream data("input.txt");
    int total = 0;
    
    unordered_map<string, vector<string>> ordermap;
    string line;
    while (getline(data, line) && line != "") {
        ordermap[line.substr(0, 2)].push_back(line.substr(3, 2));
    }

    while (getline(data, line)) {
        int start = 0;
        bool good = true;
        while (start < line.size()) {
            string curr = line.substr(start, 2);
            int dummy = start + 3;
            while (dummy < line.size()) {
                // cout << line.substr(dummy, 2) << ' ';
                if (ordermap.count(line.substr(dummy, 2))) {
                    vector<string> contvec = ordermap[line.substr(dummy, 2)];
                    // if (line.substr(dummy, 2) == "97") {
                    //     cout << curr << ' ';
                    // }
                    if (find(contvec.begin(), contvec.end(), curr) != contvec.end()) {
                        good = false;
                        break;
                    }
                }
                dummy += 3;
            }
            if (!good) {
                break;
            }
            start += 3;
        }
        if (good) {
            //cout << line << ' ' << line.substr((int)start / 2 - 1, 2) << '\n';
            total += stoi(line.substr((int)start / 2 - 1, 2));
        }
    }

    cout << total << '\n';

    return 0;
}
