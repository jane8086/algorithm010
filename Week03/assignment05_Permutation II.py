from typing import List
from collections import Counter


class Solution:
    def permuteUnique(self, nums: List[int]) -> List[List[int]]:
        res = []
        counter = Counter(nums)
        def backtrack(track, counter):
            if len(track) == len(nums):
                return res.append(track[:])
            for x in counter:
                if counter[x] > 0:
                    track.append(x)
                    counter[x] -= 1
                    backtrack(track, counter)
                    track.pop()
                    counter[x] += 1
        backtrack([], counter)
        return res