## 排列组合的DFS
### 概念
* 排列和组合的区分：
  * 看问题是否和顺序有关。有关就是排列，无关就是组合。
  * 90%DFS的题, 要么是排列, 要么是组合。



### 回溯法+DFS/BFS题型：
LeetCode的：Permutaions, PermutationsII, Combination Sum, Conbination SumII;  
**这几题解法中的for循环，不仅是为了递归拆解出可能的解，同时也使用pop_back()在每层递归上
进行一定程度的回溯，这样结合才能解题**



### 例题

#### 39. Combination Sum（理解递归和DFS的优秀题目）
Given a set of candidate numbers (C) (without duplicates) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.

The same repeated number may be chosen from C unlimited number of times.

解题思路：  
**像这种结果要求返回所有符合要求解的题十有八九都是要利用到递归，而且解题的思路都大同小异。**
* 都是需要另写一个递归函数，这里我们新加入三个变量，start记录当前的递归到的下标，out为一个解，res保存所有已经得到的解，每次调用新的递归函数时，此时的target要减去当前数组的的数。
* **递归函数注意：递归接口的定义、出口的定义、递归拆解方式的思考。**  
具体看代码如下：

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

#### 从回溯的思路看LeetCode-Combination Sum:
```cpp
#include<iostream>  
#include<vector>  
#include<algorithm>  
using namespace std;  

void backTracking(vector<vector<int>> &res, vector<int> arr ,vector<int>candidate ,int start,int target )  
{  
    if (target == 0)//满足条件，输出结果  
    {  
        res.push_back(arr);  
        return;  
    }  
    for (int i = start; i < candidate.size(); i++)//枚举所有可能的路径  
    {  
        if (candidate[i] <= target)//满足界限函数和约束条件  
        {  
            arr.push_back(candidate[i]);  
            backTracking(res, arr, candidate, i, target - candidate[i]);  
            arr.pop_back();//回溯清理工作  
        }  
    }  
}  

int main()  
{  
    vector<int> candidate = { 2, 3, 6, 7 };  
    int target = 7;  
    vector<vector<int>> res;  
    vector<int> arr;  
    sort(candidate.begin(), candidate.end());  
    backTracking(res, arr, candidate, 0, target);  
    for (int i = 0; i < res.size(); i++)  
    {  
        for (int j = 0; j < res[i].size(); j++)  
        {  
            cout << res[i][j] << " ";  
        }  
        cout << endl;  
    }  
    return 0;  
}  
```


#### 40. Combination Sum II
Given a collection of candidate numbers (C) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.

Each number in C may only be used once in the combination.

解题思路：
* 此题要考虑解决在组合中去重复的方法：
  * 首先在递归分叉时，传入下一个递归的数据集范围是[i+1 : end]
  * 然后在负责递归拆解的for循环里进行剪枝：
    * 加上if (i > start && num[i] == num[i - 1]) continue;
    * 这样可以防止res中出现重复项，然后就在递归调用combinationSum2DFS里面的参数换成i+1，这样就不会重复使用数组中的数字了，代码如下：

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
                if(i > start && E[i] == E[i-1]) continue;
                out.push_back(E[i]);
                dfs(E, T-E[i], i+1, out, res);
                out.pop_back();
            }
        }
    }
};
```

#### 46. Permutations
Given a collection of distinct numbers, return all possible permutations.  
> For example,[1,2,3] have the following permutations:  
[  
  [1,2,3],  
  [1,3,2],  
  [2,1,3],  
  [2,3,1],  
  [3,1,2],  
  [3,2,1]  
]  

解题思路：
* 典型的组合题中不同的数字顺序只算一种。
* 而此题使用DFS求全排列问题，**排列问题需要用到一个visited数组来标记某个数字是否访问过。**
* **然后在DFS递归函数从的循环应从头开始，而不是从level开始，这是和Combinations组合项不同的地方**
其余思路大体相同，代码如下：

```cpp
class Solution {
public:
    vector<vector<int> > permute(vector<int> &num)
    {
        //声明DFS求排列需要用到的变量
        vector<vector<int> > res;
        vector<int> out;
        vector<int> visited(num.size(), 0);

        //进入DFS
        dfs(num, 0, visited, out, res);
        return res;
    }
    void dfs(vector<int> &num, int level, vector<int> &visited,
             vector<int> &out, vector<vector<int> > &res) {
        if (level == num.size())
        {
            res.push_back(out);
        }
        else
        {
            //排列DFS时，使用两个方法结合控制顺序：
            //1.每个递归中的for循环都从头开始选择数据集
            //2.使用visited数组标记已选择元素，再进入下层递归
            //3.当前递归中，进行到第二个分叉时，注意要将第一次分叉的节点visited恢复
            for (int i = 0; i < num.size(); ++i)
            {
                //有序
                if (visited[i] != 0)
                {
                    continue;
                }
                visited[i] = 1;
                out.push_back(num[i]);
                dfs(num, level + 1, visited, out, res);
                out.pop_back();
                visited[i] = 0;
            }
        }
    }
};
```

#### 47. Permutations II
Given a collection of numbers that might contain duplicates, return all possible unique permutations.

> For example,[1,1,2] have the following unique permutations:  
[  
  [1,1,2],  
  [1,2,1],  
  [2,1,1]  
]

解题思路：
* 本题是关于排列的DFS问题，需要使用visited标记，并且每个递归的拆解循环都要从待选数据集的开头开始选取
* 由于待选数据集中有重复，所以要有排列组合的去重复算法：
  * 1.先对待选数据集排序
  * 2.在递归函数中要判断前面一个数和当前的数是否相等，如果相等，前面的数必须已经使用了，即对应的visited中的值为1，当前的数字才能使用，否则需要跳过，这样就不会产生重复排列了，代码如下：

```cpp
class Solution {
public:
    vector<vector<int> > permuteUnique(vector<int> &num)
    {
        //声明排序dfs的辅助变量
        vector<vector<int> > res;
        vector<int> out;
        vector<int> visited(num.size(), 0);

        //进入递归
        sort(num.begin(), num.end());
        dfs(num, 0, visited, out, res);
        return res;
    }
    void dfs(vector<int> &num, int level, vector<int> &visited,
             vector<int> &out, vector<vector<int> > &res)
    {
        //出口
        if (level >= num.size())
        {
          res.push_back(out);
        }
        else
        {
            for (int i = 0; i < num.size(); ++i)
            {
                //防止重复
                //1.使用过的元素不再使用
                //2.不可以跨过地方式使用相同的元素
                if (visited[i] != 0)
                {
                  continue;
                }
                if (i > 0 && num[i] == num[i - 1] && visited[i - 1] == 0)
                {
                  continue;
                }
                visited[i] = 1;
                out.push_back(num[i]);
                dfs(num, level + 1, visited, out, res);
                out.pop_back();
                visited[i] = 0;
            }
        }
    }
};
```

#### 526. Beautiful Arrangement**
Suppose you have N integers from 1 to N. We define a beautiful arrangement as an array that is constructed by these N numbers successfully if one of the following is true for the ith position (1 ≤ i ≤ N) in this array:

* The number at the ith position is divisible by i.
* or i is divisible by the number at the ith position.

Now given N, how many beautiful arrangements can you construct?

>Example 1:  
Input: 2   
Output: 2  
Explanation:  
* The first beautiful arrangement is [1, 2]:  
Number at the 1st position (i=1) is 1, and 1 is divisible by i (i=1).  
Number at the 2nd position (i=2) is 2, and 2 is divisible by i (i=2).  
* The second beautiful arrangement is [2, 1]:  
Number at the 1st position (i=1) is 2, and 2 is divisible by i (i=1).  
Number at the 2nd position (i=2) is 1, and i (i=2) is divisible by 1.  
Note:  
N is a positive integer and will not exceed 15.

解题思路：  
* 确定使用递归DFS解题：对于满足某种条件的解的求所有情况，这种问题通常要用递归来做。而递归方法等难点在于写递归函数，如何确定终止条件，还有for循环中变量的起始位置如何确定。
* 有去重要求，要使用visited标记：那么这里我们需要一个visited数组来记录数字是否已经访问过，因为优美排列中不能有重复数字。
* 我们用变量pos来标记已经生成的数字的个数，如果大于N了，说明已经找到了一组排列，结果res自增1。
* 在for循环中，i应该从1开始，因为我们遍历1到N中的所有数字，如果该数字未被使用过，且满足和坐标之间的整除关系，那么我们标记该数字已被访问过，再调用下一个位置的递归函数，之后不要忘记了恢复初始状态，参见代码如下：

```cpp
class Solution {
public:
    int countArrangement(int N) {
        //初始化递归需要的辅助变量
        int res = 0;
        vector<int> visited(N + 1, 0);
        //进入递归
        dfs(N, visited, 1, res);
        return res;
    }
    void dfs(int N, vector<int>& visited, int pos, int& res) {
        //递归的出口
        if (pos > N)
        {
            ++res;
            return;
        }
        //拆解递归的过程
        //每层递归都从visited[1:N]中选取还未visited的数字，根据beautiful原则进行判断
        //记得回溯时将当前选中数字i的visited重置。
        for (int i = 1; i <= N; ++i)
        {
            if (visited[i] == 0 && (i % pos == 0 || pos % i == 0))
            {
                visited[i] = 1;
                dfs(N, visited, pos + 1, res);
                visited[i] = 0;
            }
        }
    }
};
```

#### 22. Generate Parentheses
Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

>For example, given n = 3, a solution set is:  
[  
  "((()))",  
  "(()())",  
  "(())()",  
  "()(())",  
  "()()()"  
]

解题思路：  
* 输出括号的有效全排列，需要用到DFS递归。
* 定义递归出口：
  * 如果在某次递归时，左括号的个数大于右括号的个数，说明此时生成的字符串中右括号的个数大于左括号的个数，即会出现')('这样的非法串，所以这种情况直接返回，不继续处理。
  * 如果left和right都为0，则说明此时生成的字符串已有3个左括号和3个右括号，且字符串合法，则存入结果中后返回。
* 如果以上两种情况都不满足，若此时left大于0，则调用递归函数，注意参数的更新，若right大于0，则调用递归函数，同样要更新参数。代码如下：

```cpp
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        dfs(n, n, "", res);
        return res;
    }
    void dfs(int left, int right, string out, vector<string> &res) {
        if (left > right) return;
        if (left == 0 && right == 0) res.push_back(out);
        else {
            if (left > 0)  dfs(left - 1, right, out + '(', res);
            if (right > 0) dfs(left, right - 1, out + ')', res);
        }
    }
};
```

#### 494. Target Sum
You are given a list of non-negative integers, a1, a2, ..., an, and a target, S. Now you have 2 symbols + and -. For each integer, you should choose one from + and - as its new symbol.

Find out how many ways to assign symbols to make sum of integers equal to target S.

解题思路：  
* 对于这种求多种情况的问题，首先要想到使用递归来做。
* 我们从第一个数字，调用递归函数，在递归函数中，分别对目标值进行加上当前数字调用递归，和减去当前数字调用递归，这样会涵盖所有情况，并且当所有数字遍历完成后，我们看若目标值为0了，则结果res自增1，参见代码如下：

```cpp
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int S) {
        //声明递归辅助数组
        int res = 0;
        helper(nums, S, 0, res);
        return res;
    }
    void helper(vector<int>& nums, int S, int start, int& res) {
        //递归出口
        if (start >= nums.size()) {
            if (S == 0) ++res;
            return;
        }
        //当前递归开始分叉
        helper(nums, S - nums[start], start + 1, res);
        helper(nums, S + nums[start], start + 1, res);
    }
};
```


---


## DFS和剪枝
#### word breakII !!!3/8
Given a string s and a dictionary of words dict, add spaces in s to construct a sentence where each word is a valid dictionary word.

Return all such possible sentences.

For example, given
s = "catsanddog",
dict = ["cat", "cats", "and", "sand", "dog"].

A solution is ["cats and dog", "cat sand dog"].

[ref](https://www.cnblogs.com/yuzhangcmu/p/4037299.html)
[ref2](https://www.cnblogs.com/yuzhangcmu/p/4037299.html)

题目分析：  
* 本题考察DFS + 剪枝优化  

* DP与DFS的区别：DP是Bottom-up 而DFS是TOP-DOWN.

* 剪枝方法：定义一个一位数组possible，其中possible[i] = true表示在[i, n]区间上有解，n为s的长度，如果某个区间之前被判定了无解，下次循环时就会跳过这个区间，从而大大减少了运行时间。

DFS+剪枝：
```cpp
class Solution {
public:
    vector<string> wordBreak(string s, unordered_set<string>& wordDict) {
        vector<string> res;
        string out;
        vector<bool> possible(s.size() + 1, true); //剪枝部分
        wordBreakDFS(s, wordDict, 0, possible, out, res);
        return res;
    }
    void wordBreakDFS(string &s, unordered_set<string> &wordDict, int start, vector<bool> &possible, string &out, vector<string> &res) {
        if (start == s.size()) {
            res.push_back(out.substr(0, out.size() - 1));
            return;
        }
        for (int i = start; i < s.size(); ++i) {
            string word = s.substr(start, i - start + 1);
            if (wordDict.find(word) != wordDict.end() && possible[i + 1]) {  //剪枝部分
                out.append(word).append(" ");
                int oldSize = res.size();   //剪枝部分
                wordBreakDFS(s, wordDict, i + 1, possible, out, res);
                if (res.size() == oldSize) possible[i + 1] = false;  //剪枝部分
                out.resize(out.size() - word.size() - 1);
            }
        }
    }
};
```

#### Palindrome Partitioning !!!3/8
Given a string s, partition s such that every substring of the partition is a palindrome.

Return all possible palindrome partitioning of s.

For example, given s = "aab",
Return

  [
    ["aa","b"],
    ["a","a","b"]
  ]

解题思路：

* 这又是一道需要用DFS来解的题目，既然题目要求找到所有可能拆分成回文数的情况，那么肯定是所有的情况都要遍历到。对于每一个子字符串都要分别判断一次是不是回文数，那么肯定有一个判断回文数的子函数，还需要一个DFS函数用来递归，再加上原本的这个函数，总共需要三个函数来求解。

* 那么，对原字符串的所有子字符串的访问顺序是什么呢，如果原字符串是 abcd, 那么访问顺序为: a -> b -> c -> d -> cd -> bc -> bcd-> ab -> abc -> abcd, 这是对于没有两个或两个以上子回文串的情况。那么假如原字符串是 aabc，那么访问顺序为：a -> a -> b -> c -> bc -> ab -> abc -> aa -> b -> c -> bc -> aab -> aabc，中间当检测到aa时候，发现是回文串，那么对于剩下的bc当做一个新串来检测，于是有 b -> c -> bc，这样扫描了所有情况，即可得出最终答案。  

代码如下：
```cpp
class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> res;
        vector<string> out;
        partitionDFS(s, 0, out, res);
        return res;
    }
    void partitionDFS(string s, int start, vector<string> &out, vector<vector<string>> &res) {
        if (start == s.size()) {
            res.push_back(out);
            return;
        }
        for (int i = start; i < s.size(); ++i) {
            if (isPalindrome(s, start, i)) {
                out.push_back(s.substr(start, i - start + 1));
                partitionDFS(s, i + 1, out, res);
                out.pop_back();
            }
        }
    }
    bool isPalindrome(string s, int start, int end) {
        while (start < end) {
            if (s[start] != s[end]) return false;
            ++start;
            --end;
        }
        return true;
    }
};
```











---
