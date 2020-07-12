#学习笔记 
+ 如果需要对一个数组变量，进行原地操作，要在数组变量名字的后面加上[:]
+ 如何实现链表\[python\]
    + 链表的类
    + 哑节点的使用可以避免代码进行冗余的判断
```python
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

dummy =  p = ListNode(0) #作为头节点使用，具体的值不重要，最后输出dummy.next即可
for i in range(10):
    next_val = i
    p.next = ListNode(next_val) # p用作移动指针
    p = p.next
return dummy.next
```
有关哑节点使用的题：

| 题号 | 名字 |
| :------: | :------:|
| [LeetCode 2](https://leetcode.com/problems/add-two-numbers/) | Add Two Numbers|

数组、链表、跳表 相关题：

| 分类 | 题目 |
| :------: | :------:|
|数组遍历， 双指针| [LC 11 盛水最多的容器](https://leetcode.com/problems/container-with-most-water/) |
|数组遍历， 双指针| [LC 283 移动零](https://leetcode.com/problems/move-zeroes/) |
|数组存储， 动态规划|[LC 70 爬楼梯](https://leetcode.com/problems/climbing-stairs/)|
|数组和字典|[LC 1 两数之和](https://leetcode.com/problems/two-sum/)|
|数组存储， 动态规划|[LC 15 三数之和](https://leetcode.com/problems/3sum/)|
|链表|[LC 206 反转链表](https://leetcode.com/problems/reverse-linked-list/)|
|链表|[LC 24 两两交换链表中的节点](https://leetcode.com/problems/swap-nodes-in-pairs/)|
|链表， 快慢指针|[LC 141 环形链表](https://leetcode.com/problems/linked-list-cycle/)|
|链表， 快慢指针|[LC 142 环形链表 II](https://leetcode.com/problems/linked-list-cycle-ii/)|
|链表， 快慢指针|[LC 876 链表中点](https://leetcode.com/problems/middle-of-the-linked-list/)|
|链表， 快慢指针|[链表中倒数第k个元素](https://leetcode-cn.com/problems/lian-biao-zhong-dao-shu-di-kge-jie-dian-lcof/)|
|链表|[LC 25 K个一组反转链表](https://leetcode.com/problems/reverse-nodes-in-k-group/)|

栈、队列、优先队列、双端队列 相关题：

|分类|题目|
|:------:|:------:|
|源码|[python 中的高性能库](https://docs.python.org/3/library/collections.html)|
|栈|[LC 20 有效的括号](https://leetcode.com/problems/valid-parentheses/)|
|栈|[LC 155 最小栈](https://leetcode.com/problems/min-stack/)|
|栈|[LC 84 柱状图中最大的矩形](https://leetcode.com/problems/largest-rectangle-in-histogram/)|
|栈|[LC 239 滑动窗口的最大值](https://leetcode.com/problems/sliding-window-maximum/)|
|队列|[LC 641 设计双端循环队列](https://leetcode.com/problems/design-circular-deque/)|
|栈， 单调栈|[LC 42 接雨水](https://leetcode.com/problems/trapping-rain-water/)|
