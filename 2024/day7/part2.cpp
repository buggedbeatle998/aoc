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
        while (regex_search(starti, line.cend(), num, findnum)) {
            nums.push_back(stoi(num[0]));
            starti = num.suffix().first;
        }

        int operatormask = 0;
        int limit = pow(3, nums.size() - 1);
        do {
            long long int equals = nums[0];
            for (int i = 1; i < nums.size(); i++) {
                short currop = ((int)operatormask / (int)pow(3, i - 1)) % 3;
                if (currop == 0)
                    equals += nums[i];
                else if (currop == 1)
                    equals *= nums[i];
                else {
                    equals = equals * (int)pow(10, ((int)log10(nums[i]) + 1)) + nums[i];
                }
            }
            if (equals == result) {
                total += result;
                break;
            }
        } while (++operatormask < limit);
    }

    cout << total << '\n';
}
