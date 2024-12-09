#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<regex>
#include<cmath>

using namespace std;


int main() {
    ifstream data("input.txt");
    long long total = 0;
    regex findnum("[0-9]+");

    string line;
    while (getline(data, line)) {
        smatch num;
        string::const_iterator starti = line.cbegin();
        regex_search(starti, line.cend(), num, findnum);
        long long int result = stoll(num[0]);
        starti = num.suffix().first;
        vector<int> nums;
        cout << "hi" << ' ';
        while (regex_search(starti, line.cend(), num, findnum)) {
            nums.push_back(stoi(num[0]));
            starti = num.suffix().first;
        }
        cout << "hi" << '\n';

        int operatormask = 0;
        int limit = pow(2, nums.size() - 1);
        do {
            long long int equals = nums[0];
            for (int i = 1; i < nums.size(); i++) {
                equals = operatormask & (int)pow(2, i - 1) ? equals * nums[i] : equals + nums[i];
            }
            if (equals == result) {
                total += result;
                break;
            }
        } while (++operatormask < limit);
    }

    cout << total << '\n';

    return 0;
}
