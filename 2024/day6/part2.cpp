#include<fstream>
#include<iostream>
#include<string>
#include <utility>
#include<vector>
#include<unordered_map>
#include<cmath>

using namespace std;


int main() {
    ifstream data("input.txt");
    int total = 0;
    int pos[2] = {-1, -1};
    int dpos[2];
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

    while (0 <= pos[0] && pos[0] < board[0].size() && 0 <= pos[1] && pos[1] < board.size()) {
        char posh = board[pos[1]][pos[0]];
        char posr = board[pos[1] + dirs[(dir + 1) % 4].second][pos[0] + dirs[(dir + 1) % 4].first];
        char posf = 'X';
        if (0 <= pos[1] + dirs[dir].second && pos[1] + dirs[dir].second < board.size() && 0 <= pos[0] + dirs[dir].first && pos[0] + dirs[dir].first < board[0].size())
            posf = board[pos[1] + dirs[dir].second][pos[0] + dirs[dir].first];

        if (posh == '#') {
            pos[0] -= dirs[dir].first;
            pos[1] -= dirs[dir].second;
            dir = (dir + 1) % 4;
            posh = board[pos[1]][pos[0]];
            posr = board[pos[1] + dirs[(dir + 1) % 4].second][pos[0] + dirs[(dir + 1) % 4].first];
            posf = '#';
            if (0 <= pos[1] + dirs[dir].second && pos[1] + dirs[dir].second < board.size() && 0 <= pos[0] + dirs[dir].first && pos[0] + dirs[dir].first < board[0].size())
                posf = board[pos[1] + dirs[dir].second][pos[0] + dirs[dir].first];
        } else if (board[pos[1]][pos[0]] == '.')
            board[pos[1]][pos[0]] = '^';
        if (posf != 'X' && posf != '^' && posf != '@' && posf != '#') {
            short ddir = (dir + 1) % 4;
            board[pos[1] + dirs[dir].second][pos[0] + dirs[dir].first] = '#';
            dpos[0] = pos[0];
            dpos[1] = pos[1];
            unordered_map<int, short> obshit;
            while (0 <= (dpos[0] += dirs[ddir].first) && dpos[0] < board[0].size() && 0 <= (dpos[1] += dirs[ddir].second) && dpos[1] < board.size()) {
                if (board[dpos[1]][dpos[0]] == '#') {
                    if (obshit.count(dpos[0] * 1000 + dpos[1])) {
                        if (obshit[dpos[0] * 1000 + dpos[1]] & (short)pow(2, ddir)) {
                            total++;
                            break;
                        } else
                            obshit[dpos[0] * 1000 + dpos[1]] |= (short)pow(2, ddir);
                    } else
                        obshit[dpos[0] * 1000 + dpos[1]] = (short)pow(2, ddir);
                    dpos[0] -= dirs[ddir].first;
                    dpos[1] -= dirs[ddir].second;
                    ddir = (ddir + 1) % 4;
                }
            }
            board[pos[1] + dirs[dir].second][pos[0] + dirs[dir].first] = '@';
        }
        pos[0] += dirs[dir].first;
        pos[1] += dirs[dir].second;
    }

    //for (int i = 0; i < board.size(); i++) {
        //cout << board[i] << '\n';
    //}
    cout << total << '\n';

    return 0;
}
