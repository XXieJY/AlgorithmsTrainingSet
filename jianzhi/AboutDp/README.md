# Leetcode

## DP
#### 139. Word Break

Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, determine if s can be segmented into a space-separated sequence of one or more dictionary words. You may assume the dictionary does not contain duplicate words.

For example, given
s = "leetcode",
dict = ["leet", "code"].

Return true because "leetcode" can be segmented as "leet code".

[ref](http://www.cnblogs.com/grandyang/p/4257740.html)

题目分析：


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
