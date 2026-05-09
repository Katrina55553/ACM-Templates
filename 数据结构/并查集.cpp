struct DSU {
    vector<int> fa;
    // vector<int> rk;
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
    /*
    按秩合并
    void unite(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry) return;

        if (rk[rx] < rk[ry]) fa[rx] = ry;
        else if (rk[rx] > rk[ry]) fa[ry] = rx;
        else {
            fa[ry] = rx;
            rk[rx]++;
        }
    }
    */
};
