#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<regex>
#include<unordered_map>
#include<set>

using namespace std;


int main() {
    ifstream data("input.txt");
    string input((istreambuf_iterator<char>(data)),
    istreambuf_iterator<char>());
    int total = 0;
    smatch mapend;
    regex_search(input.cbegin(), input.cend(), mapend, regex("#\n\n"));
    int mapendpos = mapend.position();
    string map = input.substr(0, mapendpos + 1);
    const int height = count(map.begin(), map.end(), '\n') + 1;
    map.erase(remove(map.begin(), map.end(), '\n'), map.end());
    const int width = (int)map.size() / height;
    string instructs = input.substr(mapendpos + 3, input.size() - mapendpos - 3);
    instructs.erase(remove(instructs.begin(), instructs.end(), '\n'), instructs.end());
    smatch foundbot;
    regex_search(map.cbegin(), map.cend(), foundbot, regex("@"));
    int pos = foundbot.position();
    unordered_map<char, pair<short, short>> dirs = {{'>', {1, 0}}, {'^', {0, -1}}, {'<', {-1, 0}}, {'v', {0, 1}}};

    for (int i = 0; i < instructs.size(); i++) {
        const pair<short, short> dir = dirs[instructs[i]];
        bool good = true;
        for (int n = 0;; n++) {
            int newpos = pos + (dir.first + dir.second * width) * n;
            if (map[newpos] == '#') {
                good = false;
                break;
            }
            if (map[newpos] == '.') {
                map[newpos] = 'O';
                break;
            }
        }
        if (good) {
            map[pos] = '.';
            map[pos = pos + dir.first + dir.second * width] = '@';
        }
        // for (int k = 0; k < height; k++) {
        //     cout << map.substr(k * width, width) << '\n';
        // }
    }

    regex findbox("O");
    smatch foundbox;
    string::const_iterator start = map.cbegin();
    int ittt = 0;
    while (regex_search(start, map.cend(), foundbox, findbox)) {
        ittt += foundbox.position();
        total += ((int)ittt / width) * 100 + (ittt % width);
        start = foundbox.suffix().first;
        ittt++;
    }
    cout << total << '\n';

    return 0;
}
