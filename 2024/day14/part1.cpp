#include<fstream>
#include<iostream>
#include<string>
#include<regex>
#include<cmath>

using namespace std;


int main() {
    ifstream data("input.txt");
    int total = 0;
    regex findnum("[-0-9]+");
    const int width = 101;
    const int height = 103;
    int tlquad = 0;
    int trquad = 0;
    int blquad = 0;
    int brquad = 0;

    string line;
    while (getline(data, line)) {
        //cout << 'c' << line << '\n';
        smatch num;
        regex_search(line.cbegin(), line.cend(), num, findnum);
        int posx = stoi(num[0]);
        regex_search(num.suffix().first, line.cend(), num, findnum);
        int posy = stoi(num[0]);
        regex_search(num.suffix().first, line.cend(), num, findnum);
        int vx = width + stoi(num[0]);
        regex_search(num.suffix().first, line.cend(), num, findnum);
        //cout << num[0] << '\n';
        int vy = height + stoi(num[0]);
        int destx = (posx + vx * 100) % width;
        int desty = (posy + vy * 100) % height;
        if (destx < (int)(width) / 2) {
            if (desty < (int)(height) / 2) {
                tlquad++;
            } else if (desty > (int)(height) / 2) {
                blquad++;
            }
        } else if (destx > (int)(width) / 2) {
            if (desty < (int)(height) / 2) {
                trquad++;
            } else if (desty > (int)(height) / 2) {
                brquad++;
            }
        }
    }

    total = tlquad * trquad * blquad * brquad;

    cout << total << '\n';

    return 0;
}
