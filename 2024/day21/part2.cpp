#include<fstream>
#include<iostream>
#include<string>
#include<regex>
#include<algorithm>
#include<unordered_map>

using namespace std;


struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const
    {
        // Hash the first element
        size_t hash1 = hash<T1>{}(p.first);
        // Hash the second element
        size_t hash2 = hash<T2>{}(p.second);
        // Combine the two hash values
        return hash1
               ^ (hash2 + 0x9e3779b9 + (hash1 << 6)
                  + (hash1 >> 2));
    }
};


unordered_map<string, long long> interpret_nums(string nums) {
    unordered_map<string, long long> buckets;
    char pos = '0' - 1;
    for (auto chr : nums) {
        string presses;
        chr--;
        // / = >
        // - = <
        // 1 = ^
        // . = v
        // 2 = A
        if ((chr % 3) > (pos % 3) && !(!(chr & 16) && (pos % 3) == 0)) {
            presses = string(abs(pos / 3 - chr / 3), pos / 3 < chr / 3 ? '1' : '.');
            presses += string(abs((pos % 3) - (chr % 3)), pos % 3 < chr % 3 ? '/' : '-');
        } else if (!((chr % 3) < (pos % 3) && !(pos & 16) && (chr % 3) == 0)) {
            presses = string(abs((pos % 3) - (chr % 3)), pos % 3 < chr % 3 ? '/' : '-');
            presses += string(abs(pos / 3 - chr / 3), pos / 3 < chr / 3 ? '1' : '.');
        } else {
            presses = string(abs(pos / 3 - chr / 3), pos / 3 < chr / 3 ? '1' : '.');
            presses += string(abs((pos % 3) - (chr % 3)), pos % 3 < chr % 3 ? '/' : '-');
        }
        presses += "2";
        if (buckets.count(presses)) {
            buckets[presses]++;
        } else {
            buckets[presses] = 1;
        }
        pos = chr;
    }
    return buckets;
}


unordered_map<string, long long> interpret_buckets(unordered_map<string, long long> buckets) {
    unordered_map<string, long long> new_buckets;
    char pos = '2';
    for (auto& bucket : buckets) {
        for (auto chr : bucket.first) {
            string temp = "";
                if ((chr % 3) > (pos % 3) && !((pos % 3) == 0 && (chr & 16))) {
                    temp += string(abs(pos / 3 - chr / 3), pos / 3 < chr / 3 ? '1' : '.');
                    temp += string(abs((pos % 3) - (chr % 3)), pos % 3 < chr % 3 ? '/' : '-');
                } else if (!((chr % 3) < (pos % 3) && (chr % 3) == 0 && (pos & 16))) {
                    temp += string(abs((pos % 3) - (chr % 3)), pos % 3 < chr % 3 ? '/' : '-');
                    temp += string(abs(pos / 3 - chr / 3), pos / 3 < chr / 3 ? '1' : '.');
                } else {
                    temp += string(abs(pos / 3 - chr / 3), pos / 3 < chr / 3 ? '1' : '.');
                    temp += string(abs((pos % 3) - (chr % 3)), pos % 3 < chr % 3 ? '/' : '-');
                }
                temp += "2";
            if (new_buckets.count(temp)) {
                new_buckets[temp] += bucket.second;
            } else {
                new_buckets[temp] = bucket.second;
            }
            pos = chr;
        }
    }
    return new_buckets;
}




int main() {
    ifstream data("input.txt");
    long long total = 0;
    
    string line;
    regex find_num("[0-9]+");
    smatch found_num;
    while (getline(data, line)) {
        regex_search(line, found_num, find_num);
        int num = stoi(found_num[0]);
        replace(line.begin(), line.end(), '0' , '/');
        replace(line.begin(), line.end(), 'A' , '0');
        unordered_map<string, long long> buckets = interpret_nums(line);
        for (int i = 0; i < 25; i++) {
            buckets = interpret_buckets(buckets);
        }
        for (const auto& bucket : buckets) {
            total += num * bucket.second * bucket.first.size();
        }
    }

    cout << total << '\n';

    return 0;
}
