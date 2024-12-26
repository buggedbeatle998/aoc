#include<algorithm>
#include<fstream>
#include<iostream>
#include <scoped_allocator>
#include<string>
#include<unordered_map>
#include<set>

using namespace std;


int main() {
    ifstream data("input.txt");
    set<string> total = {};
    unordered_map<string, set<string>> graph;
    set<string> comps;

    string line;
    while (getline(data, line)) {
        string comp0 = line.substr(0, 2);
        string comp1 = line.substr(3, 2);
        comps.insert(comp0);
        comps.insert(comp1);
        if (graph.count(comp0)) {
            graph[comp0].insert(comp1);
        } else {
            graph[comp0] = {comp1};
        }
        if (graph.count(comp1)) {
            graph[comp1].insert(comp0);
        } else {
            graph[comp1] = {comp0};
        }
    }

    int msize = 0;
    set<string> biggest;
    for (const auto comp : comps) {
        set<string> scomp = {comp};
        for (const auto ccomp : comps) {
            bool good = true;
            for (const auto cscomp: scomp) {
                set<string> tocheck = graph[ccomp];
                if (!tocheck.count(cscomp)) {
                    good = false;
                    break;
                }
            }
            if (good) {
                scomp.insert(ccomp);
            }
        }
        if (scomp.size() > msize) {
            biggest = scomp;
            msize = scomp.size();
        }
    }

    for (const auto& comp : biggest) {
        cout << comp << ',';
    }


    return 0;
}
