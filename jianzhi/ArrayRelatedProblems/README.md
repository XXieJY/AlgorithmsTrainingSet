####003二维数组中的查找
在一个二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。

#####思路：
先想想最直接的做法：暴力搜索解空间，找到则true,没找到则false。此时时间复杂度是O(n*m);

* -->优化： 暴力搜索解空间，肯定是有冗余操作。如何找到本题冗余操作
  * --->首先想到利用“从左到右递增，从上到下递增。”的规律去分割出子问题。
  * --->显然，我们在每次判定target时，是缩小问题解空间的时机。
* -->那么如何缩小问题解空间？
  * ---->我们假设当前在判断数组中E[i][j]与target的大小。
  * 二维数组从左到右递增， 从上到下递增。 此时查找一个数值，应该中右上角或者左下角开始使用分治法查找；
```cpp
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <string>
#include <numeric>

using namespace std;

class Solution {
public:
        bool result = false;
        int R, C, SR;
        bool Find(int T, vector<vector<int> > E) {
                if (E.empty()) return false;
                else {
                        R = 0;
                        SR = E.size();
                        C = E[0].size() - 1;
                        for (; (R < SR) && (C >= 0);) {
                                if (T == E[R][C]) {
                                        result = true;
                                        break;
                                }
                                else if (T < E[R][C]) {
                                        //T maybe in left
                                        --C;
                                }
                                else {
                                        //T maybe in below
                                        ++R;
                                }
                        }
                        return result;
                }
        }
};
```

####004将空格替换成为字符
请实现一个函数，将一个字符串中的空格替换成“%20”。 例如，当字符串为We Are Happy.则经过替换之后的字符串为We%20Are%20Happy。

>We Are Happy   
We%20Are%20Happy

#####思路：
本质是扩大缩小数组的问题，往数组中填充元素。均先考虑，从数组的尾部开始进行迁移操作的方法。
* 先确定空格在字符串中出现的数目
* 在从后往前完成替换，每个非空格字符往后挪空格数目的位置
```cpp
#include <iostream>

using namespace std;

class Solution{
public:
  void replaceSpace(char \*str,int length)
  {
      int i, j;
      int count = 0;
      int len = length;
      for(int i = 0; i < length; i++)
      {
          if(str[i] == ' ')
          {
              count++;
          }
      }
      len = length + count * 2;
      for(i = length - 1, j = len - 1;
          i >= 0 && j >= 0;)
      {
          if(str[i] == ' ')
          {
              str[j--] = '0';
              str[j--] = '2';
              str[j--] = '%';
              i--;
          }
          else
          {
              str[j--]  = str[i--];
          }
      }
      str[len] = '\0';
  }
};
```

#####007用两个栈实现队列
用两个栈来实现一个队列，完成队列的Push和Pop操作。 队列中的元素为int类型。

#####思路：
本题没有什么特殊的东西，算是对队列FIFO和栈FILO的理解吧。

```cpp
class Solution{
public:
    void push(int V){
        E1.push(V);
    }

    int pop(){
      int RS, TMP;
      RS = 0;
      TMP = 0;
      if (!E2.empty()){
          RS = E2.top();
          E2.pop();
          return RS;
      }
      while(!E1.empty()){
        TMP = E1.top();
        E2.push(TMP);
        E1.pop();
      }
    }
private:
    stack<int> E1, E2;
}
```
####020顺时针打印矩阵
题目描述
输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字，
例如， 如果输入如下矩阵：

#####思路：
这题也是比较特殊的题，主要就是打印二维举证的过程中注意边界的控制，不能超出矩阵本来的
边界，也不能重复打印已经打印过的位置，因此可以将边界视作不断缩小的情。
因此，按顺时针逆时针或者某种方向打印数组时，需要注意的有两点：
  1. 维护边界，不要超过数组范围，不要输出已经输出过的点。
  2. 模拟输出时，数组下标的变化。

```cpp
class Solution {
        int n, m;
        //表示当前位置是否转向的二维数组
        vector<vector<bool> > B;

        //判定当前位置是否越界，以及当前要输出的点B[i][j]是否访问过了。
        bool judge(int i, int j) {
                return 0 <= i && i < n &&
                        0 <= j && j < m &&
                        !B[i][j];
        }
public:
        int i=0, j=0, d=0, c=0;
        //代表四种方向的前进方式,抽象出了顺时针时数组标识的变化方式
        //{0,1}:  从左往右走
        //{1,0}:  从上往下走
        //{0,-1}: 从右往左走
        //{-1,0}: 从下网上走
        const int D[4][2] = { {0,1},{1,0},{0,-1},{-1,0} };
        vector<int> solution(vector<vector<int> > E) {
                vector<int> RESULT{};
                //取容器大小和判断容器大小可以按下面这种语法写在一起
                if ((n = E.size()) == 0 || (m = E[0].size()) == 0)
                        return RESULT;
                //使用匿名对象为全局变量进行赋值
                B = vector<vector<bool> >(n, vector<bool>(m, false));
                c = m * n;
                while (c--) {
                        RESULT.push_back(E[i][j]);
                        B[i][j] = true;
                        //当当前方向的下一个位置超出数组边界，或者已访问过
                        //此时进行转向。
                        //d==0时表示从左往右走，d==1时表示从上往下走...
                        if (!judge(i + D[d][0], j + D[d][1]))
                                (++d) %= 4;
                        i += D[d][0];
                        j += D[d][1];
                }
                return RESULT;
        }     
};

```

####008旋转数组的最小数字
题目描述

把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。输入一个非递减序列的一个旋转，输出旋转数组的最小元素。

例如

> 数组{3,4,5,1,2}为{1,2,3,4,5}的一个旋转，该数组的最小值为1。

#####解题思路：
这题应该归类为在数组中进行搜索的题目，常见的搜索算法一般就是顺序搜索，二分搜索。
* 这题如果用顺序搜索解决，那么很明显需要先去找到旋转数组的顺序上的特点，这里可以发现旋转数组里最大
的那个数字后面的就是最小的数字，因此根据这个规律就可以顺利写出顺序搜索的代码。
* 如果这道题再要提高效率，那么可知必然和二分搜索有关系。那么就要再旋转数组里找到能够支持二分的搜索
的特征，也就是如何确定每次搜索的时候搜索数组中的哪一半。
  * 这里就需要发现，旋转数组可以被分为前后两个递增子序列。
  * 因此，A[pivot]如果大于A[low]则说明A[pivot]属于前面的子序列则最小值在A[pivot]之后。
  * 相反如果A[pivot]小于A[high]则说明A[pivot]属于后面的子序列则最大值在A[pivot]之前。

```cpp
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int LT, MD, RT, S;
        int  minNumberInRotateArray(vector<int> E) {
        		S = E.size();
                if (S == 0) return -1;

                LT = 0;
                MD = 0;
                RT = S - 1;

                if (E[LT] < E[RT]) return -1;

                while (true) {
                        if ((RT - LT) == 1) {
                                MD = RT;
                                break;
                        }

                        MD = (RT - LT) / 2 + LT;
                        if (E[MD] >= E[LT]) LT = MD;
                        else RT = MD;
                }
                return E[MD];

       }
};
```
####014 调整数组顺序使得奇数位于偶数前面并保持奇数之间和偶数之间的相对位置
题目描述

输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有的奇数位于数组的前半部分，所有的偶数位于位于数组的后半部分，并保证奇数和奇数，偶数和偶数之间的相对位置不变。

> 样例输入
5 1 2 3 4 5

> 样例输出
1 3 5 2 4

#####解题思路：
这题算是调整数组顺序的问题，虽然没有按大小排序的要求，但是按其他任意排序的问题都应该归结为排序问题。
然后本题还要求是稳定的排序，因此只能考虑插入排序、冒泡排序。综上所述，调整数组奇数偶数的相对位置，就是
在考察简单的冒泡排序。
```cpp
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void reOrderArray(vector<int> &E) {
        int S, tmp;

        S = E.size();
        if(S <= 1) return;

        tmp = 0;
        while (S >= 2) {
            int i, j;
            i = 0;
            j = 1;
            for (; j < S; ++i, ++j){
                if (E[i] % 2 == 0 && E[j] % 2 != 0){
                    tmp = E[i];
                    E[i] = E[j];
                    E[j] = tmp;
                }
            }
            --S;
        }
    }
};
```

####021 实现包含min功能的栈
题目描述
定义栈的数据结构，请在该类型中实现一个能够得到栈最小元素的min函数。

#####解题思路：
这种题目如果每次min的时候查找确实是一种慢的方法。但是这种实现一个数据结构并且要维护
这个数据结构的最大最小值，并且这个数据结构的大小会变化，因此大小值需要维护成一个
列表，也随着整个数据结构的大小变化而变化。

* 因此实现包含min功能的栈，就需要用到一个存储实时min值的辅助栈，辅助栈的栈顶永远都是
当前栈的最小值。min栈的栈顶只能越来越小
* 当入栈元素大于min栈栈顶元素时，该元素不入min栈。反之则既入普通栈又入min栈
* 在出栈时如果元素是min栈栈顶元素，则min栈也出栈。

```cpp
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
     
    stack<int> E, EMin;
     
    void push(int value) {
        E.push(value);
        if(EMin.empty())
            EMin.push(value);
        else if(value<=EMin.top())
        {
            EMin.push(value);
        }
    }
     
    void pop() {
        if(E.top()==EMin.top())
            EMin.pop();
        E.pop();
         
    }
     
    int top() {
        return E.top();       
    }
     
    int min() {
        return EMin.top();
    }
     
};
```

####022 栈的压入、弹出序列
题目描述
输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否为该栈的弹出顺序。假设压入栈的所有数字均不相等。例如序列1,2,3,4,5是某栈的压入顺序，序列4，5,3,2,1是该压栈序列对应的一个弹出序列，但4,3,5,1,2就不可能是该压栈序列的弹出序列。（注意：这两个序列的长度是相等的）
#####解题思路：
判断栈的压入弹出序列是否正确是典型和栈相关的问题。主要用到的解法就是模拟栈的出栈过程，到最后如果
模拟栈为空则说明出栈序列是正确的。
* 利用到的性质：
  * 当某个元素出栈时，早于其入栈的元素不会晚于其出栈
* 解题过程：
  * 创建一个模拟栈，每次往其中push一个元素
  * 每次push元素之后，和出栈序列的第一个元素对比：
    * 如果相等则说明当前元素已经出栈，此时也把这个元素从模拟栈中pop_back掉
    * 然后继续这个比较过程，直到不相等
  * 最后返回模拟栈是否为空的结果

```cpp
class Solution {
public:
     bool IsPopOrder(vector<int> pushV, vector<int> popV) {
                        if (pushV.size() == 0) return false;
                        vector<int> stack;
                        for (int i = 0, j = 0; i < pushV.size();) {
                                stack.push_back(pushV[i++]);
                                while (j < popV.size() && stack.back() == popV[j]) {
                                        stack.pop_back();
                                        j++;
                                }
                        }
                        return stack.empty();
                }
};
```

####029 数组中出现次数超过一半的数字
题目描述
数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。例如输入一个长度为9的数组{1,2,3,2,2,2,5,4,2}。由于数字2在数组中出现了5次，超过数组长度的一半，因此输出2。如果不存在则输出0。
#####解题思路：
这题算是数组元素统计题，是比较好想到题解的。最简单的就是，对数组排序，然后中间的那个数一定是
超过数组一半元素的嫌疑数，然后再遍历一遍数组，计算嫌疑数出现的次数即可。

我这里用的是数组元素的对消法，如果存在超出数组一半的元素，那么我们对数组中相同元素两两
相合，不同元素两两相消，那么剩下的元素就是嫌疑元素，然后再遍历一遍数组元素确认这个嫌疑元素
出现的次数即可。


```cpp
#include "stdafx.h"
#include <iostream>
#include <vector>

using namespace std;

class Solution {

public:
	int solution(vector<int> E) {
		int TMP, N, s;

		if ((s = E.size()) == 0) {
			return 0;
		}
		else if (s == 1) {
			return E[0];
		}

		int i = 1;
		TMP = E[0];
		N = 1;
		for (; i < s; ++i) {
			if (TMP == E[i]) {
				++N;
			}
			else {
				--N;
				if (N == 0) {
					TMP = E[i];
					N = 1;
				}
			}
		}

		N = 0;
		i = 0;
		for (; i < s; ++i) {
			if (E[i] == TMP) {
				++N;
			}
		}
		if (N * 2 <= s) {
			return 0;
		}
		else {
			return TMP;
		}

	}
};
```

####030 最小的K个数
题目描述
输入n个整数，找出其中最小的K个数。例如输入4,5,1,6,2,7,3,8这8个数字，则最小的4个数字是1,2,3,4。

#####解题思路：
这题算是常见搜索相关问题里面被讨论比较多，比较有深度的问题。因为可以应用上的方法很多，从快速排序的各种加强版本，到最小堆。July还为此专门有一个专题。[专题](https://github.com/gatieme/CodingInterviews/tree/master/030-%E6%9C%80%E5%B0%8F%E7%9A%84K%E4%B8%AA%E6%95%B0)

* 最大堆求数组最小k个数：
```cpp
class Solution {
public:
    vector<int> Solution(vector<int> E, int k)
    {        
        vector<int> res;

        if(E.size( ) == 0 || E.size( ) < k)
        {
            return res;
        }
        make_heap(E.begin( ), E.R( ), greater_class());

        for(int i = 0; i < k; i++)
        {
            //最小的元素在栈顶
            res.push_back(E[0]);

            ///  一下两种操作均可以
            // [1]  --  清除它, 然后重新排序堆
            //E.erase(E.begin( ));
            //sort_heap(E.begin( ), E.R( ));
            // [2]  --  当然从堆出弹出这个栈顶元素
            pop_heap(E.begin( ), E.R( ), greater_class( ));   // 弹出一个元素后，剩下的又重建了 heap，仍保持heap的性质
            E.pop_back();         // vector 删除末尾元素
        }

        return res;
    }

    class greater_class
    {
    public:

        bool operator()(int a, int b)
        {
            return a > b;
        }
    }
};
```
* 利用快速排序和分治思想：

 * 取中位数作为pivot的方法：  
    * 类似快速排序的划分方法，N个数存储在数组S中。每次排序时从数组中随机选取一个数X作为pivot,这样可以把数组划分为Sa和Sb两部分，Sa<= X <=Sb。
    * 如果要查找的K个小的元素小于Sa中的元素个数，则返回Sa中较小的K个元素，否则返回Sa中K个小的元素 + Sb中小的K-|Sa|个元素。  

 * **（随机选取枢纽元，可做到线性期望时间O(N)的复杂度）** 每次都是随机选择数列中的一个元素作为主元，使用快速排序在O(n)的时间内找到第K小的元素，然后遍历输出前面的K个小的元素。如果能的话，那么总的时间复杂度为线性期望时间：O(n+k) = O(n)（当n比较小时）；

下面这个这个实现是按照kth一个一个的来搜索到的，而不是按块搜索到的
```cpp
class Solution {
public:
    vector<int> Solution(vector<int> E, int k)
    {
        int S;
        vector<int> RES;

        S = E.size();
        if(S == 0 || S < k)
        {
            return RES;
        }
        kthQuick(E, 0, S-1, k);
        int i = 0;
        for(; i < k; ++i){
            RES.push_back(E[i]);
        }
        return RES;
    }

    void kthQuick(vector<int> &E, int L, int R, int k){
        if(L == R){
            return;
        }
        int pivot = Partition(E, L, R);
        if (pivot < k){
            kthQuick(E, pivot+1, R, k);
        }
        else if (pivot > k){
            kthQuick(E, L, pivot-1, k);
        }
        else{
            return;
        }
    }

    int Partition(vector<int> &E, int L, int R)
    {
        int i, j, pivot, pivotNum;

        ///  我们选择第一个元素作为基准
        ///  这个也可以随机选择
        i = L;
        j = R;
        pivot = L;
        pivotNum = E[pivot];
        while(i < j)
        {
            while(i < j && E[j] >= pivotNum)
            {
                j--;
            }
            E[i] = E[j]; //这里因为pivot的值已经额外记录了所以可以这样

            while(i < j && E[i] <= pivotNum)
            {
                i++;
            }
            E[j] = E[i];
        }
        E[i] = pivotNum; //确定pivot的位置             
        return i;
    }
};
```

####036 数组中的逆序对
题目描述

在数组中的两个数字，如果前面一个数字大于后面的数字，则这两个数字组成一个逆序对。 输入一个数组，求出这个数组中的逆序对的总数

> 样例输入
7 5 6 4

>样例输出
5

#####解题思路：
逆序对相关问题直接和归并排序相关的。
* 采用归并排序，计算每次左右两边的逆序对。
* 然后再计算merge后的逆序对。

```cpp
class Solution
{
public:
    int Solution(vector<int> E)
    {
        int S;
        S = E.size();
        if(S == 0)
        {
            return 0;
        }

        vector<int> TP(S);
        int RES;
        RES = mergeSort(E, 0, S - 1, TP);
        return RES;
    }

    int mergeSort(vector<int> &E, int L, int R, vector<int> &TP)
    {
        int RES = 0;
        if(L < R)
        {
            int M = (L + R) / 2;
            RES += mergeSort(E, L, M, TP); //找左半段的逆序对数目
            RES += mergeSort(E, M + 1, R, TP); //找右半段的逆序对数目
            RES += merge(E, L, M, R, TP);
        }
        return RES;
    }

    int merge(vector<int> &E, int L, int M, int R, vector<int> &TP)//数组的归并操作
    {
        // int leftLen = M - L + 1; //E[L...M]左半段长度
        // int rightLlen = R - M;   //E[M+1...R]右半段长度

        int i, j, k, count;
        i = 0;
        k = M + 1;
        k = 0;
        count = 0;        
        while(i < M + 1 && j < R + 1)
        {
            if(E[i] > E[j])
            {
                TP[k++] = E[i++];
                count += j - M;
            }
            else
            {
                TP[k++] = E[j++];
            }
        }
        while(i >= L)//表示前半段数组中还有元素未放入临时数组
        {
            TP[k++] = E[i--];
        }

        while(j>M)
        {
            TP[k++] = E[j--];
        }

        //将临时数组中的元素写回到原数组当中去。
        for(i = 0; i < k; i++)
        {
            E[R-i] = TP[i];
        }

        copy(E.begin(), E.R(), ostream_iterator<int>(cout," "));
        return count;

    }
};
```
