from typing import List
import collections
import heapq as h


class Solution:
    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        # 使用内置函数collections.Counter
        return [item for item, _ in collections.Counter(nums).most_common(k)]

        # # 使用table记录频率，使用堆pop最大频率对应的数值
        # d = collections.Counter(nums)
        # heap = [(-val, key) for key, val in d.items()]
        # h.heapify(heap)
        # # print(heap)
        # return [h.heappop(heap)[1] for _ in range(k)]