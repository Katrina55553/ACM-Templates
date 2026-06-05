// 滑动窗口最大值
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

// 滑动窗口最小值
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


// 单调栈 -- 找每个元素右边第一个比它大的元素的下标 (1-based)
stack<int> stk;   // 存储下标
for (int i = 0; i < n; ++i) {
    int cur = a[i];
    while (!stk.empty() && cur > a[stk.top()]) {
        int idx = stk.top();
        stk.pop();
        ans[idx] = i + 1;
    }
    stk.push(i);
}
