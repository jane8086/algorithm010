from typing import List


# Definition for a Node.
class Node:
    def __init__(self, val=None, children=None):
        self.val = val
        self.children = children


class Solution:
    def levelOrder(self, root: 'Node') -> List[List[int]]:
        # recursion
        def traverse_node(node, level):
            if len(res) == level:
                res.append([])
            res[level].append(node.val)
            print(f'on level{level}, child val is{node.val}, res is{res}')
            for child in node.children:
                print(f'loop: level{level}')
                traverse_node(child, level + 1)

        res = []
        if root:
            traverse_node(root, 0)
        return res