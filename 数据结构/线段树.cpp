struct SegmentTree {
    int n;
    vector<ll> a, sum, add, mul;
    SegmentTree(int _n) : n(_n) {
        a.assign(n + 1, 0);
        sum.assign(n << 2 | 1, 0);
        add.assign(n << 2 | 1, 0);
        mul.assign(n << 2 | 1, 1); 
    }

    void init(vector<ll> &arr) {
        for (int i = 1; i <= n; ++i) a[i] = arr[i] % MOD;
        build(1, n, 1);
    }

    void up(int i) {
        sum[i] = (sum[i << 1] + sum[i << 1 | 1]) % MOD;
    }

    void build(int l, int r, int i) {
        if (l == r) {
            sum[i] = a[l] % MOD;
            return;
        }
        int mid = l + r >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        up(i);
    }

    void point_add(int i, ll add_val, int len) {
        sum[i] = (sum[i] + add_val * len) % MOD;
        add[i] = (add[i] + add_val) % MOD;
    }

    void point_mul(int i, ll mul_val) {
        sum[i] = sum[i] * mul_val % MOD;
        mul[i] = mul[i] * mul_val % MOD;
        add[i] = add[i] * mul_val % MOD; 
    }

    void down(int i, int ln, int rn) { 
        if (mul[i] != 1) {
            point_mul(i << 1, mul[i]);
            point_mul(i << 1 | 1, mul[i]);
            mul[i] = 1;
        }
        
        if (add[i] != 0) {
            point_add(i << 1, add[i], ln);
            point_add(i << 1 | 1, add[i], rn);
            add[i] = 0;
        }
    }

    void range_add(int x, int y, ll v, int l, int r, int i) {
        if (x <= l && r <= y) {
            point_add(i, v, r - l + 1);
            return;
        }
        int mid = l + r >> 1;
        down(i, mid - l + 1, r - mid);
        if (x <= mid) range_add(x, y, v, l, mid, i << 1);
        if (y > mid)  range_add(x, y, v, mid + 1, r, i << 1 | 1);
        up(i);
    }

    void range_mul(int x, int y, ll v, int l, int r, int i) {
        if (x <= l && r <= y) {
            point_mul(i, v);
            return;
        }
        int mid = l + r >> 1;
        down(i, mid - l + 1, r - mid);
        if (x <= mid) range_mul(x, y, v, l, mid, i << 1);
        if (y > mid)  range_mul(x, y, v, mid + 1, r, i << 1 | 1);
        up(i);
    }

    ll range_sum(int x, int y, int l, int r, int i) {
        if (x <= l && r <= y) return sum[i];
        int mid = l + r >> 1;
        down(i, mid - l + 1, r - mid);
        ll ans = 0;
        if (x <= mid) ans = (ans + range_sum(x, y, l, mid, i << 1)) % MOD;
        if (y > mid)  ans = (ans + range_sum(x, y, mid + 1, r, i << 1 | 1)) % MOD;
        return ans;
    }
};
