deque<int> q;  // 存储下标，从大到小
vector<int> ans;
for (int i = 0; i < a.size(); ++i) {
    // 进
    while (!q.empty() && a[i] >= a[q.back()]) q.pop_back();
    q.push_back(i);
    // 出
    if (i - q.front() >= k) q.pop_front();
    // 更新
    if (i >= k - 1) ans.push_back(a[q.front()]);
}

deque<int> q;  // 存储下标，从小到大
vector<int> ans;
for (int i = 0; i < a.size(); ++i) {
    // 进
    while (!q.empty() && a[i] <= a[q.back()]) q.pop_back();
    q.push_back(i);
    // 出
    if (i - q.front() >= k) q.pop_front();
    // 更新
    if (i >= k - 1) ans.push_back(a[q.front()]);
}


stack<int> stk;
for (int i = 0; i < n; ++i) {
    int cur = a[i];
    while (!stk.empty() && cur > a[stk.top()]) {
        int idx = stk.top();
        stk.pop();
        ans[idx] = i + 1;
    }
    stk.push(i);
}
