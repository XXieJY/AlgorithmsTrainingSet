树和链表：
  * 026--复杂链表的复制
  * 025--二叉树中和为某一值的路径
  * 024--二叉搜索树的后序遍历序列
  * 023--从上往下打印二叉树
  * 019--二叉树的镜像
  * 018--树的子结构
  * 017--合并两个排序的链表
  * 016--反转链表



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
