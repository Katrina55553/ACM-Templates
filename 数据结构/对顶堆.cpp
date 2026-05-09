priority_queue<int> L;                              // 大根堆，存较小的 k 个数
priority_queue<int, vector<int>, greater<int>> R;   // 小根堆，存较大的数

for (int i = 0; i < n; i++) {
    int x = a[i];
    
    // 插入元素
    if (L.empty() || x <= L.top()) L.push(x);
    else R.push(x);
    
    // 保持 L 的大小为 k
    while (L.size() > k) {
        R.push(L.top());
        L.pop();
    }
    while (L.size() < k && !R.empty()) {
        L.push(R.top());
        R.pop();
    }
}
// 第 k 小的数就是 L.top()
int kth_smallest = L.top();
