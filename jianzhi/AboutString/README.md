### c++可以使用<sstream>库解决字符串流的问题：  
C++引入了ostringstream、istringstream、stringstream这三个类，要使用他们创建对象就必须包含<sstream>这个头文件。
[link](https://www.cnblogs.com/gamesky/archive/2013/01/09/2852356.html)
---

字符串相关问题：
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



* 自动机方法：
https://www.nowcoder.com/questionTerminal/6f8c901d091949a5837e24bb82a731f2
