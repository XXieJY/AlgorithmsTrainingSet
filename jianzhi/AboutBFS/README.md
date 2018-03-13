
### BFS面试常见种类：

* 二叉树上的宽搜
* 图上的宽搜:
* 拓扑排序
* 棋盘上的宽搜


### 常见使用BFS的题型：

* BFS解迷宫问题：
**提示：迷宫问题要是思路不清晰，可以画出搜索树**  
迷宫问题的求解可以抽象为连通图的遍历，因此主要有两种方法:

* 第一种方法是：深度优先搜索（DFS）加回溯。**（迷宫问题使用DFS，在编码上会复杂）**  
其优点：无需像广度优先搜索那样（BFS）记录前驱结点。   
其缺点：找到的第一条可行路径不一定是最短路径，如果需要找到最短路径，那么需要找出所有可行路径后，再逐一比较，求出最短路径。

* 第二种方法是：广度优先搜索（BFS）。   
其优点：找出的第一条路径就是最短路径。    
其缺点：需要记录结点的前驱结点，来形成路径。  

广度优先搜索的优点是找出的第一条路径就是最短路径，所以经常用来搜索最短路径，思路和图的广度优先遍历一样，需要借助于队列。

具体步骤：   
（1）从入口元素开始，判断它上下左右的邻边元素是否满足条件，如果满足条件就入队列；   
（2）取队首元素并出队列。寻找其相邻未被访问的元素，**将其入队列并标记元素的前驱节点为队首元素。**   
（3）重复步骤（2），直到队列为空（没有找到可行路径）或者找到了终点。**最后从终点开始，根据节点的前驱节点找出一条最短的可行路径。**

```cpp
//代码的几点说明：
//（1）BFS求迷宫最短路径，记录每个节点的前驱节点使用了mark标记。可见，三种方法中mark标记可以根据实际需求灵活为其赋予意义。
//（2）特殊的，起始节点的前驱设置为其本身。
#include <iostream>
#include <queue>
using namespace std;

struct Point{  
    //行与列
    int X;  
    int Y;  

    //默认构造函数
    Point(){
        X=Y=-1;
    }

    Point(int x,int y){
        this->X=x;
        this->Y=y;
    }

    bool operator==(const Point& V) const{
        if(this->X==V.X&&this->Y==V.Y)
            return true;
        return false;
    }
};

int maze[5][5]={
    {0,0,0,0,0},
    {0,1,0,1,0},
    {0,1,1,1,0},
    {0,1,0,0,1},
    {0,0,0,0,0}
};

//四方向坐标矩阵
//上下左右对应[0][0],[0][1],[1][0],[1][1]
int dir[][2] = {  
    {-1, 0}, {1, 0},  
    {0, -1}, {0, 1}  
};

void mazePath(void* maze,int m,int n, Point& A, Point B,vector<Point>& RES){
    int** maze2d=new int*[m];
    for(int i=0;i<m;++i){
        maze2d[i]=(int*)maze+i*n;
    }

    if(maze2d[A.X][A.Y]==1||maze2d[A.X][A.Y]==1) return ; //输入错误

    if(A==B){ //起点即终点
        RES.push_back(A);
        return;
    }

    //mark标记每一个节点的前驱节点，如果没有则为（-1，-1），如果有，则表示已经被访问
    //先初始化mark的二维数组
    Point** mark=new Point*[m];
    for(int i=0;i<m;++i){
        mark[i]=new Point[n];
    }

    queue<Point> Q;
    Q.push(A);
    //将起点的前驱节点设置为自己
    mark[A.X][A.Y]=A;

    while(Q.empty()!=true){
        Point cur=Q.front();
        Q.pop();

        if(cur.X-1>=0 && maze2d[cur.X-1][cur.Y]==0){//上节点连通
            if(mark[cur.X-1][cur.Y]==Point()){//上节点未被访问，满足条件，如队列
                mark[cur.X-1][cur.Y]=cur;
                Q.push(Point(cur.X-1,cur.Y)); //入栈
                if(Point(cur.X-1,cur.Y)==B){ //找到终点
                    break;
                }
            }
        }

        if(cur.Y+1<n && maze2d[cur.X][cur.Y+1]==0){//右节点连通
            if(mark[cur.X][cur.Y+1]==Point()){//右节点未被访问，满足条件，如队列
                mark[cur.X][cur.Y+1]=cur;
                Q.push(Point(cur.X,cur.Y+1));    //入栈
                if(Point(cur.X,cur.Y+1)==B){ //找到终点
                    break;
                }
            }
        }

        if(cur.X+1<m && maze2d[cur.X+1][cur.Y]==0){//下节点连通
            if(mark[cur.X+1][cur.Y]==Point()){//下节点未被访问，满足条件，如队列
                mark[cur.X+1][cur.Y]=cur;
                Q.push(Point(cur.X+1,cur.Y));    //入栈
                if(Point(cur.X+1,cur.Y)==B){ //找到终点
                    break;
                }
            }
        }

        if(cur.Y-1>=0 && maze2d[cur.X][cur.Y-1]==0){//左节点连通
            if(mark[cur.X][cur.Y-1]==Point()){//上节点未被访问，满足条件，如队列
                mark[cur.X][cur.Y-1]=cur;
                Q.push(Point(cur.X,cur.Y-1));    //入栈
                if(Point(cur.X,cur.Y-1)==B){ //找到终点
                    break;
                }
            }
        }
    }
    if(Q.empty()==false){
        int X=B.X;
        int Y=B.Y;
        RES.push_back(B);
        while(!(mark[X][Y]==A)){
            RES.push_back(mark[X][Y]);
            X=mark[X][Y].X;
            Y=mark[X][Y].Y;
        }
        RES.push_back(A);
    }
}

int main(){
    Point A(0,0);
    Point B(4,4);
    vector<Point> vecPath;
    mazePath(maze,5,5,A,B,vecPath);

    if(vecPath.empty()==true)
        cout<<"no right path"<<endl;
    else{
        cout<<"shortest path:";
        for(auto i=vecPath.rbegin();i!=vecPath.rend();++i)
            printf("(%d,%d) ",i->X,i->Y);
    }

    getchar();
}
```


[参考资料](http://blog.csdn.net/k346k346/article/details/51289478)
[参考资料1](http://blog.csdn.net/raphealguo/article/details/7523411)
[参考资料2](http://blog.csdn.net/k346k346/article/details/51289478)

---



[参考资料](https://zhuanlan.zhihu.com/p/26487841)


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

#### 103. Binary Tree Zigzag Level Order Traversal**
Given a binary tree, return the zigzag level order traversal of its nodes' values. (ie, from left to right, then right to left for the next level and alternate between).

解题思路：  
* 二叉树的之字形层序遍历是二叉树层序遍历的变形，不同之处在于一行是从左到右遍历，下一行是从右往左遍历，交叉往返的之字形的层序遍历。
* 根据其特点我们用到栈的后进先出的特点，这道题我们维护两个栈，相邻两行分别存到两个栈中。
  * 进栈的顺序也不相同，一个栈是先进左子结点然后右子节点。
  * 另一个栈是先进右子节点然后左子结点，这样出栈的顺序就是我们想要的之字形了，代码如下：
```cpp
class Solution {
public:
    vector<vector<int> > zigzagLevelOrder(TreeNode *root) {
        vector<vector<int> >res;
        stack<TreeNode*> RtoL;
        stack<TreeNode*> LtoR;
        vector<int> out;

        if (!root) {
          return res;
        }

        RtoL.push(root);
        while (!RtoL.empty() || !LtoR.empty()) {
            //根据题意，先右左，再左右
            //要栈按右左顺序输出，则应该按左右顺序入栈
            while (!RtoL.empty()) {
                TreeNode *cur = RtoL.top();
                RtoL.pop();
                out.push_back(cur->val);
                if (cur->left) LtoR.push(cur->left);
                if (cur->right) LtoR.push(cur->right);
            }
            //每个RtoL或LtoR循环都记录一整层的节点
            if (!out.empty()) res.push_back(out);
            out.clear();
            while (!LtoR.empty()) {
                TreeNode *cur = LtoR.top();
                LtoR.pop();
                out.push_back(cur->val);
                if (cur->right) RtoL.push(cur->right);
                if (cur->left) RtoL.push(cur->left);
            }
            if (!out.empty()) res.push_back(out);
            out.clear();
        }
        return res;
    }
};
```

#### 207. Course Schedule**  
There are a total of n courses you have to take, labeled from 0 to n - 1.

Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]

Given the total number of courses and a list of prerequisite pairs, is it possible for you to finish all courses?

解题思路：  
此题需要使用BFS判定一个有向图中是否有环存在：
* BFS的解法，我们定义二维数组graph来表示这个有向图，一维数组in来表示每个顶点的入度。
* 开始先建立这个有向图，并将入度数组也初始化好。
* 然后我们定义一个queue变量，将所有入度为0的点放入队列中，然后开始遍历队列，从graph里遍历其连接的点，每到达一个新节点，将其入度减一，如果此时该点入度为0，则放入队列末尾。
* 直到遍历完队列中所有的值，若此时还有节点的入度不为0，则说明环存在，返回false，反之则返回true。代码如下：

```cpp
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        //构造有向图，创建入度数组
        vector<vector<int> > graph(numCourses, vector<int>(0));
        vector<int> in(numCourses, 0);
        for (auto a : prerequisites) {
            graph[a[1]].push_back(a[0]);
            ++in[a[0]];
        }
        //将初始化入度为0的节点插入队列
        queue<int> q;
        for (int i = 0; i < numCourses; ++i) {
            if (in[i] == 0) q.push(i);
        }
        //队列循环出队，然后削减连通节点的入度
        //当入度为0时，将此节点插入队列
        while (!q.empty()) {
            int t = q.front();
            q.pop();
            for (auto a : graph[t]) {
                --in[a];
                if (in[a] == 0) q.push(a);
            }
        }
        //判定，当队列空时，依然存在入度大于0的节点
        //则当前图有环路。
        for (int i = 0; i < numCourses; ++i) {
            if (in[i] != 0) return false;
        }
        return true;
    }
};
```







---

2017网易的八方向BFS
https://www.nowcoder.com/questionTerminal/0385945b7d834a99bc0010e67f892e38
