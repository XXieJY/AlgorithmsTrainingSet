## 排列组合的DFS
### 概念
* 排列和组合的区分：
  * 看问题是否和顺序有关。有关就是排列，无关就是组合。
  * 90%DFS的题, 要么是排列, 要么是组合。

### 递归的模板：

```cpp
主函数(...)
{
  声明一些递归需要的辅助变量，如：res保存当前递归得到的结果，out保存目前递归得到的不完整结果。
    还比如：level和visited等记录递归进度的变量；

  进入递归

  返回结果

}
递归函数(...)
{
  先判断递归是否到达出口，不是则继续，是则保存当前out的结果到res中，因为out已经是一个完整的递归结果。

  因为还没到递归出口，使用for循环拆解当前递归的cases
  {
    向out中添加当前递归层的case；
    进入下一层递归；
    从out中取回当前递归层的case；
  }
}
```

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
    vector<vector<int> > combinationSum(vector<int> &candidates,
                                        int target)
    {
        //递归相关辅助变量的声明
        vector<vector<int> > res;
        vector<int> out;

        //进入递归
        sort(candidates.begin(), candidates.end());
        dfs(candidates, target, 0, out, res);
        return res;
    }

    void dfs(vector<int> &E, int T, int start, vector<int> &out,
             vector<vector<int> > &res)
    {
        //出口1
        if(T < 0)
        {
            return;
        }
        //出口2
        else if(T == 0)
        {
            res.push_back(out);
            return;
        }
        else
        {
            //递归拆解过程
            //for循环和传递进dfs的start参数，一起定义了每趟递归可选择的数据集的范围
            //也就是每次搜索树分叉时可做的选择种类
            for (int i = start; i < E.size(); ++i)
            {
                out.push_back(E[i]);
                dfs(E, T-E[i], i, out, res);
                out.pop_back();
            }
        }
    }
};
```


#### 40. Combination Sum II
Given a collection of candidate numbers (C) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.

Each number in C may only be used once in the combination.

解题思路：
* 此题要考虑解决在组合中去重复的方法：
  * 首先在递归分叉时，传入下一个递归的数据集范围是[i+1 : end]
  * 然后在负责递归拆解的for循环里进行剪枝：
    * 加上if (i > start && num[i] == num[i - 1]) continue;
    * 这样可以防止res中出现重复项，然后就在递归调用combinationSum2DFS里面的参数换成i+1，这样就不会重复使用数组中的数字了，代码如下：

```cpp
class Solution {
public:
    vector<vector<int> > combinationSum(vector<int> &candidates,
                                        int target)
    {
        //递归相关辅助变量的声明
        vector<vector<int> > res;
        vector<int> out;

        //进入递归
        sort(candidates.begin(), candidates.end());
        dfs(candidates, target, 0, out, res);
        return res;
    }

    void dfs(vector<int> &E, int T, int start, vector<int> &out,
             vector<vector<int> > &res)
    {
        //出口1
        if(T < 0)
        {
            return;
        }
        //出口2
        else if(T == 0)
        {
            res.push_back(out);
            return;
        }
        else
        {
            //递归拆解过程
            //for循环和传递进dfs的start参数，一起定义了每趟递归可选择的数据集的范围
            //也就是每次搜索树分叉时可做的选择种类
            for (int i = start; i < E.size(); ++i)
            {
                if(i > start && E[i] == E[i-1]) continue;
                out.push_back(E[i]);
                dfs(E, T-E[i], i+1, out, res);
                out.pop_back();
            }
        }
    }
};
```
#### 46. Permutations
Given a collection of distinct numbers, return all possible permutations.  
> For example,[1,2,3] have the following permutations:  
[  
  [1,2,3],  
  [1,3,2],  
  [2,1,3],  
  [2,3,1],  
  [3,1,2],  
  [3,2,1]  
]  

解题思路：
* 典型的组合题中不同的数字顺序只算一种。
* 而此题使用DFS求全排列问题，**排列问题需要用到一个visited数组来标记某个数字是否访问过。**
* **然后在DFS递归函数从的循环应从头开始，而不是从level开始，这是和Combinations组合项不同的地方**
其余思路大体相同，代码如下：

```cpp
class Solution {
public:
    vector<vector<int> > permute(vector<int> &num)
    {
        //声明DFS求排列需要用到的变量
        vector<vector<int> > res;
        vector<int> out;
        vector<int> visited(num.size(), 0);

        //进入DFS
        dfs(num, 0, visited, out, res);
        return res;
    }
    void dfs(vector<int> &num, int level, vector<int> &visited,
             vector<int> &out, vector<vector<int> > &res) {
        if (level == num.size())
        {
            res.push_back(out);
        }
        else
        {
            //排列DFS时，使用两个方法结合控制顺序：
            //1.每个递归中的for循环都从头开始选择数据集
            //2.使用visited数组标记已选择元素，再进入下层递归
            //3.当前递归中，进行到第二个分叉时，注意要将第一次分叉的节点visited恢复
            for (int i = 0; i < num.size(); ++i)
            {
                //有序
                if (visited[i] != 0)
                {
                    continue;
                }
                visited[i] = 1;
                out.push_back(num[i]);
                dfs(num, level + 1, visited, out, res);
                out.pop_back();
                visited[i] = 0;
            }
        }
    }
};
```

#### 47. Permutations II
Given a collection of numbers that might contain duplicates, return all possible unique permutations.

> For example,[1,1,2] have the following unique permutations:  
[  
  [1,1,2],  
  [1,2,1],  
  [2,1,1]  
]

解题思路：
* 本题是关于排列的DFS问题，需要使用visited标记，并且每个递归的拆解循环都要从待选数据集的开头开始选取
* 由于待选数据集中有重复，所以要有排列组合的去重复算法：
  * 1.先对待选数据集排序
  * 2.在递归函数中要判断前面一个数和当前的数是否相等，如果相等，前面的数必须已经使用了，即对应的visited中的值为1，当前的数字才能使用，否则需要跳过，这样就不会产生重复排列了，代码如下：

```cpp
class Solution {
public:
    vector<vector<int> > permuteUnique(vector<int> &num)
    {
        //声明排序dfs的辅助变量
        vector<vector<int> > res;
        vector<int> out;
        vector<int> visited(num.size(), 0);

        //进入递归
        sort(num.begin(), num.end());
        dfs(num, 0, visited, out, res);
        return res;
    }
    void dfs(vector<int> &num, int level, vector<int> &visited,
             vector<int> &out, vector<vector<int> > &res)
    {
        //出口
        if (level >= num.size())
        {
          res.push_back(out);
        }
        else
        {
            for (int i = 0; i < num.size(); ++i)
            {
                //防止重复
                //1.使用过的元素不再使用
                //2.不可以跨过地方式使用相同的元素
                if (visited[i] != 0)
                {
                  continue;
                }
                if (i > 0 && num[i] == num[i - 1] && visited[i - 1] == 0)
                {
                  continue;
                }
                visited[i] = 1;
                out.push_back(num[i]);
                dfs(num, level + 1, visited, out, res);
                out.pop_back();
                visited[i] = 0;
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

#### 526. Beautiful Arrangement**
Suppose you have N integers from 1 to N. We define a beautiful arrangement as an array that is constructed by these N numbers successfully if one of the following is true for the ith position (1 ≤ i ≤ N) in this array:

* The number at the ith position is divisible by i.
* or i is divisible by the number at the ith position.

Now given N, how many beautiful arrangements can you construct?

>Example 1:  
Input: 2   
Output: 2  
Explanation:  
* The first beautiful arrangement is [1, 2]:  
Number at the 1st position (i=1) is 1, and 1 is divisible by i (i=1).  
Number at the 2nd position (i=2) is 2, and 2 is divisible by i (i=2).  
* The second beautiful arrangement is [2, 1]:  
Number at the 1st position (i=1) is 2, and 2 is divisible by i (i=1).  
Number at the 2nd position (i=2) is 1, and i (i=2) is divisible by 1.  
Note:  
N is a positive integer and will not exceed 15.

解题思路：  
* 确定使用递归DFS解题：对于满足某种条件的解的求所有情况，这种问题通常要用递归来做。而递归方法等难点在于写递归函数，如何确定终止条件，还有for循环中变量的起始位置如何确定。
* 有去重要求，要使用visited标记：那么这里我们需要一个visited数组来记录数字是否已经访问过，因为优美排列中不能有重复数字。
* 我们用变量pos来标记已经生成的数字的个数，如果大于N了，说明已经找到了一组排列，结果res自增1。
* 在for循环中，i应该从1开始，因为我们遍历1到N中的所有数字，如果该数字未被使用过，且满足和坐标之间的整除关系，那么我们标记该数字已被访问过，再调用下一个位置的递归函数，之后不要忘记了恢复初始状态，参见代码如下：

```cpp
class Solution {
public:
    int countArrangement(int N) {
        //初始化递归需要的辅助变量
        int res = 0;
        vector<int> visited(N + 1, 0);
        //进入递归
        dfs(N, visited, 1, res);
        return res;
    }
    void dfs(int N, vector<int>& visited, int pos, int& res) {
        //递归的出口
        if (pos > N)
        {
            ++res;
            return;
        }
        //拆解递归的过程
        //每层递归都从visited[1:N]中选取还未visited的数字，根据beautiful原则进行判断
        //记得回溯时将当前选中数字i的visited重置。
        for (int i = 1; i <= N; ++i)
        {
            if (visited[i] == 0 && (i % pos == 0 || pos % i == 0))
            {
                visited[i] = 1;
                dfs(N, visited, pos + 1, res);
                visited[i] = 0;
            }
        }
    }
};
```

#### 22. Generate Parentheses
Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

>For example, given n = 3, a solution set is:  
[  
  "((()))",  
  "(()())",  
  "(())()",  
  "()(())",  
  "()()()"  
]

解题思路：  
* 输出括号的有效全排列，需要用到DFS递归。
* 定义递归出口：
  * 如果在某次递归时，左括号的个数大于右括号的个数，说明此时生成的字符串中右括号的个数大于左括号的个数，即会出现')('这样的非法串，所以这种情况直接返回，不继续处理。
  * 如果left和right都为0，则说明此时生成的字符串已有3个左括号和3个右括号，且字符串合法，则存入结果中后返回。
* 如果以上两种情况都不满足，若此时left大于0，则调用递归函数，注意参数的更新，若right大于0，则调用递归函数，同样要更新参数。代码如下：

```cpp
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        dfs(n, n, "", res);
        return res;
    }
    void dfs(int left, int right, string out, vector<string> &res) {
        if (left > right) return;
        if (left == 0 && right == 0) res.push_back(out);
        else {
            if (left > 0)  dfs(left - 1, right, out + '(', res);
            if (right > 0) dfs(left, right - 1, out + ')', res);
        }
    }
};
```
