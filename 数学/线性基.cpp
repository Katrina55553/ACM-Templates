ll p[64];
void insert(ll x) {
    for (int i = 63; i >= 0; --i) {
        if (x >> i & 1) {
            if (p[i]) x ^= p[i];
            else {
                p[i] = x;
                break;
            }
        }
    }
}


bool check(ll x) {
    for (int i = 63; i >= 0; --i) {
        if (x >> i & 1) x ^= p[i];
    }
    return x == 0;
}


ll getmx() {
    ll ans = 0;
    for(int i = 63; i >= 0; --i) ans = max(ans, ans ^ p[i]);
    return ans;
}


ll kth(ll k) { // 第 k 小 (注意特判：有0要k--）
    if (k == 1 && cnt < n) return 0;

    if (cnt < n) k--; // n 表示序列长度
    if (k >= (1ll << cnt)) return -1;

    ll tmp[64];
    memcpy(tmp, p, sizeof(p)); // 多测不要修改原 p

    int rk = 0;
    for (int i = 0; i <= 63; ++i) {
        for (int j = 0; j < i; ++j) {
            if (tmp[i] >> j & 1) tmp[i] ^= tmp[j];
        }
    }
    vector<ll> d;
    for (int i = 0; i <= 63; ++i) {
        if (tmp[i]) d.push_back(tmp[i]);
    }

    ll ans = 0;
    for (int i = 0; i < d.size(); ++i) {
        if (k >> i & 1) ans ^= d[i];
    }               
    return ans;
}
