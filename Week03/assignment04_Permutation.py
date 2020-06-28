from typing import List


class Solution:
    def permute(self, nums: List[int]) -> List[List[int]]:
        track = []
        res = []
        def backtrack(track, nums):
            if len(track) == len(nums):
                return res.append(track[:])

            for i in range(len(nums)):
                if nums[i] in track:
                    continue

                track.append(nums[i])
                backtrack(track, nums)
                track.pop()
        backtrack(track, nums)
        return res