// 组合数 C(n, m)
ll  C(ll n, ll m) {
    if (m < 0 || m > n) return 0;
    ll p = 1, q = 1;
    for (int i = 1; i <= m; i++) {
        p = p * (n - i + 1) % MOD;
        q = q * i % MOD;
    }
    return p * qpow(q, MOD - 2, MOD) % MOD;
}

// 排列数 A(n, m)
ll A(ll n, ll m) {
    if (m < 0 || m > n) return 0;
    ll p = 1;
    for (int i = 1; i <= m; i++) {
        p = p * (n - i + 1) % MOD;
    }
    return p;
}


const int MOD = 998244353;
ll qpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

const int N = 1e6;
vector<ll> f(N + 1), i_f(N + 1);
void init() {
	f[0] = 1;
	for (int i = 1; i <= N; ++i) f[i] = f[i - 1] * i % MOD;
	i_f[N] = qpow(f[N], MOD - 2);
	for (int i = N; i; --i) i_f[i - 1] = i_f[i] * i % MOD;
}

ll C(int n, int k) {
    if (k > n || k < 0) return 0;
    return f[n] * i_f[k] % MOD * i_f[n - k] % MOD;
}
ll A(int n, int k) {
    if (k > n || k < 0) return 0;
    return f[n] * i_f[n - k] % MOD;
}
