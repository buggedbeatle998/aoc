#include<fstream>
#include<iostream>
#include<string>
#include<regex>
#include<unordered_set>
#include <utility>

using namespace std;

pair<int, int> fill_area(int pos, unordered_set<int>& visited, const pair<short, short>(& dirs)[4], const int width, const int height, string& input) {
    int area = 1;
    int perim = 0;
    char type = input[pos];
    input[pos] ^= 32;

    for (short i = 0; i < 4; i++) {
        pair<short, short> dir = dirs[i];
        if (
           (pos % width) + dir.first >= 0
        && (pos % width) + dir.first < width
        && ((int)pos / width) + dir.second >= 0
        && ((int)pos / width) + dir.second < height) {
            int point = pos + dir.second * width + dir.first;
            if (input[point] == type) {
                pair<int, int> temp = fill_area(point, visited, dirs, width, height, input);
                area += temp.first;
                perim += temp.second;
            } else if (input[point] != (type ^ 32)) {
                if (!visited.count((point << 2) + i)) {
                    perim++;
                    //cout << '\t' << (point % width) << ' ' << (point / width) << ' ' << i << '\n';
                    visited.insert((point << 2) + i);
                    pair<short, short> tempdir = dirs[(i + 1) % 4];
                    int tpos = pos;
                    while (
                       ((tpos += tempdir.first + tempdir.second * width) % width) >= 0
                    && (tpos % width) < width
                    && ((int)tpos / width) >= 0
                    && ((int)tpos / width) < height
                    && (input[tpos] == type || input[tpos] == (type ^ 32))
                    && (input[tpos + dir.first + dir.second * width] != type && input[tpos + dir.first + dir.second * width] != (type ^ 32)))
                        visited.insert(((tpos + dir.first + dir.second * width) << 2) + i);
                    tempdir = dirs[(i + 3) % 4];
                    tpos = pos;
                    while (
                       ((tpos += tempdir.first + tempdir.second * width) % width) >= 0
                    && (tpos % width) < width
                    && ((int)tpos / width) >= 0
                    && ((int)tpos / width) < height
                    && (input[tpos] == type || input[tpos] == (type ^ 32))
                    && (input[tpos + dir.first + dir.second * width] != type && input[tpos + dir.first + dir.second * width] != (type ^ 32)))
                        visited.insert(((tpos + dir.first + dir.second * width) << 2) + i);
                }
            }
        } else {
            int point = pos + dir.second * width + dir.first;
            if (!visited.count((point << 2) + i)) {
                perim++;
                //cout << "\tc" << (point % width) << ' ' << (point / width) << ' ' << i << '\n';
                visited.insert((point << 2) + i);
                pair<short, short> tempdir = dirs[(i + 1) % 4];
                int tpos = pos;
                while (
                   ((tpos += tempdir.first + tempdir.second * width) % width) >= 0
                && (tpos % width) < width
                && ((int)tpos / width) >= 0
                && ((int)tpos / width) < height
                && (input[tpos] == type || input[tpos] == (type ^ 32)))
                    visited.insert(((tpos + dir.first + dir.second * width) << 2) + i);
                tempdir = dirs[(i + 3) % 4];
                tpos = pos;
                while (
                   ((tpos += tempdir.first + tempdir.second * width) % width) >= 0
                && (tpos % width) < width
                && ((int)tpos / width) >= 0
                && ((int)tpos / width) < height
                && (input[tpos] == type || input[tpos] == (type ^ 32)))
                    visited.insert(((tpos + dir.first + dir.second * width) << 2) + i);
            }
        }
    }

    return {area, perim};
}


int main() {
    ifstream data("input.txt");
    std::string input((std::istreambuf_iterator<char>(data)),
    std::istreambuf_iterator<char>());
    long long total = 0;
    const regex findpatches("[A-Z]");
    const int height = std::count(input.begin(), input.end(), '\n') + 1;
    input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
    const int width = (int)input.size() / height;
    pair<short, short> dirs[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    
    string::const_iterator start = input.cbegin();
    smatch foundpatch;
    int pos = 0;
    while (regex_search(start, input.cend(), foundpatch, findpatches)) {
        pos += foundpatch.position();
        int tocout;
        //cout << input[pos] << '\n';
        unordered_set<int> visited;
        pair<int, int> areaperim = fill_area(pos, visited, dirs, width, height, input);
        //cout << areaperim.first << ' ' << areaperim.second << '\n';
        total += areaperim.first * areaperim.second;
        start = foundpatch.suffix().first;
        pos++;
    }

    cout << total << '\n';

    return 0;
}
