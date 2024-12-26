#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<regex>
#include<unordered_map>
#include<queue>
#include<set>
#include<array>

using namespace std;


struct comp_pair {
    bool operator()(pair<int, int> const& a, pair<int, int> const& b) {
        return a.first > b.first;
    }
};


int main() {
    ifstream data("input.txt");
    int total = 0;

    set<array<short, 5>> keys;
    set<array<short, 5>> locks;
    string line;
    do {
        getline(data, line);
        array<short, 5> columns = {0, 0, 0, 0, 0};
        for (int i = 1; i < 6; i++) {
            getline(data, line);
            for (int n = 0; n < 5; n++) {
                columns[n] += line[n] == '#';
            }
        }  
        getline(data, line);
        if (line[0] == '#') {
            keys.insert(columns);
        } else {
            locks.insert(columns);
        }
    } while (getline(data, line));

    for (const auto& key : keys) {
        for (const auto& lock : locks) {
            if(key[0] + lock[0] <= 5
            && key[1] + lock[1] <= 5
            && key[2] + lock[2] <= 5
            && key[3] + lock[3] <= 5
            && key[4] + lock[4] <= 5) {
                total++;
            }
        }
    }

    cout << total << '\n';

    return 0;
}