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
        int x = 0;
        string::const_iterator start = input[y].cbegin();
        smatch foundx;
        while (regex_search(start, input[y].cend(), foundx, findx)) {
            x += foundx.position(0);
            for (const auto& dir : dirs) {
                if (   0 <= x + dir.first * 3
                    && x + dir.first * 3 < input[0].size()
                    && 0 <= y + dir.second * 3
                    && y + dir.second * 3 < input.size()
                    && input[y + dir.second * 1][x + dir.first * 1] == 'M'
                    && input[y + dir.second * 2][x + dir.first * 2] == 'A'
                    && input[y + dir.second * 3][x + dir.first * 3] == 'S') {
                        total++;
                }
            }
            x++;
            start = foundx.suffix().first;
        }
    }

    cout << total << '\n';

    return 0;
}
