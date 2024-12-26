
#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<regex>
#include<unordered_map>
#include<queue>
#include<set>

using namespace std;


struct comp_pair {
    bool operator()(pair<int, int> const& a, pair<int, int> const& b) {
        return a.first > b.first;
    }
};


int main() {
    ifstream data("input.txt");
    string maze((istreambuf_iterator<char>(data)),
    istreambuf_iterator<char>());
    int total = 0;
    const int height = count(maze.begin(), maze.end(), '\n') + 1;
    maze.erase(remove(maze.begin(), maze.end(), '\n'), maze.end());
    const int width = (int)maze.size() / height;
    smatch found_pos;
    regex_search(maze, found_pos, regex("S"));
    const int start = found_pos.position();
    regex_search(maze, found_pos, regex("E"));
    const int end = found_pos.position();
    pair<short, short> dirs[4] = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};
    unordered_map<int, int> places;
    places[start] = {0};
    priority_queue<pair<int, int>, vector<pair<int, int>>, comp_pair> next;
    next.push({0, start});
    set<int> done;
    queue<pair<int, int>> totry;

    while (!next.empty()) {
        int time;
        int pos;
        tie(time, pos) = next.top();
        next.pop();
        done.insert(pos);
        for (const auto& dir : dirs) {
            int newpos = pos + dir.first + dir.second * width;
            if (maze[newpos] != '#' && !done.count(newpos) && (!places.count(newpos) || time + 1 < places[newpos])) {
                places[newpos] = {time + 1};
                next.push({time + 1, newpos});
            }
        }
    }

    const int to_save = 100;

    for (const auto& place0 : places) {
        for (const auto& place1 : places) {
            int dist = abs((place0.first % width) - (place1.first % width)) + abs((place0.first / width) - (place1.first / width));
            if (dist <= 20 && place0.second - place1.second - dist >= to_save) {
                total++;
            }
        }
    }

    cout << total;

    return 0;
}
