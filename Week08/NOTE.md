# 学习笔记

+ 排序算法分类：
    + 比较类排序：<br/>
通过比较来决定元素间的相对次序， 由于其时间复杂度不能突破O(nlogn)，因此也称为非线性时间比较类排序。
    + 非比较类排序：<br/>
不通过比较来决定元素间的相对次序，它可以突破基于比较排序的时间下界，以线性时间运行，因此也称为线性时间非比较类排序。

+ [初级排序](https://www.cnblogs.com/onepixel/p/7674659.html "打开排序的动态图解") - $O(n^2)$
    + 选择排序（selection sort）<br>
    每次找最小值，然后放到待排序数组的起始位置
    + 插入排序（Insertation sort）<br>
    从前到后逐步构建有序序列，对于未排序的数据，在已排序序列中从后向前扫描，找到相应位置并插入。
    + 冒泡排序（bubble sort）<br>
    嵌套循环，每次查看相邻的元素如果逆序，则交换。

+ [高级排序]() - $/O(n*logn)$
    + 快速排序 (quick sort) <br>
        + 数组取标杆 pivot，将小元素放在 pivot 左边，将大元素放在 pivot 右边，然后依次对左右两边的子数组继续进行快排，以达到整个序列有序。
    + 归并排序 (merge sort) ——分治 <br> 
        + 把长度为n的输入序列分成两个长度为 n/2 的子序列；
        + 对这两个子序列分别采用归并排序；
        + 将两个排序好的子序列合并成一个最终的排序序列。
    + 归并和快排具有相似性，但步骤顺序相反
        + 归并：先排序左右子数组，然后合并两个有序子数组
        + 快排：先调配出左右子数组，然后对于左右子数组进行排序 
    + 堆排序 (Heap sort) -- 堆插入 O(logN)，取最大/最小值O(1)
        + 数组元素依次建立小顶堆
        + 依次取堆顶元素，并删除

+ [特殊排序]() - O(n)
    + 计数排序 (Counting Sort) <br>
    计数排序要求输入的数据必须是有确定范围的整数，将输入的数据值转化为键存储在额外开辟的数组空间中；然后依次把计数大于1的填充回原数组
    + 桶排序 (Bucket Sort) <br>
    桶排序的工作原理是，假设输入数据服从均匀分布，将数据分到有限数量的桶里，每个桶再分别排序（有可能再使用别的排序算法，或是以递归方式继续使用桶排序进行排）。
    + 基数排序 (Radix Sort) <br>
    基数排序是按照低位先排序，然后收集；再按照高位排序，然后再收集；以此类推，直到最高位。有时候有些属性是有优先级顺序的，先按照低优先级排序，再按高优先级排序。