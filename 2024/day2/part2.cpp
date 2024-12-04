#include<algorithm>
#include<fstream>
#include<iostream>
#include<string>
#include<sstream>
#include<cmath>

using namespace std;


int main() {
    ifstream data("input.txt");
    int total = 0;

    string line;
    while (getline(data, line)) {
        string num;
        bool safe = false;
        int ignore = std::count(line.begin(), line.end(), ' ') + 2;
        while (!safe && ignore-- > 0) {
            //cout << '\n';
            int i = 0;
            int prev = -1;
            short int isdec = -1;
            stringstream ss(line);
            while (getline(ss, num, ' ')) {
                if (i++ == ignore) {
                    continue;
                }
                //cout << num << ' ';
                if (prev != -1 && (abs(prev - stoi(num)) > 3 || prev - stoi(num) == 0 || (isdec != -1 && signbit(stoi(num) - prev) != isdec))) {
                    safe = false;
                    break;
                }
                if (prev != -1) {
                    isdec = signbit(stoi(num) - prev);
                }
                prev = stoi(num);
                safe = true;
            }
        }
        if (safe) {
            total++;
        }
    }

    cout << total << '\n';

    return 0;
}