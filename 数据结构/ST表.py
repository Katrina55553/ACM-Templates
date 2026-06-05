class ST:
    def __init__(self, a, n):
        """
        a: 1-indexed 的数组
        """
        self.n = n
        self.m = n.bit_length()
        self.st = [[0] * self.m for _ in range(n + 1)]
        
        # 初始化长度为 1 的区间
        for i in range(1, n + 1):
            self.st[i][0] = a[i]
        
        # 构建 ST 表
        for j in range(1, self.m):
            for i in range(1, n - (1 << j) + 2):
                self.st[i][j] = max(self.st[i][j - 1], self.st[i + (1 << (j - 1))][j - 1])
    
    def query(self, l, r):
        """查询区间 [l, r] 的最大值"""
        k = (r - l + 1).bit_length() - 1
        return max(self.st[l][k], self.st[r - (1 << k) + 1][k])