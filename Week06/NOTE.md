# 学习笔记

#### 动态规划 (dynamic programming)

+ 动态规划的[定义](https://en.wikipedia.org/wiki/Dynamic_programming "打开wiki定义")
    + 本质： 寻找重复性 -> 计算机指令集
    + "Simplifying a complicated problem by breaking it down into simpler sub-problems." (in a recursive way)
    + Divide & Conquer + Optimal substructure 分治 + 最优子结构
+ 关键点：
    + 动态规划 和 递归或者分治 没有根本上的区别（关键看有无最优子结构）
    + 共性：找到重复子问题
    + 差异性： 最优子结构、中途可以淘汰次优解
    
+ 动态规划的[解题思路](https://labuladong.gitbook.io/algo/dong-tai-gui-hua-xi-lie/dong-tai-gui-hua-xiang-jie-jin-jie "打开动态规划的解题套路框架"):
    + 最优子结构
    + 储存中间状态
    + 递推公式（状态转移方程 或者 DP方程）


动态规划 相关题：

|分类|题号|
|:------:|:------:|
|DP， fibonacci数列|[LC 70 爬楼梯](https://leetcode-cn.com/problems/climbing-stairs/)|
|DP|[LC 62 不同路径](https://leetcode-cn.com/problems/merge-two-sorted-lists/): [MIT 最短路径算法](https://www.bilibili.com/video/av53233912?from=search&seid=2847395688604491997)|
|DP|[LC 63 不同路径 II](https://leetcode-cn.com/problems/unique-paths-ii/)|
|DP|[LC 1143 最长公共子序列](https://leetcode-cn.com/problems/longest-common-subsequence/)|
|DP|[LC 120 三角形最短路径和](https://leetcode-cn.com/problems/triangle/description/ "打开题目")|
|DP|[LC 53 最大子序和](https://leetcode-cn.com/problems/maximum-subarray/)|
|DP|[LC 152 乘积最大子数组](https://leetcode-cn.com/problems/maximum-product-subarray/description/)|
|DP|[LC 322 零钱兑换](https://leetcode-cn.com/problems/coin-change/description/)|
|DP|[LC 198 打家劫舍](https://leetcode-cn.com/problems/house-robber/)|
|DP|[LC 213 打家劫舍 II](https://leetcode-cn.com/problems/house-robber-ii/description/"打开题目")|
|DP|[LC 121 买卖股票的最佳时机](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/#/description"打开题目")|
|DP|[LC 122 买卖股票的最佳时机 II](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-ii/"打开题目")|
|DP|[LC 123 买卖股票的最佳时机 III](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iii/"打开题目")|
|DP|[LC 309 买卖股票的时机含冷冻期](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/"打开题目")|
|DP|[LC 188 买卖股票的最佳时机 IV](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iv/"打开题目")|
|DP|[LC 714 买卖股票的最佳时机含手续费](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/"打开题目")|
|DP， 股票买卖问题， 题解|[买卖股票最佳时机的题解](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/solution/yi-ge-fang-fa-tuan-mie-6-dao-gu-piao-wen-ti-by-l-3/"打开题解")|

