## 排列组合的DFS
### 概念
* 排列和组合的区分：
  * 看问题是否和顺序有关。有关就是排列，无关就是组合。
  * 90%DFS的题, 要么是排列, 要么是组合。

### 例题

#### 39. Combination Sum（理解递归和DFS的优秀题目）
Given a set of candidate numbers (C) (without duplicates) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.

The same repeated number may be chosen from C unlimited number of times.

解题思路：  
**像这种结果要求返回所有符合要求解的题十有八九都是要利用到递归，而且解题的思路都大同小异。**
* 都是需要另写一个递归函数，这里我们新加入三个变量，start记录当前的递归到的下标，out为一个解，res保存所有已经得到的解，每次调用新的递归函数时，此时的target要减去当前数组的的数。
* **递归函数注意：递归接口的定义、出口的定义、递归拆解方式的思考。**  
具体看代码如下：

```cpp
class Solution {
public:
    vector<vector<int> > combinationSum(vector<int> &candidates, int target)
    {
        //递归相关辅助变量的声明
        vector<vector<int> > res;
        vector<int> out;

        //进入递归
        sort(candidates.begin(), candidates.end());
        dfs(candidates, target, 0, out, res);
        return res;
    }

    //递归的定义：
    //在candidates[start:end]中选择和为target的所有组合
    //添加到out后，在递归出口处推入res中
    void dfs(vector<int> &candidates, int target, int start,
      vector<int> &out, vector<vector<int> > &res)
      {
        //出口1
        if (target < 0) return;
        //出口2
        else if (target == 0) res.push_back(out);
        else
        {   
        //递归拆解过程
        //for循环和传递进dfs的start参数，一起定义了每趟递归可选择的数据集的范围
        //也就是每次搜索树分叉时可做的选择种类
            for (int i = start; i < candidates.size(); ++i)
            {
                out.push_back(candidates[i]);
                dfs(candidates, target - candidates[i], i, out, res);
                out.pop_back();
            }
        }
    }
};
```
---

## 图的DFS
#### 200. Number of Islands**
Given a 2d grid map of '1's (land) and '0's (water), count the number of islands. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

解题思路：  
* 这道求岛屿数量的题的本质是**求矩阵中连续区域的个数。**  
* 求矩阵连续区域个数需要想到用深度优先搜索DFS来解：
  * 先建立一个visited数组用来记录某个位置是否被访问过。
  * 然后开始DFS二维数组：
    * 对于一个为‘1’且未被访问过的位置X，我们递归进入其上下左右位置上为‘1’的数。
    * 然后将X的visited对应值赋为true，继续进入其所有相连的邻位置，这样可以将这个连通区域所有的数找出来
    * 找完本次区域后，我们将结果res自增1，然后我们在继续找下一个为‘1’且未被访问过的位置，以此类推直至遍历完整个原数组即可得到最终结果，代码如下：

```cpp
class Solution {
public:
    int numIslands(vector<vector<char> > &grid) {
        if (grid.empty() || grid[0].empty()){
          return 0;
        }

        int m, n, res;
        m = grid.size();
        n = grid[0].size();
        res = 0;
        vector<vector<bool> > visited(m, vector<bool>(n, false));

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '1' && !visited[i][j]) {
                    DFS(grid, visited, i, j);
                    ++res;
                }
            }
        }
        return res;
    }

    void DFS(vector<vector<char> > &grid,
      vector<vector<bool> > &visited, int x, int y) {

        //先检测越界，再检测是否已经访问过
        if (x < 0 || x >= grid.size() || y < 0 ||
          y >= grid[0].size() || grid[x][y] != '1' || visited[x][y]) {
              return;
          }

        //对于未访问过的节点，将其标记为已访问
        //然后BFS地访问其四方向相邻节点
        visited[x][y] = true;
        DFS(grid, visited, x - 1, y);
        DFS(grid, visited, x + 1, y);
        DFS(grid, visited, x, y - 1);
        DFS(grid, visited, x, y + 1);
    }
};
```

#### 111. Minimum Depth of Binary Tree

解题思路：  
二叉树的经典问题之最小深度问题就是就最短路径的节点个数，还是用深度优先搜索DFS来完成。

```cpp
class Solution {
public:
    int minDepth(TreeNode *root) {
        //判断根节点是否为空，如果为空直接返回0
        if (root == NULL) return 0;
        //判断当前节点是否是叶子节点，如果是则当前路径到尽头了，返回1让路径长度增加1；
        if (root->left == NULL && root->right == NULL) return 1;

        //当前节点有至少一个子节点时，当前节点就不是叶子节点
        //此时递归判断左右子节点之后的路径
        if (root->left == NULL) return minDepth(root->right) + 1;
        else if (root->right == NULL) return minDepth(root->left) + 1;
        else return 1 + min(minDepth(root->left), minDepth(root->right));
    }

};
```
