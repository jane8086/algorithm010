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

dummy = ListNode(0) #作为头节点使用，具体的值不重要，最后输出dummy.next即可
```

    

