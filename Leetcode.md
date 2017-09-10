## problem field: Sort

###56. Merge Intervals  
Given a collection of intervals, merge all overlapping intervals.

For example,  
Given [1,3],[2,6],[8,10],[15,18],  
return [1,6],[8,10],[15,18].

**区间的题目，注意不能将所有区间列举出来 然后在计算， 这样会出现很多细节性的错误。**
比如： [1, 4] [5, 6]的输出应该是 [1, 4] [5, 6] ，如果列举区间 则会有 {1,2,3,4,5,6}， 此时两个区间就融在一起了，不好判断。
