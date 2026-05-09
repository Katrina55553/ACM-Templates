struct ST {
    vector<vector<int>> st; // 从 i 开始 长度为 2^j 的区间的（max， min， gcd， &， |）
    ST(const vector<int>& a){
        int n = a.size() - 1; // 1-based
        st.assign(n + 1, vector<int>(log2(n) + 1));
        for (int i = 1; i <= n; ++i) st[i][0] = a[i];

        for (int j = 1; (1ll << j) <= n; ++j){
            for (int i = 1; i + (1ll << j) - 1 <= n; ++i){
                st[i][j] = max(st[i][j - 1], st[i + (1ll << (j - 1))][j - 1]);
            }
        }
    }

    int query(int l, int r){
        int k = log2(r - l + 1);
        return max(st[l][k], st[r - (1ll << k) + 1][k]);
    }
};


vector<vector<int>> st(n + 1, vector<int>(21)); // u点向上跳1<<i层的祖先节点
vector<int> dep(n + 1);
auto dfs = [&](auto && self, int u, int fa) -> void {
	dep[u] = dep[fa] + 1;
	st[u][0] = fa;
	for (int i = 1; i <= 20; ++i){
		st[u][i] = st[st[u][i - 1]][i - 1];
	}

	for (int v : g[u]){
		if (v == fa) continue;
		self(self, v, u);
	}
};

auto LCA = [&](int u, int v) -> int{
	if (dep[u] < dep[v]) swap(u, v);
	// u跳至与v同一层
	for (int i = 20; i >= 0; --i){
		if (dep[st[u][i]] >= dep[v]) u = st[u][i];
	}
	if (u == v) return v;
	// 一起跳至LCA的下一层
	for (int i = 20; i >= 0; --i){
		if (st[u][i] != st[v][i]) u = st[u][i], v = st[v][i];
	}
	return st[v][0];
};

dfs(dfs, rt, 0);
