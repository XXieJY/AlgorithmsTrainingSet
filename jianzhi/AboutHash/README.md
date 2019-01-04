
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
