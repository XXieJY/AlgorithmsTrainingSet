## 基础算法
* 查找算法：二分查找
* 排序算法：快速排序、归并排序
* 指针操作：前后差一步指针、快慢指针、左右指针
* 树的算法：树的遍历(前/中/后/层序)、树的恢复(前+中/中+后恢复树)、树的分解(树转数组、树转链表)
* 链表操作：链表遍历(链表环)、链表变形(链表转数组、链表头插)

---

### 查找算法
#### 二分查找

* 基本二分查找框架
```cpp
class Solution {
  int binarySearch(vector<int> E, int T)
  {
    //判断边界条件
    if((int S = E.size()) == 0)
    {
      return -1;
    }

    //声明二分查找辅助变量：左边界和右边界和中间节点
    int L = 0, R = S - 1, pivot = 0;

    //二分查找主循环体，出口条件必须是left <= right
    //L<=R结合pivot+-1可以推导出的最后结果是L与R一定会在
    //查找失败时交叉
    while(L <= R)
    {
      //每次循环更新pivot
      pivot = L + (R - L) / 2;
      //根据题目查找要求确定不同的E[pivot]与T间的比较关系
      if (E[pivot] ? T)
      {
        //更新Left或Right或返回结果
      }
      else
      {
        //更新Right或Left或返回结果
      }
    }
    //返回查找失败的结果
  }
}
```

* 在无重复有序数组中查找
```cpp
class Solution{
  int binarySearch(vector<int> E, int T)
  {
    if((int S = E.size()) == 0)
    {
      return -1;
    }
    int L = 0, R = S - 1, pivot = 0;
    while (L <= R)
    {
      pivot = L + (R - L) / 2;
      if(E[pivot] == T)
      {
        return pivot;
      }
      else if(E[pivot] < T)
      {
        L = pivot + 1;
      }
      else
      {
        R = pivot - 1;
      }
    }
    return -1;
  }
}
```

* 在有重复有序数组中查找（那就是查找区间了）
```cpp
class Solution{
    vector<int> binarySearch(vector<int> E, int T)
    {
        if ((int S = E.size()) == 0)
        {
            return -1;
        }

        //初始化变量，先查找左边界
        int L = 0, R = S - 1, pivot = 0, A = -1, B = -1;
        while (L <= R)
        {
            pivot = L + (R - L) / 2;
            //左右游标回向目标值的左边界靠拢
            if (E[pivot] >= T)
            {
                R = pivot - 1;
            }
            else
            {
                L = pivot + 1;
            }
        }
        //注意这里的判断条件
        //因为允许可重复查找则有可能会查找出边界或者结果事实上是大于Target的值
        if (L < S && E[L] == T)
        {
            A = L;
        }
        else
        {
            return new vector<int>{-1, -1};
        }
        L = 0, R = S - 1, pivot = 0;
        while (L <= R)
        {
            pivot = L + (R - L) / 2;
            if (E[pivot] <= T)
            {
                L = pivot + 1;
            }
            else
            {
                R = pivot - 1;
            }
        }
        //注意这里的判断条件
        //因为允许可重复查找则有可能会查找出边界或者结果事实上是小于Target的值
        if (R > = 0 && E[R] == T)
        {
            return new vector<int>{L, R};
        }
        else
        {
            return new vector<int>{-1, -1};
        }
    }
}
```

---

### 排序算法（基本上都是分治的思想，要么top-down，要么bottom-up）
#### 快速排序(分治top-down递归)
* 快速排序的基本过程：
  1. 进行每一趟排序时， 从数据中选出一个pivot，然后将大于等于或小于等于pivot的数值分别调整到pivot的左右两侧
  2. 然后再分别对pivot左右两部分数据再进行快速排序。 重复上述操作，直到待排序数据长度等于1.
* 快速排序的特点：
  1. 时间复杂度O(nlogn) 空间复杂度O(1) 是不稳定排序算法
  2. 递归型的快速排序通常需要实现两个个helper函数
    * 第一个用来调用快速排序算法，分割排序后数据以及重复调用自身；
    * 第二个实现快速排序算法。每次调用它，都先确定一个pivot，然后将大于等于或小于等于pivot的数据分别放在pivot两侧）
  3. 快速排序有Lomuto 和 Hoare两种常见的实现方式。

* Lomuto快速排序:
  1. 选择数据中的首个元素 或者 最后一个元素作为pivot。
  2. 将大于或者小于pivot的数据 放到pivot前面 （这里看是升序还是降序）
  3. 然后将当前pivot放到它的**最终位置**上。
  4. 重复递归，直至出口为 L < R

```cpp
class Solution{
    void lquick(vector<int> &E, int L, int R)
    {
	     if (L < R)
	     {
		       int p = lpartition(E, L, R);
		       lquick(E, L, p - 1);
		       lquick(E, p + 1, R);
	     }
}

    int lpartition(vector<int> &E, int L, int R)
    {
	     //i指定了当前pivot在排序后最终位置的前一个元素
       //快排交换元素的起点是E[-1]，每次找到标定的元素值E[j] < pivot时
       //应该是i先自加，然后和E[j]进行swap
       //最后i位置是pivot的最终位置的前一个元素
	     int pivot = E[R], i = L - 1;
	     for (int j = L; j < R; j++)
	     {
		       if (E[j] < pivot)
		       {
			          swap(E[++i], E[j]);
		       }
		       else
		       {
			          //do nothing
		       }
	      }
	      swap(E[++i], E[R]);
	      return i;
    }
}
```

#### 归并排序(分治bottom-up递归)
递归排序的基本过程：
* 分治一般都需要辅助空间。
* 先divide然后再merge，divide的出口是L < R，即子数列长度等于1时不可再分。
* 然后bottom-up的merge, 先是大小为2的小数组被排好序，然后再对两个大小为2的数组排序成大小为4的数组。

递归排序的应用：
* 递归排序除了被用作排序还会考逆序对的问题。
* 同时，递归排序的核心代码也就是标准的分治bottom-up的代码。


* 分治bottom up代码
```cpp
class Solution{
    void mergeSort(...)
    {
        if(递归出口)
        {
            分治递归1();
            分治递归2();
            本层分治处理函数();
        }
    }
    void merge(...)
    {
        处理特定的分治逻辑;
    }
}

```

* 标准归并排序代码
```cpp
//递归地完成归并排序
void mergeSort(int a[], int first, int last, int temp[])
{
	if (first < last)
	{
		int mid = (first + last) / 2;
		mergeSort(a, first, mid, temp);    //左边有序
		mergeSort(a, mid + 1, last, temp); //右边有序
		merge(a, first, mid, last, temp); //再将二个有序数列合并
	}  
}

//将有二个有序数列a[first...mid]和a[mid...last]合并。
void merge(int a[], int first, int mid, int last, int temp[])
{
	int i = first, j = mid + 1, k = 0;
	while (i <= mid && j <= last)
	{
		if (a[i] <= a[j])
        {
            temp[k++] = a[i++];
        }
		else
		{
            temp[k++] = a[j++];
        }
	}
	while (i <= mid)
	{
        temp[k++] = a[i++];
    }
	while (j <= last)
    {
        temp[k++] = a[j++];
    }
	for (i = 0; i < k; i++)
	{
        a[first + i] = temp[i];
    }
}
```

---

### 指针操作：前后差一步指针、快慢指针、左右指针

#### 前后差一步指针
常见题型：字符串滑动窗口问题、
##### 015 链表中倒数第k个结点
题目描述
输入一个链表，输出该链表中倒数第k个结点。  

解题思路：  
对于这种单链表的倒数第N个节点，就是前后差异指针方法。  

然后关于指定第k个节点的问题，都会需要注意类似：  
  * 链表可能为NULL  
  * 链表长度可能没有K个  
的边界问题。  

```cpp
/// 1 -> 2 -> 3 -> 4 -> 5
/// 比如要走倒数第3个节点
/// 那么right先走到第3 - 1个节点&[2]
/// 那么right指针向前走到其下一个节点为NULL时, left节点既是倒数第K个节点
/// 此时两个指针相差为K - 1
/// 因此right需要走到链表尾部前一个结点


/// 1 -> 2 -> 3 -> 4 -> 5
/// 比如要走倒数第3个节点
/// 那么right先走到第3个节点&[2]
/// 那么right指针向前走到链表尾部为NULL时, left节点既是倒数第K个节点
/// 此时两个指针相差为K
/// 因此right需要走到链表尾部前

class Solution
{
public:
    ListNode* FindKthToTail(ListNode* pListHead, unsigned int k)
    {
        if(pListHead == NULL)
        {
            return NULL;
        }
        unsigned int i = 0;
        ListNode *right = pListHead;

        //  left指针先向前走K - 1步
        while(i < k - 1 && right != NULL)
        {
            debug <<"index  = " <<i <<", value = " <<right->val <<endl;
            right = right->next;
            i++;
        }

        if(right == NULL)
        {
            cout <<"the list length = " <<i <<" < " <<k <<endl;
            return NULL;
        }

        ListNode *left = pListHead;
        while(right->next != NULL)
        {
            debug <<"index  = " <<i++ <<", value = " <<right->val <<endl;

            left = left->next;
            right = right->next;
        }

        return left;

    }
};
```

#### 快慢指针
常见题型： 链表环问题、

##### 141. Linked List Cycle 判断链表是否有环

解题思路：
这道题是快慢指针的经典应用。只需要设两个指针，一个每次走一步的慢指针和一个每次走两步的快指针，如果链表里有环的话，两个指针最终肯定会相遇。代码如下：

```cpp
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode *slow = head, *fast = head;
        //注意快慢指针循环的判断条件是：
        //快指针本身非空且快指针的下一个节点也非空
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) return true;
        }
        return false;
    }
};
```

#### 左右指针*
常见题型：字符串翻转问题、字符串回文问题

##### 167. Two Sum II - Input array is sorted 两数之和之二 - 输入数组有序
Given an array of integers that is already sorted in ascending order, find two numbers such that they add up to a specific target number.
The function twoSum should return indices of the two numbers such that they add up to the target, where index1 must be less than index2. Please note that your returned answers (both index1 and index2) are not zero-based.  
You may assume that each input would have exactly one solution.   
Input: numbers={2, 7, 11, 15}, target=9  
Output: index1=1, index2=2  

解题思路：  
* 需要两个指针，一个指向开头，一个指向末尾，然后向中间遍历。
* 如果指向的两个数相加正好等于target的话，直接返回两个指针的位置即可。
* 若小于target，左指针右移一位。
* 若大于target，右指针左移一位，以此类推直至两个指针相遇停止，参见代码如下：
```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int l = 0, r = numbers.size() - 1;
        while (l < r) {
            int sum = numbers[l] + numbers[r];
            if (sum == target) return {l + 1, r + 1};
            else if (sum < target) ++l;
            else --r;
        }
        return {};
    }
};
```

##### 633. Sum of Square Numbers 平方数之和
Given a non-negative integer c, your task is to decide whether there're two integers a and b such that a2 + b2 = c.  

Example 1:  

Input: 5  
Output: True  
Explanation: 1 * 1 + 2 * 2 = 5  

解题思路：  
这里用a和b代表了左右两个范围，分别为0和c的平方根，然后while循环遍历，如果a*a + b*b刚好等于c，那么返回true；如果小于c，则a增大1；反之如果大于c，则b自减1，参见代码如下：
```cpp
class Solution {
public:
    bool judgeSquareSum(int c) {
        int a = 0, b = sqrt(c);
        while (a <= b) {
            if (a * a + b * b == c) return true;
            else if (a * a + b * b < c) ++a;
            else --b;
        }
        return false;
    }
};
```

##### 345. Reverse Vowels of a String（双指针+额外判定 变形字符串）
Write a function that takes a string as input and reverse only the vowels of a string.  

Example 1:  
Given s = "hello", return "holle".  

Example 2:  
Given s = "leetcode", return "leotcede".  

解题思路：  
这道题让我们翻转字符串中的元音字母，元音字母有五个a,e,i,o,u，需要注意的是大写的也算，所以总共有十个字母。
* 我们写一个isVowel的函数来判断当前字符是否为元音字母。
* 如果两边都是元音字母，那么我们交换。
* 如果左边的不是，向右移动一位，如果右边的不是，则向左移动一位，参见代码如下：
```cpp
class Solution {
public:
    string reverseVowels(string s) {
        int left = 0, right= s.size() - 1;
        while (left < right) {
            if (isVowel(s[left]) && isVowel(s[right])) {
                swap(s[left++], s[right--]);
            } else if (isVowel(s[left])) {
                --right;
            } else {
                ++left;
            }
        }
        return s;
    }
    bool isVowel(char c) {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
    }
};
```

##### 680. Valid Palindrome II(可以修改一次字符串，再判断回文串的问题)
Given a non-empty string s, you may delete at most one character. Judge whether you can make it a palindrome.  

Example 1:  
Input: "aba"  
Output: True  
Example 2:  
Input: "abca"  
Output: True  
Explanation: You could delete the character 'c'.  

解题思路：  
* 这道题是之前那道Valid Palindrome的拓展，还是让我们验证回复字符串，但是区别是这道题的字符串中只含有小写字母，而且这道题允许删除一个字符。
* 那么当遇到不匹配的时候，我们到底是删除左边的字符，还是右边的字符呢，我们的做法是两种情况都要算一遍，只要有一种能返回true，那么结果就返回true。
* 我们可以写一个子函数来判断字符串中的某一个范围内的子字符串是否为回文串，参见代码如下：.

```cpp
class Solution {
public:
    bool validPalindrome(string s) {
        int left = 0, right = s.size() - 1;
        while (left < right)
        {
            if (s[left] != s[right])
            {
                return isValid(s, left, right - 1) || isValid(s, left + 1, right);
            }
            ++left;
            --right;
        }
        return true;
    }
    bool isValid(string s, int left, int right)
    {
        while (left < right)
        {
            if (s[left] != s[right])
            {
                return false;
            }
            ++left;
            --right;
        }
        return true;
    }
};
```

---

### 树的算法：树的遍历(前/中/后/层序)、树的恢复(前+中/中+后恢复树)、树的分解(树转数组、树转链表)
参考TreeAndLinkedList的文档



---
