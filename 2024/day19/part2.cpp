#include<fstream>
#include<iostream>
#include<string>
#include<unordered_map>
#include<set>
#include<regex>

using namespace std;


long long test_string(const string totest, const set<string>& orig, unordered_map<string, long long>& nums) {
    //cout << totest << '9' << '\n';
    if (totest.size() == 1 && orig.count(totest)) return 1;
    if (nums.count(totest)) return nums[totest];
    long long total = 0;
    if (orig.count(totest)) total++;
    for (int i = 1; i < totest.size(); i++) {
        string fhalf = totest.substr(0, i);
        string shalf = totest.substr(i, totest.size() - i);
        if (orig.count(fhalf) && (!nums.count(shalf) || nums[shalf])) {
            total += test_string(shalf, orig, nums);
        }
    }
    nums[totest] = total;
    return total;
}


int main() {
    ifstream data("input.txt");
    long long total = 0;
    string line;
    getline(data, line);
    set<string> orig;
    unordered_map<string, long long> nums;
    string::const_iterator start = line.cbegin();
    string::const_iterator linend = line.cend();
    smatch foundpossible;
    regex findpossible("[a-z]+");
    while (regex_search(start, linend, foundpossible, findpossible)) {
        orig.insert(foundpossible[0]);
        start = foundpossible.suffix().first;
    }
    getline(data, line);

    while (getline(data, line)) {
        cout << test_string(line, orig, nums) << '\n';
        total += test_string(line, orig, nums);
    }

    cout << total << '\n';

    return 0;
}