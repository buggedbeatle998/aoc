#include<fstream>
#include<iostream>
#include<string>
#include<regex>
#include<cmath>

using namespace std;


int main() {
    ifstream data("input.txt");
    int total = 0;
    regex findnum("[-0-9]+");
    const int width = 101;
    const int height = 103;
    const int robotnum = 500;
    string grid(width * height, '0');
    int robots[robotnum][4];

    int i = 0;
    string line;
    while (getline(data, line)) {
        //cout << 'c' << line << '\n';
        smatch num;
        regex_search(line.cbegin(), line.cend(), num, findnum);
        robots[i][0] = stoi(num[0]);
        regex_search(num.suffix().first, line.cend(), num, findnum);
        robots[i][1] = stoi(num[0]);
        grid[robots[i][1] * width + robots[i][0]]++;
        regex_search(num.suffix().first, line.cend(), num, findnum);
        robots[i][2] = width + stoi(num[0]);
        regex_search(num.suffix().first, line.cend(), num, findnum);
        //cout << num[0] << '\n';
        robots[i][3] = height + stoi(num[0]);
        i++;
    }

    i = 0;
    regex find_dense("([1-9]{3}.{98}){3}");
    while (true) {
        if (regex_search(grid.cbegin(), grid.cend(), find_dense)) {
            for (int n = 0; n < height; n++) {
                cout << grid.substr(n * width, width) << '\n';
            }
            cout << i << '\n';
            break;
        }
        for (auto& robot : robots) {
            grid[robot[1] * width + robot[0]]--;
            robot[0] = (robot[0] + robot[2]) % width;
            robot[1] = (robot[1] + robot[3]) % height;
            grid[robot[1] * width + robot[0]]++;
        }
        //cout << i << '\n';
        i++;
    }

    cout << total << '\n';

    return 0;
}
