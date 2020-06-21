from typing import List


class Solution:
    def groupAnagrams(self, strs: List[str]) -> List[List[str]]:
        # sort_strs = [''.join(sorted(s)) for s in strs]
        # print(sort_strs)
        # same_dict = {}
        # for i in range(len(sort_strs)):
        #     if sort_strs[i] in same_dict:
        #         same_dict[sort_strs[i]].append(i)
        #     else:
        #         same_dict[sort_strs[i]]= [i]
        # # print(len(same_dict.values()))
        # res = [[] for _ in range(len(same_dict))]
        # for i, sub_dict in enumerate(same_dict.values()):
        #     for j in sub_dict:
        #         res[i].append(strs[j])
        # return res

        dict = {}
        for item in strs:
            key = tuple(sorted(item))
            dict[key] = dict.get(key, []) + [item]
        return list(dict.values())
