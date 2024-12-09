#include<algorithm>
#include<fstream>
#include<iostream>
#include<string>
#include<vector>

using namespace std;


int main() {
    ifstream data("input.txt");
    std::string input((std::istreambuf_iterator<char>(data)), std::istreambuf_iterator<char>());
    int total = 0;
    int lptr = 0;
    int idx = 0;
    int rptr = input.size() - 1;
    int eblock = (int)input.size() / 2 + 1;
    int bblock = (int)input.size() / 2 + 1;

    while (lptr < rptr) {
        if (!(lptr % 2)) {

        }
    }

    cout << total << '\n';

    return 0;
}