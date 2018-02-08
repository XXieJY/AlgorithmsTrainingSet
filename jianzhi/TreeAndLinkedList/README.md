树和链表：
  * 026--复杂链表的复制
  * 025--二叉树中和为某一值的路径
  * 024--二叉搜索树的后序遍历序列
  * 023--从上往下打印二叉树
  * 019--二叉树的镜像
  * 018--树的子结构
  * 017--合并两个排序的链表
  * 016--反转链表
  * 015--链表中倒数第k个结点
  * 006--重建二叉树

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
