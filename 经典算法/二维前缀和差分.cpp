// 构建二维前缀和
vector<vector<int>> dp(n + 1, vector<int>(m + 1));
for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
        // 注意原数组 g 是 0-based ，所以用 g[i-1][j-1]
        dp[i][j] = dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1] + g[i - 1][j - 1];
        // 当前格子 = 上方 + 左方 - 左上角 + 原数组当前值
    }
}
// 计算子矩阵 (x1, y1) 到 (x2, y2) 的和（dp数组是1-based）
auto cal = [&](int x1, int y1, int x2, int y2) {
    return dp[x2][y2] - dp[x1 - 1][y2] - dp[x2][y1 - 1] + dp[x1 - 1][y1 - 1];
};


// 二维差分添加操作：在子矩阵 (x1,y1) 到 (x2,y2) 上全部加 v
void add(int x1, int y1, int x2, int y2, int v) {
    d[x1][y1] += v;
    d[x1][y2 + 1] -= v;
    d[x2 + 1][y1] -= v;
    d[x2 + 1][y2 + 1] += v;
}

// 创建二维差分数组，大小为 (n+2) x (m+2)
vector<vector<int>> d(n + 2, vector<int>(m + 2));

// 从原矩阵 g 构建差分数组（g 是 1-indexed）
for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
        // 差分公式：d[i][j] = g[i][j] - g[i-1][j] - g[i][j-1] + g[i-1][j-1]
        d[i][j] = g[i][j] - g[i - 1][j] - g[i][j - 1] + g[i - 1][j - 1];
    }
}

// 对差分数组做二维前缀和，还原出原矩阵（覆盖回 g）
for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
        // 前缀和公式：g[i][j] = g[i-1][j] + g[i][j-1] - g[i-1][j-1] + d[i][j]
        g[i][j] = g[i - 1][j] + g[i][j - 1] - g[i - 1][j - 1] + d[i][j];
    }
}
