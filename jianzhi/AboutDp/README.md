# Leetcode

DP的六种主流问题：
1. 坐标型15%  
Minimum Path Sum  
Climbing Stairs  
Jump Game  
Longest Increasing Subsequence  
2. 序列型30%  
Word Break  
f[i]代表前i个元素总和，i=0表示不取任何元素
3. 双序列型30%  
Longest Common Subsequence  
4. 划分型10%
5. 背包型10%  
BackPackI  
BackPackII  
K SUM  
Minimum Adjustment Cost  
5. 区间型5%
Stone Game  
Burst Ballons  
Scramble String  

匹配型：
Longest Common Subsequence  
Edit Distance  
K Edit Distance  
Distinct Subquence  
Interleaving String  

Unique Paths， Minimum Path Sum，LISLongest Increasing Subsequence

---

## 坐标和路径DP
#### 64. Minimum Path Sum
Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right which minimizes the sum of all numbers along its path.

Note: You can only move either down or right at any point in time.

>Example 1:  
[[1,3,1],  
 [1,5,1],  
 [4,2,1]]  
Given the above grid map, return 7. Because the path 1→3→1→1→1 minimizes the sum.

解题思路：  
* 比较直接的路径DP，使用Top Down+Momoization即可。
* 关于记忆过往答案：维护一个二维的dp数组，其中dp[i][j]表示当前位置的最小路径和。
* 关于状态转移方程：根据题意可以得到****dp[i][j] = grid[i][j] + min(dp[i - 1][j], dp[i][j - 1])****，代码如下：

```cpp
class Solution {
public:
    int minPathSum(vector<vector<int> > &grid) {
        int m = grid.size(), n = grid[0].size();
        int dp[m][n];
        dp[0][0] = grid[0][0];
        for (int i = 1; i < m; ++i) dp[i][0] = grid[i][0] + dp[i - 1][0];
        for (int i = 1; i < n; ++i) dp[0][i] = grid[0][i] + dp[0][i - 1];
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                dp[i][j] = grid[i][j] + min(dp[i - 1][j], dp[i][j - 1]);
            }
        }
        return dp[m - 1][n - 1];
    }
};
```


#### 120. Triangle
Given a triangle, find the minimum path sum from top to bottom. Each step you may move to adjacent numbers on the row below.

For example, given the following triangle  
[  
     [2],  
    [3,4],  
   [6,5,7],  
  [4,1,8,3]  
]  
The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).

解题思路：  
* 此题使用bottom-up的dp方式
* 因为bottom-up减少了需要记忆memoization，当前节点经过计算的值就是从三角形最后一行bottom up上来的最小值。因此，只需要复制了三角形最后一行，作为用来更新的一位数组(bottom up的过程中，数组中有些节点会慢慢被弃用，但这是可允许的行为)。
* 根据这个思想，设定bottom up的状态转移方程，之后逐个遍历这个DP数组，对于每个数字，和它之后的元素比较选择较小的再加上上面一行相邻位置的元素做为新的元素，然后一层一层的向上扫描，整个过程和冒泡排序的原理差不多，最后最小的元素都冒到前面，第一个元素即为所求。代码如下：

```cpp
class Solution {
public:
    int minimumTotal(vector<vector<int> > &triangle) {
        int n = triangle.size();
        vector<int> dp(triangle.back()); //辅助数组
        for (int i = n - 2; i >= 0; --i) { //bottom up的循环
            for (int j = 0; j <= i; ++j) {
                dp[j] = min(dp[j], dp[j + 1]) + triangle[i][j]; //本题的状态转移方程
            }
        }
        return dp[0];
    }
};
```

---

## 序列型DP



---

#### 139. Word Break

Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, determine if s can be segmented into a space-separated sequence of one or more dictionary words. You may assume the dictionary does not contain duplicate words.

For example, given
s = "leetcode",
dict = ["leet", "code"].

Return true because "leetcode" can be segmented as "leet code".

[ref](http://www.cnblogs.com/grandyang/p/4257740.html)

题目分析：
这道题仍然是动态规划的题目，我们总结一下动态规划题目的基本思路。首先我们要决定要存储什么历史信息以及用什么数据结构来存储信息。然后是最重要的递推式，就是如从存储的历史信息中得到当前步的结果。最后我们需要考虑的就是起始条件的值。
接下来我们套用上面的思路来解这道题。首先我们要存储的历史信息res[i]是表示到字符串s的第i个元素为止能不能用字典中的词来表示，我们需要一个长度为n的布尔数组来存储信息。然后假设我们现在拥有res[0,...,i-1]的结果，我们来获得res[i]的表达式。思路是对于每个以i为结尾的子串，看看他是不是在字典里面以及他之前的元素对应的res[j]是不是true，如果都成立，那么res[i]为true，写成式子是
![image](http://img.blog.csdn.net/20140328035736484?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvbGluaHVhbm1hcnM=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

```cpp
class Solution {
public:
    bool wordBreak(string s, unordered_set<string> &dict) {
        int len = s.size();
        vector<bool> res(len + 1, false);
        res[0] = true;
        for (int i = 0; i < len + 1; ++i) {
            for (int j = 0; j < i; ++j) {
                if (res[j] && dict.find(s.substr(j, i-j)) != dict.end()) {
                    res[i] = true;
                    break;
                }
            }
        }
        return res[len];
    }
};
```

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

#### 279. Perfect Squares
Given a positive integer n, find the least number of perfect square numbers (for example, 1, 4, 9, 16, ...) which sum to n.  

For example, given n = 12, return 3 because 12 = 4 + 4 + 4; given n = 13, return 2 because 13 = 4 + 9.  

**解题思路**：  
##### 使用四平方和定理：  
* 这道题是考察四平方和定理。题中说是给我们一个正整数，求它最少能由几个完全平方数组成。
* 根据四平方和定理，**任意一个正整数均可表示为4个整数的平方和，其实是可以表示为4个以内的平方数之和，那么就是说返回结果只有1,2,3或4其中的一个。** 首先我们将数字化简一下，由于一个数如果含有因子4，那么我们可以把4都去掉，并不影响结果，比如2和8,3和12等等，返回的结果都相同
* 下面我们就来尝试的将其拆为两个平方数之和，如果拆成功了那么就会返回1或2，因为其中一个平方数可能为0. (注：由于输入的n是正整数，所以不存在两个平方数均为0的情况)。
* 注意下面的!!a + !!b这个表达式，**用两个感叹号!!的作用就是看a和b是否为正整数，都为正整数的话返回2，只有一个是正整数的话返回1**。  
参见代码如下：

```cpp
class Solution {
public:
    int numSquares(int n) {
        while (n % 4 == 0) n /= 4;
        if (n % 8 == 7) return 4;
        for (int a = 0; a * a <= n; ++a) {
            int b = sqrt(n - a * a);
            if (a * a + b * b == n) {
                return !!a + !!b;
            }
        }
        return 3;
    }
};
```

#####

---

#### **053 正则表达式匹配**
题目描述

请实现一个函数用来匹配包括'.'和'*'的正则表达式。模式中的字符'.'表示任意一个字符，而'*'表示它前面的字符可以出现任意次（包含0次）。 在本题中，匹配是指字符串的所有字符匹配整个模式。例如，字符串"aaa"与模式"a.a"和"ab*ac*a"匹配，但是与"aa.a"和"ab*a"均不匹配

样例输入  
"a","ab*a"

样例输出  
false

解题思路：  
动态规划

```cpp
class Solution
{
public:
    bool match(string s, string p) {
        /**
         * f[i][j]: if s[0..i-1] matches p[0..j-1]
         * if p[j - 1] != '*'
         *      f[i][j] = f[i - 1][j - 1] && s[i - 1] == p[j - 1]
         * if p[j - 1] == '*', denote p[j - 2] with x
         *      f[i][j] is true iff any of the following is true
         *      1) "x*" repeats 0 time and matches empty: f[i][j - 2]
         *      2) "x*" repeats >= 1 times and matches "x*x": s[i - 1] == x && f[i - 1][j]
         * '.' matches any single character
         */
        int m = s.size(), n = p.size();
        vector<vector<bool>> f(m + 1, vector<bool>(n + 1, false));

        f[0][0] = true;
        for (int i = 1; i <= m; i++)
            f[i][0] = false;
        // p[0.., j - 3, j - 2, j - 1] matches empty iff p[j - 1] is '*' and p[0..j - 3] matches empty
        for (int j = 1; j <= n; j++)
            f[0][j] = j > 1 && '*' == p[j - 1] && f[0][j - 2];

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                if (p[j - 1] != '*')
                    f[i][j] = f[i - 1][j - 1] && (s[i - 1] == p[j - 1] || '.' == p[j - 1]);
                else
                    // p[0] cannot be '*' so no need to check "j > 1" here
                    f[i][j] = f[i][j - 2] || (s[i - 1] == p[j - 2] || '.' == p[j - 2]) && f[i - 1][j];

        return f[m][n];
    }
};
```


####  ** 031连续子数组的最大和







#### July最大连续乘积子串

题目描述
给一个浮点数序列，取最大乘积连续子串的值，例如 -2.5，4，0，3，0.5，8，-1，则取出的最大乘积连续子串为3，0.5，8。也就是说，上述数组中，3 0.5 8这3个数的乘积30.58=12是最大的，而且是连续的。

分析与解法
此最大乘积连续子串与最大乘积子序列不同，请勿混淆，前者子串要求连续，后者子序列不要求连续。也就是说，最长公共子串（Longest CommonSubstring）和最长公共子序列（LongestCommon Subsequence，LCS）是：

子串（Substring）是串的一个连续的部分，
子序列（Subsequence）则是从不改变序列的顺序，而从序列中去掉任意的元素而获得的新序列；
更简略地说，前者（子串）的字符的位置必须连续，后者（子序列LCS）则不必。比如字符串“ acdfg ”同“ akdfc ”的最长公共子串为“ df ”，而它们的最长公共子序列LCS是“ adf ”，LCS可以使用动态规划法解决。

解法二  
考虑到乘积子序列中有正有负也还可能有0，我们可以把问题简化成这样：数组中找一个子序列，使得它的乘积最大；同时找一个子序列，使得它的乘积最小（负数的情况）。因为虽然我们只要一个最大积，但由于负数的存在，我们同时找这两个乘积做起来反而方便。也就是说，不但记录最大乘积，也要记录最小乘积。

假设数组为a[]，直接利用动态规划来求解，考虑到可能存在负数的情况，我们用maxend来表示以a[i]结尾的最大连续子串的乘积值，用minend表示以a[i]结尾的最小的子串的乘积值，那么状态转移方程为：



```cpp
double MaxProductSubstring(double *a, int length)
{
	double maxEnd = a[0];
	double minEnd = a[0];
	double maxResult = a[0];
	for (int i = 1; i < length; ++i)
	{
		double end1 = maxEnd * a[i], end2 = minEnd * a[i];
		maxEnd = max(max(end1, end2), a[i]);
		minEnd = min(min(end1, end2), a[i]);
		maxResult = max(maxResult, maxEnd);
	}
	return maxResult;
}
```


#### July字符串编辑距离
题目描述  
给定一个源串和目标串，能够对源串进行如下操作：

* 在给定位置上插入一个字符
* 替换任意字符
* 删除任意字符
* 写一个程序，返回最小操作数，使得对源串进行这些操作后等于目标串，源串和目标串的长度都小于2000。

解题思路：  
* 使用二维dp。
* dp[i][j]来自于三种状态

    1、删除，dp[i-1][j]+1;

    2、插入，dp[i][j-1]+1;

    3、替换，if(a[i]==b[j]) dp[i][j]=dp[i-1][j-1],else dp[i][j]=dp[i-1][j-1]+1;

假如我们要将字符串str1变成str2，那么：
* 设sstr1(i)是str1的子串，范围[0到i），其中sstr1(0)是空串
* 再设sstr2(j)是str2的子串，范围[0到j），其中sstr2(0)是空串  
* dp[i][j]表示将sstr1(i)变成sstr2(j)的编辑距离  

推理过程：  
* 首先d(0,t),0<=t<=str1.size()和d(k,0)是很显然的。 如d(0,t) == t;
* 当我们要计算d(i,j)时，即计算sstr1(i)到sstr2(j)之间的编辑距离。
  * 此时，设当前sstr1(i)形式是somestr1c；sstr2(i)形如somestr2d。
  * 而将somestr1变成somestr2的编辑距离已知是d(i-1,j-1)。那么：
    * 将somestr1c变成somestr2的编辑距离已知是d(i,j-1)
    * 将somestr1变成somestr2d的编辑距离已知是d(i-1,j)   
    **那么利用这三个变量，就可以递推出d(i,j)了： 如果c==d，显然编辑距离和d(i-1,j-1)是一样的 如果c!=d，情况稍微复杂一点：**
      * 如果将c替换成d，编辑距离是somestr1变成somestr2的编辑距离 + 1，也就是d(i-1,j-1) + 1
      * 如果在c后面添加一个字d，编辑距离就应该是somestr1c变成somestr2的编辑距离 + 1，也就是d(i,j-1) + 1
      * 如果将c删除了，那就是要将somestr1编辑成somestr2d，距离就是d(i-1,j) + 1  

那最后只需要看着三种谁最小，就采用对应的编辑方案了。递推公式出来了，程序也就出来了。

[参考链接1](http://blog.unieagle.net/2012/09/19/leetcode%E9%A2%98%E7%9B%AE%EF%BC%9Aedit-distance%EF%BC%8C%E5%AD%97%E7%AC%A6%E4%B8%B2%E4%B9%8B%E9%97%B4%E7%9A%84%E7%BC%96%E8%BE%91%E8%B7%9D%E7%A6%BB%EF%BC%8C%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92/)

[参考链接2](http://www.dreamxu.com/books/dsa/dp/edit-distance.html)

```cpp
int edit_distance(char *a, char *b)
{
    int lena = strlen(a);
    int lenb = strlen(b);
    int d[lena+1][lenb+1];
    int i, j;

    for (i = 0; i <= lena; i++) {
        d[i][0] = i;
    }
    for (j = 0; j <= lenb; j++) {
        d[0][j] = j;
    }

    for (i = 1; i <= lena; i++) {
        for (j = 1; j <= lenb; j++) {
            // 算法中 a, b 字符串下标从 1 开始，c 语言从 0 开始，所以 -1
            if (a[i-1] == b[j-1]) {
                d[i][j] = d[i-1][j-1];
            } else {
                d[i][j] = min_of_three(d[i-1][j]+1, d[i][j-1]+1, d[i-1][j-1]+1);
            }
        }
    }

    return d[lena][lenb];
}
```


#### July格子取数问题(较难)

[链接1](http://www.voidcn.com/article/p-qzvoehgl-bdy.html)
