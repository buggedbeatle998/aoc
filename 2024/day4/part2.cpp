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
    regex findx("A");
    pair<short, short> dirs[4] = {{1, -1}, {-1, -1}, {-1, 1}, {1, 1}};

    for (int y = 0; y < input.size(); y++) {
        int x = 0;
        string::const_iterator start = input[y].cbegin();
        smatch foundx;
        while (regex_search(start, input[y].cend(), foundx, findx)) {
            x += foundx.position(0);
            if (   0 <= x - 1
                && x + 1 < input[0].size()
                && 0 <= y - 1
                && y + 1 < input.size()) {
                    char topright = input[y + dirs[0].second][x + dirs[0].first];
                    char topleft = input[y + dirs[1].second][x + dirs[1].first];
                    if (   (topright == 'M' || topright == 'S')
                        && input[y + dirs[2].second * 1][x + dirs[2].first * 1] == (topright == 'M' ? 'S' : 'M')
                        && (topleft == 'M' || topleft == 'S')
                        && input[y + dirs[3].second * 1][x + dirs[3].first * 1] == (topleft == 'M' ? 'S' : 'M')) {
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
