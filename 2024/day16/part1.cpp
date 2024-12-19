#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<regex>
#include<unordered_map>
#include<queue>
#include<set>

using namespace std;


struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const
    {
        // Hash the first element
        size_t hash1 = hash<T1>{}(p.first);
        // Hash the second element
        size_t hash2 = hash<T2>{}(p.second);
        // Combine the two hash values
        return hash1
               ^ (hash2 + 0x9e3779b9 + (hash1 << 6)
                  + (hash1 >> 2));
    }
};


struct comp_pair {
    bool operator()(pair<int, pair<int, short>> const& a, pair<int, pair<int, short>> const& b) {
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
    smatch foundstart;
    regex_search(maze, foundstart, regex("S"));
    int pos = foundstart.position();
    pair<short, short> dirs[4] = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};
    unordered_map<pair<int, short>, pair<int, pair<int, short>>, hash_pair> places;
    places[{pos, 0}] = {0, {-1, -1}};
    places[{pos, 1}] = {1000, {-1, -1}};
    places[{pos, 2}] = {2000, {-1, -1}};
    places[{pos, 3}] = {1000, {-1, -1}};
    priority_queue<pair<int, pair<int, short>>, vector<pair<int, pair<int, short>>>, comp_pair> next;
    next.push({0, {pos, 0}});
    next.push({1000, {pos, 1}});
    next.push({2000, {pos, 2}});
    next.push({1000, {pos, 3}});
    set<pair<int, short>> done;

    while (!next.empty()) {
        pair<int, pair<int, short>> node = next.top();
        next.pop();
        //cout << '(' << node.second.first % width << ", " << node.second.first / width << ", " << node.second.second << ") " << node.first << '\n';
        pair<short, short> dir = dirs[node.second.second];
        done.insert(node.second);
        if (maze[node.second.first + dir.first + dir.second * width] == '#') continue;
        pair<int, short> totest = {node.second.first + dir.first + dir.second * width, (maze[node.second.first + dir.first + dir.second * width] == 'E') ? -1 : node.second.second};
        //cout << "\t(" << totest.first % width << ", " << totest.first / width << ", " << totest.second << ')' << done.count(totest) << '\n';
        if (!done.count(totest) && (!places.count(totest) || node.first + 1 < places[totest].first)) {
            places[totest] = {node.first + 1, node.second};
            //cout << "hi" << '\n';
            if (maze[totest.first] == 'E') continue;
            next.push({node.first + 1, totest});
            totest = {node.second.first + dir.first + dir.second * width, (node.second.second + 1) % 4};
            if (!done.count(totest) && (!places.count(totest) || node.first + 1001 < places[totest].first)) {
                places[totest] = {node.first + 1001, node.second};
                next.push({node.first + 1001, totest});
            }
            totest = {node.second.first + dir.first + dir.second * width, (node.second.second + 3) % 4};
            if (!done.count(totest) && (!places.count(totest) || node.first + 1001 < places[totest].first)) {
                places[totest] = {node.first + 1001, node.second};
                next.push({node.first + 1001, totest});
            }
            totest = {node.second.first + dir.first + dir.second * width, (node.second.second + 2) % 4};
            if (!done.count(totest) && (!places.count(totest) || node.first + 2001 < places[totest].first)) {
                places[totest] = {node.first + 2001, node.second};
                next.push({node.first + 2001, totest});
            }
        }
    }

    smatch foundend;
    regex_search(maze, foundend, regex("E"));

    cout << places[{foundend.position(), -1}].first << '\n';

    return 0;
}
