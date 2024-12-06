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
        vector<string> line_vec;
        while (start < line.size()) {
            line_vec.push_back(line.substr(start, 2));
            start += 3;
        }
        for (int i = 0; i < line_vec.size(); i++) {
            string curr = line_vec[i];
            for (int dummy = i + 1; dummy < line_vec.size(); dummy++) {
                if (ordermap.count(line_vec[dummy])) {
                    vector<string> contvec = ordermap[line_vec[dummy]];
                    if (find(contvec.begin(), contvec.end(), curr) != contvec.end()) {
                        good = false;
                        iter_swap(line_vec.begin() + i, line_vec.begin() + dummy);
                        i--;
                        break;
                    }
                }
            }
        }
        if (!good) {
            total += stoi(line_vec[(int)line_vec.size() / 2]);
        }
    }

    cout << total << '\n';

    return 0;
}
