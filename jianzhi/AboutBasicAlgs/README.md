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

#### 树的遍历(前/中/后/层序)

* 递归法二叉树前序遍历
144. Binary Tree Preorder Traversal
```cpp
void PreOrder(TreeNode *root)
{
    //递归出口
    if(root == NULL)
    {
        return;
    }
    //前序遍历在当前节点先做些操作
    //do something here
    PreOrder(root->left);
    PreOrder(root->right);
    //如果还需要前序遍历的递归中结合一点bottom up的操作应该写在这里
    //do bottom up operations

}

```

* 非递归法二叉树前序遍历  
用非递归的方法，这就要用到栈辅助二叉树遍历。由于先序遍历的顺序是"根-左-右", 算法为：
1. 把根节点push到栈中
2. 循环检测栈是否为空，若不空，则取出栈顶元素，保存其值，然后看其右子节点是否存在，若存在则push到栈中。再看其左子节点，若存在，则push到栈中。  

代码如下：
```cpp
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        if (!root)
        {
            return{};
        }
        vector<int> res;
        stack<TreeNode*> s {{root}};
        while (!s.empty())
        {
            TreeNode *t = s.top();
            s.pop();
            res.push_back(t->val);
            if (t->right)
            {
                s.push(t->right);
            }
            if (t->left)
            {
                s.push(t->left);
            }
        }
        return res;
    }
};
```


* 中序遍历的递归解法：
```cpp
// Recursion
class Solution {
public:
    vector<int> inorderTraversal(TreeNode *root) {
        vector<int> res;
        inorder(root, res);
        return res;
    }
    void inorder(TreeNode *root, vector<int> &res) {
        //递归出口
        if (!root)
        {
          return;
        }
        if (root->left)
        {
          inorder(root->left, res);
        }
        //中序遍历先左，然后再对当前节点做一些操作
        //do somethin here
        res.push_back(root->val);
        //最后再右
        if (root->right)
        {
          inorder(root->right, res);
        }
    }
};
```

* 中序遍历非递归解法*：  
需要用栈来做，思路是从根节点开始，先将根节点压入栈，然后再将其所有左子结点压入栈，然后取出栈顶节点。  
保存节点值，再将当前指针移到其右子节点上，若存在右子节点，则在下次循环时又可将其所有左子结点压入栈中。这样就保证了访问顺序为左-根-右，代码如下：

```cpp
class Solution {
public:
    vector<int> inorderTraversal(TreeNode *root) {
        vector<int> res;
        stack<TreeNode*> s;
        TreeNode *p = root;
        while (p || !s.empty())
        {
            //将当前节点和其所有左子节点入栈
            while (p)
            {
                s.push(p);
                p = p->left;
            }
            //取出栈顶节点并访问
            p = s.top();
            s.pop();
            res.push_back(p->val);
            //然后转向这个节点的右子节点
            p = p->right;
        }
        return res;
    }
};
```


* 后序遍历递归解法*：

```cpp
class Solution {
public:
    vector<int> inorderTraversal(TreeNode *root) {
        vector<int> res;
        inorder(root, res);
        return res;
    }
    void inorder(TreeNode *root, vector<int> &res) {
        //递归出口
        if (!root)
        {
          return;
        }
        if (root->left)
        {
          inorder(root->left, res);
        }
        //再右
        if (root->right)
        {
          inorder(root->right, res);
        }
        //最后再对当前节点做一些操作
        //do somethin here
        res.push_back(root->val);
    }
};
```

* 后序遍历非递归解法*：
由于后序遍历的顺序是左-右-根，而先序遍历的顺序是根-左-右，二者其实还是很相近的，我们可以先在先序遍历的方法上做些小改动，使其遍历顺序变为根-右-左，然后翻转一下，就是左-右-根啦，翻转的方法我们使用反向Q，哦不，是反向加入结果res，每次都在结果res的开头加入结点值，而改变先序遍历的顺序就只要该遍历一下入栈顺序，先左后右，这样出栈处理的时候就是先右后左啦，参见代码如下：


```cpp
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        if (!root) return {};
        vector<int> res;
        stack<TreeNode*> s{{root}};
        while (!s.empty()) {
            TreeNode *t = s.top(); s.pop();
            res.insert(res.begin(), t->val);
            if (t->left) s.push(t->left);
            if (t->right) s.push(t->right);
        }
        return res;
    }
};
```

* 二叉树层序遍历（队列辅助层序遍历）
解题思路：  
* 层序遍历二叉树是典型的广度优先搜索BFS的应用，但是这里稍微复杂一点的是，我们要把各个层的数分开，存到一个二维向量里面。
* 大体思路还是基本相同的，建立一个queue，然后先把根节点放进去，这时候找根节点的左右两个子节点，这时候去掉根节点，此时queue里的元素就是下一层的所有节点。
* 用一个for循环遍历它们，然后存到一个一维向量里，遍历完之后再把这个一维向量存到二维向量里，以此类推，可以完成层序遍历。代码如下：

```cpp
class Solution {
public:
    vector<vector<int> > levelOrder(TreeNode *root) {
        //判断边界条件
        if (root == NULL)
        {
          return res;
        }
        //声明辅助变量
        //res保存层序遍历值，queue辅助层序遍历，层序遍历需要首先把根节点插入队列
        vector<vector<int> > res;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            vector<int> oneLevel;
            int size = q.size();
            //每层只在queue中取当前size个的节点
            for (int i = 0; i < size; ++i) {
                TreeNode *node = q.front();
                q.pop();
                oneLevel.push_back(node->val);
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            res.push_back(oneLevel);
        }
        return res;
    }
};
```

### 二叉树重建相关问题*：
**使用递归、前中后序的知识（二叉树和数组重建、二叉树和链表重建）**  


首先树的重建也可以算作遍历树的相关问题，然后遍历树的问题都要和递归有关系。  

首先要明确前序遍历和中序遍历之间的关系：  
  * 前序遍历的顺序为：根左右  
  * 中序遍历的顺序为：左根右  

因此可以根据这个关系指定重建树的递归规则：
  1. 我们先根据前序遍历序列的第一个确定根，然后在中序遍历的序列中找到根的位置，根左边的就是其左子树，右边就是其右子树
  2. 构建根和左右子树
  3. 递归的进行1和2


#### （用前序遍历和中序遍历还原二叉树）
解题思路*：  
* 由于先序的顺序的第一个肯定是根，所以原二叉树的根节点可以知道，题目中给了一个很关键的条件就是树中没有相同元素，有了这个条件我们就可以在中序遍历中也定位出根节点的位置，并以根节点的位置将中序遍历拆分为左右两个部分，分别对其递归调用原函数。代码如下：

```cpp
class Solution {
public:
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    {
        return buildTree(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1);
    }
    TreeNode *buildTree(vector<int> &preorder, int pLeft, int pRight, vector<int> &inorder, int iLeft, int iRight)
    {
        if (pLeft > pRight || iLeft > iRight)
        {
            return NULL;
        }
        int i = 0;
        for (i = iLeft; i <= iRight; ++i)
        {
            if (preorder[pLeft] == inorder[i]) break;
        }
        TreeNode *cur = new TreeNode(preorder[pLeft]);
        cur->left = buildTree(preorder, pLeft + 1, pLeft + i - iLeft, inorder, iLeft, i - 1);
        cur->right = buildTree(preorder, pLeft + i - iLeft + 1, pRight, inorder, i + 1, iRight);
        return cur;
    }
};
```

#### （用中序遍历和后序遍历还原二叉树）
解题思路*：  
* 我们知道中序的遍历顺序是左-根-右，后序的顺序是左-右-根，对于这种树的重建一般都是采用递归来做。
* 由于后序的顺序的最后一个肯定是根，所以原二叉树的根节点可以知道，题目中给了一个很关键的条件就是树中没有相同元素，有了这个条件我们就可以在中序遍历中也定位出根节点的位置，并以根节点的位置将中序遍历拆分为左右两个部分，分别对其递归调用原函数。代码如下：

```cpp
class Solution {
public:
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
        return buildTree(inorder, 0, inorder.size() - 1, postorder, 0, postorder.size() - 1);
    }
    TreeNode *buildTree(vector<int> &inorder, int iLeft, int iRight, vector<int> &postorder, int pLeft, int pRight) {
        if (iLeft > iRight || pLeft > pRight) return NULL;
        TreeNode *cur = new TreeNode(postorder[pRight]);
        int i = 0;
        for (i = iLeft; i < inorder.size(); ++i) {
            if (inorder[i] == cur->val) break;
        }
        cur->left = buildTree(inorder, iLeft, i - 1, postorder, pLeft, pLeft + i - iLeft - 1);
        cur->right = buildTree(inorder, i + 1, iRight, postorder, pLeft + i - iLeft, pRight - 1);
        return cur;
    }
};
```

### 树的分解
#### 二叉树转链表（先序遍历将二叉树展开）
解题思路：  
* 利用DFS的思路找到最左子节点，然后回到其父节点，把其父节点和右子节点断开，将原左子结点连上父节点的右子节点上，然后再把原右子节点连到新右子节点的右子节点上，然后再回到上一父节点做相同操作。代码如下：

```cpp
// Recursion
class Solution {
public:
    void flatten(TreeNode *root) {
        //选是一波dfs找到最左叶子节点
        if (!root)
        {
             return;
        }
        if (root->left)
        {
            flatten(root->left);
        }
        if (root->right)
        {
            flatten(root->right);
        }

        //然后bottom-up地展开二叉树
        TreeNode *tmp = root->right;
        root->right = root->left;
        root->left = NULL;
        while (root->right)
        {
             root = root->right;
        }
        root->right = tmp;
    }
};
```


#### BST转双向链表
**题目描述**

输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的双向链表。
要求不能创建任何新的结点，只能调整树中结点指针的指向。

##### 解题思路：
将BST转换为有序双向链表是一道比较常考的题目，因为同时考察到了BST的性质，同时又是和链表
指针操作密切相关的实操题目。  
首先，变换BST的前提是了解BST的基本性质：
  * BST的左节点的值 < 根结点的值 < 右子节点的值
  * BST的中序遍历结果是有序数列

因此解法有两种：
  * 解法一：  
  在中序遍历的过程中完成从二叉搜索树到双向链表的转换，访问过程需修改为链接操作。  
  这里需要注意的是：中序遍历中当前结点的前一个节点
    * 要么是当前结点的左子树的的最右孩子  
    * 要么是当前结点其前一个节点的右孩子    


  * 中序遍历过程中需要做的就是：  
    * 当前节点左指针指向前一个被访问节点  
    * 如果前一个被访问节点不为NULL,则让前一个节点的右指针指向当前被访问节点
    * 记录当前被访问节点为前一个被访问节点，然后继续访问右子树、继续中序遍历

```cpp
class Solution {
public:
    TreeNode* Convert(TreeNode* pRootOfTree)
    {
        if(pRootOfTree == NULL)
        {
            return NULL;
        }

        TreeNode *pLastNode = NULL;
        ConvertRecursion(pRootOfTree, &pLastNode);

        TreeNode *node = pLastNode;
        while(pLastNode != NULL
           && pLastNode->left != NULL)
        {
           pLastNode = pLastNode->left;
        }

        return pLastNode;
    }

    void ConvertRecursion(TreeNode *root, TreeNode **pLastNode)
    {
        //按中序遍历方式遍历BST同时在访问节点时构造双向链表
        if(root == NULL)
        {
            return;
        }
        TreeNode *currNode = root;

        //先递归左子树
        if(currNode->left != NULL)
        {
            ConvertRecursion(root->left, pLastNode);
        }


        //再访问当前节点，将BST进行向双向链表的转化
        currNode->left = *pLastNode;
        if(*pLastNode != NULL)
        {
            (*pLastNode)->right = currNode;
        }

        //将当前节点记作上一个被访问节点
        *pLastNode = currNode;

        //继续按中序遍历访问右子树
        if(currNode->right != NULL)
        {
            ConvertRecursion(currNode->right, pLastNode);
        }
    }
};
```
