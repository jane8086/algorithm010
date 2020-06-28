from typing import List


# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def buildTree(self, preorder: List[int], inorder: List[int]) -> TreeNode:
        if len(preorder) == 0 or len(inorder) == 0:
            return None
        # 前序遍历的定义，找到第一个值为root
        root = TreeNode(preorder[0])
        # 中序遍历的定义， 分割开左子树和右子树
        mid = inorder.index(preorder[0])
        # 左子树
        root.left = self.buildTree(preorder[1: mid+1], inorder[: mid])
        # 右子树
        root.right = self.buildTree(preorder[mid+1:], inorder[mid+1:])

        return root
