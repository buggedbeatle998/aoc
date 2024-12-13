#include<fstream>
#include<iostream>
#include<string>
#include<regex>
#include<cmath>

using namespace std;


int main() {
    ifstream data("input.txt");
    long long total = 0;
    regex findnum("[0-9]+");

    string line;
    while (getline(data, line)) {
        //cout << 'c' << line << '\n';
        pair<int, int> buta = {stoi(line.substr(12, 2)), stoi(line.substr(18, 2))};
        getline(data, line);
        pair<int, int> butb = {stoi(line.substr(12, 2)), stoi(line.substr(18, 2))};
        smatch destnum;
        getline(data, line);
        regex_search(line.cbegin(), line.cend(), destnum, findnum);
        long long destx = stoi(destnum[0]) + 10000000000000;
        regex_search(destnum.suffix().first, line.cend(), destnum, findnum);
        long long desty = stoi(destnum[0]) + 10000000000000;
        long long det_ab = buta.first * butb.second - butb.first * buta.second;
        double multa = (double)(destx * butb.second - butb.first * desty) / det_ab;
        double multb = (double)(buta.first * desty - destx * buta.second) / det_ab;
        if (fmod(multa, 1) == 0 && fmod(multb, 1) == 0)
            total += multb + multa * 3;
        getline(data, line);
    }

    cout << total << '\n';

    return 0;
}
