#include <algorithm>
#include<fstream>
#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<cmath>

using namespace std;


int main() {
    ifstream data("test.txt");
    int total = 0;

    string line;
    while (getline(data, line)) {
        int prev = -1;
        string num;
        total++;
        stringstream ss(line);
        short int isdec = -1;
        while (getline(ss, num, ' ')) {
            if (prev != -1 && (abs(prev - stoi(num)) > 3 || prev - stoi(num) == 0 || (isdec != -1 && signbit(stoi(num) - prev) != isdec))) {
                total--;
                break;
            }
            if (prev != -1) {
                isdec = signbit(stoi(num) - prev);
            }
            prev = stoi(num);
        }
    }

    cout << total << '\n';

    return 0;
}
