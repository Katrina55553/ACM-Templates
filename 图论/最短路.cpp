vector<vector<ll>> dp(n + 1, vector<ll>(n + 1, INF));
for (int i = 1; i <= n; ++i) dp[i][i] = 0; // 自环
for (int i = 0; i < m; ++i){
	int u, v, w;
	cin >> u >> v >> w;
	dp[u][v] = min(dp[u][v], 1ll * w);
}

for (int k = 1; k <= n; ++k){
	for (int i = 1; i <= n; ++i){
		for (int j = 1; j <= n; ++j){
			dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
		}
	}
}


vector<vector<pair<ll, int>>> g(n + 1);
for (int i = 0; i < m; ++i){
	int u, v, w;
	cin >> u >> v >> w;
	g[u].push_back({w, v});
}

vector<ll> dis(n + 1, INF);
priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
int st = 1;
dis[st] = 0;
pq.push({0, st});

while (!pq.empty()){
	auto [d, u] = pq.top();
	pq.pop();
	
	if (d > dis[u]) continue; // 不显式维护vis -> 通过判断d是否等于dis[u]来决定是否处理

	for (auto [w, v] : g[u]){
		if (dis[v] > dis[u] + w){
			dis[v] = dis[u] + w;
			pq.push({dis[v], v});
		}
	}
}


const int INF = 2e18;
void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> g(n + 1);
    vector<int> deg(n + 1);
    for (int i = 0; i < m; ++i){
        int u, v, w;
        cin >> u >> v >> w;
        g[u].emplace_back(w, v);
        deg[v]++;
    }

    vector<ll> dp(n + 1, -INF);
    dp[1] = 0;
    queue<int> q;
    for (int i = 1; i <= n; ++i){
        if (!deg[i]) q.emplace(i);
    }

    while (!q.empty()){
        int u = q.front(); q.pop();
        for (auto [w, v] : g[u]){
            dp[v] = max(dp[v], dp[u] + w);
            deg[v]--;
            if (!deg[v]) q.emplace(v);
        }
    }
    cout << (dp[n] == -INF ? -1 : dp[n]) << "\n";
}   
