#include<fstream>
#include<iostream>
#include<string>

using namespace std;


int main() {
    ifstream data("input.txt");
    long long total = 0;
    int tomod0 = (1 << (24 - 6)) - 1;
    int tomod2 = (1 << (24 - 11)) - 1;

    string line;
    while (getline(data, line)) {
        long long num = stoll(line);
        for (int i = 0; i < 2000; i++) {
            num = ((num & tomod0) << 6) ^ num;
            num = (num >> 5) ^ num;
            num = ((num & tomod2) << 11) ^ num;
        }
        cout << num << '\n';
        total += num;
    }

    cout << total << '\n';

    return 0;
}
