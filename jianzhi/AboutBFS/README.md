
### BFS面试常见种类：
BFS:-
* 二叉树上的宽搜
* 图上的宽搜:
* 拓扑排序
* 棋盘上的宽搜


### 常见使用BFS的题型：
1. 问题是关于图的层级遍历：
  * Level Order Traversal: 有先碰到后碰到的问题, 分距离远近；
  * Connected Component: 联通问题。 比如Smallest Rectangle，Enclosing Black Pixels；
  * 拓扑排序 Topological Sorting: 有向图
2. 问题是关于图的最短路径 Shortest Path in Simple Graph：
  * 仅限简单图求最短路径(图中每条边长度都是1,且没有方向)
  * **ps: 如果问最长的路径呢? 用DP或者dfs所有路径找一遍**

---



[参考资料](https://zhuanlan.zhihu.com/p/26487841)
[参考资料2](http://blog.csdn.net/raphealguo/article/details/7523411)

---

### LeetCode:BFS
[LeetCode题库BFS](https://leetcode.com/tag/breadth-first-search/)

#### 101. Symmetric Tree
Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).

解题思路：
* 本题是一道轻微变形的BFS题：
    * 每次递归地按层次对比二叉树的镜像位置上节点的值
    * 层次遍历地返回结果是从叶节点向上传递的
* 判断二叉树是否是对称树，比如有两个节点n1, n2，我们需要比较n1的左子节点的值和n2的右子节点的值是否相等，同时还要比较n1的右子节点的值和n2的左子结点的值是否相等。
* 算法要从根节点开始以此类推比较完所有的左右两个节点。我们可以用递归和迭代两种方法来实现，写法不同，但是算法核心都一样。

```cpp
class Solution {
public:
    bool isSymmetric(TreeNode *root) {
        if (!root) return true;
        return isSymmetric(root->left, root->right);
    }
    bool isSymmetric(TreeNode *left, TreeNode *right) {
        if (!left && !right) return true;
        if (left && !right || !left && right || left->val != right->val) return false;
        return isSymmetric(left->left, right->right) && isSymmetric(left->right, right->left);
    }
};
```

#### 513. Find Bottom Left Tree Value
Given a binary tree, find the leftmost value in the last row of the tree.

**解题思路**：  
1. 这题可以直接通过先序遍历+维护当前深度和最大深度来做。
* 因为本题要求二叉树的最左下树结点的值，那么首先应该想到使用先序遍历很快能访问到左下角节点。
* 然后维护一个最大深度和当前节点的深度，由于先序遍历遍历的顺序是根-左-右，所以每一行最左边的结点肯定最先遍历到，那么由于是新一行，那么当前深度肯定比之前的最大深度大，所以我们可以更新最大深度为当前深度，结点值res为当前结点值，这样在遍历到该行其他结点时就不会更新结果res了，参见代码如下：
* **此题只有使用共享参数的递归才比较好做,因此所有递归都会根据深度的判断去修改统一个res变量。**

```cpp
class Solution {
public:
    int findBottomLeftValue(TreeNode* root) {
        if (!root) return 0;
        int max_depth = 1, res = root->val;
        helper(root, 1, max_depth, res);
        return res;
    }
    void helper(TreeNode* node, int depth, int& max_depth, int& res) {
        if (!node) return;
        //先序遍历每次会是左子节点先访问到
        //因此每次访问节点时，判断一下当前节点的深度是否大于最大深度
        if (depth > max_depth) {
            max_depth = depth;
            res = node->val;
        }
        helper(node->left, depth + 1, max_depth, res);
        helper(node->right, depth + 1, max_depth, res);
    }
};
```
2. 使用层序遍历二叉树，也就是BFS的思路，每次遍历到新的一层时，将第一个树节点，也就是当前层的最左节点的值记录下来
直到层序遍历完毕，最后返回保存的值。
```cpp
class Solution {
public:
    int findBottomLeftValue(TreeNode* root) {
        if (!root) return 0;
        int res = 0;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            int n = q.size();
            for (int i = 0; i < n; ++i) {
                TreeNode *t = q.front(); q.pop();
                if (i == 0) res = t->val;
                if (t->left) q.push(t->left);
                if (t->right) q.push(t->right);
            }
        }
        return res;
    }
};
```

#### 515. Find Largest Value in Each Tree Row
You need to find the largest value in each row of a binary tree.

**解题思路**：  
这题按BFS思路遍历每层元素然后，每层中最大的保存到结果中。

```cpp
class Solution {
public:
    vector<int> largestValues(TreeNode* root) {
        //基本上，树的root节点在代码中都需要特殊对待，单独被判断。
        if (!root) return {};
        vector<int> res;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            int n = q.size(), mx = INT_MIN;
            for (int i = 0; i < n; ++i) {
                TreeNode *t = q.front(); q.pop();
                mx = max(mx, t->val);
                if (t->left) q.push(t->left);
                if (t->right) q.push(t->right);
            }
            res.push_back(mx);
        }
        return res;
    }
};
```

#### 199. Binary Tree Right Side View
Given a binary tree, imagine yourself standing on the right side of it, return the values of the nodes you can see ordered from top to bottom.

**解题思路**：  
* 这道题要求我们打印出二叉树每一行最右边的一个数字，实际上是求二叉树层序遍历的一种变形，我们只需要保存每一层最右边的数字即可。
* 这道题需要用到数据结构队列queue，遍历每层的节点时,先取出当前层的最后一个节点(也就是queue的最后一个节点)，然后把下一层的节点都存入到queue中。
* 每当开始新一层节点的遍历之前，先把新一层最后一个节点值存到结果中，代码如下：
```cpp
class Solution {
public:
    vector<int> rightSideView(TreeNode *root) {
        vector<int> res;
        if (!root) return res;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            res.push_back(q.back()->val);
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                TreeNode *node = q.front();
                q.pop();
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }
        return res;
    }
};
```




**解题思路**：
这题是将二叉树层序遍历输出到二维数组中：
* 首先建立一个queue，然后先把根节点放进去；
* 然后找根节点的左右两个子节点，然后将结果全部存入queue中，然后同时也要把根节点存入二维数组的第一维中，此时queue里的元素就是下一层的所有节点；
* 继续下一层的遍历，在当前层中用一个for循环遍历当前层的节点，先将当前层节点存入结果中，然后将当前层的子节点存入queue中。代码如下：

```cpp
class Solution {
public:
    vector<vector<int> > levelOrder(TreeNode *root) {
        vector<vector<int> > res;
        if (root == NULL) return res;

        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            vector<int> oneLevel;
            int size = q.size();
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









---

2017网易的八方向BFS
https://www.nowcoder.com/questionTerminal/0385945b7d834a99bc0010e67f892e38
