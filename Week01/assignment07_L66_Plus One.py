from typing import List
class Solution:
    def plusOne(self, digits: List[int]) -> List[int]:

        # # string 解法
        # str_digits = [str(i) for i in digits]
        # new_digits = int("".join(str_digits))
        # new_digits += 1
        # res = [int(j) for j in str(new_digits)]
        # return res

        # recursion
        if digits == []:
            return [1]
        elif digits[-1] < 9:
            return digits[:-1]+[digits[-1]+1]
        else:
            return self.plusOne(digits[:-1])+[0]