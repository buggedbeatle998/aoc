#include<algorithm>
#include<fstream>
#include<iostream>
#include<string>
#include<sstream>
#include<cmath>

using namespace std;


int main() {
    ifstream data("input.txt");
    int total = 0;

    string line;
    while (getline(data, line)) {
        string num;
        bool safe = false;
        int ignore = std::count(line.begin(), line.end(), ' ') + 2;
        while (!safe && ignore-- > 0) {
            //cout << '\n';
            int i = 0;
            int prev = -1;
            short int isdec = -1;
            stringstream ss(line);
            while (getline(ss, num, ' ')) {
                if (i++ == ignore) {
                    continue;
                }
                //cout << num << ' ';
                if (prev != -1 && (abs(prev - stoi(num)) > 3 || prev - stoi(num) == 0 || (isdec != -1 && signbit(stoi(num) - prev) != isdec))) {
                    safe = false;
                    break;
                }
                if (prev != -1) {
                    isdec = signbit(stoi(num) - prev);
                }
                prev = stoi(num);
                safe = true;
            }
        }
        if (safe) {
            total++;
        }
    }

    cout << total << '\n';

    return 0;
}


// int main() {
//     ifstream data("test.txt");
//     int total = 0;

//     string line;
//     while (getline(data, line)) {
//         int prev = -1;
//         string num;
//         total++;
//         stringstream ss(line);
//         short int valid = 2;
//         vector<int> curr;
//         while (getline(ss, num, ' ')) {
//             curr.push_back(stoi(num));
//         }
//         int lsize = curr.size();
//         if (curr[0] == curr[1]) {
//             break;
//         }
//         for (int i = 1; i < lsize - 1; i++) {
//             if (abs(curr[i] - curr[i - 1]) > 3 && abs(curr[i + 1] - curr[i - 1]) > 3) {
//                 valid--;
//             }
//             if (signbit(curr[i] - curr[i - 1]) ^ signbit(curr[i + 1] - curr[i])) {
//                 bool left = signbit(curr[i] - curr[i - 1]);
//                 bool right = signbit(curr[i + 1] - curr[i]);
//                 if (i != 1) {
                    
//                 }
//             }
//         }

//     }

//     cout << total << '\n';

//     return 0;
// }
