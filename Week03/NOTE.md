# 学习笔记

+ 递归模版
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
    

+ 回溯模版
result = []
def backtrack(路径, 选择列表):
    if 满足结束条件:
        result.add(路径)
        return
    
    for 选择 in 选择列表:
        做选择
        backtrack(路径, 选择列表)
        撤销选择

+ 分治模版
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