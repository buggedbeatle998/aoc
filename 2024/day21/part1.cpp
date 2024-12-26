#include<fstream>
#include<iostream>
#include<string>
#include<regex>
#include<algorithm>

using namespace std;


string interpret_nums(string nums) {
    char pos = '0' - 1;
    string presses = "";
    for (auto chr : nums) {
        chr--;
        // / = >
        // - = <
        // 1 = ^
        // . = v
        // 2 = A
        if (chr / 3 < pos / 3 && !(chr / 3 < '0' / 3 && (pos % 3) == 0)) {
            presses += string(abs(pos / 3 - chr / 3), pos / 3 < chr / 3 ? '1' : '.');
            presses += string(abs((pos % 3) - (chr % 3)), pos % 3 < chr % 3 ? '/' : '-');
        } else if (!(chr / 3 > pos / 3 && pos / 3 < '0' / 3 && (chr % 3) == 0)) {
            presses += string(abs((pos % 3) - (chr % 3)), pos % 3 < chr % 3 ? '/' : '-');
            presses += string(abs(pos / 3 - chr / 3), pos / 3 < chr / 3 ? '1' : '.');
        } else {
            presses += string(abs(pos / 3 - chr / 3), pos / 3 < chr / 3 ? '1' : '.');
            presses += string(abs((pos % 3) - (chr % 3)), pos % 3 < chr % 3 ? '/' : '-');
        }
        presses += "2";
        pos = chr;
    }
    return presses;
}


string interpret_keys(string keys) {
    char pos = '2';
    string presses = "";
    for (auto chr : keys) {
        if (chr / 3 < pos / 3) {
            presses += string(abs(pos / 3 - chr / 3), pos / 3 < chr / 3 ? '1' : '.');
            presses += string(abs((pos % 3) - (chr % 3)), pos % 3 < chr % 3 ? '/' : '-');
        } else {
            presses += string(abs((pos % 3) - (chr % 3)), pos % 3 < chr % 3 ? '/' : '-');
            presses += string(abs(pos / 3 - chr / 3), pos / 3 < chr / 3 ? '1' : '.');
        }
        presses += "2";
        pos = chr;
    }
    return presses;
}


int main() {
    ifstream data("input.txt");
    long long total = 0;
    
    string line;
    regex find_num("[0-9]+");
    smatch found_num;
    while (getline(data, line)) {
        regex_search(line, found_num, find_num);
        int num = stoi(found_num[0]);
        replace(line.begin(), line.end(), '0' , '/');
        replace(line.begin(), line.end(), 'A' , '0');
        cout << interpret_nums(line) << '\n';
        cout << interpret_keys(interpret_nums(line)) << '\n';
        cout << interpret_keys(interpret_keys(interpret_nums(line))) << '\n';
        cout << num << ' ' << interpret_keys(interpret_keys(interpret_nums(line))).size() << '\n';
        total += num * interpret_keys(interpret_keys(interpret_nums(line))).size();
    }

    cout << total << '\n';

    return 0;
}
