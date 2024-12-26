#include<cstdint>
#include<fstream>
#include<iostream>
#include<string>
#include<deque>
#include<unordered_map>
#include<set>

using namespace std;


struct hash_deque {
    size_t operator()(const deque<int8_t>& p) const
    {
        return p[0] + (p[1] << 8) + (p[2] << 16) + (p[3] << 24);
    }
};


int main() {
    ifstream data("input.txt");
    int tomod0 = (1 << (24 - 6)) - 1;
    int tomod2 = (1 << (24 - 11)) - 1;
    unordered_map<deque<int8_t>, long long, hash_deque> seqs;

    string line;
    while (getline(data, line)) {
        long long num = stoll(line);
        long long prev;
        set<deque<int8_t>> done;
        deque<int8_t> seq;
        for (int i = 0; i < 2000; i++) {
            prev = num;
            num = ((num & tomod0) << 6) ^ num;
            num = (num >> 5) ^ num;
            num = ((num & tomod2) << 11) ^ num;
            seq.push_back((num % 10) - (prev % 10));
            if (i >= 3) {
                if (!done.count(seq)) {
                    done.insert(seq);
                    if (!seqs.count(seq)) {
                        seqs[seq] = num % 10;
                    } else {
                        seqs[seq] += num % 10;
                    }
                }
                seq.pop_front();
            }
        }
    }
    
    long long most = 0;
    for (const auto& seq : seqs) {
        //if (seq.second > 20)
        //cout << (int)seq.first[0] << ", " << (int)seq.first[1] << ", " << (int)seq.first[2] << ", " << (int)seq.first[3] << ": " << seq.second << '\n';
        most = max(most, seq.second);
    }
    cout << most << '\n';

    return 0;
}
