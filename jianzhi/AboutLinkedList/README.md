## 链表

### 常见考点
**（其中双指针分为先后指针和快慢指针两种，先后指针主要解决倒数第k个节点相关问题，快慢指针主要解决环的问题）**

* 链表排序算法：主要记住基于链表的归并排序（链表的递归）

* 逆向查找/打印相关： 使用栈、先后指针、头插法；

* 链表变形相关：使用指针遍历；经常用到头结点统一遍历操作；快慢指针找中间节点、头插法、隔空插法；（合并两个链表；链表去重；）

* 链表环相关：快慢指针找入口节点；

* 链表和树的转化相关：合理地使用递归在链表和树之间相互转化

* 其他：BST和卡特兰数、

---

### 链表排序相关

#### 148. Sort List

常见排序方法有很多，插入排序，选择排序，堆排序，快速排序，冒泡排序，归并排序，桶排序等等。。它们的时间复杂度不尽相同，而这里题目限定了时间必须为O(nlgn)，符合要求只有快速排序，归并排序，堆排序，而根据单链表的特点，最适于用归并排序。代码如下：

```cpp
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if (!head || !head->next) return head;
        ListNode *slow = head, *fast = head, *pre = head;
        while (fast && fast->next) {
            pre = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        pre->next = NULL;
        return merge(sortList(head), sortList(slow));
    }
    ListNode* merge(ListNode* l1, ListNode* l2) {
        ListNode *dummy = new ListNode(-1);
        ListNode *cur = dummy;
        while (l1 && l2) {
            if (l1->val < l2->val) {
                cur->next = l1;
                l1 = l1->next;
            } else {
                cur->next = l2;
                l2 = l2->next;
            }
            cur = cur->next;
        }
        if (l1) cur->next = l1;
        if (l2) cur->next = l2;
        return dummy->next;
    }
};
```


---

### 逆向查找/打印

#### 005 从尾到头打印链表
题目描述
输入一个链表，从尾到头打印链表每个节点的值。

#####解题思路：  
* 本题考察两个方向：
  * 单向链表的头插法可以使得单向链表轻松倒序
  * 递归在本质上就是一个栈结构，使用递归可以模拟栈的先进后出特性。

* 题解1：  
使用递归访问单项链表，直到node->next==null; 然后开始从后往前遍历单向链表。

```cpp
class Solution {
  public:
    vector<int> dev;
    vector<int>& printListFromTailToHead(struct ListNode* head) {

    if(head!=NULL) {
      if(head->next!=NULL) {
        dev=printListFromTailToHead(head->next);
      }
      dev.push_back(head->val);
    }
    return dev;
  }
};
```

**快指针走K-1步时，慢指针最终指向倒数第K个节点；快指针走K步时，慢指针最终指向倒数第K+1个节点；**

#### 015 链表中倒数第k个结点
题目描述
输入一个链表，输出该链表中倒数第k个结点。

#####解题思路：
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

#### 19. Remove Nth Node From End of List

解题思路：  
用两个指针来帮助我们解题，pre和cur指针。
* 首先cur指针先向前走N步，如果此时cur指向空，说明N为链表的长度，则需要移除的为首元素，那么此时我们返回head->next即可.
* 如果cur存在，我们再继续往下走，此时pre指针也跟着走，直到cur为最后一个元素时停止，**此时pre指向要移除元素的前一个元素**，我们再修改指针跳过需要移除的元素即可。代码如下：
```cpp
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if (!head->next) return NULL;
        ListNode *pre = head, *cur = head;
        for (int i = 0; i < n; ++i) cur = cur->next;
        if (!cur) return head->next;
        while (cur->next) {
            cur = cur->next;
            pre = pre->next;
        }
        pre->next = pre->next->next;
        return head;
    }
};
```


#### 016 反转链表
题目描述  
输入一个链表，反转链表后，输出链表的所有元素。  

#####解题思路：  
反转单向链表使用头插法就行：如果每次插入元素的时候都是在头结点的前一个位置插入，那么链表元素的顺序正好跟插入的顺序相反，然后也是要注意每次保存next的位置防止丢失。  

```cpp
class Solution
{
public:
    ListNode* ReverseList(ListNode* L)
    {
        if(L == NULL)
        {
            return NULL;
        }

        ListNode *B;
        ListNode *A;
        ListNode *TMP;

        //  由于链表不带头节点，因此第一个元素的插入需要特殊处理
        A = L;
        B = A->next;
        TMP = NULL;         
        A->next = NULL;

        //  首先构建原链表的头结点为新链表的尾节点(也就是第一个被插入节点)
        while(B != NULL)
        {
            TMP = B->next;        
            B->next = A;

            A = B;
            B = TMP;          
        }
        return A;
    }
};
```

#### 037 两个链表的第一个公共结点
**题目描述**  
输入两个链表，找出它们的第一个公共结点。

解题思路：  
这一题主要是两种方式：
 * 利用栈从后往前比较找到第一个不相同的点，这个点就是第一个公共节点的前一个节点。
 * 利用快慢指针的方式，链表长的先走，链表短的后走。然后这里计算快慢指针的k步有一种比较geek的方法把：
    * 先同时遍历两个链表，如果长度不一致则比然有一个链表先到头，此时没到头的链表的剩余节点数就是快慢指针需要的差距，这时候再交换链表指向，将原本指向短链表的指针指向长链表，再继续同时遍历，最后就能够取得快慢指针的效果。

解法一利用栈的先入后出逆转链表：
```cpp
class Solution
{
public:
    ListNode* FindFirstCommonNode(ListNode *leftHead, ListNode *rightHead)
    {
        ListNode *left = leftHead;
        ListNode *right = rightHead;

        stack<ListNode *> leftStack;
        stack<ListNode *> rightStack;

        /// 结点依次入栈
        while(left != NULL)
        {
            leftStack.push(left);
            left = left->next;
        }

        while(right != NULL)
        {
            rightStack.push(right);
            right = right->next;
        }

        ///  开始同步弹出元素
        while(leftStack.empty( ) != true
           && rightStack.empty( ) != true)
        {
            left = leftStack.top( );
            right = rightStack.top( );

            ///  不相同的元素就是合并的前一个结点
            if(left != right)
            {
                break;
            }
            leftStack.pop( );
            rightStack.pop( );
        }

        ///  不相同元素的下一个结点就是共同结点
        if(left != right)
        {
            return left->next;
        }
        else
        {
            return NULL;
        }
    }
};
```



解法二利用快慢指针：
```cpp
class Solution {
public:
    ListNode* FindFirstCommonNode(ListNode *pHead1, ListNode *pHead2) {
        ListNode *p1 = pHead1;
        ListNode *p2 = pHead2;
        while(p1!=p2){
            p1 = (p1==NULL ? pHead2 : p1->next);
            p2 = (p2==NULL ? pHead1 : p2->next);
        }
        return p1;
    }
};
```

---

### 链表变形相关*

**链表变形相关记住要设置头结点（又叫dummy节点），统一整个算法操作**

**使用快慢指针可以快速找到链表中间节点**

#### 203. Remove Linked List Elements(遍历并删除链表中的节点，需要依赖dummy节点和pre指针)

```cpp
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        //创建dummy节点
        ListNode *dummy = new ListNode(-1), *pre = dummy;
        dummy->next = head;
        //使用pre指针，每次pre要处理的是pre->next的那个节点
        //因此pre可以保证不要链表越界遍历，并且可以提前处理终点节点的问题。
        while (pre->next) {
            if (pre->next->val == val) {
                ListNode *t = pre->next;
                pre->next = t->next;
                t->next = NULL;
                delete t;
            } else {
                pre = pre->next;
            }
        }
        return dummy->next;
    }
};
```




#### 24. Swap Nodes in Pairs
解题思路：  
对于迭代实现，还是需要建立dummy节点，注意在连接节点的时候，最好画个图，以免把自己搞晕了，参见代码如下：
```cpp
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        //建立dummy节点
        ListNode *dummy = new ListNode(-1), *pre = dummy;
        dummy->next = head;

        while (pre->next && pre->next->next) {
            ListNode *t = pre->next->next;
            pre->next->next = t->next;
            t->next = pre->next;
            pre->next = t;
            pre = t->next;
        }
        return dummy->next;
    }
};
```

#### 25. Reverse Nodes in k-Group
解题思路**：   
* 这道题让我们以每k个为一组来翻转链表，实际上是把原链表分成若干小段，然后分别对其进行翻转，那么肯定总共需要两个函数，一个是用来分段的，一个是用来翻转的。
* 加入dummy node后的链表变为-1->1->2->3->4->5，如果k为3的话，我们的目标是将1,2,3翻转一下，那么我们需要一些指针，[pre, cur->next]将当前分段区间框起来。然后翻转后pre的位置更新到如下新的位置：
```cpp
class Solution {
public:
    ListNode *reverseKGroup(ListNode *head, int k) {
        //判断边界条件
        if (!head || k == 1)
        {
            return head;
        }
        //创建dummy节点
        ListNode *dummy = new ListNode(-1);
        ListNode *pre = dummy, *cur = head;
        dummy->next = head;
        //循环分段地reverse链表
        int i = 0;
        while (cur)
        {
            ++i;
            //如果[pre,cur->next]构成k的长度的段，对段进行reverse；
            if (i % k == 0)
            {
                pre = reverseOneGroup(pre, cur->next);
                cur = pre->next;
            }
            else
            {
                cur = cur->next;
            }
        }
        return dummy->next;
    }

    ListNode *reverseOneGroup(ListNode *pre, ListNode *next)
    {
        ListNode *last = pre->next;
        ListNode *cur = last->next;
        while(cur != next)
        {
            last->next = cur->next;
            cur->next = pre->next;
            pre->next = cur;
            cur = last->next;
        }
        return last;
    }
};
```

#### 017 合并两个排序的链表

题目描述  
输入两个单调递增的链表，输出两个链表合成后的链表，当然我们需要合成后的链表满足单调不减规则。

> 样例输入  
1 3 5 7 9 2 4  

> 样例输出  
1 2 3 4 5 7 9

#####解题思路：
合并多个链表，多个数组的题目都算作一类题目。这类题目可以使用while循环，每次挑出当前
最小节点然后进行合并。也可以使用递归实现：

while循环解法：正常while循环，就是在while处进行链表为空的判断。最后哪个链表还剩下的，
就让其全部接上去。

```cpp
class Solution
{
public:
    ListNode* Merge(ListNode *pLeft, ListNode *pRight)
    {

        if(pLeft == NULL)
        {
            return pRight;
        }
        else if(pRight == NULL)
        {
            return pLeft;
        }

        ListNode *left = pLeft;
        ListNode *right = pRight;

        //  先生成头结点
        ListNode *head = NULL;
        if(left->val < right->val)
        {
            head = left;
            left = left->next;
        }
        else
        {
            head = right;
            right = right->next;
        }

        //  遍历两个链表
        ListNode *curr = head;

        while(left != NULL && right != NULL)
        {
            //  每次找到一个小的加入新的链表
            if(left->val < right->val)
            {
                curr->next = left;
                curr = curr->next;

                left = left->next;
            }
            else
            {
                curr->next = right;
                curr = curr->next;

                right = right->next;
            }
        }

        //  处理较长链表的剩余部分
        if(left != NULL)
        {
            curr->next = left;
        }
        else
        {
            curr->next = right;
        }
        return head;

    }
};

```

##### 23. Merge k Sorted Lists

解题思路**：
* 这道题让我们合并k个有序链表，并且需要提高合并效率。
* **两两合并问题的高效率解法基本上就是分治法**。
  * 简单来说就是不停的对半划分，比如k个链表先划分为合并两个k/2个链表的任务，再不停的往下划分，直到划分成只有一个或两个链表的任务，开始合并。参见代码如下：

```cpp
class Solution {
public:
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        if (lists.size() == 0) return NULL;
        int n = lists.size();
        while (n > 1) {
            int k = (n + 1) / 2;
            for (int i = 0; i < n / 2; ++i) {
                lists[i] = mergeTwoLists(lists[i], lists[i + k]);
            }
            n = k;
        }
        return lists[0];
    }

    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        ListNode *head = new ListNode(-1);
        ListNode *cur = head;
        while (l1 && l2) {
            if (l1->val < l2->val) {
                cur->next = l1;
                l1 = l1->next;
            } else {
                cur->next = l2;
                l2 = l2->next;
            }
            cur = cur->next;
        }
        if (l1) cur->next = l1;
        if (l2) cur->next = l2;
        return head->next;
    }
};
```


#### 057 删除链表中重复的结点
**题目描述**

在一个排序的链表中，存在重复的结点，请删除该链表中重复的结点，重复的结点不保留，返回链表头指针。  
> 例如，链表1->2->3->3->4->4->5  
处理后为 1->2->5

* 从头到尾判定每个结点是否是重复结点
    * 如果不是重复结点则尾部指针向后移动到这个结点，然后继续判定下一个结点的重复性。
    * 如果是重复结点，那么修改当前尾部指针指向结点的next值，时尾部结点的next指针指向下一个非重复结点上。

```cpp
class Solution
{
public:
    ListNode* deleteDuplication(ListNode* pHead)
    {
        //设置一个trick, 作为头指针, 这样我们无需单独考虑第一个元素
        ListNode *first = new ListNode(-1);
        first->next = pHead;

        ListNode *p = pHead;
        ListNode *last = first;

        while (p != NULL && p->next != NULL)
        {
            //  如果有元素重复
            if (p->val == p->next->val)
            {
                //  就跳过所有重复的数字
                int val = p->val;
                while (p != NULL && p->val == val)
                {
                    p = p->next;
                }

                //  此时p指向了非重复的第一个元素
                //  我们设置last->next = p
                //  但是此时p-val也可能是重复的,
                //  因此我们不可以设置last = p
                //  而是重新进入循环
                last->next = p;
            }
            else
            {
                last = p;
                p = p->next;
            }
        }
        return first->next;
    }
};
```

#### 61. Rotate List
解题思路**：
分析题目可知，就是要找到倒数第k个节点，然后将[k,end]的部分截取出来拼接到链表头部
因此使用快慢指针可解。

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if (!head || !(head->next) || k == 0)
        {
            return head;
        }

        int S = 0;
        for (ListNode* i = head; i; i = i->next)
        {
            ++S;
        }
        if (k == S)
        {
            return head;
        }
        else
        {
            int remain = k % S;
            ListNode* pre = head;
            ListNode* cur = head;
            for (; remain > 0; --remain)
            {
                cur = cur->next;
            }
            while(cur->next)
            {
                pre = pre->next;
                cur = cur->next;
            }
            cur->next = head;
            cur = pre->next;
            pre->next = NULL;
            return cur;
        }
    }
};
```

#### 143. Reorder List

这道链表重排序问题可以拆分为以下三个小问题：

1. 使用快慢指针来找到链表的中点，并将链表从中点处断开，形成两个独立的链表。

2. 将第二个链翻转。

3. 将第二个链表的元素间隔地插入第一个链表中

```cpp
class Solution {
public:
    void reorderList(ListNode *head) {
        if (!head || !head->next || !head->next->next) return;
        ListNode *fast = head;
        ListNode *slow = head;
        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        ListNode *mid = slow->next;
        slow->next = NULL;
        ListNode *last = mid;
        ListNode *pre = NULL;
        while (last) {
            ListNode *next = last->next;
            last->next = pre;
            pre = last;
            last = next;
        }
        while (head && pre) {
            ListNode *next = head->next;
            head->next = pre;
            pre = pre->next;
            head->next->next = next;
            head = next;
        }
    }
};
```




---

### 链表环相关



#### 141. Linked List Cycle 判断链表是否有环

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




#### 056 链表中环的入口结点

题目描述

一个链表中包含环，请找出该链表的环的入口结点。


解题思路：  
设快慢指针，不过这次要记录两个指针相遇的位置，当两个指针相遇了后，让其一指针从链表头开始，此时再相遇的位置就是链表中环的起始位置。代码如下

```cpp
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode *slow = head, *fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) break;
        }
        if (!fast || !fast->next) return NULL;
        slow = head;
        while (slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }
        return fast;
    }
};
```

### 链表和树的转化相关***

这类题型包括：链表转为树，树转为链表；主要就是考察在链式结构中对递归的应用。

#### 109. Convert Sorted List to Binary Search Tree
* 这道题是要求把有序链表转为二叉搜索树。
* 数组方便就方便在可以通过index直接访问任意一个元素，而链表不行。**由于二分查找法每次需要找到中点，而链表的查找中间点可以通过快慢指针来操作。**
* 找到中点后，要以中点的值建立一个数的根节点，然后需要把原链表断开，分为前后两个链表，都不能包含原中节点，然后再分别对这两个链表递归调用原函数，分别连上左右子节点即可。代码如下：

```cpp
class Solution {
public:
    TreeNode *sortedListToBST(ListNode *head) {
        if (!head) return NULL;
        if (!head->next) return new TreeNode(head->val);
        ListNode *slow = head;
        ListNode *fast = head;
        ListNode *last = slow;
        while (fast->next && fast->next->next) {
            last = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        fast = slow->next;
        last->next = NULL;
        TreeNode *cur = new TreeNode(slow->val);
        if (head != slow) cur->left = sortedListToBST(head);
        cur->right = sortedListToBST(fast);
        return cur;
    }
};
```

---
