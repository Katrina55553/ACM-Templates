while (r - l > eps) {
    db lmid = l + (r - l) / 3.0;
    db rmid = r - (r - l) / 3.0;
    if (f(lmid) > f(rmid)) l = lmid; // 凹函数反过来 l = lmid + 1
    else r = rmid;
}
db ans = f((l + r) * 0.5);


while (l < r) {
    int lmid = l + (r - l) / 3;
    int rmid = r - (r - l) / 3;
    if (f(lmid) >= f(rmid)) r = rmid - 1; // 凹函数反过来 l = lmid + 1
    else l = lmid + 1;
}
for (int k = l; k <= r; k++) ans = max(ans, f(k));
