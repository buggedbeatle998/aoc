#include<fstream>
#include<iostream>
#include<string>

using namespace std;


int main() {
    ifstream data("input.txt");
    std::string input((std::istreambuf_iterator<char>(data)), std::istreambuf_iterator<char>());
    long long total = 0;
    int lptr = 0;
    int idx = -1;
    int rptr = input.size() - 1;

    while (lptr <= rptr) {
        //cout << '\t' << idx << ' ' << lptr << ' ' << rptr << '\n';
        if (input[lptr] == '0') {
            lptr++;
            continue;
        }
        if (input[rptr] == '0') {
            rptr -= 2;
            continue;
        }

        if (!(lptr % 2)) {
            int endidx = idx + input[lptr] - '0';
            //cout << "0c" << endidx - idx << ' ' << (int)(lptr + 1) / 2 << '\n';
            total += (long long)(lptr + 1) / 2 * (endidx * (endidx + 1) - idx * (idx + 1)) / 2;
            idx += input[lptr] - '0';
            input[lptr] = '0';
            lptr++;
        } else {
            if (input[lptr] == input[rptr]) {
                int endidx = idx + input[lptr] - '0';
                //cout << "1c" << endidx - idx << ' ' << (int)(rptr + 1) / 2 << '\n';
                total += (long long)(rptr + 1) / 2  * (endidx * (endidx + 1) - idx * (idx + 1)) / 2;
                idx += input[lptr] - '0';
                input[rptr] = '0';
                lptr++;
                rptr -= 2;
            } else if (input[lptr] < input[rptr]) {
                int endidx = idx + input[lptr] - '0';
                //cout << "2c" << endidx - idx << ' ' << (int)(rptr + 1) / 2 << '\n';
                total += (long long)(rptr + 1) / 2 * (endidx * (endidx + 1) - idx * (idx + 1)) / 2;
                idx += input[lptr] - '0';
                input[rptr] -= input[lptr] - '0';
                lptr++;
            } else {
                int endidx = idx + input[rptr] - '0';
                //cout << "3c" << endidx - idx << ' ' << (int)(rptr + 1) / 2 << '\n';
                total += (long long)(rptr + 1) / 2 * (endidx * (endidx + 1) - idx * (idx + 1)) / 2;
                idx += input[rptr] - '0';
                input[lptr] -= input[rptr] - '0';
                rptr -= 2;
            }
        }
        //cout << total << '\n';
    }

    cout << total << '\n';

    return 0;
}
