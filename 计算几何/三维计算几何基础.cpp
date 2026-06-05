struct Point { db x, y, z; };
using Vec = Point;

Vec operator+(Point a, Point b) { 
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}
Vec operator-(Point a, Point b) { 
    return {a.x - b.x, a.y - b.y, a.z - b.z};
}
Vec operator*(Point a, db k) { 
    return {a.x * k, a.y * k, a.z * k};
}

db dot(Point a, Point b) { 
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
Vec cross(Point a, Point b) {
    return {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}
db len(Vec v) { 
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z); 
}
// 归一化向量（单位向量）
Vec norm(Vec v) { 
    db l = len(v);
    return {v.x / l, v.y / l, v.z / l};
}
