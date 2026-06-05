struct Trie {
    int idx = 0;
    vector<int> cnt;  // 以节点 i 结尾的字符串个数
    vector<vector<int>> ch;   // 节点 i 沿着 j 这条边走到的子节点

    Trie (int n) {
        cnt.assign(n + 1, 0);
        ch.assign(n + 1, vector<int>(62, 0)); // 26 + 26 + 10 
    }

    int get(char c) {
        if (c >= 'A' && c <= 'Z') return c - 'A';
        else if (c >= 'a' && c <= 'z') return c - 'a' + 26;
        else return c - '0' + 52;
    }

    void insert(const string & s) {
        int i = 0;
        for (char c : s){
            int j = get(c);
            if (!ch[i][j]) ch[i][j] = ++idx;
            i = ch[i][j];
        }
        cnt[i]++;
    }

    int query (const string & s) {
        int i = 0;
        for (char c : s){
            int j = get(c);
            if (!ch[i][j]) return 0;
            i = ch[i][j];
        }
        return cnt[i];
    }
};


struct Trie {
    int idx = 0;
    vector<vector<int>> ch;   

    Trie (int n) {
        ch.assign(31 * (n + 1), vector<int>(2));  
    }

    void insert(int x) {
        int p = 0;
        for (int i = 30; i >= 0; --i) {
            int j = x >> i & 1;
            if (!ch[p][j]) ch[p][j] = ++idx;
            p = ch[p][j];
        }
    }

    int query (int x, int op) {
        int p = 0, res = 0;
        // op = 1, max
        if (op) {
            for (int i = 30; i >= 0; --i) {
                int j = x >> i & 1;
                if (ch[p][!j]) {
                    res += 1 << i;
                    p = ch[p][!j];
                }
                else p = ch[p][j];
            }
        }
        // op = 0, min
        else {
            for (int i = 30; i >= 0; --i) {
                int j = x >> i & 1;
                if (ch[p][j]) p = ch[p][j];
                else {
                    res += 1 << i;
                    p = ch[p][!j];
                }
            }
        }
        return res;
    }
};
