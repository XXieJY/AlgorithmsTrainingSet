### 相关考点：  
* 二叉树遍历问题：二叉树的前中后序遍历，层序遍历的递归和非递归解法；  
* 二叉树重建：使用递归、前中后序的知识（二叉树和数组重建、二叉树和链表重建）
* 树的匹配问题：使用递归，和特定匹配要求（相关题目：树的子结构、对称/镜像树、路径和值的匹配、树深度匹配）
* 二叉搜索树的问题： BST的前中后序、BST与双向链表转化
* 平衡二叉树问题：AVG的树判定、AVG树的性质；

### 树的算法：树的遍历(前/中/后/层序)、树的恢复(前+中/中+后恢复树)、树的分解(树转数组、树转链表)

#### 树的前序遍历

* 递归法二叉树前序遍历


```cpp
void PreOrder(TreeNode *root)
{
    //递归出口
    if(root == NULL)
    {
        return;
    }
    //前序遍历在当前节点先做些操作
    cout << root->val;
    //do something here
    PreOrder(root->left);
    PreOrder(root->right);
    //如果还需要前序遍历的递归中结合一点bottom up的操作应该写在这里
    //写在这里的代码会从叶子节点（也就是这里的递归出口）开始按bottom-up的顺序执行
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

### 求二叉树的高度和宽度：

#### dfs求二叉树高度：
解题思路：  
这个可以使用递归，分别求出左子树的深度、右子树的深度，两个深度的较大值+1即可。

```cpp
int  getHeight(TreeNode root)
{
    if(root==null)
       return 0;  
   else{
       int left=getHeight(root.left);
       int right=getHeight(root.right);
       return 1+Math.max(left,right);
         }
}
```

#### 求二叉树宽度
求叶子树即为二叉树宽度：

```cpp
public  static int countOfLeaf(TreeNode root)
{
    int result=0;
    if(root==null)
      return 0;
    if(root.left==null  || root.right==null)
      return 1;
    else
         result= countOfLeaf(root.left)+countOfLeaf(root.right);

    return result;


}
```

### 二叉树的LCA（最近公共祖先）问题：

#### 235 Lowest Common Ancestor of a Binary Search Tree
解题思路：  
这道题让我们求二叉搜索树的最小共同父节点,。这道题我们可以用BST递归来求解，我们首先来看题目中给的例子，由于二叉搜索树的特点是左<根<右，所以根节点的值一直都是中间值，大于左子树的所有节点值，小于右子树的所有节点值，那么我们可以做如下的判断，如果根节点的值大于p和q之间的较大值，说明p和q都在左子树中，那么此时我们就进入根节点的左子节点继续递归，如果根节点小于p和q之间的较小值，说明p和q都在右子树中，那么此时我们就进入根节点的右子节点继续递归，如果都不是，则说明当前根节点就是最小共同父节点，直接返回即可，参见代码如下：

```cpp
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root) return NULL;
        if (root->val > max(p->val, q->val))
            return lowestCommonAncestor(root->left, p, q);
        else if (root->val < min(p->val, q->val))
            return lowestCommonAncestor(root->right, p, q);
        else return root;
    }
};
```

#### 236 Lowest Common Ancestor of a Binary Tree
解题思路：  
这道求二叉树的最小共同父节点的题是之前那道Lowest Common Ancestor of a Binary Search Tree 二叉搜索树的最小共同父节点的Follow Up。跟之前那题不同的地方是，这道题是普通是二叉树，不是二叉搜索树，所以就不能利用其特有的性质，所以我们只能在二叉树中来搜索p和q，然后从路径中找到最后一个相同的节点即为父节点，我们可以用递归来实现，写法很简洁，代码如下：

```cpp
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
       if (!root || p == root || q == root) return root;
       TreeNode *left = lowestCommonAncestor(root->left, p, q);
       TreeNode *right = lowestCommonAncestor(root->right, p , q);
       if (left && right) return root;
       return left ? left : right;
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

---

### 树的匹配问题*
**使用递归，和特定匹配要求（相关题目：树的子结构、对称/镜像树、路径和值的匹配、树深度匹配）**


#### 100. Same Tree
解题思路：  
判断两棵树是否相同和之前的判断两棵树是否对称都是一样的原理，利用深度优先搜索DFS来递归。代码如下：

```cpp
class Solution {
public:
    bool isSameTree(TreeNode *p, TreeNode *q) {
        if (!p && !q) return true;
        if ((p && !q) || (!p && q) || (p->val != q->val)) return false;
        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
};
```

#### 018 树的子结构
题目描述*:
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

#### 059 对称的二叉树 101. Symmetric Tree
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

#### 039 二叉树的深度（Bottom-Up和Top-Down必备题目）

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
            //Top-down应该随着递归参数一起传递给下一个递归
            int leftDepth = TreeDepthRecursion(root->left, depth + 1);
            int rightDepth = TreeDepthRecursion(root->right, depth + 1);
            return max(leftDepth, rightDepth);
        }
    }
```

* 自底向上返回参数的递归思路：  
Bottom up的递归应该写在递归调用代码的最后面
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
            //bottom up代码写在递归调用的最后面
            return max(leftDepth, rightDepth) + 1;
        }
    }
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

---
**
### 二叉搜索树问题

#### 99. Recover Binary Search Tree
解题思路：  
* 遍历二叉搜索树到一维数组中。然后对数组排序以后再放回BST中。
* 这种最一般的解法可针对任意个数目的节点错乱的情况，这里先贴上此种解法：  

```cpp
class Solution {
public:
    void recoverTree(TreeNode *root) {
        vector<TreeNode*> list;
        vector<int> vals;
        inorder(root, list, vals);
        sort(vals.begin(), vals.end());
        for (int i = 0; i < list.size(); ++i) {
            list[i]->val = vals[i];
        }
    }
    void inorder(TreeNode *root, vector<TreeNode*> &list, vector<int> &vals) {
        if (!root) return;
        inorder(root->left, list, vals);
        //将BST节点值按中序遍历顺序存在list
        //将BST节点按中序遍历顺序存在另一个list
        list.push_back(root);
        vals.push_back(root->val);
        inorder(root->right, list, vals);
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



---

### 平衡二叉树问题

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

---

#### 95. Unique Binary Search Trees （BST和卡特兰数）

卡特兰数递归过程：  
0 1 2 3 4  5    

5 = 0*4 + 1*3 + 2*2 + 3*1 + 4*0    

4 = 0*3 + 1*2 + 3*0    

```cpp
class Solution {
public:
    int numTrees(int n) {
        vector<int> dp(n + 1, 0);
        dp[0] = 1;
        dp[1] = 1;
        for (int i = 2; i <= n; ++i) {
            for (int j = 0; j < i; ++j) {
                dp[i] += dp[j] * dp[i - 1 - j];
            }
        }
        return dp[n];
    }
};
```
