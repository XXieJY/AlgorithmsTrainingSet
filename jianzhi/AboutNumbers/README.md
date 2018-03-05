数论相关：


  * 041-和为S的连续正数序列
  * 045-孩子们的游戏(圆圈中最后剩下的数)

#### 009 斐波那契数列
题目描述

大家都知道斐波那契数列， 现在要求输入一个整数n， 请你输出斐波那契数列的第n项。

解题思路：  
对于斐波那契数列相关问题，都应该统一使用for循环计算数列的第n项进行解决。

```cpp
class Solution
{

public:
    int Fibonacci(int n)
    {
        if(n <= 1)
        {
            return n;
        }
        long one = 0;
        long two = 1;;
        long res = 0;

        for(int i = 2; i <= n; i++)
        {
            res = one + two;

            one = two;
            two = res;
        }

        return res;
    }
};
```

#### 034 丑数
题目描述

把只包含因子2、3和5的数称作丑数（Ugly Number）。

例如6、8都是丑数，但14不是，因为它包含因子7。 习惯上我们把1当做是第一个丑数。求按从小到大的顺序的第N个丑数。

解题思路：  
根据丑数的定义，丑数应该是另一个丑数乘以2、3或者5的结果（1除外）。 因此我们可以创建一个数组，里面的数字是排好序的丑数。里面的每一个丑数是前面的丑数乘以2、3或者5得到的。那关键就是确保数组里的丑数是有序的了。 我们假设数组中已经有若干个丑数，排好序后存在数组中。我们把现有的最大丑数记做M。 现在我们来生成下一个丑数，该丑数肯定是前面某一个丑数乘以2、3或者5的结果。 我们首先考虑把已有的每个丑数乘以2。在乘以2的时候，能得到若干个结果小于或等于M的。由于我们是按照顺序生成的，小于或者等于M肯定已经在数组中了，我们不需再次考虑； 我们还会得到若干个大于M的结果，但我们只需要第一个大于M的结果，因为我们希望丑数是按从小到大顺序生成的，其他更大的结果我们以后再说。 我们把得到的第一个乘以2后大于M的结果，记为M2。同样我们把已有的每一个丑数乘以3和5，能得到第一个大于M的结果M3和M5。那么下一个丑数应该是M2、M3和M5三个数的最小者。
```cpp
class Solution
{
protected:
    int ugly[10000];
    int min(int a, int b, int c)
    {
        int temp = (a < b ? a : b);

        return (temp < c ? temp : c);
    }

public:
    int GetUglyNumber_Solution(int N)
    {
        ugly[0] = 1;
        int index2 = 0;
        int index3 = 0;
        int index5 = 0;
        int index = 1;
        while (index < N)
        {
            //竞争产生下一个丑数
            int val = min(ugly[index2]*2,
                          ugly[index3]*3,
                          ugly[index5]*5);

            if (val == ugly[index2] * 2) //将产生这个丑数的index*向后挪一位；
            {
                ++index2;
            }
            if (val == ugly[index3] * 3)   //这里不能用elseif，因为可能有两个最小值，这时都要挪动；
            {
                ++index3;
            }
            if (val == ugly[index5] * 5)
            {
                ++index5;
            }

            ugly[index++] = val;
        }
        int result = ugly[N - 1];
        return result;
    }
};
```
