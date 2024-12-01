#include <algorithm>
#include<fstream>
#include<iostream>
#include<string>
#include<vector>

using namespace std;


bool comp(int a, int b) {
    return a < b;
}


int main() {
    ifstream data("input.txt");
    vector<int> left;
    vector<int> right;
    const int numsize = 5;

    string line;
    while (getline(data, line)) {
        left.push_back(stoi(line.substr(0, numsize)));
        right.push_back(stoi(line.substr(numsize + 3, 2 * numsize + 3)));
    }
    sort(left.begin(), left.end(), comp);
    sort(right.begin(), right.end(), comp);
    
    int total = 0;
    const int ilen = left.size();
    for (int i = 0; i < ilen;) {
        int ubound = distance(left.begin(), upper_bound(left.begin(), left.end(), left[i]));
        total += (ubound - i) * (upper_bound(right.begin(), right.end(), left[i]) - lower_bound(right.begin(), right.end(), left[i])) * left[i];
        i = ubound;
    }

    cout << total << '\n';

    return 0;
}
