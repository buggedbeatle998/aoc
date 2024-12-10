#include<fstream>
#include<iostream>
#include<string>
#include<vector>

using namespace std;


int main() {
    ifstream data("test.txt");
    std::string input((std::istreambuf_iterator<char>(data)), std::istreambuf_iterator<char>());
    long long total = 0;
    int lptr = 0;
    int idx = -1;
    int end = input.size();
    int rptr = end - 1;
    vector<short> offs(0, end);

    while (lptr <= rptr) {
        if (input[rptr] == '0') {
            rptr -= 2;
            continue;
        }
        int counter = 0;
        int sum = -1;
        while (counter < rptr) {
            cout << counter << '\n';
            if (!(counter % 2)) {
                sum += input[counter];
            } else {
                if (input[counter] >= input[rptr]) {
                    sum += offs[counter];
                    int endidx = sum + input[counter] - '0';
                    total += (long long)(rptr + 1) / 2 * (endidx * (endidx + 1) - sum * (sum + 1)) / 2;
                    cout << ((long long)(rptr + 1) / 2 * (endidx * (endidx + 1) - sum * (sum + 1)) / 2) << ' ' << sum << ' ' << counter << '\n';
                    if (input[counter] == input[rptr]) {
                        input[counter] = '0';
                    } else {
                        input[counter] -= input[rptr] - '0';
                        offs[counter] += input[counter] - input[rptr];
                    }
                    sum += input[counter];
                    input[rptr] = '0';
                } else {
                    sum += (input[counter] - '0') + (offs[counter]);
                }
            }
            counter++;
        }
        rptr -= 2;
    }

    while (lptr < end) {
        if (input[lptr] == '0') {
            lptr++;
            continue;
        }

        if (!(lptr % 2)) {
            int endidx = idx + input[lptr] - '0';
            //cout << "0c" << endidx - idx << ' ' << (int)(lptr + 1) / 2 << '\n';
            total += (long long)(lptr + 1) / 2 * (endidx * (endidx + 1) - idx * (idx + 1)) / 2;
        }
        idx += input[lptr] - '0';
        input[lptr] = '0';
        lptr++;
    }

    cout << total << '\n';

    return 0;
}
