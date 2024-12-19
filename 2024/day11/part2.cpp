#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<cmath>
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


unordered_map<pair<long long, int>, long long, hash_pair> stone_cache;
long long iterate_stone(long long stone, long long depth) {
    if (!depth) {
        //cout << stone << '\n';
        return 1;
    }
    if (stone_cache.count({stone, depth})) {
        //cout << 'c' << stone << ' ' << depth << ' ' << stone_cache[(stone << 6) + depth] << ' ' << ((stone << 6) + depth) << '\n';
        return stone_cache[{stone, depth}];
    }
    long long total = 0;

    if (!stone) {
        total += iterate_stone(1, depth - 1);
    } else if ((long long)log10(stone) % 2) {
        long long half = (long long)pow(10, (int)log10(stone) / 2 + 1);
        total += iterate_stone((long long)stone / half, depth - 1);
        total += iterate_stone((long long)stone % half, depth - 1);
    } else {
        total += iterate_stone(stone * 2024, depth - 1);
    }

    //cout << stone << ' ' << depth << ' ' << total << ' ' << ((stone << 6) + depth) << '\n';

    stone_cache[{stone, depth}] = total;

    return total;
}

int main() {
    ifstream data("input.txt");
    long long total = 0;
    
    string stone;
    while(getline(data, stone, ' ')) {
        long long temp = iterate_stone(stoll(stone), 75);
        //cout << temp << '\n';
        total += temp;
    }

    cout << total << '\n';

    return 0;
}
