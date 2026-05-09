using db = double;

struct Point { db x, y; };         // 点
using Vec = Point;                 // 向量
struct Line { Point P; Vec v; };   // 直线
struct Seg { Point A, B; };        // 线段
// Line Seg 传地址可以节省拷贝时间
struct Circle { Point O; db r; };  // 圆

// NOTE: 浮点数比较 记得加eps
const db PI = acos(-1), eps = 1e-9;   
const Point O = {0, 0};                        // 原点
const Line Ox = {O, {1, 0}}, Oy = {O, {0, 1}}; // 坐标轴

bool eq(db a, db b) { return fabs(a - b) < eps; }
Vec operator+(Vec u, Vec v) { return {u.x + v.x, u.y + v.y}; } 
Vec operator-(Vec u, Vec v) { return {u.x - v.x, u.y - v.y}; }  
Vec operator*(db k, Vec v) { return {k * v.x, k * v.y}; }         // 数乘
db dot(Vec u, Vec v) { return u.x * v.x + u.y * v.y; }     // 点乘
db cross(Vec u, Vec v) { return u.x * v.y - u.y * v.x; }   // 叉乘
db len(Vec v) { return sqrt(v.x * v.x + v.y * v.y); }    // 向量长度
Vec r90a(Vec v) { return {-v.y, v.x}; }        // 向量逆时针旋转90度
Vec r90c(Vec v) { return {v.y, -v.x}; }        // 向量顺时针旋转90度


// 两向量的夹角余弦
db cos_t(Vec u, Vec v) { return dot(u, v) / len(u) / len(v); } 
//两向量的夹角正弦
db sin_t(Vec u, Vec v) { return cross(u, v) / len(u) / len(v); } 

通过 acos asin 转弧度制时 c = max(-1.0, min(1.0, c)); // 防止精度误差
// 两向量夹角（弧度，0 到 π） 
db angle(Vec u, Vec v) {
    db c = cos_t(u, v); // 求点与面的夹角 c 要加fabs
    c = max(-1.0, min(1.0, c));
    return acos(c); 
}

// 归一化向量（单位向量）
Vec norm(Vec v) { return {v.x / len(v), v.y / len(v)}; }
// 横坐标大于等于0的归一化向量(单位向量)
Vec pnorm(Vec v) { return (v.x < 0 ? -1 : 1) / len(v) * v; }
// 线段的方向向量   NOTE：直线的方向向量直接访问属性v
Vec dvec(Seg l) { return l.B - l.A; }


Line line(Point A, Point B) { return {A, B - A}; }  // 两点式直线
Line line(db k, db b) { return {{0, b}, {1, k}}; }  // 斜截式直线
Line line(Point P, db k) { return {P, {1, k}}; }  // 点斜式直线
Line line(Seg l) { return {l.A, l.B - l.A}; }  // 线段所在直线

// 给定直线的横坐标求纵坐标   NOTE:请确保直线不与y轴平行
db at_x(Line l, db x) { return l.P.y + (x - l.P.x) * l.v.y / l.v.x; }
// 给定直线的纵坐标求横坐标   NOTE:请确保直线不与x轴平行
db at_y(Line l, db y) { return l.P.x - (y + l.P.y) * l.v.x / l.v.y; }

// 点到直线的垂足
Point pedal(Point P, Line l) { 
	return l.P - dot((l.P - P), l.v) / dot(l.v, l.v) * l.v; 
} 
// 线段中点
Point midp(Seg l) { return {(l.A.x + l.B.x) / 2, (l.A.y + l.B.y) / 2}; }  
Line perp(Seg l) { return {midp(l), r90c(l.B - l.A)}; }  // 线段中垂线
// 过某点作直线的垂线
Line perp(Line l, Point P) { return {P, r90c(l.v)}; }  
Line bisec(Point P, Vec u, Vec v) { 
	return {P, norm(u) + norm(v)}; 
}  // 角平分线


bool verti(Vec u, Vec v) { return eq(dot(u, v), 0); }   // 向量是否垂直
bool paral(Vec u, Vec v) { return eq(cross(u, v), 0); } // 向量是否平行
bool paral_x(Vec v) { return eq(v.y, 0); } // 向量是否与x轴平行
bool paral_y(Vec v) { return eq(v.x, 0); } // 向量是否与y轴平行

// 点是否在直线上
bool on(Point P, Line l) { return eq(cross(P - l.P, l.v), 0); } 
// 点是否在线段上
bool on(Point P, Seg l) { 
    return eq(len(P - l.A) + len(P - l.B), len(l.A - l.B)); 
} 

// 两个点是否重合
bool operator==(Point A, Point B) { 
    return eq(A.x, B.x) && eq(A.y, B.y); 
} 
// 两条直线是否重合
bool operator==(Line a, Line b) { 
    return on(a.P, b) && on(a.P + a.v, b); 
} 
// 两条线段是否重合
bool operator==(Seg a, Seg b) { 
    return (a.A == b.A && a.B == b.B) || (a.A == b.B && a.B == b.A); 
}

// 两条线段是否相交
int intersect(Seg l1, Seg l2) {
    Point A = l1.A, B = l1.B, C = l2.A, D = l2.B;
    db c1 = cross(B - A, C - A), c2 = cross(B - A, D - A);
    db c3 = cross(D - C, A - C), c4 = cross(D - C, B - C);
    // 快速排斥
    if (max(A.x, B.x) < min(C.x, D.x) - eps || 
        max(C.x, D.x) < min(A.x, B.x) - eps ||
        max(A.y, B.y) < min(C.y, D.y) - eps || 
        max(C.y, D.y) < min(A.y, B.y) - eps)  return 0;
    // 规范相交：两条线段互相跨立
    if (c1 * c2 < -eps && c3 * c4 < -eps) return 1;
    // 非规范相交：有端点在线段上
    if ((fabs(c1) < eps && on(C, l1)) || (fabs(c2) < eps && on(D, l1)) ||
        (fabs(c3) < eps && on(A, l2)) || (fabs(c4) < eps && on(B, l2))) return 2;
    return 0; 
}

// 直线与线段是否相交
int intersect(Seg l1, Line l) {
    Point A = l1.A, B = l1.B;
    db c1 = cross(l.v, A - l.P), c2 = cross(l.v, B - l.P);
    if (c1 * c2 > 0) return 0;
    if (c1 * c2 < 0) return 1; // 规范相交
    bool onA = (fabs(c1) < eps), onB = (fabs(c2) < eps);
    if (onA && onB) return 3;  // 整个线段都在直线上
    return 2;  // 只有一个端点在直线上
}

// 直线与圆是否相切
bool tangency(Line l, Circle C) { 
    return eq(abs(cross(C.O - l.P, l.v)), C.r * len(l.v)); 
}  
// 圆与圆是否相切
bool tangency(Circle C1, Circle C2) { 
    return eq(len(C1.O - C2.O), C1.r + C2.r); 
}


// 两点间的欧式距离
db dis(Point A, Point B) { return len(A - B); } 
// 两点间的曼哈顿距离
db manhattan(Point A, Point B) {
    return fabs(A.x - B.x) + fabs(A.y - B.y); 
}
// 两点间的切比雪夫距离
db chebyshev(Point A, Point B) {
    return max(fabs(A.x - B.x), fabs(A.y - B.y)); 
}
// 点到直线的距离
db dis(Point P, Line l) { return abs(cross(P - l.P, l.v)) / len(l.v); } 
// 平行直线间的距离  NOTE: 请确保两直线是平行的
db dis(Line a, Line b) { 
    return abs(cross(a.P, pnorm(a.v)) - cross(b.P, pnorm(b.v))); 
}


// 沿着向量v的方向平移
Line operator+(Line l, Vec v) { return {l.P + v, l.v}; }
Seg operator+(Seg l, Vec v) { return {l.A + v, l.B + v}; }

// 点P绕原点O逆时针旋转rad弧度 (如 90° 写 PI/2)
Point rotate(Point P, db rad) { 
    return {cos(rad) * P.x - sin(rad) * P.y, sin(rad) * P.x + cos(rad) * P.y}; 
}
// 点P绕点C逆时针旋转rad弧度
Point rotate(Point P, db rad, Point C) { 
    return C + rotate(P - C, rad); 
}                    
// 直线l绕点C逆时针旋转rad弧度 (C默认为原点)
Line rotate(Line l, db rad, Point C = O) { 
    return {rotate(l.P, rad, C), rotate(l.v, rad)}; 
}  
// 线段l绕点C逆时针旋转rad弧度 (C默认为原点)
Seg rotate(Seg l, db rad, Point C = O) { 
    return {rotate(l.A, rad, C), rotate(l.B, rad, C)}; 
}


// 关于点对称
Point reflect(Point A, Point P) { 
    return {P.x * 2 - A.x, P.y * 2 - A.y}; 
}
Line reflect(Line l, Point P) { return {reflect(l.P, P), l.v}; }  
Seg reflect(Seg l, Point P) { 
    return {reflect(l.A, P), reflect(l.B, P)}; 
} 

// 关于直线对称 NOTE：向量和点在这里的表现不同，求向量关于某直线的对称向量需要用reflect_v
Point reflect(Point A, Line ax) { return reflect(A, pedal(A, ax)); }    
Vec reflect_v(Vec v, Line ax) { 
    return reflect(v, ax) - reflect(O, ax); 
}   // refl(O + V) - refl(O)    
Line reflect(Line l, Line ax) { 
    return { reflect(l.P, ax), reflect_v(l.v, ax)}; 
} 
Seg reflect(Seg l, Line ax) { 
    return { reflect(l.A, ax), reflect(l.B, ax)}; 
}


// 直线与直线交点
// 克莱姆法则 线性代数法
vector<Point> inter(Line a, Line b) {
    db c = cross(a.v, b.v);
    if (eq(c, 0)) return {};
    Vec v = 1 / c * Vec{cross(a.P, (a.P + a.v)), cross(b.P, (b.P + b.v))};
    return {{dot(v, Vec{-b.v.x, a.v.x}), dot(v, Vec{-b.v.y, a.v.y})}}; 
}
/* 参数方程法
vector<Point> inter(Line a, Line b) {
    db c = cross(a.v, b.v);
    if (eq(c, 0)) return {};
    db t = cross(b.P - a.P, b.v) / c;
    Point P = {a.P.x + t * a.v.x, a.P.y + t * a.v.y};  return {P}; 
} */

// 直线与圆交点
vector<Point> inter(Line l, Circle C) {
    Point P = pedal(C.O, l); 
    db h = len(P - C.O);
    if (h - C.r > eps) return {}; 
    if (eq(h, C.r)) return {P};
    db d = sqrt(C.r * C.r - h * h);
    Vec vec = d / len(l.v) * l.v;
    return {P + vec, P - vec}; 
}

// 圆与圆的交点
vector<Point> inter(Circle C1, Circle C2) {
    Vec v1 = C2.O - C1.O, v2 = r90c(v1);
    db d = len(v1);
    if ((d - (C1.r + C2.r) > eps) || (abs(C1.r - C2.r) - d > eps)) return {};
    if (eq(d, C1.r + C2.r) || eq(d, abs(C1.r - C2.r))) return {C1.O + C1.r / d * v1};
    db a = ((C1.r * C1.r - C2.r * C2.r) / d + d) / 2;
    db h = sqrt(C1.r * C1.r - a * a);
    Vec av = a / len(v1) * v1, hv = h / len(v2) * v2;
    return {C1.O + av + hv, C1.O + av - hv}; 
}


// 三角形的重心
Point barycenter(Point A, Point B, Point C) {  
    return {(A.x + B.x + C.x) / 3, (A.y + B.y + C.y) / 3}; 
}

// 三角形的外心
Point circumcenter(Point A, Point B, Point C) {
    db a = dot(A, A), b = dot(B, B), c = dot(C, C);
    db d = 2 * (A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y));
    if (eq(d, 0)) return {};  
    return 1 / d * r90c(a * (B - C) + b * (C - A) + c * (A - B)); 
}

// 三角形的内心  
Point incenter(Point A, Point B, Point C) {
    db a = len(B - C), b = len(A - C), c = len(A - B);
    db d = a + b + c;  if (eq(d, 0)) return {};
    return 1 / d * (a * A + b * B + c * C); 
}

// 三角形的垂心
Point orthocenter(Point A, Point B, Point C) {
    db n = dot(B, (A - C)), m = dot(A, (B - C));
    db d = cross((B - C), (A - C));  if (eq(d, 0)) return {};
    return 1 / d * r90c(n * (C - B) - m * (C - A)); 
}


// 判断凸多边形
bool isConvex(const vector<Point>& p) {
    int n = p.size();
    if (n < 3) return 0;
    int sign = 0;
    for (int i = 0; i < n; ++i) {
        Point a = p[i], b = p[(i+1) % n], c = p[(i+2) % n];
        db v = cross(b - a, c - b);

        if (fabs(v) > eps) {
            if (sign == 0) sign = v > 0 ? 1 : -1;
            else if (sign * v < 0) return 0;
        }
    }
    return 1; 
}

// 求三角形的面积
db areaTriangle(Point a, Point b, Point c) {
    return fabs(cross(b - a, c - a)) * 0.5;
}

// 求任意多边形的面积
db area(const vector<Point>& p) {
    int n = p.size();
    if (n < 3) return 0.0;  
    db ans = 0;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        ans += cross(p[i], p[j]);
    }
    return fabs(ans) * 0.5; 
}

// 判断点在多边形内部
bool in(const vector<Point>& p, Point A) {
    int cnt = 0, n = p.size();
    for (int i = 0; i < n; ++i) {
        Point a = p[i], b = p[(i + 1) % n];
        Seg l = {a, b};
        if (on(A, l)) return 1;
        if ((a.y > A.y) != (b.y > A.y)) {  
            db x_intersect = a.x + (b.x - a.x) * (A.y - a.y) / (b.y - a.y);
            if (A.x < x_intersect - eps) cnt++;
        }
    }
    return cnt & 1; 
}
      
// 判断线段在任意多边形内部（考不考虑端点接触）
// 如果是凸多边形：只需判断两个端点是否在凸多边形内部即可
bool in(const vector<Point>& p, Seg l) {
    Point A = l.A, B = l.B;
    if (!in(p, A) || !in(p, B)) return 0;

    int n = p.size();
    for (int i = 0; i < n; ++i) {
        Point a = p[i], b = p[(i + 1) % n];
        Seg seg_p = {a, b};
        if (intersect(l, seg_p) == 1) return 0;
    }
    return 1; 
}
