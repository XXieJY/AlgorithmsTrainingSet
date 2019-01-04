## 堆相关题目

常见题型有：
* K-th问题: 最大kth应该使用最小堆构造、最小kth应该使用最大堆构造，c++使用priority_queue实现最大最小堆；

* hash-set 应该使用 unordered_map；

---

## Problem 1.海量数据处理的 Top K大的数问题 from:http://www.cnblogs.com/xudong-bupt/archive/2013/03/20/2971262.html
* 解答：
  * 中心思想：使用小顶堆存放海量数据中Top k大的数。
  * 步骤：
    * 首先取海量数据中前k个元素，作为size=k的小顶堆的初始数据。
    * 然后从第i = k+1个元素开始，按顺序遍历一次所有的数据。
    * 如果 data[i]的值小于或等于小顶堆的根结点，则i++，然后继续遍历余下数据。
    * 如果 data[i]的值大于小顶堆的根结点，则用data[i]替代小顶堆根节点，然后调整一趟小顶堆，最后令i++，继续遍历余下数据。

```cpp
#include<stdio.h>
int n;  ///数字个数，n很大(n>10000)
int dui[10];
#define K 10    ///Top K,K的取值

void create_dui();　　///建堆
void UpToDown(int);　　///从上到下调整
int main()
{
    int i;
    int tmp;
    while(scanf("%d",&n)!=EOF)
    {
        for(i=1;i<=K;i++) ///先输入K个
            scanf("%d",&dui[i]);
        create_dui();  ///建小顶堆
        for(i=K+1;i<=n;i++)
        {
            scanf("%d",&tmp);
            if(tmp>dui[1])  ///只有大于根节点才处理
            {
                dui[1]=tmp;
                UpToDown(1);    ///向下调整堆
            }
        }
    }
    return 1;
}

void create_dui()
{
    int i;
    int pos=K/2;      ///从末尾数，第一个非叶节点的位置K/2
    for(i=pos;i>=1;i--)
        UpToDown(i);
}

void UpToDown(int i)
{
    int t1,t2,tmp,pos;
    t1=2*i; ///左孩子(存在的话)
    t2=t1+1;    ///右孩子(存在的话)
    if(t1>K)    ///无孩子节点
        return;
    else
    {
        if(t2>K)  ///只有左孩子
            pos=t1;
        else
            pos=dui[t1]>dui[t2]? t2:t1;

        if(dui[i]>dui[pos]) ///pos保存在子孩子中，数值较小者的位置
        {
            tmp=dui[i];dui[i]=dui[pos];dui[pos]=tmp;
            UpToDown(pos);
        }
    }
}
```




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
