#include<fstream>
#include<iostream>
#include<regex>
#include<string>
#include<unordered_map>
#include<map>

using namespace std;


void make_res(const pair<string, tuple<string, short, string>>& wire, map<string, bool>& result, unordered_map<string, bool>& res_cache, unordered_map<string, tuple<string, short, string>>& res_wires) {
    string wwire = wire.first;
    bool res;
    string left;
    bool rleft;
    short mid;
    string right;
    bool rright;
    tie(left, mid, right) = wire.second;
    //cout << wwire << " = " << left << ' ' << mid << ' ' << right << '\n';

    if (!res_cache.count(left)) {
        make_res({left, res_wires[left]}, result, res_cache, res_wires);
    }
    rleft = res_cache[left];

    if (!res_cache.count(right)) {
        make_res({right, res_wires[right]}, result, res_cache, res_wires);
    }
    rright = res_cache[right];

    if (mid == 0) {
        res = rleft && rright;
    } else if (mid == 1) {
        res = rleft || rright;
    } else {
        res = rleft != rright;
    }
    res_cache[wwire] = res;
    if (wwire[0] == 'z') {
        result[wwire] = res;
    }
}


int main() {
    ifstream data("input.txt");
    long long total = 0;

    unordered_map<string, bool> res_cache;
    string line;
    while (getline(data, line)) {
        if (line == "") break;
        res_cache[line.substr(0, 3)] = line[5] & 1;
    }
    
    unordered_map<string, tuple<string, short, string>> res_wires;
    while (getline(data, line)) {
        regex find_secs("[a-zA-Z0-9]+");
        smatch found_secs;
        tuple<string, short, string> equation;
        regex_search(line, found_secs, find_secs);
        string left = found_secs[0];
        regex_search(found_secs.suffix().first, line.cend(), found_secs, find_secs);
        short mid = found_secs[0] == "AND" ? 0 : found_secs[0] == "OR" ? 1 : 2;
        regex_search(found_secs.suffix().first, line.cend(), found_secs, find_secs);
        string right = found_secs[0];
        regex_search(found_secs.suffix().first, line.cend(), found_secs, find_secs);
        res_wires[found_secs[0]] = {left, mid, right};
    }

    map<string, bool> result;
    for (const auto& wire : res_wires) {
        make_res(wire, result, res_cache, res_wires);
    }

    //for (const auto& subres : result) {
        //cout << subres.first << ' ' << subres.second << '\n';
    //}

    long long mask = 1;
    for (const auto& subres : result) {
        total += subres.second * mask;
        mask <<= 1;
    }

    cout << total << '\n';

    return 0;
}
