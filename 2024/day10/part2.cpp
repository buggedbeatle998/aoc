#include<fstream>
#include<iostream>
#include<string>
#include<regex>
#include<unordered_map>

using namespace std;

unordered_map<int, int> find_top_cache;
int find_top(int pos, const pair<short, short>(& dirs)[4], const int width, const int height, const string& input) {
    if (find_top_cache.count(pos)) {
        return find_top_cache[pos];
    }

    int score = 0;

    for (short i = 0; i < 4; i++) {
        pair<short, short> dir = dirs[i];
        if (
           (pos % width) + dir.first >= 0
        && (pos % width) + dir.first < width
        && ((int)pos / width) + dir.second >= 0
        && ((int)pos / width) + dir.second < height
        && input[pos + dir.second * width + dir.first] == input[pos] + 1) {
            int point = pos + dir.second * width + dir.first;
            if (input[point] == '9') {
                score++;
            } else {
                score += find_top(point, dirs, width, height, input);
            }
        }
    }

    find_top_cache[pos] = score;

    return score;
}


int main() {
    ifstream data("input.txt");
    std::string input((std::istreambuf_iterator<char>(data)),
    std::istreambuf_iterator<char>());
    long long total = 0;
    const regex findtrails("0");
    const int height = std::count(input.begin(), input.end(), '\n') + 1;
    input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
    const int width = (int)input.size() / height;
    pair<short, short> dirs[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    
    string::const_iterator start = input.cbegin();
    smatch trailhead;
    int pos = 0;
    while (regex_search(start, input.cend(), trailhead, findtrails)) {
        pos += trailhead.position();
        total += find_top(pos, dirs, width, height, input);
        start = trailhead.suffix().first;
        pos++;
    }

    cout << total << '\n';

    return 0;
}
