#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<regex>
#include<unordered_map>
#include<set>

using namespace std;


int main() {
    ifstream data("input.txt");
    std::string input((std::istreambuf_iterator<char>(data)),
    std::istreambuf_iterator<char>());
    int total = 0;
    const regex findpos("[0-9a-zA-Z]");
    const int height = std::count(input.begin(), input.end(), '\n') + 1;
    input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
    const int width = (int)input.size() / height;

    unordered_map<string, vector<pair<int, int>>> antennas;
    smatch antfound;
    string::const_iterator start = input.cbegin();
    int pos = 0;
    while (regex_search(start, input.cend(), antfound, findpos)) {
        if (!antennas.count(antfound[0])) {
            antennas[antfound[0]] = vector<pair<int, int>>();
        }
        antennas[antfound[0]].push_back({(pos + antfound.position()) % width, (int)(pos + antfound.position()) / width});
        pos += antfound.position() + 1;
        start = antfound.suffix().first;
    }
    
    set<pair<int, int>> antinodes;
    for (const auto& kv : antennas) {
        vector<pair<int, int>> posses = kv.second;
        for (const auto& pos0 : posses) {
            for (const auto& pos1 : posses) {
                if (pos0 == pos1) continue;
                pair<int, int> antinode = {pos0.first - (pos1.first - pos0.first), pos0.second - (pos1.second - pos0.second)};
                if (antinode.first >= 0 && antinode.first < width && antinode.second >= 0 && antinode.second < height && !antinodes.count(antinode)) {
                    antinodes.insert(antinode);
                    //cout << antinode.first << ' ' << antinode.second << '\n';
                    input[antinode.second * width + antinode.first] = '#';
                    total++;
                }
                antinode = {pos1.first + (pos1.first - pos0.first), pos1.second + (pos1.second - pos0.second)};
                if (antinode.first >= 0 && antinode.first < width && antinode.second >= 0 && antinode.second < height && !antinodes.count(antinode)) {
                    antinodes.insert(antinode);
                    //cout << antinode.first << ' ' << antinode.second << '\n';
                    input[antinode.second * width + antinode.first] = '#';
                    total++;
                }
            }
        }
    }

    //for (int i = 0; i < height; i++)
        //cout << input.substr(i * width, width) << '\n';
    cout << total << '\n';

    return 0;
}
