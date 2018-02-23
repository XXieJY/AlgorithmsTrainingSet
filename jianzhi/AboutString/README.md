字符串相关问题：

  * 042-左旋转字符串
  * 049-把字符串转换成整数
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
class Solutin
{
public :
    void PrintToMaxOfNDigits(int N)
    {
        if(N <= 0)
        {
            return ;
        }

        char *number = new char[N + 1];
        number[N] = '\0';

        //  最低位循环0~9
        for(int i = 0; i < 10; i++)
        {
            number[0] = i + '0';  //使用int + '0'的方式转为字符
            Recursion(number, n, 0);
        }

        delete[] number;
    }

    void Recursion(char *number, int length, int index)
    {
        //循环到最深层
        if(index == length - 1)
        {
            PrintNumber(number);
            return ;
        }

        //  当前位循环0~9
        for(int i = 0; i < 10; i++)
        {
            number[index + 1] = i + '0';
            Recursion(number, length , index + 1);
        }
    }

    void PrintNumber(char *number)
    {
        int i = 0;
        int length = strlen(number);
        for(i = 0; i < length; i++)
        {
            if(number[i] != '0')
            {
                break;
            }
        }
        if(i != length)         //  开始的0不应该输出
        {
            cout << &number[i] <<endl;  //&数组 会从数组开始输出。
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
class Solution
{
public:
    int FirstNotRepeatingChar(string str)
    {
        int x[26] = {0}, y[26] = {0};

        for(unsigned int i = 0; i < str.size(); ++i)
        {
            //  小写字母
            if('a' <= str[i] && str[i] <= 'z')
            {
                if(x[str[i] - 'a'] == 0)
                {
                    //  首次出现保存出现位置
                    x[str[i] - 'a'] = i + 1;
                }
                else
                {
                    //  出现多次, 就置标识-1
                    x[str[i] - 'a'] = -1;
                }
            }
            else if('A' <= str[i] && str[i] <= 'Z')      // 大写字母
            {
                if(y[str[i] - 'A'] == 0)
                {
                     //  首次出现保存出现位置
                     y[str[i] - 'A']= i + 1;
                }
                else
                {
                    //  出现多次, 就置标识-1
                    y[str[i] - 'A'] = -1;
                }

            }
        }

        //  由于标识数组中
        //  只出现一次的字符会存储出现的位置
        //  出现多次的字符就存储标识-1
        //  因此查找数组中非-1的最小值即可
        int res = INT_MAX;
        for(int i = 0; i < 26; ++i)
        {
            if(x[i] != 0 && x[i] != -1)
            {
                res = min(res, x[i]);
            }
            if(y[i] != 0 && y[i] != -1)
            {
                res = min(res, y[i]);
            }
        }
        return res > str.size() ? -1 : res - 1;
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
