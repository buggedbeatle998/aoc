#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;


int main() {
    ifstream data("input.txt");
    int total = 1;
    int pos[2] = {-1, -1};
    pair<short, short> dirs[4] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
    short dir = 0;

    vector<string> board;
    string line;
    while (getline(data, line)) {
        board.push_back(line);
        if (pos[0] == -1) {
            pos[1]++;
            if (line.find('^') != line.npos)
                pos[0] = line.find('^');
        }
    }

    while (0 <= (pos[0] += dirs[dir].first) && pos[0] < board[0].size() && 0 <= (pos[1] += dirs[dir].second) && pos[1] < board.size()) {
        if (board[pos[1]][pos[0]] == '#') {
            pos[0] -= dirs[dir].first;
            pos[1] -= dirs[dir].second;
            dir = (dir + 1) % 4;
        } else if (board[pos[1]][pos[0]] == '.') {
            board[pos[1]][pos[0]] = 'X';
            total++;
        }
    }

    // for (int i = 0; i < board.size(); i++) {
    //     cout << board[i] << '\n';
    // }
    cout << total << '\n';

    return 0;
}
