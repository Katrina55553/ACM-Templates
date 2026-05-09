struct DSU {
    vector<int> fa;
    DSU (int n) {
        fa.resize(n);
        for (int i = 0; i < n; ++i) fa[i] = i;
    }

    int find (int x) {
        if (fa[x] != x) fa[x] = find(fa[x]);
        return fa[x];
    }

    void unite(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry) return;
        fa[rx] = ry;
    }
};
void solve() {  
    int n, m; cin >> n >> m;
    vector<array<int, 3>> e(m);
    for (int i = 0; i < m; ++i) {
        int u, v, w; cin >> u >> v >> w;
        e[i] = {w, u, v};
    }
    sort(e.begin(), e.end());
    DSU t(n + 1);
    int ans = 0, cnt = 0;
    for (int i = 0; i < m; ++i) {
        auto [w, u, v] = e[i];
        if (t.find(u) == t.find(v)) continue;
        t.unite(u, v);
        ans += w;
        cnt++;
    }
    if (cnt == n - 1) cout << ans << "\n";
    else cout << "orz\n"; // 不连通
}   


const int INF = 2e9;
void solve() {  
    int n, m; cin >> n >> m;
    vector<vector<pair<int, int>>> g(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v, w; cin >> u >> v >> w;
        g[u].push_back({w, v});
        g[v].push_back({w, u});
    }
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> dis(n + 1, INF), vis(n + 1);
    dis[1] = 0; pq.push({0, 1});
    int ans = 0, cnt = 0;
    while (pq.size() && cnt < n) {
        auto [d, u] = pq.top(); pq.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        ans += d; cnt++;
        for (auto [w, v] : g[u]) {
            if (vis[v]) continue;
            if (w < dis[v]) {
                dis[v] = w;
                pq.push({w, v});
            }
        }
    }
    if (cnt == n) cout << ans << "\n";
    else cout << "orz\n"; // 不连通
}   
