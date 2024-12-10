#include<fstream>
#include<iostream>
#include<string>

using namespace std;


int main() {
    ifstream data("test.txt");
    std::string input((std::istreambuf_iterator<char>(data)), std::istreambuf_iterator<char>());
    long long total = 0;
    int lptr = 0;
    int idx = -1;
    int end = input.size();
    int rptr = end - 1;

    while (lptr <= rptr) {
        if (input[rptr] == '0') {
            rptr -= 2;
            continue;
        }
        int counter = 0;
        int sum = -1;
        while (counter < rptr) {
            if (!(counter % 2)) {
                sum += input[counter];
            } else {
                if ((input[counter] & '?') >= input[rptr]) {
                    sum += ((input[counter] & 960) >> 6);
                    int endidx = sum + (input[counter] & '?') - '0';
                    total += (long long)(rptr + 1) / 2 * (endidx * (endidx + 1) - sum * (sum + 1)) / 2;
                    cout << ((long long)(rptr + 1) / 2 * (endidx * (endidx + 1) - sum * (sum + 1)) / 2) << ' ' << sum << ' ' << ((input[counter] & 960) >> 6) << ' ' << counter << '\n';
                    if (input[counter] == input[rptr]) {
                        input[counter] = 0;
                    } else {
                        input[counter] -= input[rptr] - '0';
                        input[counter] += input[rptr] << 6;
                    }
                    sum += (input[counter] & '?');
                } else {
                    sum += (input[counter] & '?') + ((input[counter] & 960) >> 6);
                }
            }
            counter++;
        }
        rptr -= 2;
    }

    for (int i = 1; i < end; i += 2) {
        input[i] = (input[i] + ((input[i] & 960) >> 6)) & '?';
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
