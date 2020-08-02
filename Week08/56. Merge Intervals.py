from typing import List


class Solution:
    def merge(self, intervals: List[List[int]]) -> List[List[int]]:
        if len(intervals) <= 1:
            return intervals
        intervals = sorted(intervals, key = lambda l: l[0])
        # print(intervals)
        merged = [intervals[0]]
        # print(merged)
        for cur_interval in intervals[1:]:
            if cur_interval[0] <= merged[-1][1]:
                cur_right = max(merged[-1][1], cur_interval[1])
                merged[-1] = [merged[-1][0], cur_right]
            else:
                merged.append(cur_interval)
        return merged