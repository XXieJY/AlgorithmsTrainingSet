* 063-二叉搜索树的第K个结点
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

    //第二个事实上是一个BFS算法，宽度优先遍历/**层序遍历树**
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

#### 024 二叉搜索树的后序遍历序列
题目描述

输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历的结果。如果是则输出Yes,否则输出No。假设输入的数组的任意两个数字都互不相同。

#####解题思路：
要判定一个序列是否是BST的后序遍历，则必须先熟悉BST的性质：  
  * 二叉排序树或者是一棵空树，或者是具有下列性质的二叉树：

    * 若左子树不空，则左子树上所有结点的值均小于它的根结点的值；

    * 若右子树不空，则右子树上所有结点的值均大于或等于它的根结点的值；

    * 左、右子树也分别为二叉排序树；

    * 没有键值相等的节点。

    * 对一棵二叉搜索树进行中序遍历（左根右）可得到一个关键字递增有序序列。

* 然而，BST的后序序列的合法序列是：  
    * 对于一个序列S，最后一个元素是x （也就是根）  


* 如果去掉最后一个元素的序列为T，那么T满足：

    * T可以分成两段，前一段（左子树）小于x，后一段（右子树）大于x，

    * 且这两段（子树）都是合法的后序序列。

    * 完美的递归定义  

比如二叉排序树的后序遍历是：
> 后序序列 2, 9, 5, 16, 17, 15, 19, 18, 12  

1. 当前树的根是12，12可以把后序序列分成两段：[2,9,5] 和 [16,17,15,19,18]
2. 然后左子树[2,9,5]被子树树根5分割成[2],[9]，右子树是[16,17]，[19,18]
3. 然后继续递归地套用这个关系就可以循环检验出是否是二叉搜索树的后序遍历了

```cpp
class Solution {
public:
	/*
	step1：最后一个为根节点；
	step2：从根节点的左边开始往前遍历，找到第一个比它大的节点作为右子树，记为right
	step3：从右子树的左边开始往前遍历，找到第一个比它小的节点作为左子树，记为left
	step4：判断( left, right )中的值是否都比根节点大，如果有比根节点小的则返回false
	step5: 判断( 0, left )中的值是否都比根节点小，如果有比根节点大的则返回false
	step6: 返回true

	时间复杂度：O(n), 空间复杂度: O(1)
	没有证明过，但是代码通过了，求反例，心里没底
	*/
	bool VerifySquenceOfBST(vector<int> sequence) {
		if (sequence.empty()) return true;
		int len = sequence.size();

		int left = -1, right = -1;
		for (int i = len - 2; i >= 0; --i)
		{
			if (right == -1 && sequence[i] > sequence[len - 1])
                right = i;
			if (left == -1 && sequence[i] < sequence[len - 1])
                left = i;
		}
        cout <<"left = " <<left <<", right = " <<right <<endl;
		for (int i = right - 1; i > left; --i)
        {
            if (sequence[i] < sequence[len - 1])
            {
                return false;
            }
        }
		for (int i = left - 1; i > 0; --i)
		{
			if (sequence[i] > sequence[len - 1])
            {

                return false;
            }

        }
		return true;
	}
};
```

#### 025 二叉树中和为某一值的路径

题目描述
输入一颗二叉树和一个整数，打印出二叉树中结点值的和为输入整数的所有路径。路径定义为从树的根结点开始往下一直到叶结点所经过的结点形成一条路径

#####解题思路：
思路还是比较好想的，用个递归来实现，先序遍历，

* 每次访问一个节点，那么就将当前权值求和
* 如果当前权值和与期待的和一致，那么说明我们找到了一个路径，保存或者输出
* 否则的话就递归其左右孩子节点 这里需要注意一个问题，就是递归退出的时候。  
**权值和的信息是保存在递归栈中的会恢复，但是我们保存的路径是无法恢复的，那么我们就需要在递归返回时将数据弹出**

**针对递归问题，传参数优于使用static共享变量，因为共享变量会导致多线程问题以及资源竞争**
```cpp
class Solution
{
public:
    vector< vector<int> > m_res;

    vector< vector<int> > FindPath(TreeNode* root, int expectNumber)
    {
        if(root == NULL)
        {
            return m_res;
        }
        vector<int> path;
        FindPath(root, expectNumber, path, 0);

        return m_res;
    }

    void FindPath(TreeNode* root, int expectNumber, vector<int> path, int currentSum)
    {
        currentSum += root->val;
        path.push_back(root->val);

        ///
        if(currentSum == expectNumber
        && ((root->left == NULL && root->right == NULL)))
        {
            debug <<"find a path" <<endl;
            for(int i = 0; i < path.size( ); i++)
            {
                debug <<path[i] <<" ";
            }
            debug <<endl;

            m_res.push_back(path);
        }

        if(root->left != NULL)
        {
            FindPath(root->left, expectNumber, path, currentSum);
        }
        if(root->right != NULL)
        {
            FindPath(root->right, expectNumber, path, currentSum);
        }

        //  此处不需要恢复currentSum和path的值:                                  
        //  因为currentSum作为参数在函数递归调用返回时会自动恢复                 
        //  而如果作为静态局部变量存储则需要进行恢复                             
        //currentSum -= root->val;                                               
       //path.pop_back( );      
    }

};
```

#### 026 复杂链表的复制


#### 027 二叉搜索树与双向链表
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
#### 039 二叉树的深度

**题目描述**  
输入一棵二叉树，求该树的深度。从根结点到叶结点依次经过的结点（含根、叶结点）形成树的一条路径，最长路径的长度为树的深度。

解题思路：  
本题是一道比较简单地题目，主要考察树的深度遍历方法。然后值得注意的就是，递归两种主要的解题&参数传递的思路，一种是自顶向下的，另一种是自底向上的。  
相关链接： [树的遍历](http://blog.csdn.net/gatieme/article/details/51163010)

* 自顶向下传递参数的递归思路：
```cpp
int TreeDepthRecursion(TreeNode *root, int depth)
    {
        if(root == NULL)
        {
            return depth;
        }
        else
        {
            int leftDepth = TreeDepthRecursion(root->left, depth + 1);
            int rightDepth = TreeDepthRecursion(root->right, depth + 1);

            return max(leftDepth, rightDepth);
        }
    }
```

* 自底向上返回参数的递归思路：

```cpp
int TreeDepthRecursion(TreeNode *root)
    {
        if(root == NULL)
        {
            return 0;
        }
        else
        {
            int leftDepth = TreeDepthRecursion(root->left);
            int rightDepth = TreeDepthRecursion(root->right);

            return max(leftDepth, rightDepth) + 1;
        }
    }
```
#### 039 平衡二叉树
题目描述

输入一棵二叉树，判断该二叉树是否是平衡二叉树。

解题思路：  
要判定是否是平衡二叉树需要知道平衡二叉树的定义：  
  * 平衡二叉树要求对于每一个节点来说，它的左右子树的高度之差不能超过1

递归解法：
  * 递归的判断二叉树的每一个节点，判断其左右子树的高度差：
    * 如果高度差小于1 则继续将其左右子树进行平衡二叉树的判断直到叶子节点返回true。
    * 如果高度差大于1则返回false，判断结束。

```cpp
class Solution
{
public:
    bool IsBalanced_Solution(TreeNode* root)
    {
        if(root == NULL)
        {
            return true;
        }

        int leftDepth = TreeDepth(root->left);
        int rightDepth = TreeDepth(root->right);

        if(fabs(leftDepth - rightDepth) <= 1)
        {
            return IsBalanced_Solution(root->left) && IsBalanced_Solution(root->right);
        }
        else
        {
            return false;
        }
    }

    int TreeDepth(TreeNode *root)
    {
        if(root == NULL)
        {
            return 0;
        }

        int leftDepth = TreeDepth(root->left);
        int rightDepth = TreeDepth(root->right);

        //  返回左右子树中深度最深的
        return max(leftDepth, rightDepth) + 1;
    }
};
```

#### 056 链表中环的入口结点

题目描述

一个链表中包含环，请找出该链表的环的入口结点。


解题思路：  
计算环形链表的路口的典型方法就是快慢指针法：  
 * 第一步，让快慢指针在环中相遇：分别用p1，p2指向链表头部，p1每次走一步，p2每次走二步。
    * 如果p1走完整个链表没遇到p2说明链表没有环。
    * 如果p1==p2此时p1和p2一定是在环中相遇。

 * 第二步，找环的长度。从环中的相汇点开始, p2不动, p1前移，当再次相遇时，p1刚好绕环一周, 其移动即为环的长度K

 * 第三步, 快慢指针求环的入口结点：
    * 因为环的长度已知，所以使用快慢指针让快指针先走k步后会发现快慢指针最终将会在环的入口结点交汇。

```cpp
#define SLOW_STEP   1
#define FAST_STEP   2

class Solution
{
public:

    /*
        如果链表中有环, 则返回环中的任意一个节点
        否则返回NULL
     */
    ListNode* HasCycle(ListNode *pHead)
    {
        if(pHead == NULL)
        {
            return NULL;
        }

        ListNode *pSlow = pHead->next;
        ListNode *pFast = pSlow->next;
        while(pSlow != NULL && pFast != NULL)
        {
            if(pFast == pSlow)
            {
                return pSlow;
            }
            pSlow = NextNode(pSlow, 1);
            pFast = NextNode(pFast, 2);
        }

        return NULL;
    }

    //  获取到node节点后stpe的节点
    ListNode* NextNode(ListNode *node, int step)
    {
        for(int i = 0; i < step && node != NULL; i++)
        {
            node = node->next;
        }

        return node;
    }

    //  获取到链表中环的长度
    //  node是一个链表环内节点的指针
    int GetCycleLength(ListNode *node)
    {
        int length = 0;
        if(node == NULL)
        {
            return length;
        }

        //  考虑一下环内, 从任何一个节点出现再回到这个节点的距离就是环的长度
        ListNode *currNode = node;
        ListNode *stepNode = node->next;
        for(length = 1; ; length++)
        {
            if(stepNode == currNode)
            {
                return length;
            }
            stepNode = stepNode->next;
        }
        return 0;
    }


    ListNode* EntryNodeOfLoop(ListNode* pHead)
    {
        //  先找到链表环中的某一个节点
        ListNode* meetingNode = HasCycle(pHead);
        if(meetingNode == NULL)
        {
            return NULL;
        }
        debug <<"a node in cycle " <<meetingNode->val <<endl;
        //  获取到链表中环路的长度
        int cycleLength = GetCycleLength(meetingNode);
        debug <<"cycle length = " <<cycleLength <<endl;

        //  找到链表的中环的入口
        ListNode *leftNode = pHead;
        ListNode *rightNode = pHead;

        //  右指针先往前走n步
        rightNode = NextNode(rightNode, cycleLength);
        while(leftNode != rightNode)
        {
            leftNode = leftNode->next;
            rightNode = rightNode->next;
        }

        return leftNode;

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
#### 058 二叉树的下一个结点
**题目描述**  
给定一个二叉树和其中的一个结点，请找出中序遍历顺序的下一个结点并且返回。注意，树中的结点不仅包含左右子结点，同时包含指向父结点的指针。

**解题思路**：  
中序遍历时，当前结点与下一个被遍历到的结点间的关系是：
  * 如果当前结点有右子树, 那么其中序遍历的下一个结点就是其右子树的最左结点；

  * 如果当前结点没有右子树, 而它是其父结点的左子结点那么其中序遍历的下一个结点就是他的父亲结点；

  * 如果当前结点没有右子树，而它还是其父结点的右子结点，这种情况下其下一个结点应该是当前结点所在的左子树的根, 因此我们可以顺着其父节点一直向上遍历, 直到找到一个是它父结点的左子结点的结点。

  ```cpp
  class Solution {
  public:
      TreeLinkNode* GetNext(TreeLinkNode* pNode)
      {
          if(pNode == NULL)
          {
              return NULL;
          }

          TreeLinkNode *pNext = NULL;

          //  如果当前结点有右子树, 那么其中序遍历的下一个结点就是其右子树的最左结点
          if(pNode->right != NULL)
          {
              //  找到右子树的最左孩子
              pNext = pNode->right;
              while(pNext->left != NULL)
              {
                  pNext = pNext->left;
              }
          }
          else if(pNode->right == NULL && pNode->next != NULL)
          {
              TreeLinkNode *pCurrent = pNode;
              TreeLinkNode *pParent = pNode->next;
              //  如果当前结点是其父结点的左子结点那么其中序遍历的
              //  下一个结点就是他的父亲结点

              //  如果当前结点是其父结点的右子结点，
              //  这种情况下其下一个结点应该是当前结点所在的左子树的根
              //  因此我们可以顺着其父节点一直向上遍历,
              //  直到找到一个是它父结点的左子结点的结点
              while(pParent != NULL && pCurrent == pParent->right)
              {
                  pCurrent = pParent;
                  pParent = pParent->next;
              }
              pNext = pParent;
          }

          return pNext;
      }
  };
  ```

#### 059 对称的二叉树
**题目描述**：  
请实现一个函数，用来判断一颗二叉树是不是对称的。
注意，如果一个二叉树同此二叉树的镜像是同样的，定义其为对称的


#####题目分析：  
判断二叉树是否对称和二叉树镜像是一类题目。
  * 制造二叉树镜像时就是层序遍历然后交换左右子树；
  * 所以判断二叉树镜像时可以层序遍历然后判断当前结点的左右子结点是否相等。

```cpp
class Solution
{
public:
    bool isSymmetrical(TreeNode* pRoot)
    {
        if(pRoot == NULL)
        {
            return true;   
        }
        return isSymmetricalRecursion(pRoot->left, pRoot->right);
    }

    bool isSymmetricalRecursion(TreeNode *pLeft, TreeNode *pRight)
    {
        //层序遍历：先判断左右子节点是否相等。
        if(pLeft->val != pRight->val)
        {
            return false;
        }

        //然后继续左右子树的判断
        //首先判断左右子节点是否同时为空
        if(pLeft == NULL && pRight == NULL)
        {
            return true;
        }
        if((pLeft == NULL && pRight != NULL) ||
              (pLeft != NULL && pRight == NULL))
        {
            return false;
        }

        //  左子树的左与右子树的右对称
        //  左子树的右与右子树的左对称
        return isSymmetricalRecursion(pLeft->left, pRight->right)
            && isSymmetricalRecursion(pLeft->right, pRight->left);
    }
};
```


#### 062 序列化二叉树
