// 单点修改 + 区间查询
struct BIT {
    int n;
    vector<ll> f;

    BIT(int size) {
        n = size;
        f.resize(n + 1);
    }
    void update(int i, ll d) {
        while (i <= n) {
            f[i] += d;
            i += i & -i;
        }
    }
    ll query(int i) {
        ll res = 0;
        while (i > 0) {
            res += f[i];
            i -= i & -i;
        }
        return res;
    }
    ll range(int l, int r) {
        if (l > r) return 0;
        return query(r) - query(l - 1);
    }
};


// 区间修改 + 区间查询（差分 + 双树状数组）
BIT t1(n + 1), t2(n + 1);
for (int i = 1; i <= n; ++i){
	t1.update(i, a[i]), t1.update(i + 1, -a[i]);
	t2.update(i, a[i] * (i - 1)), t2.update(i + 1, -a[i] * i);
}

while (m--){
	int op, x, y;
	cin >> op >> x >> y;
	if (op == 1){
		ll k;
		cin >> k;
		t1.update(x, k), t1.update(y + 1, -k);
		t2.update(x, k * (x - 1)), t2.update(y + 1, -k * y);
	}
	else{
		ll ans = t1.query(y) * y - t2.query(y) - (t1.query(x - 1) * (x - 1) - t2.query(x - 1));
		cout << ans << "\n";
	}
}


// 离散化 + 树状数组求逆序对
int n; cin >> n;
vector<int> a(n + 1);
for (int i = 1; i <= n; ++i) cin >> a[i];

vector<int> b = a;
sort(b.begin() + 1, b.end());
b.erase(unique(b.begin() + 1, b.end()), b.end());
int m = (int)b.size();

vector<int> rk(n + 1);
for (int i = 1; i <= n; ++i){
	rk[i] = lower_bound(b.begin() + 1, b.end(), a[i]) - b.begin();
}
BIT t(m);  
ll ans = 0;
for (int i = n; i > 0; --i) {
	ans += t.query(rk[i] - 1);   // 统计小于当前数的个数
	t.update(rk[i], 1);          // 将当前数加入树状数组
}

cout << ans << "\n";

