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

vector<ll> f(m + 1);
auto add = [&](int i, ll d) -> void{
	while (i <= n){
		f[i] += d;
		i += i & -i;
	}
};

auto query = [&](int i) -> ll{
	ll s = 0;
	while (i){
		s += f[i];
		i -= i & -i;
	}
	return s;
};

ll ans = 0;
for (int i = n; i > 0; --i){
	ans += query(rk[i] - 1);
	add(rk[i], 1);  
}
cout << ans << "\n";
}   
