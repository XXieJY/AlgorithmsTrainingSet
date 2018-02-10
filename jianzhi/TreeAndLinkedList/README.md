树和链表：
  * 026--复杂链表的复制
  * 025--二叉树中和为某一值的路径
  * 024--二叉搜索树的后序遍历序列
  * 023--从上往下打印二叉树



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

* 题解2：
使用头插法逆序单向链表：  


#### 006 重建二叉树
题目描述
输入某二叉树的前序遍历和中序遍历的结果，请重建出该二叉树。  
假设输入的前序遍历和中序遍历的结果中都不含重复的数字。

> 输入
前序遍历序列{1,2,4,7,3,5,6,8}  
中序遍历序列{4,7,2,1,5,3,8,6}

则重建二叉树并返回。

#####解题思路：
首先树的重建也可以算作遍历树的相关问题，然后遍历树的问题都要和递归有关系。

首先要明确前序遍历和中序遍历之间的关系：
  * 前序遍历的顺序为：根左右  
  * 中序遍历的顺序为：左根右  

因此可以根据这个关系指定重建树的递归规则：
  1. 我们先根据前序遍历序列的第一个确定根，然后在中序遍历的序列中找到根的位置，根左边的就是其左子树，右边就是其右子树
  2. 构建根和左右子树
  3. 递归的进行1和2

```cpp
static void PreOrder(TreeNode *root)
 {
     if(root == NULL)
     {
         return;
     }
     cout <<root->val;
     PreOrder(root->left);
     PreOrder(root->right);
 }

 static void InOrder(TreeNode *root)
 {
     if(root == NULL)
     {
         return;
     }
     InOrder(root->left);
     cout <<root->val;
     InOrder(root->right);
 }



class Solution
{
public:
 struct TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> in)
 {
     //  前序遍历的长度跟中序遍历的长度应该相同
     if(pre.size( ) != in.size( ))
     {
         return NULL;
     }

     // 长度不能为0
     int size = pre.size( );
     if(size == 0)
     {
         return NULL;
     }

     int length = pre.size( );
     int value = pre[0];      //  前序遍历的第一个结点是根节点
     TreeNode *root = new TreeNode(value);

     //  在中序遍历中查找到根的位置
     int rootIndex = 0;
     for(rootIndex = 0; rootIndex < length; rootIndex++)
     {
         if(in[rootIndex] == value)
         {
             break;
         }
     }
     if(rootIndex >= length)
     {
         return NULL;
     }

     ///  区分左子树和右子树
     ///  中序遍历中, 根左边的就是左子数, 右边的就是右子树
     ///  前序遍历中, 根后面是先遍历左子树, 然后是右子树

     ///  首先确定左右子树的长度, 从中序遍历in中确定
     int leftLength = rootIndex;
     int rightLength = length - 1 - rootIndex;
     vector<int> preLeft(leftLength), inLeft(leftLength);
     vector<int> preRight(rightLength), inRight(rightLength);
     for(int i = 0; i < length; i++)
     {
         if(i < rootIndex)
         {
             //  前序遍历的第一个是根节点, 根后面的(leftLegnth = rootIndex) - 1个节点是左子树, 因此是i+1
             preLeft[i] = pre[i + 1];
             //  中序遍历前(leftLength = rootIndex) - 1个节点是左子树, 第rootIndex个节点是根
             inLeft[i] = in[i];

         }
         else if(i > rootIndex)
         {
             //  前序遍历的第一个是根节点, 根后面的(leftLegnth = rootIndex) - 1个节点是左子树, 后面是右子树
             preRight[i - rootIndex - 1] = pre[i];
             //  中序遍历前(leftLength = rootIndex) - 1个节点是左子树, 第rootIndex个节点是根, 然后是右子树
             inRight[i - rootIndex - 1] = in[i];

         }
     }
     for(int i = 0; i < leftLength; i++)
     {
     }
     for(int i = 0; i < rightLength; i++)
     {
     }

     root->left = reConstructBinaryTree(preLeft, inLeft);
     root->right = reConstructBinaryTree(preRight, inRight);

     return root;
 }

};
```

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

* 递归解法：递归实现合并多个链表，注意需要在递归的开始处进行链表为空的判断。（这个判断
的作用相当于while循环合并数组中的出口条件：
```cpp
class Solution
{
public:
    ListNode* Merge(ListNode *pLeft, ListNode *pRight)
    {
        //在递归开始处进行链表为空的判断
        if(pLeft == NULL)
        {
            debug <<"left list is NULL" <<endl;
            return pRight;
        }
        else if(pRight == NULL)
        {
            debug <<"right list is NULL" <<endl;
            return pLeft;
        }

        ListNode *head = NULL;

        if(pLeft->val < pRight->val)
        {
            head = pLeft;
            head->next = Merge(pLeft->next, pRight);
        }
        else
        {
            head = pRight;
            head->next = Merge(pLeft, pRight->next);
        }

        return head;
    }
};
```

* while循环解法：正常while循环，就是在while处进行链表为空的判断。最后哪个链表还剩下的，
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

#### 018 树的子结构
题目描述
> 输入两颗二叉树A，B，判断B是不是A的子结构。

#####解题思路：  
要查找树A中是否存在和树B结构一样的子树，可以分成两步递归：  

1. 第一步：  
**递归地在树A中找到和B的根节点的值一样的结点R； 这实际上就是树的遍历。**  
递归调用HasSubTree遍历二叉树A。如果发现某一结点的值和树B的头结点的值相同，则转向第2步判断两个结点为根的数是否存在父子关系

2. 第二步：  
**再递归地判断树A中以R为根结点的子树是不是包含和树B一样的结构：**  
这个过程其实就是要要判断两棵树对应的节点数据是否相同。这个是一个递归的过程:
    * 判断B树是否为空：
      * 如果当前传入的B树节点是空，则说明B树的某条到叶子节点的路径是在A树中的，
  此时应该在递归中返回true。
      * 如果当前传入的B树节点非空，但A树是空，则说明B树这一条路径不能在A树中cover住，
    所以此时应该在递归中返回false。

    * 如果A,B树当前传入结点都非空，那么就去判断这两个节点是否相等：
      * 如果不相等，则返回false。
      * 如果相等，则继续递归判断左右子节点。


```cpp
class Solution {
public:
    bool HasSubtree(TreeNode* A, TreeNode* B)
    {
        //第一个递归，在A中找到B的根节点相等的节点，并调用第二递归进行判定
        if(B == NULL || A == NULL)
        {
            return false;
        }

        bool result;
        result = false;
        if(A->val == B->val)
        {
            result = DoesAHaveB(A, B);
        }

        if(result != true)
        {
            return HasSubtree(A->left, B)
            || HasSubtree(A->right, B);    
        }
        else
        {
            return true;
        }

    }

    bool DoesAHaveB(TreeNode *A, TreeNode *B)
    {
        if(B == NULL)      //  子树为NULL，那么必然是子树
        {
            return true;
        }
        else if(A == NULL)      //  子树不是NULL, 但是父亲树是NULL
        {
            return false;
        }

        //  两个节点的值不相等，那么两个树必然不是父子关系
        if(A->val != B->val)
        {
            return false;
        }
        else      // 否则当前节点当前相等，则递归的判断左子树和右子树对应节点是否相同
        {
            return DoesAHaveB(A->left, B->left)
                && DoesAHaveB(A->right, B->right);
        }
    }
};
```

#### 019 二叉树的镜像
题目描述

操作给定的二叉树，将其变换为源二叉树的镜像。

#####解题思路：  
1. 递归解法制造镜像二叉树最简单： 按照先序遍历访问每个节点，然后交换当前节点的左右指针
即可。
```cpp
class Solution
{
public:
    void Mirror(TreeNode *pRoot)
    {

        if(pRoot == NULL)
        {
            return;
        }

        swap(pRoot->left, pRoot->right);
        Mirror(pRoot->left);
        Mirror(pRoot->right);
    }

};
```

2. 非递归解法:  
非递归遍历树时必须使用栈对必要的节点指针进行保存。

```cpp
class Solution
{
public:
    //第一个算法直接用栈模拟先序遍历的完整过程
    void MirrorPre(TreeNode *root)
    {
        if(root == NULL)
        {
            return ;
        }

        stack<TreeNode *> nstack;
        TreeNode *node = root;

        while(node != NULL
           || nstack.empty( ) != true)
        {
            while(node != NULL)
            {
                //先序遍历先访问当前节点
                if(node->left != NULL || node->right != NULL)
                {
                    swap(node->left, node->right);
                }
                //然后将当前节点存到栈，因为后面还需要它来访问右子树
                nstack.push(node);
                //然后继续访问左子节点
                node = node->left;
            }

            //直到当前节点为空，访问上一个节点的右子节点
            if(nstack.empty( ) != true)
            {
                node = nstack.top( );
                nstack.pop( );
                node = node->right;
            }
        }
    }

    //第二个事实上是一个BFS算法，宽度优先遍历/层序遍历树
    void MirrorPreBFS(TreeNode *root)
    {
        if(root == NULL)
        {
            return;
        }
        TreeNode *node;
        stack<TreeNode *> nstack;

        nstack.push(root);
        while(nstack.empty() != true)
        {
            node = nstack.top( );
            nstack.pop( );

            //  先交换, 然后递归左，接着递归右
            //  相当与一次前序遍历
            if(node->left != NULL || node->right != NULL)
            {
                swap(node->left, node->right);
            }

            if(node->left != NULL)
            {
                nstack.push(node->left);
            }
            if(node->right != NULL)
            {
                nstack.push(node->right);
            }
        }
    }

};
```

```cpp
//中序遍历
class Solution
{
public:
    void MirrorIn(TreeNode *root)
    {
        if(root == NULL)
        {
            debug <<"The tree is NULL..." <<endl;
            return NULL;
        }

        stack<TreeNode *> nstack;
        TreeNode *node = root;

        //  开始遍历整个二叉树
        while(node != NULL || nstack.empty() != true)
        {
            // 不输出当前根节点，但是递归直至当前根节点node的最左端
            while(node != NULL)
            {
                nstack.push(node);
                node = node->left;
            }

            //  此时栈顶的元素是当前最左元素
            //  它应该被输出
            if(nstack.empty( ) != true)
            {
                node = nstack.top( );

                //  将原来的输出改为交换左右子树即可
                if(node->left != NULL || node->right != NULL)
                {
                    swap(node->left, node->right);
                }

                nstack.pop( );
                //  中序遍历输出根后，向右转向
                //  此时由于左右子树交换，因此原来的右子树是其左子树，向左转向
                node = node->left;
            }
        }
    }

};
```


2. 非递归解法：








#### 027 二叉搜索树与双向链表
题目描述

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
