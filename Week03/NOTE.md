# 学习笔记


+ 递归模版
```python
def recursion(level, param1, param2, ...):
    # recursion terminator 递归终结条件
    if level > MAX_LEVEL:
        process result
        return
    # process logic in current level 处理当前逻辑
    process(level, data, ...)
    
    # drill down 下探到下一层
    self.recursion(level+1, p1, ...)
    
    # reverse the current level status if needed  清理当前层
```


+ 回溯模版
```python
result = []
def backtrack(路径, 选择列表):
    if 满足结束条件:
        result.add(路径)
        return
    
    for 选择 in 选择列表:
        做选择
        backtrack(路径, 选择列表)
        撤销选择
```


+ 分治模版
```python
def divide_conquer(problem, parma1, param2, ...):
    # recursion terminator 
    if problem is None:
      print_result
      return 
      
    #prepare data
    data = prepare_data(problem)
    subproblems = split_problem(problem, data)
    
    #conquer subproblem
    subresult1 = self.divide_conquer(subproblem[0], p1, ...)
    subresult2 = self.divide_conquer(subproblem[1], p2, ...)
    subresult3 = self.divide_conquer(subproblem[2], p3, ...)
    ...
    
    #process and generate the final result
    result = process_result(subresult1, subresult2, subresult3, ...)
    
    # revert the current level states
```

泛型递归、树的递归 相关题：

|分类|题目|
|:------:|:------:|
|泛型递归|[70. 爬楼梯](https://leetcode-cn.com/problems/climbing-stairs/)|
|泛型递归|[22. 括号生成](https://leetcode-cn.com/problems/generate-parentheses/)|
|泛型递归|[77. 组合](https://leetcode-cn.com/problems/combinations/)|
|泛型递归|[46. 全排列](https://leetcode-cn.com/problems/permutations/)|
|泛型递归|[47. 全排列 II](https://leetcode-cn.com/problems/permutations-ii/)|
|树的递归|[226. 翻转二叉树](https://leetcode-cn.com/problems/invert-binary-tree/description/)|
|树的递归|[98. 验证二叉搜索树](https://leetcode-cn.com/problems/validate-binary-search-tree/)|
|树的递归|[104. 二叉树的最大深度](https://leetcode-cn.com/problems/maximum-depth-of-binary-tree/)|
|树的递归|[111. 二叉树的最小深度](https://leetcode-cn.com/problems/minimum-depth-of-binary-tree/)|
|树的递归|[297. 二叉树的序列化与反序列化](https://leetcode-cn.com/problems/serialize-and-deserialize-binary-tree/)|
|树的递归|[236. 二叉树的最近公共祖先](https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree/)|
|树的递归|[105. 从前序与中序遍历序列构造二叉树](https://leetcode-cn.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/)|

分治、回溯 相关题：

|分类|题目|
|:------:|:------:|
|分治|[50. Pow(x, n)](https://leetcode-cn.com/problems/powx-n/) [牛顿迭代法](http://www.matrix67.com/blog/archives/361) [代码](http://www.voidcn.com/article/p-eudisdmk-zm.html)|  
|分治|[78. 子集](https://leetcode-cn.com/problems/subsets/)|
|分治|[169. 多数元素](https://leetcode-cn.com/problems/majority-element/description/)|
|分治|[17. 电话号码的字母组合](https://leetcode-cn.com/problems/letter-combinations-of-a-phone-number/)|
|分治|[51. N皇后](https://leetcode-cn.com/problems/n-queens/)|
|分治|[]()|