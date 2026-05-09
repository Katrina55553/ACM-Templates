#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// long long ? mt19937_64 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rd(int l, int r) { return uniform_int_distribution<int>(l, r)(rng); }

const int max_n = 100, max_v = 1e9;
int main() {
    int n = max_n; cout << n << endl;
    for (int i = 1; i <= n; ++i) cout << rd(1, max_v) << " \n"[i == n];
    return 0;
}
