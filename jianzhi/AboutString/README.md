字符串相关问题：
  * 053-正则表达式匹配
  * 054-表示数值的字符串
  * 055-字符流中第一个不重复的字符


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

#### 035 第一个只出现一次的字符位置


解题思路：  
  bitmap方法-同计数法，略微有变动。我们计数数组不简单的存储计数。
  * 只出现一次的字符会存储出现的位置
  * 出现多次的字符就存储标识-1 因此查找数组中非-1的最小值即可。

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
