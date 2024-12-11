#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<unordered_map>

using namespace std;

unordered_map<long long, int> stone_cache;
int iterate_stone(long long stone, int depth) {
    if (!depth) {
        //cout << stone << '\n';
        return 1;
    }
    if (stone_cache.count((long long)stone << 6 + depth)) {
        //cout << 'c' << stone << ' ' << depth << ' ' << stone_cache[(stone << 6) + depth] << ' ' << ((stone << 6) + depth) << '\n';
        return stone_cache[(stone << 6) + depth];
    }
    int total = 0;

    if (!stone) {
        total += iterate_stone(1, depth - 1);
    } else if ((int)log10(stone) % 2) {
        long long half = (long long)pow(10, (int)log10(stone) / 2 + 1);
        total += iterate_stone((long long)stone / half, depth - 1);
        total += iterate_stone((long long)stone % half, depth - 1);
    } else {
        total += iterate_stone(stone * 2024, depth - 1);
    }

    //cout << stone << ' ' << depth << ' ' << total << ' ' << ((stone << 6) + depth) << '\n';

    stone_cache[(stone << 6) + depth] = total;

    return total;
}

int main() {
    ifstream data("input.txt");
    int total = 0;
    
    string stone;
    while(getline(data, stone, ' ')) {
        //cout << iterate_stone(stoll(stone), 5) << '\n';
        total += iterate_stone(stoll(stone), 75);
    }

    cout << total << '\n';

    return 0;
}