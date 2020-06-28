from typing import List


class Solution:
    def combine(self, n: int, k: int) -> List[List[int]]:
        res = []
        def backtrack(start=1, curr=[]):
            if n <= 0 or k <= 0 or n < k:
                return res
            # 满足输出条件，剪枝
            if len(curr) == k:
                return res.append(curr[:])
            for i in range(start, n+1):
                curr.append(i)
                backtrack(i+1, curr)
                curr.pop()
        backtrack()
        return res