from typing import List

class Solution:
    def moveZeroes(self, nums: List[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """

        # 统计0的个数，添在数组后面
        # unzero_counter = 0
        # for j in range(len(nums)):
        #     if nums[j] != 0:
        #         nums[unzero_counter] = nums[j]
        #         unzero_counter += 1
        # zero_counter = len(nums)-unzero_counter
        # nums[unzero_counter:] = [0] * (zero_counter)

        # 双下标
        # unzero_counter = 0
        # for i in range(len(nums)):
        #     if nums[i] != 0:
        #         nums[unzero_counter] = nums[i]
        #         if i != unzero_counter:
        #             nums[i] = 0
        #         unzero_counter += 1

        # 交换位置
        j = 0
        for i in range(len(nums)):
            if nums[i] != 0:
                nums[j], nums[i] = nums[i], nums[j]
                j += 1

        return nums