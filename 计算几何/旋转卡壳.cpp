db areaTriangle2(Point a, Point b, Point c) { // 四边形面积
    return fabs(cross(b - a, c - a));
}

db get_longest(const vector<Point>& p) {
    int n = p.size();  
    if (n < 2) return 0;
    if (n == 2) return dis(p[0], p[1]);
    
    int j = 1;
    db ans = 0;
    for (int i = 0; i < n; ++i) {
        int ni = (i + 1) % n;  
        while (areaTriangle2(p[i], p[ni], p[(j + 1) % n]) > areaTriangle2(p[i], p[ni], p[j]) + eps) {
            j = (j + 1) % n;
        }
        ans = max({ans, dis(p[i], p[j]), dis(p[ni], p[j])});
    }
    return ans;
}


void minRectangleCover(const vector<Point> &p) {
    int n = p.size();
    db ans = 1e10;
    Point res[4]; // 四个顶点（逆时针：左下→右下→右上→左上）

    int j = 1, l = 1, r = 1; // j:对面最远, l:左投影最小, r:右投影最大
    {
        int i = 0, ni = 1;
        Vec u = (p[ni] - p[i]) * (1.0 / (len(p[ni] - p[i])));
        db dotmin = 1e10, dotmax = -1e10;
        for (int k = 0; k < n; ++k) {
            db t = dot(p[k] - p[i], u);
            if (t < dotmin - eps) {
                dotmin = t;
                l = k;
            }
            if (t > dotmax + eps) {
                dotmax = t;
                r = k;
            }
        }   
    }

    for (int i = 0; i < n; ++i) {
        int ni = (i + 1) % n;
        Vec u = (p[ni] - p[i]) * (1.0 / (len(p[ni] - p[i]))); // i->i+1的单位向量
        Vec u_r90 = {-u.y, u.x}; // 逆时针转90°
        while (areaTriangle2(p[i], p[ni], p[(j + 1) % n]) > areaTriangle2(p[i], p[ni], p[j]) + eps) j = (j + 1) % n;
        while (dot(p[(l + 1) % n] - p[i], u) < dot(p[l] - p[i], u) - eps) l = (l + 1) % n;
        while (dot(p[(r + 1) % n] - p[i], u) > dot(p[r] - p[i], u) + eps) r = (r + 1) % n;
        db h = areaTriangle2(p[i], p[ni], p[j] ) / len(p[ni] - p[i]);
        db w = dot(p[r] - p[i], u) - dot(p[l] - p[i], u);
        db cur = h * w;
        
        if (cur < ans) {
            ans = cur;
            res[0] = p[i] + u * dot(p[l] - p[i], u);
            res[1] = p[i] + u * dot(p[r] - p[i], u);
            res[2] = res[1] + u_r90 * h;
            res[3] = res[0] + u_r90 * h;
        }
    }
    cout << ans << "\n";
    for (int i = 0; i < 4; ++i) {
        cout << res[i].x << ' ' << res[i].y << "\n";
    }
}   
