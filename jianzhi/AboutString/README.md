### c++可以使用<sstream>库解决字符串流的问题：  
C++引入了ostringstream、istringstream、stringstream这三个类，要使用他们创建对象就必须包含<sstream>这个头文件。
[link](https://www.cnblogs.com/gamesky/archive/2013/01/09/2852356.html)

---

## 字符串相关问题：
* 字符串变形：
  * 翻转之类的字符串变形：（使用一个或者多个栈翻转字符串）
  * 字符串和排列组合：常见为字符串打印相关(递归全排列法、交换排列法)
* 字符串查找/匹配：
  * 无重复、子串相关问题（使用hash记录位置）
  * 如查找第一次出现的 （常见使用 hash存储、额外数组存储）
  * 匹配字符串判断字符串是否是有效数字；
  * 匹配括号问题；（使用栈）
* 字符串和整数间的转换：
  * 字符串转整数
  * 整数转字符串
* 回文问题；（常见是使用DP来解决回文问题，判断回文有专门的dp递推式）


---

### 字符串查找匹配：

#### 3. Longest Substring Without Repeating Characters（最长无重复子串）
* 建立一个256位大小的整型数组来代替哈希表，这样做可以记录256个字符。
* 然后我们需要定义两个变量res和left，其中res用来记录最长无重复子串的长度，left指向该无重复子串左边的起始位置。
* 然后我们遍历整个字符串，对于每一个遍历到的字符：
  * 如果哈希表中该字符串对应的值为0，说明没有遇到过该字符，则此时更新最长无重复子串，i - left + 1，其中i是最长无重复子串最右边的位置，left是最左边的位置.
  * 还有一种情况也需要计算最长无重复子串，就是当哈希表中的值小于left，这是由于此时出现过重复的字符，left的位置更新了，如果又遇到了新的字符，就要重新计算最长无重复子串。
* 最后每次都要在哈希表中将当前字符对应的值赋值为i+1，这样就可以在hash中存储对应字符的下一个字符位置，如果当前字符重复，则直接可以将left移动到当前重复字符的下一个字符位置。代码如下：
```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s)
    {
        int m[256] = {0}, res = 0, left = 0;
        for (int i = 0; i < s.size(); ++i)
        {
            if (m[s[i]] == 0 || m[s[i]] < left)
            {
                res = max(res, i - left + 1);
            }
            else
            {
                left = m[s[i]];
            }
            m[s[i]] = i+1;
        }
        return res;
    }
};
```

#### 14. Longest Common Prefix

解题思路：  
这道题让我们求一系列字符串的共同前缀，没有什么特别的技巧，无脑查找即可。
* 我们定义两个变量i和j，其中i是遍历搜索字符串中的字符，j是遍历字符串集中的每个字符串。
* 这里将单词上下排好，则相当于一个各行长度有可能不相等的二维数组，我们遍历顺序和一般的横向逐行遍历不同，而是采用纵向逐列遍历。我们每次取出第一个字符串的某一个位置的单词，然后遍历其他所有字符串的对应位置看是否相等。
  * 在遍历的过程中，如果某一行没有了，说明其为最短的单词，因为共同前缀的长度不能长于最短单词，所以此时返回已经找出的共同前缀。
  * 如果有不满足的直接返回res。
  * 如果都相同，则将当前字符存入结果，继续检查下一个位置的字符，参见代码如下：
```cpp
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        //判断边界条件
        if (strs.empty())
        {
            return "";
        }
        string res = "";
        for (int j = 0; j < strs[0].size(); ++j) {
            char c = strs[0][j];
            //按纵列同时遍历每一行的每个单词
            for (int i = 1; i < strs.size(); ++i) {
                //如果当前行的长度小于j，或者当前行的第j个字符值strs[i][j] != c
                if (j >= strs[i].size() || strs[i][j] != c)
                {
                    return res;
                }
            }
            res.push_back(c);
        }
        return res;
    }
};
```

#### 035 第一个只出现一次的字符位置
解题思路：  
  bitmap方法-同计数法，略微有变动。我们计数数组不简单的存储计数。
  * 声明两个size=26的数组分别存放a-z和A-Z在字符串中出现的情况
  * 只出现一次的字符，则存储这个字符在字符串中出现的位置。
  * 出现多次的字符，就存储标识-1，因此查找数组中非-1的最小值即可。

```cpp
class Solution {
public:
        int FirstNotRepeatingChar(string V) {
                int E[26] = { 0 }, E2[26] = { 0 };
                int S;

                S = V.size();
                for (int i = 0; i < S; ++i) {
                        if ('a' <= V[i] && V[i] <= 'z') {
                                int j = V[i] - 'a';
                                if (E[j] == 0) {
                                        E[j] = i + 1;
                                }
                                else {
                                        E[j] = -1;
                                }
                        }
                        else if ('A' <= V[i] && V[i] <= 'Z') {
                                int j = V[i] - 'A';
                                if (E2[j] == 0) {
                                        E2[j] = i + 1;
                                }
                                else {
                                        E2[j] = -1;
                                }
                        }
                }

                int res = INT_MAX;
                for (int i = 0; i < 26; ++i)
                {
                        if (E[i] != 0 && E[i] != -1)
                        {
                                res = min(res, E[i]);
                        }
                        if (E2[i] != 0 && E2[i] != -1)
                        {
                                res = min(res, E2[i]);
                        }
                }
                return res > V.size() ? -1 : res - 1;
        }


};
```

#### 20. Valid Parentheses(括号字符串匹配)
这道题让我们验证输入的字符串是否为括号字符串，包括大括号，中括号和小括号。
* 用一个栈，从开始遍历输入字符串。
  * 如果当前字符为左半边括号时，则将其压入栈中。
  * 如果遇到右半边括号时，若此时栈为空，则直接返回false，如不为空，则取出栈顶元素，若为对应的左半边括号，则继续循环，反之返回false，代码如下：
```cpp
class Solution {
public:
    bool isValid(string s) {
        //声明辅助栈，用来括号匹配
        stack<char> parentheses;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '(' || s[i] == '[' || s[i] == '{')
            {
                parentheses.push(s[i]);
            }
            else
            {
                if (parentheses.empty())
                {
                     return false;
                }
                else if (s[i] == ')' && parentheses.top() != '(')
                {
                    return false;
                }
                else if (s[i] == ']' && parentheses.top() != '[')
                {
                    return false;
                }
                else if (s[i] == '}' && parentheses.top() != '{')
                {
                    return false;
                }
                else
                {
                    parentheses.pop();
                }

            }
        }
        return parentheses.empty();
    }
}; 
```

---

### 字符串变形：

#### 042 翻转单词顺序列

**解题思路**：  
字符串逆序就是使用栈的FILO性质，如果是按单词的字符串逆序则使用双栈进行，先逆序单词然后进第二个栈逆序整个句子。

```cpp
class Solution
{
public:
    string ReverseSentence(string str)
    {
        if (str.size() == 0)
        {
            return str;
        }

        string result;
        stack<char>stk1;
        stack<char>stk2;

        for (auto i : str)
        { //把str中的全部压入
            stk1.push(i);
        }
        //  通过将字符串压入栈中, 现在出栈顺序正好是入展顺序的逆序
        //  即我们实现了一次整个字符串的翻转

        //  接下来我们翻转每个单词
        //  只要不是空格就一直入栈(实现翻转)
        //  遇见空格的时候，就读取栈中元素(出栈的顺序正好是每个单词的顺序)
        result = "";
        while (!stk1.empty())
        {
            if (stk1.top() != ' ')
            {   //没有遇到空格 就再弹出 压到第二个栈
                stk2.push(stk1.top());
                stk1.pop();
            }
            else
            {   //如果遇到了空格 一个单词结束了  将第二个栈里的弹出
                stk1.pop();
                while (!stk2.empty())
                {
                    result += stk2.top();
                    stk2.pop();
                }
                result += " ";
            }
        }
        //将第二个栈剩余的单词输出
        while (!stk2.empty()) {
            result += stk2.top();
            stk2.pop();
        }
        return result;
    }
};
```


#### *012 打印1到最大的N位数
**(关于字符串排列组合输出的样板题)**

题目描述  
给定一个数字N，打印从1到最大的N位数。输入每个输入文件仅包含一组测试样例。
对于每个测试案例，输入一个数字N(1<=N<=5)。 输出 对应每个测试案例，依次打印从1到最大的N位数。  

样例输入：  
1  
样例输出：  
1 2 3 4 5 6 7 8 9

##### 解题思路：
对于打印字符串排列组合的相关问题，应该考虑使用递归全排列或者交换排列的方法。  
本题要打印1到N位的所有数，可以递归全排列数的每一位。数字大小低于N位的数字会被高位排0的排序情况表示。  

```cpp
class Solution {
public:
        void PrintToMaxOfDigits(int N) {
                if (N <= 0) {
                        return;
                }

                char* E = new char[N + 1];
                E[N] = '\0';

                for (int i = 0; i < 10; ++i) {
                        E[0] = i + '0';
                        Recursion(E, N, 2);
                }

                delete[] E; //手动申请空间需要手动释放
       }

        void Recursion(char* E, int S, int P) {
                if (P == S) {
                        PrintNumber(E);
                        return;
                }

                for (int i = 0; i < 10; ++i) {
                        E[P - 1] = i + '0';
                        Recursion(E, S, P + 1);
                }
        }

        void PrintNumber(char* E) {
                int S, i;
                S = strlen(E);
                i = 0;

                for (; i < S; ++i) {
                        if (E[i] != '0') {
                                break;
                        }
                }

                if (i != S) {
                        cout << &E[i] << endl;
                }
        }
};
```

#### 17. Letter Combinations of a Phone Number（求字符串排列组合的所有情况应该递归DFS+字典）
解题思路：  
这道题让我们求电话号码的字母组合，即数字2到9中每个数字可以代表若干个字母，然后给一串数字，求出所有可能的组合。
* 我们用递归Recursion来解。
* 此外因为是从字符串待选项中pick排列组合的元素，所有需要建立一个字典(hash)，用来保存每个数字所代表的字符串。
* 然后我们还需要一个变量level，记录当前生成的字符串的字符个数，实现套路和上述那些题十分类似，代码如下：
```cpp
class Solution {
public:
    vector<string> letterCombinations(string digits)
    {
        //判断边界条件
        vector<string> res;
        if (digits.empty())
        {
            return res;
        }
        //创建字典数组
        string dict[] = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        //进入递归主体
        letterCombinationsDFS(digits, dict, 0, "", res);
        return res;
    }
    void letterCombinationsDFS(string digits, string dict[], int level, string out, vector<string> &res)
    {
        //dfs递归出口
        if (level == digits.size())
        {
             res.push_back(out);
        }
        else
        {
            string str = dict[digits[level] - '2'];
            //每层的每个字符可以分叉出k个递归
            for (int i = 0; i < str.size(); ++i)
            {
                out.push_back(str[i]);
                letterCombinationsDFS(digits, dict, level + 1, out, res);
                out.pop_back();
            }
        }
    }
};
```
---

### 字符串和整数间的转换：

#### 049 把字符串转换成整数

题目描述

写一个函数，求两个整数之和，要求在函数体内不得使用四则运算符号。

> 样例输入  
1a33  
-2147483648

> 样例输出  
0  
-2147483648

##### 解题思路：  
这题主要要注意string To vector时的边界条件，是一道不错的面试题。  

字符串转化为数字时需要注意：
* 排除字符串前面的空白字符
* 判断字符串的符号位
* 判断是否溢出，使用INT_MAX和INT_MIN关键字

```cpp
#include <iostream>
using namespace std;

class Solution
{
public:
    int StrToInt(string V)
    {
        //string使用迭代器遍历
        string::iterator P;
        bool F;
        long long int RES; //保存int大小的数值，需要用到至少long int的变量

        P = V.begin( );
        while (*P == ' ')
        {
            P++;
        }

        F= false;
        //  判断符号位
        if (*P == '+')
        {
            P++;
        }
        else if (*P == '-')
        {
            P++;
            F = true;
        }

        RES = 0;
        for (; P != V.end( ); P++)
        {
            if ('0' <= *P && *P <= '9')
            {
                RES *= 10;
                RES += *P - '0';
            }
            else
            {
                break;
            }

            //  解决OVER_FLOW的问题
            //  INT_MAX     2147483647
            //  INT_MIN     -2147483648  F = true
            //  负数绝对值最大为INT_MAX + 1
            //  正数最大值为INT_MAX
            if((F == true  && RES > (unsigned long)(INT_MAX) + 1)     
              || (F == false && RES > INT_MAX))                         
            {
                break;
            }

        }

        //如果P没遍历到字符串尾部说明字符串转整数失败
        //要么是字符串中有非0-9的数值
        //要么字符串代表的数值溢出了
        if(P != V.end( ))
        {
            return 0;
        }
        else
        {

            if (F == true)
            {
                RES = -RES;
            }

            if (RES >= INT_MAX)
            {
                RES = INT_MAX;
            }
            else if (RES <= INT_MIN)
            {
                RES = INT_MIN;
            }

            return (int)RES;

        }
    }
};
```

####* 054-表示数值的字符串
题目描述  
请实现一个函数用来判断字符串是否表示数值（包括整数和小数）。例如，字符串"+100","5e2","-123","3.1416"和"-1E-16"都表示数值。 但是"12e","1a3.14","1.2.3","+-5"和"12e+4.3"都不是。


解题思路：  
* 直白解题方法：**（字符串遍历匹配）**  
此题径直的解法就是直接按照题目中个自己对数值字符串格式的理解，从头到尾地匹配给定字符串。

我们首先分析一下子可能是数值的字符串的格式 在数值之前可能有一个表示正负的’-‘或者’+’。 接下来是若干个0到9的数位表示数值的整数部分（在某些小数里可能没有数值的整数部分）。 如果数值是一个小数，那么在小数点后面可能会有若干个0到9的数位表示数值的小数部分。如果数值用科学计数法表示，接下来是一个’e’或者‘E’，以及紧跟着的一个整数（可以有正负号）表示指数。 　　 判断一个字符串是否符合上述模式时，

* 首先看第一个字符是不是正负号。
* 如果是，在字符串上移动一个字符，继续扫描剩余的字符串中0到9的数位。
* 如果是一个小数，则将遇到小数点。
* 另外，如果是用科学计数法表示的数值，在整数或者小数的后面还有可能遇到’e’或者’E’。

```cpp
class Solution
{
public:
    bool isNumeric(char* str)
    {
        if(str == NULL)
        {
            return false;
        }

        //  可能遇见符号+/-
        if(*str == '+' || *str == '-')
        {
            ++str;
        }

        if(*str == '\0')
        {
            return false;
        }

        bool numberic = true;

        //  把字符串按照e,E和.分成一段或几段数字
        //  那么e,E和.就是分隔符，在段中的每个字符就必须满足'0'~'9'
        //  str指针作为要被ScanDigits修改的参数传入时需要传入str指针自己的地址值
        //  然后ScanDigits(char** str)指向指针的指针接收
        ScanDigits(&str);

        if(*str != '\0')
        {
            if(*str == '.')
            {
                ++str;
                ScanDigits(&str);

                if(*str == 'e' || *str == 'E')
                {
                    numberic = IsExponential(&str);
                }
            }
            else if(*str == 'e' || *str == 'E')
            {
                numberic = IsExponential(&str);
            }
            else
            {

                numberic = false;
            }
        }

        return numberic && *str == '\0';

    }


    void ScanDigits(char **str)
    {
        while(**str != '\0'
          && (**str >= '0' && **str <= '9'))
        {
            ++(*str);
        }
    }

    bool IsExponential(char **str)
    {
        if(**str != 'e' && **str != 'E')
        {
            return false;
        }

        ++(*str);

        if(**str == '+' || **str == '-')
        {
            ++(*str);
        }
        if(**str == '\0')
        {
            return false;
        }
        ScanDigits(str);

        return (**str == '\0') ? true : false;
    }



};
```

---

### 回文问题****：

#### 5. Longest Palindromic Substring
* 此题可以用动态规划Dynamic Programming来解。
* 维护一个二维数组dp，其中dp[i][j]表示字符串区间[i, j]是否为回文串。
  * 当i = j时，只有一个字符，肯定是回文串。
  * 如果i = j + 1，说明是相邻字符，此时需要判断s[i]是否等于s[j]。
  * 如果i和j不相邻，即i - j >= 2时，除了判断s[i]和s[j]相等之外，dp[j + 1][i - 1]若为真，就是回文串，通过以上分析，可以写出递推式如下：

  >  dp[i, j] = 1,    if i == j  
     dp[i, j]= s[i] == s[j],                                if j = i + 1  
    dp[i, j]= s[i] == s[j] && dp[i + 1][j - 1],    if j > i + 1      

```cpp
class Solution {
public:
    string longestPalindrome(string s)
    {
        //初始化二维dp数组和一些辅助变量
        int dp[s.size()][s.size()] = {0}, left = 0, right = 0, len = 0;

        //二维dp的for循环
        for (int j = 0; j < s.size(); ++j)
        {
            //长度为1的子串一定是回文串
            dp[j][j] = 1;
            for (int i = 0; i < j; ++i)
            {
                //判断子串[i,j]是否是回文串的dp递推式
                //即：(当前子串的两端字符是否相等 && (子串长度为1或者2 || 子串包含的子串[i+1 : j-1]是否是回文串)
                dp[i][j] = (s[i] == s[j] && (j - i < 2 || dp[i + 1][j - 1]));
                //如果当前回文串的长度大于记录中的回文串则替换它
                if (dp[i][j] && len < j - i + 1)
                {
                    len = j - i + 1;
                    left = i;
                    right = j;
                }
            }
        }
        return s.substr(left, right - left + 1);
    }
};
```
