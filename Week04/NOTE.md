# 学习笔记
## 深度优先算法
```python
visited = set() 
def dfs(node, visited):
    if node in visited: # terminator
    	# already visited 
    	return 
	visited.add(node) 
	# process current node here. 
	...
	for next_node in node.children(): 
		if next_node not in visited: 
			dfs(next_node, visited)
```
```python
def DFS(self, tree): 
	if tree.root is None: 
		return [] 
	visited, stack = [], [tree.root]
	while stack: 
		node = stack.pop() 
		visited.add(node)
		process (node) 
		nodes = generate_related_nodes(node) 
		stack.push(nodes) 
	# other processing work 
	...
```
## 广度优先算法
```python
def BFS(graph, start, end):
    visited = set()
	queue = [] 
	queue.append([start]) 
	while queue: 
		node = queue.pop() 
		visited.add(node)
		process(node) 
		nodes = generate_related_nodes(node) 
		queue.push(nodes)
	# other processing work 
	...
```
## 二分查找
```python
left, right = 0, len(array) - 1 
while left <= right: 
	  mid = (left + right) / 2 
	  if array[mid] == target: 
		    # find the target!! 
		    break or return result 
	  elif array[mid] < target: 
		    left = mid + 1 
	  else: 
		    right = mid - 1
```

深度优先搜索、广度优先搜索 相关题：

|分类|题目|
|:------:|:------:|
|BFS|[102. 二叉树的层序遍历](https://leetcode-cn.com/problems/binary-tree-level-order-traversal/#/description)|
|DFS|[433. 最小基因变化](https://leetcode-cn.com/problems/minimum-genetic-mutation/#/description)|
|DFS|[22. 括号生成](https://leetcode-cn.com/problems/generate-parentheses/#/description)|
|BFS|[515. 在每个树行中找最大值](https://leetcode-cn.com/problems/find-largest-value-in-each-tree-row/#/description)|
|BFS|[127. 单词接龙](https://leetcode-cn.com/problems/word-ladder/)|
|BFS|[126. 单词接龙 II](https://leetcode-cn.com/problems/word-ladder-ii/description/)|
|DFS|[200. 岛屿数量](https://leetcode-cn.com/problems/number-of-islands/)|
|DFS|[529. 扫雷游戏](https://leetcode-cn.com/problems/minesweeper/description/)|

贪心算法 相关题：

|分类|题目|
|:------:|:------:|
|贪心|[322. 零钱兑换](https://leetcode-cn.com/problems/coin-change/)|
|贪心|[860. 柠檬水找零](https://leetcode-cn.com/problems/lemonade-change/description/)|
|贪心|[122. 买卖股票的最佳时机 II](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-ii/description/)|
|贪心|[455. 分发饼干](https://leetcode-cn.com/problems/assign-cookies/)|
|贪心|[874. 模拟行走机器人](https://leetcode-cn.com/problems/walking-robot-simulation/description/)|
|贪心|[55. 跳跃游戏](https://leetcode-cn.com/problems/jump-game/)|
|贪心|[45. 跳跃游戏 II](https://leetcode-cn.com/problems/jump-game-ii/)|

二分查找 相关题：

|分类|题目|
|:------:|:------:|
|二分， 找一个值|[69. x 的平方根](https://leetcode-cn.com/problems/sqrtx/) -> [Fast InvSqrt() 扩展阅读](https://www.beyond3d.com/content/articles/8/)|
|二分， 找一个值|[367. 有效的完全平方数](https://leetcode-cn.com/problems/valid-perfect-square/)|
|二分， 分段单调， 找一个值|[33. 搜索旋转排序数组](https://leetcode-cn.com/problems/search-in-rotated-sorted-array/)|
|二分， 二维空间， 找一个值|[74. 搜索二维矩阵](https://leetcode-cn.com/problems/search-a-2d-matrix/)|
|二分， 分段单调， 找一个值|[153. 寻找旋转排序数组中的最小值](https://leetcode-cn.com/problems/find-minimum-in-rotated-sorted-array/)|
