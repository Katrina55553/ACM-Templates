vector<int> sieve(int n) {
    vector<bool> is_p(n + 1, 1);
    is_p[0] = is_p[1] = 0;
    for (int i = 2; i * i <= n; ++i) {
        if (is_p[i]) {
            for (int j = i * i; j <= n; j += i) is_p[j] = 0;
        }
    }
    vector<int> p;
    for (int i = 2; i <= n; ++i) {
        if (is_p[i]) p.push_back(i);
    }
    return p;
}


vector<int> Euler(int n) {
    vector<bool> is_p(n + 1, 1);
    vector<int> p;
    
    for (int i = 2; i <= n; ++i) {
        if (is_p[i]) p.push_back(i);
        for (int x : p) {
            if (1ll * i * x > n) break;
            is_p[i * x] = 0;
            if (i % x == 0) break;
        }
    }
    return p;
}
