#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<regex>
#include<unordered_map>
#include<set>

using namespace std;

bool test_push_box(pair<short, short> dir, string& map, int pos, const int width, const int height) {
    if (map[pos] == ']') pos--;
    if (dir.second != 0) {
        int below = pos + dir.second * width;
        if (map[below] == '.' && map[below + 1] == '.') {
            return true;
        }
        if (map[below] == '#' || map[below + 1] == '#') {
            return false;
        }
        if (map[below] == ']' && map[below + 1] == '.') {
            if (test_push_box(dir, map, below, width, height)) {
                return true;
            }
            return false;
        }
        if (map[below] == '.' && map[below + 1] == '[') {
            if (test_push_box(dir, map, below + 1, width, height)) {
                return true;
            }
            return false;
        }
        if (map[below] == '[' && map[below + 1] == ']') {
            if (test_push_box(dir, map, below, width, height)) {
                return true;
            }
            return false;
        }
        if (map[below] == ']' && map[below + 1] == '[') {
            if (test_push_box(dir, map, below, width, height) && test_push_box(dir, map, below + 1, width, height)) {
                return true;
            }
            return false;
        }
    } else {
        if (dir.first == 1) {
            if (map[pos + 2] == '.') {
                return true;
            }
            if (map[pos + 2] == '#') {
                return false;
            }
            if (map[pos + 2] == '[') {
                if (test_push_box(dir, map, pos + 2, width, height)) {
                    return true;
                }
                return false;
            }
        } else {
            if (map[pos - 1] == '.') {
                return true;
            }
            if (map[pos - 1] == '#') {
                return false;
            }
            if (map[pos - 1] == ']') {
                if (test_push_box(dir, map, pos - 1, width, height)) {
                    return true;
                }
                return false;
            }
        }
    }
    return false;
}

bool push_box(pair<short, short> dir, string& map, int pos, const int width, const int height) {
    if (map[pos] == ']') pos--;
    if (dir.second != 0) {
        int below = pos + dir.second * width;
        if (map[below] == '.' && map[below + 1] == '.') {
            map[below] = '[';
            map[below + 1] = ']';
            map[pos] = '.';
            map[pos + 1] = '.';
            return true;
        }
        if (map[below] == '#' || map[below + 1] == '#') {
            return false;
        }
        if (map[below] == ']' && map[below + 1] == '.') {
            if (push_box(dir, map, below, width, height)) {
                map[below] = '[';
                map[below + 1] = ']';
                map[pos] = '.';
                map[pos + 1] = '.';
                return true;
            }
            return false;
        }
        if (map[below] == '.' && map[below + 1] == '[') {
            if (push_box(dir, map, below + 1, width, height)) {
                map[below] = '[';
                map[below + 1] = ']';
                map[pos] = '.';
                map[pos + 1] = '.';
                return true;
            }
            return false;
        }
        if (map[below] == '[' && map[below + 1] == ']') {
            if (push_box(dir, map, below, width, height)) {
                map[below] = '[';
                map[below + 1] = ']';
                map[pos] = '.';
                map[pos + 1] = '.';
                return true;
            }
            return false;
        }
        if (map[below] == ']' && map[below + 1] == '[') {
            if (push_box(dir, map, below, width, height) && push_box(dir, map, below + 1, width, height)) {
                map[below] = '[';
                map[below + 1] = ']';
                map[pos] = '.';
                map[pos + 1] = '.';
                return true;
            }
            return false;
        }
    } else {
        if (dir.first == 1) {
            if (map[pos + 2] == '.') {
                map[pos + 2] = ']';
                map[pos + 1] = '[';
                map[pos] = '.';
                return true;
            }
            if (map[pos + 2] == '#') {
                return false;
            }
            if (map[pos + 2] == '[') {
                if (push_box(dir, map, pos + 2, width, height)) {
                    map[pos + 2] = ']';
                    map[pos + 1] = '[';
                    map[pos] = '.';
                    return true;
                }
                return false;
            }
        } else {
            if (map[pos - 1] == '.') {
                map[pos - 1] = '[';
                map[pos] = ']';
                map[pos + 1] = '.';
                return true;
            }
            if (map[pos - 1] == '#') {
                return false;
            }
            if (map[pos - 1] == ']') {
                if (push_box(dir, map, pos - 1, width, height)) {
                    map[pos - 1] = '[';
                    map[pos] = ']';
                    map[pos + 1] = '.';
                    return true;
                }
                return false;
            }
        }
    }
    return false;
}

int main() {
    ifstream data("input.txt");
    string input((istreambuf_iterator<char>(data)),
    istreambuf_iterator<char>());
    int total = 0;
    smatch mapend;
    regex_search(input.cbegin(), input.cend(), mapend, regex("#\n\n"));
    int mapendpos = mapend.position();
    string map = input.substr(0, mapendpos + 1);
    string newString;
    for (auto character : map) {
        switch (character) {
            case '#':
            case '.':
                newString.append(2, character);
                break;
            case 'O':
                newString.append(1, '[');
                newString.append(1, ']');
                break;
            case '@':
                newString.append(1, '@');
                newString.append(1, '.');
                break;
            default:
                newString.append(1, character);
                break;
        }
    }
    map = newString;
    const int height = count(map.begin(), map.end(), '\n') + 1;
    map.erase(remove(map.begin(), map.end(), '\n'), map.end());
    const int width = (int)map.size() / height;
    string instructs = input.substr(mapendpos + 3, input.size() - mapendpos - 3);
    instructs.erase(remove(instructs.begin(), instructs.end(), '\n'), instructs.end());
    smatch foundbot;
    regex_search(map.cbegin(), map.cend(), foundbot, regex("@"));
    int pos = foundbot.position();
    unordered_map<char, pair<short, short>> dirs = {{'>', {1, 0}}, {'^', {0, -1}}, {'<', {-1, 0}}, {'v', {0, 1}}};
    
    // for (int k = 0; k < height; k++) {
    //     cout << map.substr(k * width, width) << '\n';
    // }
string cdcnd = "";
    for (int i = 0; i < instructs.size(); i++) {
    // while (true) {
    //     string i;
    //     cin >> i;
        const pair<short, short> dir = dirs[instructs[i]];
        int newpos = pos + dir.first + dir.second * width;
        if (map[newpos] == '.') {
            map[pos] = '.';
            map[newpos] = '@';
            pos = newpos;
        } else if ((map[newpos] == '[' || map[newpos] == ']') && test_push_box(dir, map, newpos, width, height)) {
            push_box(dir, map, newpos, width, height);
            map[pos] = '.';
            map[newpos] = '@';
            pos = newpos;
        }
        //cout << i << '\n';
    //cout << (cdcnd += instructs[i]) << '\n';
        // for (int k = 0; k < height; k++) {
        //     cout << map.substr(k * width, width) << '\n';
        // }  
    }

        for (int k = 0; k < height; k++) {
            cout << map.substr(k * width, width) << '\n';
        }  
    regex findbox("\\[");
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
