#include<algorithm>
#include<fstream>
#include<iostream>
#include<string>
#include<unordered_map>
#include<set>

using namespace std;


int main() {
    ifstream data("input.txt");
    int total = 0;
    unordered_map<string, set<string>> graph;
    set<string> corr_comps;

    string line;
    while (getline(data, line)) {
        string comp0 = line.substr(0, 2);
        string comp1 = line.substr(3, 2);
        if (graph.count(comp0)) {
            graph[comp0].insert(comp1);
        } else {
            graph[comp0] = {comp1};
            if (comp0[0] == 't') {
                corr_comps.insert(comp0);
            }
        }
        if (graph.count(comp1)) {
            graph[comp1].insert(comp0);
        } else {
            graph[comp1] = {comp0};
            if (comp1[0] == 't') {
                corr_comps.insert(comp1);
            }
        }
    }

    for (const auto comp : corr_comps) {
        set<string>* con_comp = &graph[comp];
        while (con_comp->size()) {
            string ccomp = *(con_comp->begin());
            set<string>* con_ccomp = &graph[ccomp];
            con_comp->erase(con_comp->find(ccomp));
            con_ccomp->erase(con_ccomp->find(comp));
            set<string> intersect;
            set_intersection(con_comp->begin(), con_comp->end(), con_ccomp->begin(), con_ccomp->end(), inserter(intersect, intersect.begin()));
            total += intersect.size();
        }
    }

    cout << total << '\n';

    return 0;
}
