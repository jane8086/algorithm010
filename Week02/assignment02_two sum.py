from typing import List


class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        dict = {}
        for i, n in enumerate(nums):
            m = target - n
            if m in dict:
                return [i, dict[m]]
            else:
                dict[n] = i