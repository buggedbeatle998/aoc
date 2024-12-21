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
    unordered_map<int, pair<int, int>> places;
    places[start] = {0, -1};
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
            if (!done.count(newpos) && (!places.count(newpos) || time + 1 < places[newpos].first)) {
                places[newpos] = {time + 1, pos};
                if (maze[newpos] == '#') {
                    if ((newpos % width) != 0 && (newpos % width) != width - 1 && (newpos / width) != 0 && (newpos / width) != height - 1) {
                        totry.push({time + 1, newpos});
                    }
                } else if (maze[newpos] != 'E')
                    next.push({time + 1, newpos});
            }
        }
    }
    next = priority_queue<pair<int, int>, vector<pair<int, int>>, comp_pair>();
    cout << totry.size() << '\n';
    constexpr const int time_to_save = 100;
    const int end_dist = places[end].first;
    const int threshold = end_dist - time_to_save;
    unordered_map<int, int> dists;
    int tile = end;
    do {
        dists[tile] = end_dist - places[tile].first;
    } while ((tile = places[tile].second) != -1);

    while (!totry.empty()) {
        done.clear();
        if (totry.front().first >= threshold){
            totry.pop();
            continue;
        }
        next.push(totry.front());
        unordered_map<int, pair<int, int>> cheated_places;
        cheated_places[totry.front().second] = {totry.front().first, -1};
        // cout << (totry.front().second % width) << ' ' << (totry.front().second / width) << '\n';
        totry.pop();
        while (!next.empty()) {
            // cout << "\t\thi" << '\n';
            int time;
            int pos;
            tie(time, pos) = next.top();
            next.pop();
            done.insert(pos);
            // cout << '\t' << (pos % width) << ' ' << (pos / width) << '\n';
            for (const auto& dir : dirs) {
                // cout << "\t\t" << dir.first << ' ' << dir.second << '\n';
                int newpos = pos + dir.first + dir.second * width;
                if (maze[newpos] != '#' && !done.count(newpos) && (!places.count(newpos) || time + time_to_save <= places[newpos].first)) {
                    if (dists.count(newpos)) {
                        if (time + 1 + dists[newpos] <= threshold) {
                            total++;
                            // while (!next.empty()) next.pop();
                            int ttile = pos;
                                //cout << "hi";
                            do {
                                dists[ttile] = end_dist - cheated_places[ttile].first;
                            } while ((ttile = cheated_places[ttile].second) != -1);
                            next = priority_queue<pair<int, int>, vector<pair<int, int>>, comp_pair>();
                            break;
                        }
                    } else {
                        cheated_places[newpos] = {time + 1, pos};
                        next.push({time + 1, newpos});
                    }
                }
            }
        }
    }

    cout << total << '\n';

    return 0;
}
