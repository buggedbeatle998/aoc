#include <algorithm>
#include<fstream>
#include<iostream>
#include <iterator>
#include<regex>
#include<string>
#include<unordered_map>
#include<map>
#include<bitset>
#include<cmath>
#include<set>

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
    ifstream data("editedinput.txt");
    long long total = 0;

    unordered_map<string, bool> res_cache;
    string line;
    long long xtot = 0;
    long long xmask = 1;
    long long ytot = 0;
    long long ymask = 1;
    while (getline(data, line)) {
        if (line == "") break;
        if (line[0] == 'x') {
            xtot += (line[5] - '0') * xmask;
            xmask <<= 1;
        } else {
            ytot += (line[5] - '0') * ymask;
            ymask <<= 1;
        }
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
    int maxbit;
    for (const auto& subres : result) {
        total += subres.second * mask;
        mask <<= 1;
    }
    maxbit = log2(mask) + 1;
    bitset<64> bit_rep((xtot + ytot) ^ total);

    set<string> no_touch;
    set<string> maybe_touch;
    for (int i = 0; i < maxbit; i++) {
        string temp = "z" + to_string(i / 10) + to_string(i % 10);
        if (!bit_rep[i]) {
            no_touch.insert(get<0>(res_wires[temp]));
            no_touch.insert(get<2>(res_wires[temp]));
        } else {
            maybe_touch.insert(get<0>(res_wires[temp]));
            maybe_touch.insert(get<2>(res_wires[temp]));
            string left;
            short mid;
            string right;
            tie(left, mid, right) = res_wires[temp];
            if (res_cache[temp]) {
                if (mid == 0) {cout << left << " or " << right << " to 0\n";}
                else if (mid == 1) {
                    if (res_cache[left] ^ res_cache[right]) {
                        cout << (res_cache[left] ? left : right) << " to 0\n";
                    } else {
                        cout << left << " and " << right << " to 0\n";
                    }
                } else {
                    cout << (res_cache[left] ? left + " to 0 or " + right + " to 1\n" : right + " to 0 or " + left + " to 1\n");
                }
            } else {
                if (mid == 0) {
                    if (res_cache[left] ^ res_cache[right]) {
                        cout << string(12, ' ') << (res_cache[right] ? left : right) << " to 1\n";
                    } else {
                        cout << left << " and " << right << " to 0\n";
                    }
                } else if (mid == 1) {cout << left << " or " << right << " to 1\n";}
                else {
                    cout << (res_cache[left] ? left + " to 0 or " + right + " to 1\n" : right + " to 0 or " + left + " to 1\n");
                }
            }
            //maybe_touch.insert(get<0>(res_wires[temp]));
            //maybe_touch.insert(get<2>(res_wires[temp]));
        }
    }

    set<string> out;
    set_intersection(maybe_touch.begin(), maybe_touch.end(), no_touch.begin(), no_touch.end(), inserter(out, out.begin()));
    for (const auto touch : out) {
        cout << touch << '\n';
    }

    cout << bitset<46>((xtot + ytot) ^ total) << '\n';

    return 0;
}
