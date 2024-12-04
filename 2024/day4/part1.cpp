#include <algorithm>
#include<fstream>
#include<iostream>
#include<regex>
#include<string>

using namespace std;


int main() {
    int total = 0;
    ifstream data("input.txt");
    vector<string> input;
    string line;
    while (getline(data, line)) {
        input.push_back(line);
    }
    regex findx("X");
    pair<short, short> dirs[8] = {{1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}};

    for (int y = 0; y < input.size(); y++) {
        string::const_iterator start = input[y].cbegin();
        smatch foundx;
        while (regex_search(start, input[y].cend(), foundx, findx)) {
            
        }
    }

    cout << total << '\n';

    return 0;
}
