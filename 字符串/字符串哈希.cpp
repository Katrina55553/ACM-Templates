const int N = 1e6 + 5, base = 131;
ull h[N], p[N];
ull get(int l, int r) {
    return h[r] - h[l - 1] * p[r - l + 1];
}

h[0] = 0, p[0] = 1;
for (int i = 1; i <= n; ++i) {
	p[i] = p[i - 1] * base;
	h[i] = h[i - 1] * base + s[i];
}
