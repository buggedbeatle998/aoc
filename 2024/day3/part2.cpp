#include<fstream>
#include<iostream>
#include<regex>

using namespace std;


int main() {
    ifstream data("input.txt");
    std::string input((std::istreambuf_iterator<char>(data)), std::istreambuf_iterator<char>());
    int total = 0;

    regex mulregex("don't\\(\\)|do\\(\\)|mul\\(([0-9]+),([0-9]+)\\)");
    smatch matched;
    string::const_iterator start(input.cbegin());
    bool can = true;
    while (regex_search(start, input.cend(), matched, mulregex)) {
        cout << matched[0];
        if (matched[0] == "do()") can = true;
        else if (matched[0] == "don't()") can = false;
        else if (can) {
            cout << matched[1] << ' ' << matched[2] << '\n';
            total += stoi(matched[1]) * stoi(matched[2]);
        }
        start = matched.suffix().first;
    }

    cout << total << '\n';

    return 0;
}
