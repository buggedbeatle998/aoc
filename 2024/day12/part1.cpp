#include<fstream>
#include<iostream>
#include<string>
#include<regex>

using namespace std;

pair<int, int> fill_area(int pos, const pair<short, short>(& dirs)[4], const int width, const int height, string& input) {
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
                pair<int, int> temp = fill_area(point, dirs, width, height, input);
                area += temp.first;
                perim += temp.second;
            } else if (input[point] != (type ^ 32)) {
                perim++;
            }
        } else perim++;
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
        //cout << input[pos] << ' ';
        pair<int, int> areaperim = fill_area(pos, dirs, width, height, input);
        //cout << areaperim.first << ' ' << areaperim.second << '\n';
        total += areaperim.first * areaperim.second;
        start = foundpatch.suffix().first;
        pos++;
    }

    cout << total << '\n';

    return 0;
}
