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
###349. Intersection of Two Arrays  
Given two arrays, write a function to compute their intersection.

Example:
Given nums1 = [1, 2, 2, 1], nums2 = [2, 2], return [2].

Note:
Each element in the result must be unique.
The result can be in any order.

**集合论的题目，虽然LC把它归在sort类别里， 但是，本题 应该属于那种查找操作较为频繁的问题，因此事实上更好的解决方法是使用Hash查找。**

解题思路ver0.1:

1. 先对两个集合A,B进行排序和去重，减少后面判断intersection时的麻烦。  
比如:  
* 如果是两个无序的集合：则判断交集时，需要为A集合（假设A={2,1,4,3}）里的每个元素都去遍历一趟B集合中的元素（假设B={1，7，2}）,才能确认A的当前元素是否也在B中（也就是是否有交集）。因此，使用两个无序集合判断intersection的时间复杂度至少在O(n^2); 排序的时间复杂度是O(nlogn)，因此我们经过排序就把本题的时间复杂度降到了至少O(nlogn)。
* 如果是两个含重复元素的集合：则判断交集时，为了保证结果和题目要求的一样，result must be unique。则还需要额外判断一次，现在的交集是否存在于结果数组中，那么就是O(n^2)的复杂度（因为O(nlogn\*n)); **因此我们需要进行集合排序去重来降低算法的时间复杂度和问题的麻烦程度**
* 再对两个有序去重集合A,B进行遍历，具体思路参照归并排序时的merge方法:  
	* (1)如果两个序列都没遍历完，则继续遍历.  
	* (2)如果当前指向A的元素小于当前B的元素，那么根据有序的情况可知当前A元素不会与B有交集，因此指向A的指针++，B指针不动
	
	


```cpp
// 代码实现了： 原地去重算法unique， 这个算法经常会用到。

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
private:
	void unique(vector<int>& v) {
		int s = v.size();
		if (s == 0 || s == 1) return;
		int f = 0;
		for (int b = 1, i = 0, e = s; b != e; ++b) {
			if (v[b] != v[f]) {
				v[b - i] = v[b];
				++f;
			}
			else
			{
				++i;
			}
		}
		v.resize(f+1);
	}
public:
	vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
		if (nums1.size() == 0) return nums1;
		else if (nums2.size() == 0) return nums2;
		else {
			sort(nums1.begin(), nums1.end());
			sort(nums2.begin(), nums2.end());
			unique(nums1);
			unique(nums2);
			vector<int> r;
			int b1 = 0, b2 = 0, e1 = nums1.size(), e2 = nums2.size();
			while (b1 != e1 && b2 != e2) {
				if (nums1[b1] < nums2[b2]) {
					++b1;
				}
				else if (nums1[b1] > nums2[b2]) {
					++b2;
				}
				else {
					r.push_back(nums1[b1]);
					++b1;
					++b2;
				}
			}
			return r;
		}
	}
};

int main()
{
	vector<int> a{1 };
	vector<int> b{1, 2};
	Solution s;
	vector<int> r = s.intersection(a, b);
	for (vector<int>::iterator b = r.begin(), e = r.end(); b != e; ++b) {
		cout << *b << ", ";
	}
    return 0;
}
```

###147. Insertion Sort List
Sort a linked list using insertion sort.

解题思路：

**一道关于链表排序的题目，一般来说 使用链表进行排序不能够随机读数据，也就是说在排序的时候，不能再像数组那样从后往前倒。我们需要为链表维护一个
表头元素，每次排序时都从表头开始遍历整个链表（PS.这是链表排序比数组排序耗时大的地方）**

1.链表插入排序思路和一般插入排序思路相同，首先维护一个游标cur指向左侧有序子链表的最后一个节点。不同的是，我们还需要维护一个pre指针，
初始化时指向链表表头节点new_head，其作用是：每次需要将右侧无序元素插入到左侧在子链表时，都使用pre指针从new_head位置开始遍历有序子链表
直至找到合适的插入位置，此时pre -> next -> val >= cur -> next -> val;
2.在pre指针找到当前无序元素正确插入位置时，就可以执行链表节点的插入操作，如图所示：
![](https://coding.net/u/jxie0001/p/config/git/raw/master/InsertionSort.png)

参考资料：
http://blog.csdn.net/feixiaoxing/article/details/6905260/
http://www.cnblogs.com/TenosDoIt/p/3666585.html

```cpp
//代码来自: LC的用户jianchao.li.fighter 
class Solution { 
public:
    ListNode* insertionSortList(ListNode* head) {
        ListNode* new_head = new ListNode(0);
        new_head -> next = head;
        ListNode* pre = new_head;
        ListNode* cur = head;
        while (cur) {
            if (cur -> next && cur -> next -> val < cur -> val) {
                while (pre -> next && pre -> next -> val < cur -> next -> val)
                    pre = pre -> next;
                /* Insert cur -> next after pre.*/
                ListNode* temp = pre -> next;
                pre -> next = cur -> next;
                cur -> next = cur -> next -> next;
                pre -> next -> next = temp;
                /* Move pre back to new_head. */
                pre = new_head;
            }
            else cur = cur -> next;
        }
        ListNode* res = new_head -> next;
        delete new_head;
        return res;
    }
};
```
###179. Largest Number
Given a list of non negative integers, arrange them such that they form the largest number.  
For example, given [3, 30, 34, 5, 9], the largest formed number is 9534330.  
Note: The result may be very large, so you need to return a string instead of an integer.   

解题思路:  

**一道字符串排序题目。因为，对于任意给定正整数的数组，Largest Number是唯一的，只有当每个元素都处在数组所有元素中的一个特定相对位置时才能得到那个Largest Number。所以，本题‘找到数组的Largest formed number’问题转化成‘按特定排序规则对数组正整数进行排序，得到Largest formed number’ 是合理的思路**

**在处理本题时所犯的错误：  
1.拿到题目没有从抽象和整体的程度分析问题(没想到Largest formed Number抽象上对应的是数组各个元素具有特定相对位置)。  
2.反而陷入具体的细节，比如：为什么34 要 排在 30前面，那么如果是340和30该怎么排，我该怎么穷举出所有的排序规则 然后解题。  
所以，以后解题时：  
牢记从整体和抽象的层次分析，不要轻易尝试穷举规则和规律，避免陷入细节（这也是我主要犯的问题）。**

解题步骤:
1. 将题目求Largest formed number 看成对数组元素按特定排序规则排序的题目，特定规则为: 如果 字符串组合 str1+str2 < str2+str1，此时应该将str2排在str1前面（可以看作是：str2 < str1）.  
2. 把nums数组中所有正整数转化成字符串然后存到临时vector<string> tmp中。 将上述规则写成自定义函数，然后对tmp按规则排序.  
3. 排序后会得到这么一个vector<string> tmp，即: 对于tmp中的任两个元素 str1 和 str2 (str1位于str2之前), 都有 str1+str2 > str2+str1; 此时tmp组成的字符串满足nums的Largest formed number要求.  
比如： [3, 30, 34, 5, 9] --排序后--> [9,5,34,3,30]; 此时 "95 > 59", "934 > 349", "93 > 39", "930 > 309"，说明9排在第一个位置时，数组组成的字符串才有可能是Largest formed number.  

ps:本题还用到了c++11的两个新特性: (1) 新的for循环功能: for(auto i:nums); (2)lambda函数 ```cpp[捕获数据方式](参数列表){函数体}```
	
```cpp
//代码来自: LC的用户isaac7
class Solution {
public:
    string largestNumber(vector<int>& nums) {
        vector<string> tmp;
        for(auto i:nums) {
            tmp.push_back(to_string(i));
        }
        sort(begin(tmp), end(tmp), [](string& s1, string& s2){ return s1 + s2 > s2 + s1;});
        string result;
        for(auto s:tmp)
            result+=s;
        while(result[0]=='0' && result.length()>1)
            result.erase(0,1);
        return result;
    }
};
```
###324. Wiggle Sort II
Given an unsorted array nums, reorder it such that nums[0] < nums[1] > nums[2] < nums[3]....  

Example:  
(1) Given nums = [1, 5, 1, 1, 6, 4], one possible answer is [1, 4, 1, 5, 1, 6].   
(2) Given nums = [1, 3, 2, 2, 3, 1], one possible answer is [2, 3, 1, 3, 1, 2].  

Note:  
You may assume all input has valid answer.  

Follow Up:  
Can you do it in O(n) time and/or in-place with O(1) extra space?   

解题思路:  

