#include <bits/stdc++.h>
using namespace std;

int main() {
    system("g++ -std=c++17 gen.cpp -o gen.exe");
    system("g++ -std=c++17 brute.cpp -o brute.exe");
    system("g++ -std=c++17 std.cpp -o std.exe");
    while (1) {
        system("gen.exe > data.txt");
        system("brute.exe < data.txt > brute.txt");
        int st = clock();
        system("std.exe < data.txt > std.txt");
        int ed = clock();
        cout << "std " << ed - st << "ms\n";
        int d = system("fc /n brute.txt std.txt > nul");
        if (d) {
            cout << "WA" << endl;
            system("type data.txt");
            system("type brute.txt");
            system("type std.txt");
            break;
        }
        else cout << "AC" << endl;
    }
    return 0;
}
/* Linux
int main() {
    system("g++ -std=c++17 gen.cpp -o gen");
    system("g++ -std=c++17 brute.cpp -o brute");
    system("g++ -std=c++17 std.cpp -o std");

    while (1) {
        system("./gen > data.txt");
        system("./brute < data.txt > brute.txt");
        system("./std < data.txt > std.txt");

        int d = system("diff -q brute.txt std.txt > /dev/null");
        if (d) {
            cout << "WA" << endl;
            system("cat data.txt");
            system("cat brute.txt");
            system("cat std.txt");
            break;
        } else cout << "AC" << endl;
    }
    return 0;
}
*/