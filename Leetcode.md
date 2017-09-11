## problem field: Sort

###56. Merge Intervals  
Given a collection of intervals, merge all overlapping intervals.

For example,  
Given [1,3],[2,6],[8,10],[15,18],  
return [1,6],[8,10],[15,18].

**区间的题目，注意不能将所有区间列举出来 然后在计算， 这样会出现很多细节性的错误。**
比如： [1, 4] [5, 6]的输出应该是 [1, 4] [5, 6] ，如果列举区间 则会有 {1,2,3,4,5,6}， 此时两个区间就融在一起了，不好判断。

解题思路ver0.1:

1. 先判断intervals.size() == 0, If true, then return intervals and exit;
2. 将intervals里的区间降序排序， 排序规则是:  
If Interval1.start < Interval2.start, then Interval1 < Interval2;  
Else if Interval1.start == Interval2.start && Interval1.end < Interval2.end, then Interval1 < Interval2;
Else Interval1 > Interval2;  
3. 创建一个辅助空间: vector<Interval> temp; 将intervals的第一个Interval元素直接放入temp, 设置i = 1 指向当前在进行merge操作区间。此时temp初始化完毕。
4. 从intervals第二个元素(设j=2)开始按逐个元素遍历intervals。遍历规则如下:  
  * If (intervals[j].start < temp[i].end && intervals[j].end < temp[i].end), then temp[i].end = intervals[j].end;
  * Else if (intervals[j].start > temp[i].end), then temp.push_back(intervals[i]);
  * Else do nothing;
5. 返回temp作为结果。

```cpp
/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
private:
	void quickSort(vector<Interval> &v, int l, int h){
		if (l < h) {
			int p = partition(v, l, h);
			quickSort(v, l, p - 1);
			quickSort(v, p + 1, h);
		}
	}
	int partition(vector<Interval> &v, int l, int h){
		Interval pivot = v[h];
		int i = l - 1;
		for (int j = l; j < h; j++) {
			if (v[j].start < pivot.start) {
				swap(v[++i], v[j]);
			} else if (v[j].start == pivot.start && v[j].end < pivot.end) {
				swap(v[++i], v[j]);
			} else {
				//do nothing;
			}
		}
		swap(v[++i], v[h]);
		return i;
	}
	
	
public:
	vector<Interval> merge(vector<Interval>& intervals) {
		if (intervals.size() == 0) return intervals;
		quickSort(intervals, 0, (int)(intervals.size() - 1));
		vector<Interval> r;
		r.push_back(intervals[0]);
		int b2 = 0;
		int size = (int)intervals.size();
		int i = 1;
		while (i < size) {
			if(intervals[i].start < r[b2].end) {
				if (intervals[i].end > r[b2].end) r[b2].end = intervals[i].end;
			} else if(intervals[i].start == r[b2].end) {
				r[b2].end = intervals[i].end;
			} else {
				r.push_back(intervals[i]);
				++b2;
			}
			++i;
		}
		return r;
	}
	
};
```
