db theta(Vec u) { return atan2(u.y, u.x); }  // 求极角
const Point O = {0, 0};

// 直接排序（每次比较都计算极角）
void psort(vector<Point>& p, Point c = O) {
    sort(p.begin(), p.end(), [&](Point a, Point b) {
        return theta(a - c) < theta(b - c);
    });
}

// 预计算极角，减少常数
void psort2(vector<Point>& p, Point c = O) {
    int n = p.size();
    vector<pair<db, int>> ang(n);
    for (int i = 0; i < n; ++i) {
        ang[i] = {theta(p[i] - c), i};
    }
    sort(ang.begin(), ang.end());
    vector<Point> res(n);
    for (int i = 0; i < n; ++i) {
        res[i] = p[ang[i].second];
    }
    p = move(res);
}
