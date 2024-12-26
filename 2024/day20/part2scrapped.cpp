#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<regex>
#include<unordered_map>
#include<queue>
#include<set>
#include<deque>

using namespace std;


struct comp_pair {
    bool operator()(pair<int, int> const& a, pair<int, int> const& b) {
        return a.first > b.first;
    }
};


struct comp_tuple {
    bool operator()(tuple<int, int, int, short> const& a, tuple<int, int, int, short> const& b) {
        return get<0>(a) > get<0>(b);
    }
};


int main() {
    ifstream data("test.txt");
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
    deque<tuple<int, int, int, short>> totry;

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
                        totry.push_back({time + 1, newpos, pos, 19});
                    }
                } else if (maze[newpos] != 'E') {
                    next.push({time + 1, newpos});
                }
            }
        }
    }

    // cout << totry.size();
    priority_queue<tuple<int, int, int, short>, vector<tuple<int, int, int, short>>, comp_tuple> nnext;
    // cout << totry.size() << '\n';
    constexpr const int time_to_save = 76;
    const int end_dist = places[end].first;
    const int threshold = end_dist - time_to_save;
    for (int i = totry.size() - 1; i >= 0; i--) {
        tuple<int, int, int, short> temp = totry[i];
        if (get<0>(temp) - 1 + abs((end % width) - (get<2>(temp) % width)) + abs((end / width - get<2>(temp) / width)) <= threshold) {
            totry.erase(totry.begin() + i);
        }
    }
    set<pair<int, int>> cheats_done;
    unordered_map<int, int> dists;
    int tile = end;
    do {
        dists[tile] = end_dist - places[tile].first;
    } while ((tile = places[tile].second) != -1);

    while (!totry.empty()) {
        done.clear();
        if (get<0>(totry.front()) >= threshold){
            totry.pop();
            continue;
        }
        nnext.push(totry.front());
        unordered_map<int, pair<int, int>> cheated_places;
        cheated_places[get<1>(totry.front())] = {get<0>(totry.front()), -1};
        // cout << (totry.front().second % width) << ' ' << (totry.front().second / width) << '\n';
        totry.pop();
        while (!nnext.empty()) {
            // cout << "\t\thi" << '\n';
            int time;
            int pos;
            int start;
            short cheats;
            tie(time, pos, start, cheats) = nnext.top();
            nnext.pop();
            done.insert(pos);
            cheats--;
            //  cout << '\t' << (pos % width) << ' ' << (pos / width) << '\n';
            for (const auto& dir : dirs) {
                //  cout << "\t\t" << dir.first << ' ' << dir.second << '\n';
                int newpos = pos + dir.first + dir.second * width;
                if (!done.count(newpos) && time + 1 < cheated_places[newpos].first) {
                    // if (dists.count(newpos)) {
                    //     if (time + 1 + dists[newpos] <= threshold) {

                    int ttile = pos;
                    int last_tile;
                    do {
                        last_tile = ttile;
                    } while ((maze[cheated_places[ttile = cheated_places[ttile].second].first]) != '#');
                    total++;
                            // int ttile = pos;
                            // do {
                            //     dists[ttile] = end_dist - cheated_places[ttile].first;
                            // } while ((ttile = cheated_places[ttile].second) != -1);
                            // nnext = priority_queue<tuple<int, int, short>, vector<tuple<int, int, short>>, comp_tuple>();
                            // break;
                        }
                    // } else {
                        cheated_places[newpos] = {time + 1, pos};

                        nnext.push({time + 1, newpos, cheats});
                    }
                }
            }
        }
    }

    cout << total << '\n';

    return 0;
}
