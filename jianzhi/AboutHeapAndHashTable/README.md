## 堆相关题目

常见题型有：
* K-th问题: 最大kth应该使用最小堆构造、最小kth应该使用最大堆构造，c++使用priority_queue实现最大最小堆；


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
