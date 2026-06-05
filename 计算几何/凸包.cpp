struct AndrewResult {
    vector<Point> hi;  // 上凸包
    vector<Point> lo;  // 下凸包
};
AndrewResult Andrew (vector<Point>& p){
    sort(p.begin(), p.end(), [&](Point a, Point b) { 
        return a.x == b.x ? a.y < b.y : a.x < b.x; }); // 重载 operator==
    p.erase(unique(p.begin(), p.end()), p.end());
    int n = p.size();
    
    vector<Point> hi, lo; 
    for (int i = 0; i < n; ++i) {
        while (hi.size() > 1 && 
	    cross(hi.back() - hi[hi.size() - 2], p[i] - hi.back()) >= 0) {
            hi.pop_back();
        }
        while (lo.size() > 1 && 
        cross(lo.back() - lo[lo.size() - 2], p[i] - lo.back()) <= 0) {
            lo.pop_back();
        }
        hi.push_back(p[i]);
        lo.push_back(p[i]);
    }
    return {hi, lo};
    // 也可以返回完整凸包
    vector<Point> hull;
	for (int i = 0; i < lo.size(); ++i) hull.push_back(lo[i]);
	for (int i = hi.size() - 2; i > 0; --i) hull.push_back(hi[i]);
	return hull;
}
