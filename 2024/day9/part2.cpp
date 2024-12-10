#include<fstream>
#include<iostream>
#include<string>
#include<vector>

using namespace std;


int main() {
    ifstream data("input.txt");
    std::string input((std::istreambuf_iterator<char>(data)), std::istreambuf_iterator<char>());
    long long total = 0;
    int lptr = 0;
    int idx = -1;
    int end = input.size();
    int rptr = end - 1;
    vector<short> offs(end, 0);

    while (lptr <= rptr) {
        if (input[rptr] == '0') {
            rptr -= 2;
            continue;
        }
        int counter = 0;
        int sum = -1;
        while (counter < rptr) {
            //cout << counter << '\n';
            if (!(counter % 2)) {
                sum += input[counter] - '0';
                //cout << '\t' << sum << '\n';
            } else {
                //cout << input[counter] << ' ' << input[rptr] << '\n';
                if (input[counter] >= input[rptr]) {
                    //cout << 'c' << offs[counter] << '\n';
                    sum += offs[counter];
                    int endidx = sum + input[rptr] - '0';
                    total += (long long)(rptr + 1) / 2 * (endidx * (endidx + 1) - sum * (sum + 1)) / 2;
                    //cout << ((long long)(rptr + 1) / 2 * (endidx * (endidx + 1) - sum * (sum + 1)) / 2) << ' ' << sum << ' ' << counter << '\n';
                    offs[counter] += input[rptr] - '0';
                    if (input[counter] == input[rptr]) {
                        input[counter] = '0';
                    } else {
                        input[counter] -= input[rptr] - '0';
                    }
                    offs[rptr] = input[rptr] - '0';
                    input[rptr] = '0';
                    break;
                } else {
                    sum += (input[counter] - '0') + (offs[counter]);
                    //cout << '\t' << sum << ' ' << input[counter] - '0' << ' ' << offs[counter] << '\n';
                }
            }
            counter++;
        }
        rptr -= 2;
        //cout << '\n';
    }

    while (lptr < end) {
        if (!(lptr % 2) && input[lptr] > '0') {
            int endidx = idx + input[lptr] - '0';
            //cout << "0c" << endidx - idx << ' ' << (int)(lptr + 1) / 2 << '\n';
            total += (long long)(lptr + 1) / 2 * (endidx * (endidx + 1) - idx * (idx + 1)) / 2;
            //cout << ((long long)(lptr + 1) / 2 * (endidx * (endidx + 1) - idx * (idx + 1)) / 2) << ' ' << lptr << '\n';
        }
        idx += input[lptr] - '0' + offs[lptr];
        //cout << '\t' << offs[lptr] << ' ' << input[lptr] << ' ' << lptr << ' ' << idx << '\n';
        input[lptr] = '0';
        lptr++;
    }

    cout << total << '\n';

    return 0;
}
