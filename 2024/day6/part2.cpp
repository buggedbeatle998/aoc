#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

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

    while (0 <= (pos[0] += dirs[dir].first) && pos[0] < board[0].size() && 0 <= (pos[1] += dirs[dir].second) && pos[1] < board.size()) {
        //cout << pos[0] << ' ' << pos[1] << '\n';
        char posh = board[pos[1]][pos[0]];
        char posr = board[pos[1] + dirs[(dir + 1) % 4].second][pos[0] + dirs[(dir + 1) % 4].first];
        char posf;
        if (0 <= pos[1] + dirs[dir].second && pos[1] + dirs[dir].second < board.size() && 0 <= pos[0] + dirs[dir].first && pos[0] + dirs[dir].first < board[0].size())
            posf = board[pos[1] + dirs[dir].second][pos[0] + dirs[dir].first];

        if (posh == '#') {
            pos[0] -= dirs[dir].first;
            pos[1] -= dirs[dir].second;
            dir = (dir + 1) % 4;
        } else if (board[pos[1]][pos[0]] == '.')
            board[pos[1]][pos[0]] = '^';
        if (posf != '^' && posf != '@' && posf != '#' && posr != '#') {
            dir = (dir + 1) % 4;
            dpos[0] = pos[0];
            dpos[1] = pos[1];
            while (0 <= (dpos[0] += dirs[dir].first) && dpos[0] < board[0].size() && 0 <= (dpos[1] += dirs[dir].second) && dpos[1] < board.size()) {
                //cout << '\t' << dpos[0] << ' ' << dpos[1] << '\n';
                if (board[dpos[1]][dpos[0]] == '#') {
                    dpos[0] -= dirs[dir].first;
                    dpos[1] -= dirs[dir].second;
                    char dposh = board[dpos[1]][dpos[0]];
                    char dposr = board[dpos[1] + dirs[(dir + 1) % 4].second][dpos[0] + dirs[(dir + 1) % 4].first];
                    if ((dposr == '^' || dposr == '@') && (dposh == '^' || dposh == '@')) {
                        if (0 <= pos[1] + dirs[(dir + 3) % 4].second && pos[1] + dirs[(dir + 3) % 4].second < board.size() && 0 <= pos[0] + dirs[(dir + 3) % 4].first && pos[0] + dirs[(dir + 3) % 4].first < board[0].size()) {
                            board[pos[1] + dirs[(dir + 3) % 4].second][pos[0] + dirs[(dir + 3) % 4].first] = '@';
                            //cout << "\t\t" << pos[0] + dirs[(dir + 3) % 4].first << ' ' << pos[1] + dirs[(dir + 3) % 4].second << '\n';
                            total++;
                    }
                    }
                    break;
                }
            }
            dir = (dir + 3) % 4;
        }
    }

    for (int i = 0; i < board.size(); i++) {
        cout << board[i] << '\n';
    }
    cout << total << '\n';

    return 0;
}
