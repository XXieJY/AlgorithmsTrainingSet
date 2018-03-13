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
