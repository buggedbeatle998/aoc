#include<fstream>
#include<iostream>
#include<string>
#include<unordered_map>
#include<set>
#include<regex>

using namespace std;


bool test_string(const string totest, set<string>& possible, set<string>& impossible) {
    //cout << totest << '9' << '\n';
    for (int i = totest.size() - 1; i > 0; i--) {
        string fhalf = totest.substr(0, i);
        string shalf = totest.substr(i, totest.size() - i);
        if (!impossible.count(fhalf) && !impossible.count(shalf)) {
            if ((possible.count(fhalf) || test_string(fhalf, possible, impossible))
            && (possible.count(shalf) || test_string(shalf, possible, impossible))) {
                possible.insert(totest);
                return true;
            }
        }
    }
    impossible.insert(totest);
    return false;
}


int main() {
    ifstream data("input.txt");
    int total = 0;
    string line;
    getline(data, line);
    set<string> possible;
    string::const_iterator start = line.cbegin();
    string::const_iterator linend = line.cend();
    smatch foundpossible;
    regex findpossible("[a-z]+");
    while (regex_search(start, linend, foundpossible, findpossible)) {
        possible.insert(foundpossible[0]);
        start = foundpossible.suffix().first;
    }
    set<string> impossible;
    getline(data, line);

    while (getline(data, line)) {
        if (possible.count(line) || test_string(line, possible, impossible))
            total++;
    }

    cout << total << '\n';

    return 0;
}