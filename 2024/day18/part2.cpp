#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<queue>
#include<set>
#include<regex>
#include<cmath>

using namespace std;

struct comp_pair {
    bool operator()(pair<int, int> const& a, pair<int, int> const& b) {
        return a.first > b.first;
    }
};

int main() {
    ifstream data("input.txt");
    const int width = 71;
    const int height = 71;
    string maze(width * height, '.');
    string line;
    smatch num;
    regex findnum("[0-9]+");
    int byte = 0;
    for (; byte < 1024 && getline(data, line); byte++) {
        string::const_iterator start = line.cbegin();
        regex_search(start, line.cend(), num, findnum);
        int toadd = stoi(num[0]);
        start = num.suffix().first;
        regex_search(start, line.cend(), num, findnum);
        toadd += stoi(num[0]) * width;
        //cout << toadd << '\n';
        maze[toadd] = '#';
    }
    // for (int i = 0; i < height; i++) {
    //     //cout << maze.substr(i * width, width) << '\n';
    // }
    const int end = (width - 1) + width * (height - 1);
    pair<short, short> dirs[4] = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};
    while (true) {
        unordered_map<int, pair<int, int>> places;
        places[0] = {0, -1};
        priority_queue<pair<int, int>, vector<pair<int, int>>, comp_pair> next;
        next.push({0, 0});
        set<int> done;

        while (!next.empty()) {
            pair<int, int> node = next.top();
            next.pop();
            int pos = node.second;
            done.insert(pos);
            //cout << '(' << node.second.first % width << ", " << node.second.first / width << ", " << node.second.second << ") " << node.first << '\n';
            for (const auto& dir : dirs) {
                int newpos = pos + dir.first + dir.second * width;
                // cout << (newpos % width) << ' ' << (newpos / width) << '\n';
                // cout << maze[newpos] << '\n';
                if ((pos % width) + dir.first >= 0
                && (pos % width) + dir.first < width
                && ((int)pos / width) + dir.second >= 0
                && ((int)pos / width) + dir.second < height
                && !done.count(newpos = pos + dir.first + dir.second * width)
                && maze[newpos] != '#'
                && (!places.count(newpos)
                || node.first + 1 < places[newpos].first)) {
                    places[newpos] = {node.first + 1, pos};
                    if (newpos != end) {
                        next.push({node.first + 1, newpos});
                    }
                }
            }
        }

        if (!places.count(end)) {
            break;
        }

        set<int> tiles;
        int tile = end;
        while (tile != -1) {
            tiles.insert(tile);
            tile = places[tile].second;
        }
        for (; getline(data, line); byte++) {
            string::const_iterator start = line.cbegin();
            regex_search(start, line.cend(), num, findnum);
            int toadd = stoi(num[0]);
            start = num.suffix().first;
            regex_search(start, line.cend(), num, findnum);
            toadd += stoi(num[0]) * width;
            //cout << toadd << '\n';
            maze[toadd] = '#';
            if (tiles.count(toadd)) {
                break;
            }
        }
    }

    cout << line << '\n';

    return 0;
}