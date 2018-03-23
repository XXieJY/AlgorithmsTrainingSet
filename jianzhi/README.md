算法部分：  
* 基础算法：
  * 分治：快排、二分搜索
  * 双指针

常见算法：
  * BFS ！
  * DFS ！
    * 基于树的深度优先搜索 Tree-based DFS
    * 基于组合的深度优先搜索 Combination-based DFS
    * 基于排列、图的深度优先搜索 Permutation / Graph based DFS
  * 动态规划 ！
  * 辅助技巧：
    * 回溯法 ！
    * 剪枝
    * 记忆

数据结构：
* 基础数据结构
  * 链表：链表的各种操作吧
  * 数组
  * 字符串：整理各种常考题
* 算法相关的数据结构：
  * 栈：对应递归、DFS
  * 队列: 对应BFS，层序遍历
  * 树：
    * 是查找、搜索问题的基础结构，时常可以通过构想解答树来理解递归dfs,bfs的解题过程
    * 要会遍历二叉树（前/中/后序dfs，层序bfs）
  * 图：比较经典的dfs求连同区域（常结合递归和栈一起实现），bfs求最短路径（常结合队列实现）。
  * 堆：TOP k问题的数据结构  
  * 哈希表：查找频繁时直接用他



---

Time Complexity in Coding Interview
• O(1) 极少
• O(logn) 几乎都是二分法
• O(√n) 几乎是分解质因数
• O(n) 高频
• O(nlogn) 一般都可能要排序
• O(n2) 数组，枚举，动态规划
• O(n3) 数组，枚举，动态规划
• O(2^n) 与组合有关的搜索 combination
• O(n!) 与排列有关的搜索 permutation

---

(面试参考)[https://www.nowcoder.com/discuss/55353]:  

* c++
  * STL：
    * STL的数据结构: (如何实现的、特点)
      * 连续存储的数据结构： vector, queue, stack
      * 链式存储的数据结构： 链表？ 堆priority_queue
      * 集合和哈希： set, map
    * STL的内存分配器/迭代器：
      * Allocator、iterator
  * 基础语言特性：
    * OOP:基础结构（class、struct）；基本服务（多态、重载、虚函数、构造/拷贝构造/析构、动态绑定）
    * 内存结构（堆内存、栈内存）、内存操作（new\malloc\delete\free)
    * 指针、引用
  * c++11特性：
    * 多线程、智能指针

* 网络
  * TCP/IP
    * 链接的建立和终止（三次握手四次挥手）
    * 超时重传机制
  * HTTP
    * GET POST等等
    * 状态码
    * 长连接
* 操作系统
  * linux进程
    * 进程间通信
    * 进程调度
  * 虚拟内存
* 项目
  * 设计模式
  * 业务效果
  * 线程池

[refs](https://www.nowcoder.com/discuss/61958?type=2&order=4&pos=14&page=16)

---

九章推荐题库： https://www.zhihu.com/question/24964987

九章课表： http://www.jiuzhang.com/course/1/


---

toutiao

1.dp (考了：魔方问题、)

2.dfs (考了推箱子问题、)

3.模拟问题（考了分配房间、踢球问题、房间传送）

4.字符串（考了最长相同字符的子串、）

没有考树、递归相关的东西？ 是因为太简单了吗

模拟问题考得蛮多、倾向性？


复习顺序：

* 基础算法：二分查找、快速排序、双指针、树的遍历、链表操作

* 最优化算法：dp (回溯 剪枝 经典题) 、 贪心思想
  * dp：分割整数、矩阵路径、Fibonacci、最长递增子序列&最长公共子序列、背包问题、数组区间问题、字符串匹配

* 递归：dfs bfs 树 图 分治

* 字符文本：字符串 hash

* 模拟问题
