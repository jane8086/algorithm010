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
