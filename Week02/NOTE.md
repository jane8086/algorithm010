# 学习笔记
+ Binary Tree Traversal
 ```python
class root:
    def __init__(self, val, left = None, right = None):
        root.val = val
        root.left = left
        root.right = right

def preorder(root):
  if root:
      print(root.val)
      preorder(root.left) 
      preorder(root.right) 

def inorder(root):
    if root:
        inorder(root.left)
        print(root.val)
        inorder(root.right)

def postorder(root):
    if root:
        postorder(root.left)
        postorder(root.right)
        print(root.val)        
```

+ N-ary Tree Traversal
```python
class node:
    def __init__(self, val, children = None):
        node.val = val
        node.children = children

def preorder(node):
    if node:
        print(node.val)
        for child in node.children:
            preorder(child)

def postorder(node):
    if node:
        for child in node.children:
            postorder(child)
        print(node.val)
```

+ Heap
    + 堆可以看作是一个API, heap[0] 可以返回这个堆的最大值或者是最小值
    + python 中的堆默认为是小顶堆 
    + [python heapq 的源码](https://docs.python.org/3/library/heapq.html)
```python
import heapq as h

# 初始化一个list作为堆
heap = []

nums = [3, -5, 9, 2, 1, 0, 6, 8]
# 堆的填入操作
# 可以往堆里填入一个tuple， 堆栈时按照tuple的第一个值的大小为准 
for i in range(len(nums)):
    h.heappush(heap,(nums[i], i))

# 如果想把这个堆改造成大顶堆的话， 把nums的值取负即可
for i in range(len(nums)):
    h.heappush(heap,(-nums[i], i))

# 堆的弹出操作, 弹出堆顶的值
x, idx = h.heappop(heap)
# 添加回堆
h.heappush(heap, (x, idx))

# 把一个list变成堆
heap = nums
h.heapify(heap)

```
哈希表（字典）、映射、集合 有关题：

|分类|题目|
|:------:|:------:|
|字典|[LC 242 有效字母异位词](https://leetcode-cn.com/problems/valid-anagram/description/)|
|字典|[LC 49 字母异位词分组](https://leetcode-cn.com/problems/group-anagrams/)|
|字典|[LC 1 两数之和](https://leetcode-cn.com/problems/two-sum/description/)|

树、二叉树、[二叉搜索树](https://visualgo.net/zh/bst?slide=1) 有关题：

|分类|题目|
|:------:|:------:|
|二叉树遍历|[LC94 二叉树的中序遍历](https://leetcode-cn.com/problems/binary-tree-inorder-traversal/)|
|二叉树遍历|[LC144 二叉树的前序遍历](https://leetcode-cn.com/problems/binary-tree-preorder-traversal/)|
|N叉树遍历|[LC590 N叉树的后序遍历](https://leetcode-cn.com/problems/n-ary-tree-postorder-traversal/)|
|N叉树遍历|[LC589 N叉树的前序遍历](https://leetcode-cn.com/problems/n-ary-tree-preorder-traversal/description/)|
|N叉树遍历|[LC429 N叉树的层序遍历](https://leetcode-cn.com/problems/n-ary-tree-level-order-traversal/)|

堆、二叉堆、图 相关题：

|分类|题目|
|:------:|:------:|
|堆|[剑指 Offer 40. 最小的k个数](https://leetcode-cn.com/problems/zui-xiao-de-kge-shu-lcof/)|
|堆|[239. 滑动窗口最大值](https://leetcode-cn.com/problems/sliding-window-maximum/)|
|堆|[剑指 Offer 49. 丑数](https://leetcode-cn.com/problems/chou-shu-lcof/)|
|堆|[347. 前 K 个高频元素](https://leetcode-cn.com/problems/top-k-frequent-elements/)|
|源码实现，堆|[HeapSort](https://www.geeksforgeeks.org/heap-sort/)|
|图|[连通图个数](https://leetcode-cn.com/problems/number-of-islands/)|
|图|[拓扑排序 (Topological Sorting)](https://zhuanlan.zhihu.com/p/34871092)|
|图|[最短路径（Shortest Path）：Dijkstra](https://www.bilibili.com/video/av25829980?from=search&seid=13391343514095937158)|
|图|[最小生成树 (Minimum Spanning Tree)](https://www.bilibili.com/video/av84820276?from=search&seid=17476598104352152051)|
