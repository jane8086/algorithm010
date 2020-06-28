# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def lowestCommonAncestor(self, root: 'TreeNode', p: 'TreeNode', q: 'TreeNode') -> 'TreeNode':
        # terminator
        # 当越过叶子节点，直接返回null
        # 或者当root == p or root == q 时，返回root的值
        if not root or root == p or root == q:
            return root

        # drill down
        left = self.lowestCommonAncestor(root.left, p, q)
        right = self.lowestCommonAncestor(root.right, p, q)

        # process
        # 如果既不在左子树中也不在右子树中， 那么返回None
        if not left and not right:
            return None
        # 这个右子树储存的是q的值，或者root的值
        if not left:
            return right
        if not right:
            return left
        # 如果left和right都有值，说明这个时候的根是最近公共祖先
        return root
