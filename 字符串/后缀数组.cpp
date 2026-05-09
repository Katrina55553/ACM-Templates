struct SA {
	// 1-based
    int n, m;
    string s;
    vector<int> sa, rk, oldrk, id, cnt, ht;
    SA(string _s) : s(_s) {
        n = s.size();
        sa.resize(n + 5);
        rk.resize(n * 2 + 5);
        oldrk.resize(n * 2 + 5);
        id.resize(n + 5);
        cnt.resize(max(256, n + 5));
        ht.resize(n + 5);
        init();
        // sa[i]: 排名第i的后缀起始位置
	    // rk[i]: 起始于i的后缀的排名
	    // oldrk[i]: 上一轮的rk数组，用于比较两个子串是否相等
	    // id[i]: 临时数组，用于存储按第二关键字排序后的下标
	    // cnt[i]: 计数数组，用于基数排序
	    // ht[i]: 高度数组，ht[i] = lcp(sa[i], sa[i-1])，即相邻后缀的最长公共前缀
    }
    
    void init() {
        s = ' ' + s;
        m = 128;
        for (int i = 1; i <= n; i++) cnt[rk[i] = s[i]]++;
        for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
        for (int i = n; i >= 1; i--) sa[cnt[rk[i]]--] = i;
        // 倍增法构建后缀数组
        for (int w = 1; ; w <<= 1, m = cnt[n]) {
            int cur = 0;
            for (int i = n - w + 1; i <= n; i++) id[++cur] = i;
            for (int i = 1; i <= n; i++) {
                if (sa[i] > w) id[++cur] = sa[i] - w;
            }
            
            fill(cnt.begin(), cnt.begin() + m + 1, 0);
            for (int i = 1; i <= n; i++) cnt[rk[i]]++;
            for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
            for (int i = n; i >= 1; i--) sa[cnt[rk[id[i]]]--] = id[i];
            
            copy(rk.begin(), rk.end(), oldrk.begin());
            cur = 0;
            for (int i = 1; i <= n; i++) {
                if (oldrk[sa[i]] == oldrk[sa[i - 1]] && 
                    oldrk[sa[i] + w] == oldrk[sa[i - 1] + w]) {
                    rk[sa[i]] = cur;
                } else {
                    rk[sa[i]] = ++cur;
                }
            }
            if (cur == n) {
                for (int i = 1; i <= n; i++) sa[rk[i]] = i;
                break;
            }
        }
        // 构建高度数组 ht
        int k = 0;
        for (int i = 1; i <= n; i++) {
            if (rk[i] == 1) {
                k = 0;
                continue;
            }
            if (k) k--;
            int j = sa[rk[i] - 1];
            while (i + k <= n && j + k <= n && s[i + k] == s[j + k]) k++;
            ht[rk[i]] = k;
        }
    }
    /*
    // 使用RMQ查询任意两个后缀的LCP
    int LCP(int i, int j) {
        if (i == j) return n - i + 1;
        i = rk[i], j = rk[j];
        if (i > j) swap(i, j);

        int l = i + 1, r = j;
        RMQ();
        int k = __lg(r - l + 1);
        return min(st[k][l], st[k][r - (1 << k) + 1]);
    }
    */
};
