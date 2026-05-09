ll qpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}


vector<vector<ll>> operator*(const vector<vector<ll>>& a, const vector<vector<ll>>& b) {
    int n = a.size(), m = b[0].size(), p = a[0].size();
    vector<vector<ll>> c(n, vector<ll>(m, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < p; ++k) {
                c[i][j] = (c[i][j] + a[i][k] * b[k][j] % MOD) % MOD;
            }
        }
    }
    return c;
}

vector<vector<ll>> mat_pow(vector<vector<ll>> a, ll k) {
    int n = a.size();
    vector<vector<ll>> res(n, vector<ll>(n, 0));
    for (int i = 0; i < n; ++i) res[i][i] = 1;

    while (k) {
        if (k & 1) res = res * a;
        a = a * a;
        k >>= 1;
    }
    return res;
}
