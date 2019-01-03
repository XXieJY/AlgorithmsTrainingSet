* 数组搜索问题，能用循环就不要用分治，分治会导致TLE.

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

给定一个整数序列，需要得到一个wiggle sort序列，其中：任意奇数位置的元素都大于其左右相邻偶数位置的元素。  

可以先:  
1. 对整组序列按递减排序，然后找到序列的中间数m，那么位于中间数之前的元素就都大于位于中间数之后的元素。
2. 使用插空法的方式，将中间数之后的元素插到到中间数之前的序列的奇数位置上。

如:
origin: [1,5,1,1,6,4]  
reverse sort: [6,5,4,1,1,1], median is [4], the larger part is [6,5], the smaller part is [1,1,1]  
insertion operation: [1,6,1,5,1,4]

``` cpp
class Solution {
private:
	int partition(vector<int>& nums, int l, int h) {
		int pivot = nums[h], m = l - 1;
		for (int i = l; i < h; i++) {
			if (nums[i] > pivot) {
				int tmp = nums[i];
				nums[i] = nums[++m];
				nums[m] = tmp;
			}
			else {
				//do nothing
			}
		}
		int tmp = nums[h];
		nums[h] = nums[++m];
		nums[m] = tmp;
		return m;
	}
	void quickSort(vector<int>& nums, int l, int h) {
		int p;
		if (l < h) {
			p = partition(nums, l, h);
			quickSort(nums, l, p - 1);
			quickSort(nums, p + 1, h);
		}
	}
public:

	void wiggleSort(vector<int>& nums) {
		int s = nums.size();
		if (s == 0) return;
		if (s == 1) return;
		quickSort(nums, 0, s - 1);
		vector<int> tmp = nums;
		//这里应该取中间数的前一位，而不是就取中间数的位置。
		//如果直接取中间数的位置，在当中间数大于2个的时候，得到的结果会有两个中间数连在一起
		int median = nums.size() / 2 - 1, i = 0, j = median + 1;
		vector<int>::iterator iter = nums.begin();
		while (i <= median && j < s) {
			*iter = tmp[j];
			*(++iter) = tmp[i];
			++j;
			++i;
			++iter;
		}
        if (j < s) {
			*iter = tmp[j];
		}
		if (i <= median) {
			*iter = tmp[i];
		}


	}

};
```
###524. Longest Word in Dictionary through Deleting
Given a string and a string dictionary, find the longest string in the dictionary that can be formed by deleting some characters of the given string. If there are more than one possible results, return the longest word with the smallest lexicographical order. If there is no possible result, return the empty string.  

Example 1:  
Input:  
s = "abpcplea", d = ["ale","apple","monkey","plea"]  

Output:  
"apple"  
Example 2:  
Input:  
s = "abpcplea", d = ["a","b","c"]  

Output:   
"a"  
Note:  
All the strings in the input will only contain lower-case letters.  
The size of the dictionary won't exceed 1,000.  
The length of all the strings in the input won't exceed 1,000.  

解题思路:  

这题目前只想到了一种算得上是“优化过了的暴力解法”。 除此之外，想不到另外的方法能够不通过逐个比对的方式得到结果(比如索引的方式？或者用树形结构或者其它数据结构？)

具体解题步骤如下:

根据题目要求，我们可以知道 vector<string>里至少有一个及以上的string能够按字符串s的deleting匹配的方式得到自身.  
但我们需要的结果是Longest word并且，如果有多个等长的Longest word则需要的是字典序最小的.  

所以我们可以:
	1. 按照word长度升序和字典降序的方式对d进行排序，比如: d=["ale","aae","atee","acee","abcdef"]
	2. 然后从d的最后一个word开始匹配，匹配到的第一个word就是结果

代码如下：（值得注意的就是使用c++11的lambda函数简洁地自定义sort函数）

```cpp
class Solution {
public:
	bool okDelete(const string s,const string t) {
		int ss = s.length(), ts = t.length(), si = 0, st = 0;
		while (si < ss && st < ts) {
			if (s[si] == t[st]) ++st;
			++si;
		}
		if (st == ts) return true;
		else return false;
	}
	string findLongestWord(string s, vector<string>& d) {
		sort(begin(d), end(d)
		, [](string& s1, string& s2) {return s1.length() < s2.length() ? 1
		: s1.length() != s2.length() ?  0
		: s1 < s2 ? 0 : 1; });
		string result("");
		for (vector<string>::reverse_iterator rb = d.rbegin(), re = d.rend(); rb != re; ++rb) {
			if (okDelete(s, *rb)) {
				result = *rb;
				return result;
			}
			else {
				//do nothing
			}
		}
        return result;
	}
};
```


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


#### 698. Partition to K Equal Sum Subsets

Given an array of integers nums and a positive integer k, find whether it's possible to divide this array into knon-empty subsets whose sums are all equal.

Example 1:

Input: nums = [4, 3, 2, 3, 5, 2, 1], k = 4
Output: True
Explanation: It's possible to divide it into 4 subsets (5), (1, 4), (2,3), (2,3) with equal sums.


Note:

1 <= k <= len(nums) <= 16.
0 < nums[i] < 10000.

解题思路：  
这道题我们可以用递归来做:
* 首先我们还是求出数组的所有数字之和sum，首先判断sum是否能整除k，不能整除的话直接返回false。
* 然后需要一个visited数组来记录哪些数组已经被选中了，然后调用递归函数进行递归。  
* 对于递归函数：  
  * 我们的目标是组k个子集合，是的每个子集合之和为target = sum/k。
  * 我们还需要变量start，表示从数组的某个位置开始查找，curSum为当前子集合之和.
  * 如果k=1，说明此时只需要组一个子集合，那么当前的就是了，直接返回true。
  * 如果curSum等于target了，说明凑够一个k的子集合。此时递归传入k-1，并将start和curSum都重置为0，开始继续找下一个。参见代码如下：

```cpp
class Solution {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        //判断是否整除K
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % k != 0) return false;
        //创建一个访问数组标记
        vector<bool> visited(nums.size(), false);
        return helper(nums, k, sum / k, 0, 0, visited);
    }
    bool helper(vector<int>& nums, int k, int target, int start, int curSum, vector<bool>& visited) {
        if (k == 1) return true;
        if (curSum == target) return helper(nums, k - 1, target, 0, 0, visited);
        for (int i = start; i < nums.size(); ++i) {
            if (visited[i]) continue;
            visited[i] = true;
            if (helper(nums, k, target, i + 1, curSum + nums[i], visited)) return true;
            visited[i] = false;
        }
        return false;
    }
};
```

#### 315. Count of Smaller Numbers After Self
解题思路：  
这道题给定我们一个数组，让我们计算每个数字右边所有小于这个数字的个数，目测我们不能用brute force，OJ肯定不答应。
* 那么我们为了提高运算效率，首先可以使用用二分搜索法，思路是将给定数组从最后一个开始，用二分法插入到一个新的数组，这样新数组就是有序的，那么此时该数字在新数组中的坐标就是原数组中其右边所有较小数字的个数，参见代码如下：
```cpp
class Solution {
public:
    vector<int> countSmaller(vector<int>& nums)
    {
        vector<int> t, res(nums.size());
        for (int i = nums.size() - 1; i >= 0; --i)
        {
            int left = 0, right = t.size();
            while (left < right)
            {
                int mid = left + (right - left) / 2;
                if (t[mid] >= nums[i])
                {
                  right = mid;
                }
                else
                {
                  left = mid + 1;
                }
            }
            res[i] = right;
            t.insert(t.begin() + right, nums[i]);
        }
        return res;
    }
};
```

#### 003二维数组中的查找
在一个二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。

##### 思路：
先想想最直接的做法：暴力搜索解空间，找到则true,没找到则false。此时时间复杂度是O(n*m);

* -->优化： 暴力搜索解空间，肯定是有冗余操作。如何找到本题冗余操作
  * --->首先想到利用“从左到右递增，从上到下递增。”的规律去分割出子问题。
  * --->显然，我们在每次判定target时，是缩小问题解空间的时机。
* -->那么如何缩小问题解空间？
  * ---->我们假设当前在判断数组中E[i][j]与target的大小。
  * 二维数组从左到右递增， 从上到下递增。 此时查找一个数值，应该中右上角或者左下角开始使用分治法查找；
```cpp
class Solution {
public:
    bool Find(int T, vector<vector<int> > E) {
        if(E.size() == 0 || E[0].size() == 0)
        {
            return false;
        }
        int x = 0, y = E[0].size()-1, rows = E.size();
        while(x < rows && y >= 0)
        {
            if(T == E[x][y])
            {
                return true;
            }
            else if(T < E[x][y])
            {
                --y;
            }
            else
            {
                ++x;
            }
        }
        return false;
    }
};
```


#### 628. Maximum Product of Three Numbers (多种情况的数组元素相乘)(以“计算+比较”代替麻烦的“讨论多种情况+计算”)

解题思路：  
* 我们来考虑几种情况，如果全是负数，三个负数相乘还是负数，为了让负数最大，那么其绝对值就该最小，而负数排序后绝对值小的都在末尾，所以是末尾三个数字相乘，这个跟全是正数的情况一样。
* 那么重点在于前半段是负数，后半段是正数，那么最好的情况肯定是两个最小的负数相乘得到一个正数，然后跟一个最大的正数相乘，这样得到的肯定是最大的数，所以我们让前两个数相乘，再和数组的最后一个数字相乘，就可以得到这种情况下的最大的乘积。
* 实际上我们并不用分情况讨论数组的正负，只要把这两种情况的乘积都算出来，比较二者取较大值，就能涵盖所有的情况，从而得到正确的结果，参见代码如下：

```cpp
class Solution {
public:
    int maximumProduct(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        int p = nums[0] * nums[1] * nums[n - 1]; //带正负数的情况
        int q = nums[n - 1] * nums[n - 2] * nums[n - 3]; //只有正数的情况
        return max(p, q); //只有正数的情况和带正负数的情况比较
    }
};
```



#### 004将空格替换成为字符
请实现一个函数，将一个字符串中的空格替换成“%20”。 例如，当字符串为We Are Happy.则经过替换之后的字符串为We%20Are%20Happy。

>We Are Happy   
We%20Are%20Happy

##### 思路：
本质是扩大缩小数组的问题，往数组中填充元素。均先考虑，从数组的尾部开始进行迁移操作的方法。
* 先确定空格在字符串中出现的数目
* 在从后往前完成替换，每个非空格字符往后挪空格数目的位置
```cpp
#include <iostream>

using namespace std;

class Solution{
public:
  void replaceSpace(char *str,int length)
  {
      int i, j;
      int count = 0;
      int len = length;
      for(int i = 0; i < length; i++)
      {
          if(str[i] == ' ')
          {
              count++;
          }
      }
      len = length + count * 2;
      for(i = length - 1, j = len - 1;
          i >= 0 && j >= 0;)
      {
          if(str[i] == ' ')
          {
              str[j--] = '0';
              str[j--] = '2';
              str[j--] = '%';
              i--;
          }
          else
          {
              str[j--]  = str[i--];
          }
      }
      str[len] = '\0';
  }
};
```

##### 007用两个栈实现队列
用两个栈来实现一个队列，完成队列的Push和Pop操作。 队列中的元素为int类型。

##### 思路*：
本题没有什么特殊的东西，算是对队列FIFO和栈FILO的理解吧。

```cpp
class Solution{
public:
    void push(int V){
        E1.push(V);
    }

    int pop(){
      int RS, TMP;
      RS = 0;
      TMP = 0;
      if (!E2.empty()){
          RS = E2.top();
          E2.pop();
          return RS;
      }
      while(!E1.empty()){
        TMP = E1.top();
        E2.push(TMP);
        E1.pop();
      }
    }
private:
    stack<int> E1, E2;
}
```

#### 020顺时针打印矩阵
题目描述
输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字，
例如， 如果输入如下矩阵：

##### 思路：
这题也是比较特殊的题，主要就是打印二维举证的过程中注意边界的控制，不能超出矩阵本来的
边界，也不能重复打印已经打印过的位置，因此可以将边界视作不断缩小的情。
因此，按顺时针逆时针或者某种方向打印数组时，需要注意的有两点：
  1. 维护边界，不要超过数组范围，不要输出已经输出过的点。
  2. 模拟输出时，数组下标的变化。

```cpp
class Solution {
public:
    vector<int> printMatrix(vector<vector<int> > E) {
        int m, n;
        vector<int> res;
        if ((m = E.size()) == 0 || (n = E[0].size()) == 0)
        {
            return res;
        }
        vector<vector<bool> > visited = vector<vector<bool> >(m, vector<bool>(n, false));
        const int D[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};
        for(int c = m * n, i = 0, j = 0, d = 0; c >= 0; --c)
        {
            res.push_back(E[i][j]);
            visited[i][j] = true;
            int ti = i+D[d][0], tj = j + D[d][1];
            if(ti < 0 || ti >= m ||
                tj < 0 || tj >= n ||
                visited[ti][tj])
            {
                d = (d + 1) % 4;
            }
            i += D[d][0];
            j += D[d][1];
        }
        return res;
    }
};
```

#### 008旋转数组的最小数字
题目描述*:

把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。输入一个非递减序列的一个旋转，输出旋转数组的最小元素。

例如

> 数组{3,4,5,1,2}为{1,2,3,4,5}的一个旋转，该数组的最小值为1。

##### 解题思路：
这题应该归类为在数组中进行搜索的题目，常见的搜索算法一般就是顺序搜索，二分搜索。
* 这题如果用顺序搜索解决，那么很明显需要先去找到旋转数组的顺序上的特点，这里可以发现旋转数组里最大
的那个数字后面的就是最小的数字，因此根据这个规律就可以顺利写出顺序搜索的代码。
* 如果这道题再要提高效率，那么可知必然和二分搜索有关系。那么就要再旋转数组里找到能够支持二分的搜索
的特征，也就是如何确定每次搜索的时候搜索数组中的哪一半。
  * 这里就需要发现，旋转数组可以被分为前后两个递增子序列。
  * 因此，A[pivot]如果大于A[low]则说明A[pivot]属于前面的子序列则最小值在A[pivot]之后。
  * 相反如果A[pivot]小于A[high]则说明A[pivot]属于后面的子序列则最大值在A[pivot]之前。

```cpp
class Solution {
public:
    int minNumberInRotateArray(vector<int> E) {
        int S;
        if((S = E.size()) == 0)
        {
            return 0;
        }
        int L = 0, R = S - 1, pivot;
        while (R - L > 1)
        {
            pivot = L + (R - L)/2;
            if (E[pivot] >= E[L])
            {
                L = pivot;
            }
            else
            {
                R = pivot;
            }
        }
        return E[R];
    }
};
```

#### 665. Non-decreasing Array (改变一个数成为非递减数组)
解题思路：  
这道题给了我们一个数组，说我们最多有1次修改某个数字的机会，问能不能将数组变为非递减数组。题目中给的例子太少，不能覆盖所有情况，我们再来看下面三个例子：  

4，2，3  

-1，4，2，3  

2，3，3，2，4  

我们通过分析上面三个例子可以发现，当我们发现后面的数字小于前面的数字产生冲突后，有时候需要修改前面较大的数字(比如前两个例子需要修改4)，有时候却要修改后面较小的那个数字(比如前第三个例子需要修改2)，那么有什么内在规律吗？
* 是有的，判断修改那个数字其实跟再前面一个数的大小有关系，首先如果再前面的数不存在，比如例子1，4前面没有数字了，我们直接修改前面的数字为当前的数字2即可。
* 而当再前面的数字存在，并且小于当前数时，比如例子2，-1小于2，我们还是需要修改前面的数字4为当前数字2；
* 如果再前面的数大于当前数，比如例子3，3大于2，我们需要修改当前数2为前面的数3。
* 这是修改的情况，由于我们只有一次修改的机会，所以用一个变量cnt，初始化为1，修改数字后cnt自减1，当下次再需要修改时，如果cnt已经为0了，直接返回false。遍历结束后返回true，参见代码如下：

```cpp
class Solution {
public:
    bool checkPossibility(vector<int>& nums) {
        int cnt = 1, n = nums.size();
        for (int i = 1; i < n; ++i) {
            if (nums[i] < nums[i - 1]) {
                if (cnt == 0) return false;
                if (i == 1 || nums[i] >= nums[i - 2]) nums[i - 1] = nums[i];
                else nums[i] = nums[i - 1];
                --cnt;
            }
        }
        return true;
    }
};
```


#### 014 调整数组顺序使得奇数位于偶数前面并保持奇数之间和偶数之间的相对位置
题目描述

输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有的奇数位于数组的前半部分，所有的偶数位于位于数组的后半部分，并保证奇数和奇数，偶数和偶数之间的相对位置不变。

> 样例输入
5 1 2 3 4 5

> 样例输出
1 3 5 2 4

##### 解题思路：
这题算是调整数组顺序的问题，虽然没有按大小排序的要求，但是按其他任意排序的问题都应该归结为排序问题。
然后本题还要求是稳定的排序，因此只能考虑插入排序、冒泡排序。综上所述，调整数组奇数偶数的相对位置，就是
在考察简单的冒泡排序。
```cpp
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void reOrderArray(vector<int> &E) {
        int S, tmp;

        S = E.size();
        if(S <= 1) return;

        tmp = 0;
        while (S >= 2) {
            int i, j;
            i = 0;
            j = 1;
            for (; j < S; ++i, ++j){
                if (E[i] % 2 == 0 && E[j] % 2 != 0){
                    tmp = E[i];
                    E[i] = E[j];
                    E[j] = tmp;
                }
            }
            --S;
        }
    }
};
```

#### 021 实现包含min功能的栈
题目描述
定义栈的数据结构，请在该类型中实现一个能够得到栈最小元素的min函数。

##### 解题思路：
这种题目如果每次min的时候查找确实是一种慢的方法。但是这种实现一个数据结构并且要维护
这个数据结构的最大最小值，并且这个数据结构的大小会变化，因此大小值需要维护成一个
列表，也随着整个数据结构的大小变化而变化。

* 因此实现包含min功能的栈，就需要用到一个存储实时min值的辅助栈，辅助栈的栈顶永远都是
当前栈的最小值。min栈的栈顶只能越来越小
* 当入栈元素大于min栈栈顶元素时，该元素不入min栈。反之则既入普通栈又入min栈
* 在出栈时如果元素是min栈栈顶元素，则min栈也出栈。

```cpp
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
     
    stack<int> E, EMin;
     
    void push(int value) {
        E.push(value);
        if(EMin.empty())
            EMin.push(value);
        else if(value<=EMin.top())
        {
            EMin.push(value);
        }
    }
     
    void pop() {
        if(E.top()==EMin.top())
            EMin.pop();
        E.pop();
         
    }
     
    int top() {
        return E.top();       
    }
     
    int min() {
        return EMin.top();
    }
     
};
```

#### 022 栈的压入、弹出序列
题目描述
输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否为该栈的弹出顺序。假设压入栈的所有数字均不相等。例如序列1,2,3,4,5是某栈的压入顺序，序列4，5,3,2,1是该压栈序列对应的一个弹出序列，但4,3,5,1,2就不可能是该压栈序列的弹出序列。（注意：这两个序列的长度是相等的）
##### 解题思路：
判断栈的压入弹出序列是否正确是典型和栈相关的问题。主要用到的解法就是模拟栈的出栈过程，到最后如果
模拟栈为空则说明出栈序列是正确的。
* 利用到的性质：
  * 当某个元素出栈时，早于其入栈的元素不会晚于其出栈
* 解题过程：
  * 创建一个模拟栈，每次往其中push一个元素
  * 每次push元素之后，和出栈序列的第一个元素对比：
    * 如果相等则说明当前元素已经出栈，此时也把这个元素从模拟栈中pop_back掉
    * 然后继续这个比较过程，直到不相等
  * 最后返回模拟栈是否为空的结果

```cpp
class Solution {
public:
     bool IsPopOrder(vector<int> pushV, vector<int> popV) {
                        if (pushV.size() == 0) return false;
                        vector<int> stack;
                        for (int i = 0, j = 0; i < pushV.size();) {
                                stack.push_back(pushV[i++]);
                                while (j < popV.size() && stack.back() == popV[j]) {
                                        stack.pop_back();
                                        j++;
                                }
                        }
                        return stack.empty();
                }
};
```

---

### 数组元素的搜索


#### Search for a Range 搜索一个范围(数组的范围搜索：先确定一个位置，然后左右向外延伸)
Given a sorted array of integers, find the starting and ending position of a given target value.  

Your algorithm's runtime complexity must be in the order of O(log n).  

If the target is not found in the array, return [-1, -1].  

For example,  
Given [5, 7, 7, 8, 8, 10] and target value 8,  
return [3, 4].  

解题思路：  
* 这道题让我们在一个有序整数数组中寻找相同目标值的起始和结束位置，而且限定了时间复杂度为O(logn)，这是典型的二分查找法的时间复杂度，所以这道题我们也需要用此方法。
* 我们的思路是首先对原数组使用二分查找法。
    * 找出其中一个目标值的位置。
    * 然后向两边搜索找出起始和结束的位置，代码如下：

```cpp
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int idx = search(nums, 0, nums.size() - 1, target);
        if (idx == -1) return {-1, -1};
        int left = idx, right = idx;
        while (left > 0 && nums[left - 1] == nums[idx]) --left;
        while (right < nums.size() - 1 && nums[right + 1] == nums[idx]) ++right;
        return {left, right};
    }
    int search(vector<int>& nums, int left, int right, int target) {
        if (left > right) return -1;
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) return mid;
        else if (nums[mid] < target) return search(nums, mid + 1, right, target);
        else return search(nums, left, mid - 1, target);
    }
};
```


#### Third Maximum Number 第三大的数 (变量记录元素值法)
解题思路：  
这道题让我们求数组中第三大的数，如果不存在的话那么就返回最大的数，题目中说明了这里的第三大不能和第二大相同，必须是严格的小于，而并非小于等于。这道题并不是很难，如果知道怎么求第二大的数，那么求第三大的数的思路都是一样的。
* 那么我们用三个变量first, second, third来分别保存第一大，第二大，和第三大的数，然后我们遍历数组，如果遍历到的数字大于当前第一大的数first，那么三个变量各自错位赋值，如果当前数字大于second，小于first，那么就更新second和third，如果当前数字大于third，小于second，那就只更新third；
* 注意这里有个坑，就是初始化要用长整型long的最小值，否则当数组中有INT_MIN存在时，程序就不知道该返回INT_MIN还是最大值first了，参见代码如下：

```cpp
class Solution {
public:
    int thirdMax(vector<int>& nums) {
        long first = LONG_MIN, second = LONG_MIN, third = LONG_MIN;
        for (int num : nums) {
            if (num > first) {
                third = second;
                second = first;
                first = num;
            } else if (num > second && num < first) {
                third = second;
                second = num;
            } else if (num > third && num < second) {
                third = num;
            }
        }
        return (third == LONG_MIN || third == second) ? first : third;
    }
};
```


#### 029 数组中出现次数超过一半的数字(排序和查找法)
题目描述
数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。例如输入一个长度为9的数组{1,2,3,2,2,2,5,4,2}。由于数字2在数组中出现了5次，超过数组长度的一半，因此输出2。如果不存在则输出0。
##### 解题思路：
这题算是数组元素统计题，是比较好想到题解的。最简单的就是，对数组排序，然后中间的那个数一定是
超过数组一半元素的嫌疑数，然后再遍历一遍数组，计算嫌疑数出现的次数即可。

我这里用的是数组元素的对消法，如果存在超出数组一半的元素，那么我们对数组中相同元素两两
相合，不同元素两两相消，那么剩下的元素就是嫌疑元素，然后再遍历一遍数组元素确认这个嫌疑元素
出现的次数即可。


```cpp
class Solution {
public:
    int MoreThanHalfNum_Solution(vector<int> E) {
        int S;
        if ((S = E.size()) == 0)
        {
            return 0;
        }
        else if (S == 1)
        {
            return E[0];
        }
        else
        {
            int count = 1, res = E[0];
            for(int i = 1; i < S; ++i)
            {
                count += E[i] == res ? 1 : -1;
                if (count == 0)
                {
                    res = E[i];
                    count = 1;
                }
            }
            int recount = 0;
            for (int i = 0; i < S; ++i)
            {
                if (E[i] == res)
                {
                    ++recount;
                }
            }
            return 2*recount > S ? res : 0;
        }
    }
};
```

#### 030 最小的K个数
题目描述
输入n个整数，找出其中最小的K个数。例如输入4,5,1,6,2,7,3,8这8个数字，则最小的4个数字是1,2,3,4。

##### 解题思路：
这题算是常见搜索相关问题里面被讨论比较多，比较有深度的问题。因为可以应用上的方法很多，从快速排序的各种加强版本，到最小堆。July还为此专门有一个专题。[专题](https://github.com/gatieme/CodingInterviews/tree/master/030-%E6%9C%80%E5%B0%8F%E7%9A%84K%E4%B8%AA%E6%95%B0)

* 最大堆求数组最小k个数：
```cpp
class Solution {
public:
    vector<int> Solution(vector<int> E, int k)
    {        
        vector<int> res;

        if(E.size( ) == 0 || E.size( ) < k)
        {
            return res;
        }
        make_heap(E.begin( ), E.R( ), greater_class());

        for(int i = 0; i < k; i++)
        {
            //最小的元素在栈顶
            res.push_back(E[0]);

            ///  一下两种操作均可以
            // [1]  --  清除它, 然后重新排序堆
            //E.erase(E.begin( ));
            //sort_heap(E.begin( ), E.R( ));
            // [2]  --  当然从堆出弹出这个栈顶元素
            pop_heap(E.begin( ), E.R( ), greater_class( ));   // 弹出一个元素后，剩下的又重建了 heap，仍保持heap的性质
            E.pop_back();         // vector 删除末尾元素
        }

        return res;
    }

    class greater_class
    {
    public:

        bool operator()(int a, int b)
        {
            return a > b;
        }
    }
};
```
* 利用快速排序和分治思想：

 * 取中位数作为pivot的方法：  
    * 类似快速排序的划分方法，N个数存储在数组S中。每次排序时从数组中随机选取一个数X作为pivot,这样可以把数组划分为Sa和Sb两部分，Sa<= X <=Sb。
    * 如果要查找的K个小的元素小于Sa中的元素个数，则返回Sa中较小的K个元素，否则返回Sa中K个小的元素 + Sb中小的K-|Sa|个元素。  

 * **（随机选取枢纽元，可做到线性期望时间O(N)的复杂度）** 每次都是随机选择数列中的一个元素作为主元，使用快速排序在O(n)的时间内找到第K小的元素，然后遍历输出前面的K个小的元素。如果能的话，那么总的时间复杂度为线性期望时间：O(n+k) = O(n)（当n比较小时）；

下面这个这个实现是按照kth一个一个的来搜索到的，而不是按块搜索到的
```cpp
class Solution {
public:
    vector<int> Solution(vector<int> E, int k)
    {
        int S;
        vector<int> RES;

        S = E.size();
        if(S == 0 || S < k)
        {
            return RES;
        }
        kthQuick(E, 0, S-1, k);
        int i = 0;
        for(; i < k; ++i){
            RES.push_back(E[i]);
        }
        return RES;
    }

    void kthQuick(vector<int> &E, int L, int R, int k){
        if(L == R){
            return;
        }
        int pivot = Partition(E, L, R);
        if (pivot < k){
            kthQuick(E, pivot+1, R, k);
        }
        else if (pivot > k){
            kthQuick(E, L, pivot-1, k);
        }
        else{
            return;
        }
    }

    int Partition(vector<int> &E, int L, int R)
    {
        int i, j, pivot, pivotNum;

        ///  我们选择第一个元素作为基准
        ///  这个也可以随机选择
        i = L;
        j = R;
        pivot = L;
        pivotNum = E[pivot];
        while(i < j)
        {
            while(i < j && E[j] >= pivotNum)
            {
                j--;
            }
            E[i] = E[j]; //这里因为pivot的值已经额外记录了所以可以这样

            while(i < j && E[i] <= pivotNum)
            {
                i++;
            }
            E[j] = E[i];
        }
        E[i] = pivotNum; //确定pivot的位置             
        return i;
    }
};
```

#### 036 数组中的逆序对
题目描述

在数组中的两个数字，如果前面一个数字大于后面的数字，则这两个数字组成一个逆序对。 输入一个数组，求出这个数组中的逆序对的总数

> 样例输入
7 5 6 4

>样例输出
5

##### 解题思路：
逆序对相关问题直接和归并排序相关的。
* 采用归并排序，计算每次左右两边的逆序对。
* 然后再计算merge后的逆序对。

```cpp
class Solution {
public:
    int InversePairs(vector<int> E) {
       int S = E.size();
       if(S <= 0)
       {
           return 0;
       }
       vector<int> copy(E.begin(),E.end());
       return InversePairsCore(E, copy, 0, S-1) % 1000000007;
    }
    long long InversePairsCore(vector<int> &E, vector<int> &copy, int L, int R)
    {
       if(L == R)
          {
            copy[L] = E[L];
            return 0;
          }
       int M = L + (R - L) / 2;
       long long res1 = InversePairsCore(E, copy, L, M);
       long long res2 = InversePairsCore(E, copy, M + 1, R); 
       
       int i = M;
       int j = R;
       int indexcopy = R;
       long long count = 0;
       while(i >= L && j > M)
          {
             if(E[i] > E[j])
                {
                  copy[indexcopy--] = E[i--];
                  count += j - M;
                }
             else
                {
                  copy[indexcopy--] = E[j--];
                }          
          }
       for(; i >= L; --i)
           copy[indexcopy--] = E[i];
       for(; j > M; --j)
           copy[indexcopy--] = E[j];
       for (int i = L; i <= R; ++i)
           E[i] = copy[i];
       return res1 + res2 + count;
    }
};
```

#### 038 数字在排序数组中出现的次数
题目描述  
统计一个数字在排序数组中出现的次数。

解题思路：  
* 暴力搜索解空间求解：  
本题可以简单地使用顺序暴力统计的方式解题。相当于遍历解空间以求解。

* 提升解空间维度+二分搜索求解：  
但是这题也可以高效地在解空间中搜索，就是将解空间增大一个维度，以“数值+元素位置”作为解空间的两个维度，此时每个元素都是唯一的了，然后通过二分搜索找出第一个出现的数字K和最后一个出现的数字k，然后将他们的序号相减就得到数字K在数组中出现的次数。


```cpp
class Solution
{
    /*二分查找 找到第一个K 和 最后一个K 二者位置相减*/
public:
    int GetNumberOfK(vector<int> E ,int k)
    {
        if(E.empty())
        {
            return 0;
        }

        int RESULT, A, B, S;
        S = E.size();
        RESULT = 0;
        A = GetFirstIndex(E, k, 0, S - 1);
        B  = GetLastIndex(E, k, 0, S - 1);

        if(A > -1 && B > -1)
        {
            RESULT = B - A + 1;
            return RESULT;
        }
    }

    // 查找第一个的位置
    int GetFirstIndex(vector<int> &E, int L, int R, int k)
    {
        if(L > R)
        {
            return -1;
        }

        int mid;

        mid = L + (R - L) / 2;

        if(E[mid] > k)
        {
            R = mid - 1;
        }
        else if(E[mid] < k)
        {
            L = mid + 1;
        }
        else
        {
            if((mid > 0 && E[mid-1] != k) || mid == 0)
            {
                return mid;
            }
            else
            {
                R = mid - 1;
            }
        }

        return GetFirstIndex(E, k, L, R);
    }

    int GetLastIndex(vector<int> &E, int L, int R, int k)
    {
        if(L > R)
        {
            return -1;
        }

        int mid;
        mid = (L + R) / 2;

        if(E[mid] > k)
        {
            R = mid - 1;
        }
        else if(E[mid] < k)
        {
            L = mid + 1;
        }
        else
        {
            if((mid>0 && E[mid+1] !=k) || mid == R)
            {
                return mid;
            }
            else
            {
                L = mid +1;
            }
        }

        return GetLastIndex(E,k,low,R);
    }
};
```

#### 040 数组中只出现一次的数字
题目描述

一个整型数组里除了两个数字之外，其他的数字都出现了两次。请写程序找出这两个只出现一次的数字。  

> 样例输入  
2 4 3 6 3 2 5 5

> 样例输出  
4 6

解题思路：  
此题是一道搜索问题，但是此题根数字排序无关只和数字出现次数有关。并且只有两个元素只出现一次，其他元素都出现了两次。这样的出现次数应该及时联系到与“两个相同元素相抵”有关的算术运算。  
 * 全局计数相抵：即全局遍历整个数组，相同元素则计数加1，不同则计数减1，计数为0时换成下一个元素进行计数。这种方法在问题“求出现次数超过数组一半大小的元素”中使用到。  

但是本题如果使用全局计数相抵相关的方法，其时间复杂度依然是O(n^2)，因为需要对每个元素进行全局遍历，才能确定它是不是只出现一次。  

* 异或相同元素结果为0：因为相同元素的异或结果为0，所以把数组中的元素一起异或得到的结果一定不为0，因为存在两个只出现一次的元素。然后根据bit位找到bit值为1的最高位元素，根据这个位置是否为1可以把数组分成两部分。然后再对这两部分分别计算异或，可想而知这两个结果就是只出现一次的两个数字。  
ps: 找xor中最后一个1的位置的时候，可以用(XOR & (-XOR))

```cpp
class Solution
{
public:
    #define INT_SIZE (sizeof(int) * 8)

    #define IS_BIT(number, index) (((number) & (1 << (index))) >>index)

    void FindNumsAppearOnce(vector<int> array, int *num1, int *num2)
    {
        *num1 = *num2 = 0;
        if(array.size( ) < 2)
        {
            return ;
        }
        int XOR = array[0];
        for(int i = 1; i < array.size( ); i++)
        {
            XOR ^= array[i];
        }

        ///  查找到1的位置
        int flag = XOR & (-XOR);
        *num1 = *num2 = XOR;// 也可以等于XOR
        for(int i = 0; i < array.size( ); i++)
        {
            if((array[i] & flag) == flag)
            {
                *num1 ^= array[i];
            }
            else
            {
                *num2 ^= array[i];
            }
        }
    }
};
```
#### *051 数组中重复的数字

**题目描述**  
在一个长度为n的数组里的所有数字都在0到n-1的范围内。数组中某些数字是重复的，但不知道有几个数字是重复的。也不知道每个数字重复几次。请找出数组中任意一个重复的数字。例如，如果输入长度为7的数组{2,3,1,0,2,5,3}，那么对应的输出是重复的数字2或者3。  

> 样例输入  
2, 3, 1, 0, 2, 5, 3  
2, 1, 3, 1, 4  

> 样例输出  
2  
1


解题思路：  
本题最简单的解法就是为每个元素遍历整个数组也就是遍历整个解空间。  

缩小解空间：如果再将元素排序后在进行搜索，，那么可以将每个元素搜索时涉及到的解空间大小缩小到其元素相邻的右边一个元素。

再降低时间复杂度：因为排序最好的时间复杂度只能到O(nlogn),所以本题如果还想提高时间复杂度，那么可以往hashset辅助查找。也就是说我们可以从前到后构造一个unique set，每当有元素被添加到set时，需要查找是否已经存在此元素，若存在则说明重复。

```cpp
class Solution
{
public:
    bool CheckValidity(int *numbers, int length)
    {
      //  输入数据不合法
      if(numbers == NULL || length <= 0)
      {
        return false;
      }

      //  元素必须在[0, n-1]的范围
      for(int i = 0; i < length; i++)
      {
        if(numbers[i] < 0 || numbers[i] > length - 1)
        {
          return false;
        }
      }

      return true;
    }
    // Parameters:
    //        numbers:     an array of integers
    //        length:      the length of array numbers
    //        duplication: (Output) the duplicated number in the array number
    // Return value:       true if the input is valid, and there are some duplications in the array number
    //                     otherwise false
    bool duplicate(int numbers[], int length, int* duplication)
    {
        *duplication = -1;

        if(CheckValidity(numbers, length) == false)
        {
            return false;
        }

        set<int> s;
        bool isDup;
        isDup = false;
        for(int i = 0; i < length; i++)
        {
            if(s.count(numbers[i]) == 1)  // 如果当前元素已经存在set中
            {
                isDup = true;
                *duplication = numbers[i];
                break;
            }
            s.insert(numbers[i]);

        }

        return isDup;
    }
};
```


#### 052 构建乘积数组
**题目描述**

给定一个数组A[0,1,...,n-1],请构建一个数组B[0,1,...,n-1],其中B中的元素B[i]=A[0]A[1]...A[i-1]A[i+1]...A[n-1]。不能使用除法。
> 样例输入  
[1, 2, 3, 4, 5]

>样例输出  
[120, 60, 40, 30, 24]

* 解法1：  
这个解法就是利用解的叠加性，简化计算过程。

<分析>：  
解释下代码，设有数组大小为5。  
对于第一个for循环  
第一步：b[0] = 1;  
第二步：b[1] = b[0] * a[0] = a[0]  
第三步：b[2] = b[1] * a[1] = a[0] * a[1];  
第四步：b[3] = b[2] * a[2] = a[0] * a[1] * a[2];  
第五步：b[4] = b[3] * a[3] = a[0] * a[1] * a[2] * a[3];  
然后对于第二个for循环  
第一步  
temp *= a[4] = a[4];  
b[3] = b[3] * temp = a[0] * a[1] * a[2] * a[4];  
第二步  
temp *= a[3] = a[4] * a[3];  
b[2] = b[2] * temp = a[0] * a[1] * a[4] * a[3];  
第三步  
temp *= a[2] = a[4] * a[3] * a[2];  
b[1] = b[1] * temp = a[0] * a[4] * a[3] * a[2];  
第四步  
temp *= a[1] = a[4] * a[3] * a[2] * a[1];  
b[0] = b[0] * temp = a[4] * a[3] * a[2] * a[1];  
由此可以看出从b[4]到b[0]均已经得到正确计算。  

```cpp
class Solution {
public:
  vector<int> multiply(const vector<int>& E) {
      vector<int> vec;
      int sz=E.size();
      if(sz==0)
        return vec;
      vec.push_back(1);
      for(int i=0;i<sz-1;i++)
        vec.push_back(vec.back()*E[i]);
      int tmp=1;
      for(int i=sz-1;i>=0;i--)
      {
        vec[i]=vec[i]*tmp;
        tmp=tmp*E[i];
      }
      return vec;
  }
};
```

* **解法2**：
B[i]的值可以看作下图的矩阵中每行的乘积。  
下三角用连乘可以很容求得，上三角，从下向上也是连乘。  
因此我们的思路就很清晰了，先算下三角中的连乘，即我们先算出B[i]中的一部分，然后倒过来按上三角中的分布规律，把另一部分也乘进去。


```cpp
public class Solution {
    public int[] multiply(int[] A) {
        int length = A.length;
        int[] B = new int[length];
        if(length != 0 ){
            B[0] = 1;
            //计算下三角连乘
            for(int i = 1; i < length; i++){
                B[i] = B[i-1] * A[i-1];
            }
            int temp = 1;
            //计算上三角
            for(int j = length-2; j >= 0; j--){
                temp *= A[j+1];
                B[j] *= temp;
            }
        }
        return B;
    }
}
```

---

数组和DP

#### Climbing Stairs 爬梯子问题

解题思路：  
假设梯子有n层，那么如何爬到第n层呢，因为每次只能爬1或2步，那么爬到第n层的方法要么是从第n-1层一步上来的，要不就是从n-2层2步上来的，所以递推公式非常容易的就得出了：dp[n] = dp[n-1] + dp[n-2]。 由于斐波那契额数列的求解可以用递归，所以我最先尝试了递归，拿到OJ上运行，显示Time Limit Exceeded，就是说运行时间超了，因为递归计算了很多分支，效率很低，这里需要用动态规划 (Dynamic Programming) 来提高效率，代码如下：

```cpp
class Solution {
public:
    int climbStairs(int n) {
        if (n <= 1) return 1;
        vector<int> dp(n);
        dp[0] = 1; dp[1] = 2;
        for (int i = 2; i < n; ++i) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp.back();
    }
};
```

#### Min Cost Climbing Stairs 爬楼梯的最小损失

解题思路：  
还是用动态规划Dynamic Programming来做。这里我们定义一个一维的dp数组，其中dp[i]表示爬到第i层的最小cost，然后我们来想dp[i]如何推导。我们来思考一下如何才能到第i层呢？是不是只有两种可能性，一个是从第i-2层上直接跳上来，一个是从第i-1层上跳上来。不会再有别的方法，所以我们的dp[i]只和前两层有关系，所以可以写做如下：  

dp[i] = min(dp[i- 2] + cost[i - 2], dp[i - 1] + cost[i - 1])  

最后我们返回最后一个数字dp[n]即可，参见代码如下：  

```cpp
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        vector<int> dp(n + 1, 0);
        for (int i = 2; i < n + 1; ++i) {
            dp[i] = min(dp[i- 2] + cost[i - 2], dp[i - 1] + cost[i - 1]);
        }
        return dp.back();
    }
};
```

####  Longest Increasing Subsequence 最长递增子序列 LIS

解题思路*：  
* 一种动态规划Dynamic Programming的解法，这种解法的时间复杂度为O(n2)，类似brute force的解法。
* 我们维护一个一维dp数组，其中dp[i]表示以nums[i]为结尾的最长递增子串的长度。
* 对于每一个nums[i]，我们从第一个数再搜索到i，如果发现某个数小于nums[i]，我们更新dp[i]，更新方法为dp[i] = max(dp[i], dp[j] + 1)，即比较当前dp[i]的值和那个小于num[i]的数的dp值加1的大小，我们就这样不断的更新dp数组，到最后dp数组中最大的值就是我们要返回的LIS的长度，参见代码如下：

```cpp
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> dp(nums.size(), 1);
        int res = 0;
        for (int i = 0; i < nums.size(); ++i) {
            for (int j = 0; j < i; ++j) {
                if (nums[i] > nums[j]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            res = max(res, dp[i]);
        }
        return res;
    }
};
```

下面我们来看一种优化时间复杂度到O(nlgn)的解法，这里用到了二分查找法，所以才能加快运行时间哇。思路是，我们先建立一个数组ends，把首元素放进去，然后比较之后的元素，如果遍历到的新元素比ends数组中的首元素小的话，替换首元素为此新元素，如果遍历到的新元素比ends数组中的末尾元素还大的话，将此新元素添加到ends数组末尾(注意不覆盖原末尾元素)。如果遍历到的新元素比ends数组首元素大，比尾元素小时，此时用二分查找法找到第一个不小于此新元素的位置，覆盖掉位置的原来的数字，以此类推直至遍历完整个nums数组，此时ends数组的长度就是我们要求的LIS的长度，特别注意的是ends数组的值可能不是一个真实的LIS，比如若输入数组nums为{4, 2， 4， 5， 3， 7}，那么算完后的ends数组为{2， 3， 5， 7}，可以发现它不是一个原数组的LIS，只是长度相等而已，千万要注意这点。参见代码如下：

```cpp
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        if (nums.empty()) return 0;
        vector<int> ends{nums[0]};
        for (auto a : nums) {
            if (a < ends[0]) ends[0] = a;
            else if (a > ends.back()) ends.push_back(a);
            else {
                int left = 0, right = ends.size();
                while (left < right) {
                    int mid = left + (right - left) / 2;
                    if (ends[mid] < a) left = mid + 1;
                    else right = mid;
                }
                ends[right] = a;
            }
        }
        return ends.size();
    }
};
```


#### 674. Longest Continuous Increasing Subsequence(最长连续递增子序列LCIS)

解题思路*：  
* 由于有了连续这个条件，跟之前那道Number of Longest Increasing Subsequence比起来，其实难度就降低了很多。
* 我们可以使用一个计数器，如果遇到大的数字，计数器自增1；如果是一个小的数字，则计数器重置为1。
* 我们用一个变量cur来表示前一个数字，初始化为整型最大值，当前遍历到的数字num就和cur比较就行了，每次用cnt来更新结果res，参见代码如下：

```cpp
class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        int res = 0, cnt = 0, cur = INT_MAX;
        for (int num : nums) {
            if (num > cur) ++cnt;
            else cnt = 1;
            res = max(res, cnt);
            cur = num;
        }
        return res;
    }
};
```

### 子数组的和的相关问题
计算子数组之和的常用方法应该是建立累加数组，然后我们可以快速计算出任意一个长度为k的子数组，用来更新结果res。

#### Maximum Average Subarray I 子数组的最大平均值

```cpp
class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> sums = nums;
        for (int i = 1; i < n; ++i) {
            sums[i] = sums[i - 1] + nums[i];
        }
        double mx = sums[k - 1];
        for (int i = k; i < n; ++i) {
            mx = max(mx, (double)sums[i] - sums[i - k]);
        }
        return mx / k;
    }
};
```

#### Maximum Product Subarray 求最大子数组乘积

解题思路：  
* 这道题最直接的方法就是用DP来做，而且要用两个dp数组，其中f[i]表示子数组[0, i]范围内的最大子数组乘积，g[i]表示子数组[0, i]范围内的最小子数组乘积，初始化时f[0]和g[0]都初始化为nums[0]，其余都初始化为0。
* 那么从数组的第二个数字开始遍历，那么此时的最大值和最小值只会在这三个数字之间产生，即f[i-1]*nums[i]，g[i-1]*nums[i]，和nums[i]。所以我们用三者中的最大值来更新f[i]，用最小值来更新g[i]，然后用f[i]来更新结果res即可，参见代码如下：

```cpp
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int res = nums[0], n = nums.size();
        vector<int> f(n, 0), g(n, 0);
        f[0] = nums[0];
        g[0] = nums[0];
        for (int i = 1; i < n; ++i) {
            f[i] = max(max(f[i - 1] * nums[i], g[i - 1] * nums[i]), nums[i]);
            g[i] = min(min(f[i - 1] * nums[i], g[i - 1] * nums[i]), nums[i]);
            res = max(res, f[i]);
        }
        return res;
    }
};
```


### 数组排列组合+DFS

#### 79. Word Search

解题思路*：  
这道题是典型的深度优先遍历DFS的应用，原二维数组就像是一个迷宫，可以上下左右四个方向行走，我们以二维数组中每一个数都作为起点和给定字符串做匹配，我们还需要一个和原数组等大小的visited数组，是bool型的，用来记录当前位置是否已经被访问过，因为题目要求一个cell只能被访问一次。如果二维数组board的当前字符和目标字符串word对应的字符相等，则对其上下左右四个邻字符分别调用DFS的递归函数，只要有一个返回true，那么就表示可以找到对应的字符串，否则就不能找到，具体看代码实现如下：

```cpp
class Solution {
public:
    bool exist(vector<vector<char> > &board, string word) {
        if (word.empty()) return true;
        if (board.empty() || board[0].empty()) return false;
        vector<vector<bool> > visited(board.size(), vector<bool>(board[0].size(), false));
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[i].size(); ++j) {
                if (search(board, word, 0, i, j, visited)) return true;
            }
        }
        return false;
    }
    bool search(vector<vector<char> > &board, string word, int idx, int i, int j, vector<vector<bool> > &visited) {
        if (idx == word.size()) return true;
        if (i < 0 || j < 0 || i >= board.size() || j >= board[0].size() || visited[i][j] || board[i][j] != word[idx]) return false;
        visited[i][j] = true;
        bool res = search(board, word, idx + 1, i - 1, j, visited)
                 || search(board, word, idx + 1, i + 1, j, visited)
                 || search(board, word, idx + 1, i, j - 1, visited)
                 || search(board, word, idx + 1, i, j + 1, visited);
        visited[i][j] = false;
        return res;
    }
};
```


#### Combinations 组合项
Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.  

For example,    
If n = 4 and k = 2, a solution is:    

[  
  [2,4],  
  [3,4],  
  [2,3],  
  [1,2],  
  [1,3],  
  [1,4],  
]  

解题思路：  
这道题让求1到n共n个数字里k个数的组合数的所有情况，还是要用深度优先搜索DFS来解，根据以往的经验，像这种要求出所有结果的集合，一般都是用DFS调用递归来解。那么我们建立一个保存最终结果的大集合res，还要定义一个保存每一个组合的小集合out，每次放一个数到out里，如果out里数个数到了k个，则把out保存到最终结果中，否则在下一层中继续调用递归。网友u010500263的博客里有一张图很好的说明了递归调用的顺序，请点击这里。根据上面分析，可写出代码如下：

```cpp
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> res;
        vector<int> out;
        helper(n, k, 1, out, res);
        return res;
    }
    void helper(int n, int k, int level, vector<int>& out, vector<vector<int>>& res) {
        if (out.size() == k) res.push_back(out);
        for (int i = level; i <= n; ++i) {
            out.push_back(i);
            helper(n, k, i + 1, out, res);
            out.pop_back();
        }
    }
};
```


####  Combination Sum 组合之和
For example, given candidate set 2,3,6,7 and target 7,   
A solution set is:   
[7]   
[2, 2, 3]   

解题思路：  
像这种结果要求返回所有符合要求解的题十有八九都是要利用到递归，而且解题的思路都大同小异，如果仔细研究这些题目发现都是一个套路，都是需要另写一个递归函数，这里我们新加入三个变量，start记录当前的递归到的下标，out为一个解，res保存所有已经得到的解，每次调用新的递归函数时，此时的target要减去当前数组的的数，具体看代码如下：

```cpp
class Solution {
public:
    vector<vector<int> > combinationSum(vector<int> &candidates,
                                        int target)
    {
        //递归相关辅助变量的声明
        vector<vector<int> > res;
        vector<int> out;

        //进入递归
        sort(candidates.begin(), candidates.end());
        dfs(candidates, target, 0, out, res);
        return res;
    }

    void dfs(vector<int> &E, int T, int start, vector<int> &out,
             vector<vector<int> > &res)
    {
        //出口1
        if(T < 0)
        {
            return;
        }
        //出口2
        else if(T == 0)
        {
            res.push_back(out);
            return;
        }
        else
        {
            //递归拆解过程
            //for循环和传递进dfs的start参数，一起定义了每趟递归可选择的数据集的范围
            //也就是每次搜索树分叉时可做的选择种类
            for (int i = start; i < E.size(); ++i)
            {
                out.push_back(E[i]);
                dfs(E, T-E[i], i, out, res);
                out.pop_back();
            }
        }
    }
};
```

#### Combination Sum II 组合之和之二
Given a collection of candidate numbers (C) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.  

Each number in C may only be used once in the combination.  

Note:  

All numbers (including target) will be positive integers.  
Elements in a combination (a1, a2, … , ak) must be in non-descending order. (ie, a1 ≤ a2 ≤ … ≤ ak).  
The solution set must not contain duplicate combinations.  


For example, given candidate set 10,1,2,7,6,1,5 and target 8,   
A solution set is:   
[1, 7]   
[1, 2, 5]   
[2, 6]   
[1, 1, 6]   

解题思路：  
这道题跟之前那道 Combination Sum 组合之和 本质没有区别，只需要改动一点点即可。
* 之前那道题给定数组中的数字可以重复使用，而这道题不能重复使用，只需要在之前的基础上修改两个地方即可，首先在递归的for循环里加上if (i > start && num[i] == num[i - 1]) continue; 这样可以防止res中出现重复项。
* 然后就在递归调用combinationSum2DFS里面的参数换成i+1，这样就不会重复使用数组中的数字了，代码如下：

```cpp
class Solution {
public:
    vector<vector<int> > combinationSum2(vector<int> &num, int target) {
        vector<vector<int> > res;
        vector<int> out;
        sort(num.begin(), num.end());
        combinationSum2DFS(num, target, 0, out, res);
        return res;
    }
    void combinationSum2DFS(vector<int> &num, int target, int start, vector<int> &out, vector<vector<int> > &res) {
        if (target < 0) return;
        else if (target == 0) res.push_back(out);
        else {
            for (int i = start; i < num.size(); ++i) {
                if (i > start && num[i] == num[i - 1]) continue;
                out.push_back(num[i]);
                combinationSum2DFS(num, target - num[i], i + 1, out, res);
                out.pop_back();
            }
        }
    }
};
```


#### Combination Sum III 组合之和之三
Find all possible combinations of k numbers that add up to a number n, given that only numbers from 1 to 9 can be used and each combination should be a unique set of numbers.  

Ensure that numbers within the set are sorted in ascending order.  


Example 1:  

Input: k = 3, n = 7  

Output:  

[[1,2,4]]  

Example 2:  

Input: k = 3, n = 9  

Output:  

[[1,2,6], [1,3,5], [2,3,4]]  
Credits:  
Special thanks to @mithmatt for adding this problem and creating all test cases.  

解题思路：  
这道题题是组合之和系列的第三道题，跟之前两道Combination Sum 组合之和，Combination Sum II 组合之和之二都不太一样，那两道的联系比较紧密，变化不大，而这道跟它们最显著的不同就是这道题的个数是固定的，为k。个人认为这道题跟那道Combinations 组合项更相似一些，但是那道题只是排序，对k个数字之和又没有要求。所以实际上这道题是它们的综合体，两者杂糅到一起就是这道题的解法了。
* n是k个数字之和，如果n小于0，则直接返回，如果n正好等于0，而且此时out中数字的个数正好为k，说明此时是一个正确解，将其存入结果res中，具体实现参见代码入下：

```cpp
class Solution {
public:
    vector<vector<int> > combinationSum3(int k, int n) {
        vector<vector<int> > res;
        vector<int> out;
        combinationSum3DFS(k, n, 1, out, res);
        return res;
    }
    void combinationSum3DFS(int k, int n, int level, vector<int> &out, vector<vector<int> > &res) {
        if (n < 0) return;
        if (n == 0 && out.size() == k) res.push_back(out);
        for (int i = level; i <= 9; ++i) {
            out.push_back(i);
            combinationSum3DFS(k, n - i, i + 1, out, res);
            out.pop_back();
        }
    }
};
```

####  Permutations 全排列
Given a collection of numbers, return all possible permutations.  

For example,  
[1,2,3] have the following permutations:  
[1,2,3], [1,3,2], [2,1,3], [2,3,1], [3,1,2], and [3,2,1].  

解题思路：  
这道题是求全排列问题，给的输入数组没有重复项，这跟之前的那道 Combinations 组合项 和类似，解法基本相同，但是不同点在于那道不同的数字顺序只算一种，是一道典型的组合题，而此题是求全排列问题，还是用递归DFS来求解。这里我们需要用到一个visited数组来标记某个数字是否访问过，然后在DFS递归函数从的循环应从头开始，而不是从level开始，这是和 Combinations 组合项 不同的地方，其余思路大体相同，代码如下：

```cpp
class Solution {
public:
    vector<vector<int> > permute(vector<int> &num) {
        vector<vector<int> > res;
        vector<int> out;
        vector<int> visited(num.size(), 0);
        permuteDFS(num, 0, visited, out, res);
        return res;
    }
    void permuteDFS(vector<int> &num, int level, vector<int> &visited, vector<int> &out, vector<vector<int> > &res) {
        if (level == num.size()) res.push_back(out);
        else {
            for (int i = 0; i < num.size(); ++i) {
                if (visited[i] == 0) {
                    visited[i] = 1;
                    out.push_back(num[i]);
                    permuteDFS(num, level + 1, visited, out, res);
                    out.pop_back();
                    visited[i] = 0;
                }
            }
        }
    }
};
```

#### Permutations II 全排列之二
Given a collection of numbers that might contain duplicates, return all possible unique permutations.  

For example,  
[1,1,2] have the following unique permutations:  
[1,1,2], [1,2,1], and [2,1,1].  

解题思路：  
这道题是之前那道 Permutations 全排列的延伸，由于输入数组有可能出现重复数字，如果按照之前的算法运算，会有重复排列产生，我们要避免重复的产生，在递归函数中要判断前面一个数和当前的数是否相等，如果相等，前面的数必须已经使用了，即对应的visited中的值为1，当前的数字才能使用，否则需要跳过，这样就不会产生重复排列了，代码如下：

```cpp
class Solution {
public:
    vector<vector<int> > permuteUnique(vector<int> &num) {
        vector<vector<int> > res;
        vector<int> out;
        vector<int> visited(num.size(), 0);
        sort(num.begin(), num.end());
        permuteUniqueDFS(num, 0, visited, out, res);
        return res;
    }
    void permuteUniqueDFS(vector<int> &num, int level, vector<int> &visited, vector<int> &out, vector<vector<int> > &res) {
        if (level >= num.size()) res.push_back(out);
        else {
            for (int i = 0; i < num.size(); ++i) {
                if (visited[i] == 0) {
                    if (i > 0 && num[i] == num[i - 1] && visited[i - 1] == 0) continue;
                    visited[i] = 1;
                    out.push_back(num[i]);
                    permuteUniqueDFS(num, level + 1, visited, out, res);
                    out.pop_back();
                    visited[i] = 0;
                }
            }
        }
    }
};
```

#### Next Permutation 下一个排列
这道题让我们求下一个排列顺序，有题目中给的例子可以看出来，如果给定数组是降序，则说明是全排列的最后一种情况，则下一个排列就是最初始情况，可以参见之前的博客 Permutations 全排列。我们再来看下面一个例子，有如下的一个数组  

1　　2　　7　　4　　3　　1    

下一个排列为：  

1　　3　　1　　2　　4　　7  

那么是如何得到的呢，我们通过观察原数组可以发现，如果从末尾往前看，数字逐渐变大，到了2时才减小的，然后我们再从后往前找第一个比2大的数字，是3，那么我们交换2和3，再把此时3后面的所有数字转置一下即可，步骤如下：  

1　　2　　7　　4　　3　　1  

1　　2　　7　　4　　3　　1  

1　　3　　7　　4　　2　　1  

1　　3　　1　　2　　4　　7  

```cpp
class Solution {
public:
    void nextPermutation(vector<int> &num) {
        int i, j, n = num.size();
        for (i = n - 2; i >= 0; --i) {
            if (num[i + 1] > num[i]) {
                for (j = n - 1; j > i; --j) {
                    if (num[j] > num[i]) break;
                }
                swap(num[i], num[j]);
                reverse(num.begin() + i + 1, num.end());
                return;
            }
        }
        reverse(num.begin(), num.end());
    }
};
```




####  Subsets 子集合
Given a set of distinct integers, S, return all possible subsets.  

Note:  

Elements in a subset must be in non-descending order.  
The solution set must not contain duplicate subsets.  


For example,  
If S = [1,2,3], a solution is:  

[    
  [3],  
  [1],  
  [2],  
  [1,2,3],  
  [1,3],  
  [2,3],  
  [1,2],  
  []  
]  

解题思路：  
这道求子集合的问题，由于其要列出所有结果。
* 下面来看递归的解法，相当于一种深度优先搜索，参见网友JustDoIt的博客，由于原集合每一个数字只有两种状态，要么存在，要么不存在，那么在构造子集时就有选择和不选择两种情况，所以可以构造一棵二叉树，左子树表示选择该层处理的节点，右子树表示不选择，最终的叶节点就是所有子集合，树的结构如下：

```cpp
// Recursion
class Solution {
public:
    vector<vector<int> > subsets(vector<int> &S) {
        vector<vector<int> > res;
        vector<int> out;
        sort(S.begin(), S.end());
        getSubsets(S, 0, out, res);
        return res;
    }
    void getSubsets(vector<int> &S, int pos, vector<int> &out, vector<vector<int> > &res) {
        res.push_back(out);
        for (int i = pos; i < S.size(); ++i) {
            out.push_back(S[i]);
            getSubsets(S, i + 1, out, res);
            out.pop_back();
        }
    }
};
```


####  Subsets II 子集合之二
Given a collection of integers that might contain duplicates, S, return all possible subsets.  

Note:  

Elements in a subset must be in non-descending order.  
The solution set must not contain duplicate subsets.  


For example,  
If S = [1,2,2], a solution is:  

[  
  [2],  
  [1],  
  [1,2,2],  
  [2,2],  
  [1,2],  
  []  
]  

解题思路：  
对于递归的解法，根据之前 Subsets 子集合 里的构建树的方法，在处理到第二个2时，由于前面已经处理了一次2，这次我们只在添加过2的[2] 和 [1 2]后面添加2，其他的都不添加。  
代码只需在原有的基础上增加一句话，while (S[i] == S[i + 1]) ++i; 这句话的作用是跳过树中为X的叶节点，因为它们是重复的子集，应被抛弃。代码如下：

```cpp
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int> &S) {
        if (S.empty()) return {};
        vector<vector<int>> res;
        vector<int> out;
        sort(S.begin(), S.end());
        getSubsets(S, 0, out, res);
        return res;
    }
    void getSubsets(vector<int> &S, int pos, vector<int> &out, vector<vector<int>> &res) {
        res.push_back(out);
        for (int i = pos; i < S.size(); ++i) {
            out.push_back(S[i]);
            getSubsets(S, i + 1, out, res);
            out.pop_back();
            while (i + 1 < S.size() && S[i] == S[i + 1]) ++i;
        }
    }
};
```

### 滑动窗口计算数组的子数组
解题思路：  
这道题给了我们一个数组，让我们求最短的无序连续子数组，根据题目中的例子也不难分析出来是让我们找出数组中的无序的部分。
* 那么我最开始的想法就是要确定无序子数组的起始和结束位置，这样就能知道子数组的长度了。
    * 所以我们用一个变量start来记录起始位置，然后我们开始遍历数组，当我们发现某个数字比其前面的数字要小的时候，说明此时数组不再有序，所以我们要将此数字向前移动，移到其应该在的地方；
    * 我们用另一个变量j来记录移动到的位置，然后我们考虑要不要用这个位置来更新start的值，当start还是初始值-1时，肯定要更新，因为这是出现的第一个无序的地方，还有就是如果当前位置小于start也要更新，这说明此时的无序数组比之前的更长了。
* 我们举个例子来说明，比如数组[1,3,5,4,2]，第一个无序的地方是数字4，它移动到的正确位置是坐标2，此时start更新为2，然后下一个无序的地方是数字2，它的正确位置是坐标1，所以此时start应更新为1，这样每次用i - start + 1来更新结果res时才能得到正确的结果，参见代码如下：
```cpp
class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        int res = 0, start = -1, n = nums.size();
        for (int i = 1; i < n; ++i) {
            if (nums[i] < nums[i - 1]) {
                int j = i;
                while (j > 0 && nums[j] < nums[j - 1]) {
                    swap(nums[j], nums[j - 1]);
                    --j;
                }
                if (start == -1 || start > j) start = j;
                res = max(res, i - start + 1);
            }
        }
        return res;
    }
};
```

## 堆相关题目

常见题型有：
* K-th问题: 最大kth应该使用最小堆构造、最小kth应该使用最大堆构造，c++使用priority_queue实现最大最小堆；

* hash-set 应该使用 unordered_map；

---

### k-th问题：

#### 215. Kth Largest Element in an Array
解题思路：  
利用了priority_queue的自动排序的特性，跟上面的解法思路上没有什么区别，当然我们也可以换成multiset来做，一个道理，参见代码如下：
```cpp
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int> q(nums.begin(), nums.end());
        for (int i = 0; i < k - 1; ++i) {
            q.pop();
        }
        return q.top();
    }
};
```

#### 378. Kth Smallest Element in a Sorted Matrix
解题思路：  
* kth最小问题，可以使用容积为k的小顶堆实现，也可以使用容积为k的大顶堆，每次进来第k+1个数时，去掉堆顶元素，这样遍历完留下来的堆顶元素必然是第k小的元素；
* 我们使用一个最大堆，然后遍历数组每一个元素，将其加入堆，根据最大堆的性质，大的元素会排到最前面，然后我们看当前堆中的元素个数是否大于k，大于的话就将首元素去掉，循环结束后我们返回堆中的首元素即为所求:
```cpp
class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k)
    {
        priority_queue<int> q;
        for (int i = 0; i < matrix.size(); ++i)
        {
            for (int j = 0; j < matrix[i].size(); ++j)
            {
                q.emplace(matrix[i][j]);
                if (q.size() > k)
                {
                   q.pop();
                }
            }
        }
        return q.top();
    }
};
```

### Top k频率问题：（hash表 + pair + heap）

#### 347. Top K Frequent Elements
解题思路：  
这道题给了我们一个数组，让我们统计前k个高频的数字，那么对于这类的统计数字的问题，首先应该考虑用哈希表来做，建立数字和其出现次数的映射，然后再按照出现次数进行排序。我们可以用堆排序来做，使用一个最大堆来按照映射次数从大到小排列，在C++中使用priority_queue来实现，默认是最大堆，参见代码如下：
```cpp
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        //构建hashmap和最大堆priority_queue
        unordered_map<int, int> m;
        priority_queue<pair<int, int>> q;
        vector<int> res;
        for (auto a : nums)
        {
            ++m[a];
        }
        for (auto it : m)
        {
            q.push({it.second, it.first});
        }
        for (int i = 0; i < k; ++i)
        {
            res.push_back(q.top().second); q.pop();
        }
        return res;
    }
};
```

#### 692. Top K Frequent Words
解题思路：  
这道题让我们求前K个高频词，跟之前那道题Top K Frequent Elements极其类似，换了个数据类型就又是一道新题。唯一的不同就是之前那道题对于出现频率相同的数字，没有顺序要求。而这道题对于出现频率相同的单词，需要按照字母顺序来排。但是解法都一样，还是用最大堆和桶排序的方法。首先来看最大堆的方法，思路是先建立每个单词和其出现次数之间的映射，然后把单词和频率的pair放进最大堆，如果没有相同频率的单词排序要求，我们完全可以让频率当作pair的第一项，这样priority_queue默认是以pair的第一项为key进行从大到小的排序，而当第一项相等时，又会以第二项由大到小进行排序，这样就与题目要求的相同频率的单词要按字母顺序排列不相符，当然我们可以在存入结果res时对相同频率的词进行重新排序处理，也可以对priority_queue的排序机制进行自定义，这里我们采用第二种方法，我们自定义排序机制，我们让a.second > b.second，让小频率的词在第一位，然后当a.second == b.second时，我们让a.first < b.first，这是让字母顺序大的排在前面（这里博主需要强调一点的是，priority_queue的排序机制的写法和vector的sort的排序机制的写法正好顺序相反，同样的写法，用在sort里面就是频率小的在前面，不信的话可以自己试一下）。定义好最小堆后，我们首先统计单词的出现频率，然后组成pair排序最小堆之中，我们只保存k个pair，超过了就把队首的pair移除队列，最后我们把单词放入结果res中即可，参见代码如下：

```cpp
class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        vector<string> res(k);
        unordered_map<string, int> freq;
        auto cmp = [](pair<string, int>& a, pair<string, int>& b) {
            return a.second > b.second || (a.second == b.second && a.first < b.first);
        };
        priority_queue<pair<string, int>, vector<pair<string, int>>, decltype(cmp) > q(cmp);
        for (auto word : words) ++freq[word];
        for (auto f : freq) {
            q.push(f);
            if (q.size() > k) q.pop();
        }
        for (int i = res.size() - 1; i >= 0; --i) {
            res[i] = q.top().first; q.pop();
        }
        return res;
    }
};
```

#### 451. Sort Characters By Frequency
* 给一个字符串按照字符出现的频率来排序，那么毫无疑问肯定要先统计出每个字符出现的个数。
* 我们可以利用优先队列的自动排序的特点，先使用hashmap循环记录每个单词的出现次数。
* 然后把个数和字符组成pair放到优先队列里排好序后，再取出来组成结果res即可，参见代码如下：

```cpp
class Solution {
public:
    string frequencySort(string s) {
        string res = "";
        priority_queue<pair<int, char>> q;
        unordered_map<char, int> m;
        for (char c : s)
        {
          ++m[c];
        }
        for (auto a : m)
        {
          q.push({a.second, a.first});
        }
        while (!q.empty())
        {
            auto t = q.top();
            q.pop();
            res.append(t.first, t.second);
        }
        return res;
    }
};
```

## Hash Table相关题目：

* Hash经常和需要频繁查找的问题相关联：
  * X-sum问题：如two sum, 3 sum, 4 sum; 这些问题需要先遍历一遍数组构造hash表，最后通过快速查找得到结果
* Hash和String相关题目；


#### 1. Two Sum
解题思路：  
O(n)的算法来实现，整个实现步骤为：
* 先遍历一遍数组，建立map数据。
* 然后再遍历一遍，开始查找，找到则记录index。代码如下：
```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        //声明辅助hash表和记录结果的数组
        unordered_map<int, int> m;
        vector<int> res;
        //记录hash表：<value, pos>
        for (int i = 0; i < nums.size(); ++i)
        {
            m[nums[i]] = i;
        }
        //根据剩余值t在hash表中查找
        for (int i = 0; i < nums.size(); ++i)
        {
            int t = target - nums[i];
            if (m.count(t) && m[t] != i)
            {
                res.push_back(i);
                res.push_back(m[t]);
                break;
            }
        }
        return res;
    }
};
```

#### 599. Minimum Index Sum of Two Lists
解题思路：  
这道题给了我们两个字符串数组，让我们找到坐标位置之和最小的相同的字符串。
* 那么对于这种数组项和其坐标之间关系的题，最先考虑到的就是要建立数据和其位置坐标之间的映射。我们建立list1的值和坐标的之间的映射，然后遍历list2.
* 如果当前遍历到的字符串在list1中也出现了，那么我们计算两个的坐标之和，如果跟我们维护的最小坐标和mn相同，那么将这个字符串加入结果res中，如果比mn小，那么mn更新为这个较小值，然后将结果res清空并加入这个字符串，参见代码如下：
```cpp
class Solution {
public:
    vector<string> findRestaurant(vector<string>& list1, vector<string>& list2) {
        vector<string> res;
        unordered_map<string, int> m;
        int mn = INT_MAX, n1 = list1.size(), n2 = list2.size();
        for (int i = 0; i < n1; ++i) m[list1[i]] = i;
        for (int i = 0; i < n2; ++i) {
            if (m.count(list2[i])) {
                int sum = i + m[list2[i]];
                if (sum == mn) res.push_back(list2[i]);
                else if (sum < mn) {
                    mn = sum;
                    res = {list2[i]};
                }
            }
        }
        return res;
    }
};
```


#### 500. Keyboard Row
这道题给了我们一些单词，问哪些单词可以由键盘上的一行中的键符打出来，难度其实并不大。
* 首先我们把键盘的三行字符分别保存到三个set中.
* 然后遍历每个单词中的每个字符，分别看当前字符是否在三个集合中，如果在，对应的标识变量变为1，我们统计三个标识变量之和就知道有几个集合参与其中了，参见代码如下：

```cpp
class Solution {
public:
    vector<string> findWords(vector<string>& words) {
        vector<string> res;
        unordered_set<char> row1{'q','w','e','r','t','y','u','i','o','p'};
        unordered_set<char> row2{'a','s','d','f','g','h','j','k','l'};
        unordered_set<char> row3{'z','x','c','v','b','n','m'};
        for (string word : words) {
            //访问字符串中每个单词的每个英文字母在三个set的哪个；
            int one = 0, two = 0, three = 0;
            for (char c : word) {
                if (c < 'a') c += 32;
                if (row1.count(c)) one = 1;
                if (row2.count(c)) two = 1;
                if (row3.count(c)) three = 1;
                if (one + two + three > 1) break;
            }
            if (one + two + three == 1)
            {
              res.push_back(word);
            }
        }
        return res;
    }
};
```

#### 575. Distribute Candies
这道题给我们一堆糖，每种糖的个数不定，分给两个人，让我们求其中一个人能拿到的最大的糖的种类数。
* 那么我们想，如果总共有n个糖，平均分给两个人，每人得到n/2块糖。
* （先平均分，然后让一个人从另一个人的n/2块中拿糖）那么能拿到的最大的糖的种类数也就是n/2种，不可能再多，只可能再少。
* 那么我们要做的就是统计出总共的糖的种类数，如果糖的种类数小于n/2，说明拿不到n/2种糖，最多能拿到的种类数数就是当前糖的总种类数，明白了这点就很容易了，我们利用集合set的自动去重复特性来求出糖的种类数，然后跟n/2比较，取二者之中的较小值返回即可，参加代码如：

```cpp
class Solution {
public:
    int distributeCandies(vector<int>& candies) {
        unordered_set<int> s;
        for (int candy : candies) s.insert(candy);
        return min(s.size(), candies.size() / 2);
    }
};
```

#### 645. Set Mismatch(这题比较偏记录额外信息，而不偏频繁查找。所以应该用记录数组而不是HashTable)
解题思路：  
* 这道题给了我们一个长度为n的数组，说里面的数字是从1到n，但是有一个数字重复出现了一次，从而造成了另一个数字的缺失，让我们找出重复的数字和缺失的数字。
* 使用另外一个数组统计每个数字出现的次数了，然后再遍历次数数组，如果某个数字出现了两次就是重复数，如果出现了0次，就是缺失数，参见代码如下：

```cpp
class Solution {
public:
    vector<int> findErrorNums(vector<int>& nums)
    {
        //声明两个辅助数组：
        //1.cnt记录每个数字的出现次数cnt[i]=times
        //2.res记录重复数字和缺失数字
        vector<int> res(2, 0), cnt(nums.size(), 0);
        for (int num : nums)
        {
          ++cnt[num - 1];
        }
        for (int i = 0; i < cnt.size(); ++i)
        {
            if (res[0] != 0 && res[1] != 0)
            {
               return res;
            }
            if (cnt[i] == 2)
            {
              res[0] = i + 1;
            }
            else if (cnt[i] == 0)
            {
               res[1] = i + 1;
            }
        }
        return res;
    }
};
```

#### 290. Word Pattern

解题思路：  
这道题给我们一个模式字符串，又给我们一个单词字符串，让我们求单词字符串中单词出现的规律是否符合模式字符串中的规律。
* 用哈希表来做，建立模式字符串中每个字符和单词字符串每个单词之间的映射，而且这种映射必须是一对一关系的，不能'a‘和’b'同时对应‘dog'。
* 所以我们在碰到一个新字符时，首先检查其是否在哈希表中出现。
  * 若出现，其映射的单词若不是此时对应的单词，则返回false。
  * 如果没有在哈希表中出现，我们还要遍历一遍哈希表，看新遇到的单词是否已经是哈希表中的映射。
    * 如果没有，再跟新遇到的字符建立映射，参见代码如下：
```cpp
class Solution {
public:
    bool wordPattern(string pattern, string str) {
        //使用<char, string>映射字符串中单词
        //使用istringstream读取单词
        unordered_map<char, string> m;
        istringstream in(str);
        int i = 0;
        for (string word; in >> word; ++i) {
            if (m.find(pattern[i]) != m.end()) {
                if (m[pattern[i]] != word) return false;
            } else {
                for (unordered_map<char, string>::iterator it = m.begin(); it != m.end(); ++it) {
                    if (it->second == word) return false;
                }
                m[pattern[i]] = word;
            }
        }
        return i == pattern.size();
    }
};
```

---



### Hash和String相关题目


#### 387. First Unique Character in a String
解题思路：  
* 只要用哈希表建立每个字符和其出现次数的映射<字符char, 出现次数int>。
* 然后按顺序遍历字符串，找到第一个出现次数为1的字符，返回其位置即可，参见代码如下：


#### 30. Substring with Concatenation of All Words

解题思路：  
这道题让我们求串联所有单词的子串，就是说给定一个长字符串，再给定几个长度相同的单词，让我们找出串联给定所有单词的子串的起始位置，还是蛮有难度的一道题。这道题我们需要用到两个哈希表，第一个哈希表先把所有的单词存进去，然后从开头开始一个个遍历，停止条件为当剩余字符个数小于单词集里所有字符的长度。这时候我们需要定义第二个哈希表，然后每次找出给定单词长度的子串，看其是否在第一个哈希表里，如果没有，则break，如果有，则加入第二个哈希表，但相同的词只能出现一次，如果多了，也break。如果正好匹配完给定单词集里所有的单词，则把i存入结果中，具体参见代码如下：
```cpp
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> res;
        if (s.empty() || words.empty()) return res;
        int n = words.size(), m = words[0].size();
        unordered_map<string, int> m1;
        for (auto &a : words) ++m1[a];
        for (int i = 0; i <= (int)s.size() - n * m; ++i) {
            unordered_map<string, int> m2;
            int j = 0;
            for (j = 0; j < n; ++j) {
                string t = s.substr(i + j * m, m);
                if (m1.find(t) == m1.end()) break;
                ++m2[t];
                if (m2[t] > m1[t]) break;
            }
            if (j == n) res.push_back(i);
        }
        return res;
    }
};
```
