### 回溯法+DFS/BFS题型：
LeetCode的：Permutaions, PermutationsII, Combination Sum, Conbination SumII;  
**这几题解法中的for循环，不仅是为了递归拆解出可能的解，同时也使用pop_back()在每层递归上
进行一定程度的回溯，这样结合才能解题**

#### 从回溯的思路看LeetCode-Combination Sum:
```cpp
#include<iostream>  
#include<vector>  
#include<algorithm>  
using namespace std;  

void backTracking(vector<vector<int>> &res, vector<int> arr ,vector<int>candidate ,int start,int target )  
{  
    if (target == 0)//满足条件，输出结果  
    {  
        res.push_back(arr);  
        return;  
    }  
    for (int i = start; i < candidate.size(); i++)//枚举所有可能的路径  
    {  
        if (candidate[i] <= target)//满足界限函数和约束条件  
        {  
            arr.push_back(candidate[i]);  
            backTracking(res, arr, candidate, i, target - candidate[i]);  
            arr.pop_back();//回溯清理工作  
        }  
    }  
}  

int main()  
{  
    vector<int> candidate = { 2, 3, 6, 7 };  
    int target = 7;  
    vector<vector<int>> res;  
    vector<int> arr;  
    sort(candidate.begin(), candidate.end());  
    backTracking(res, arr, candidate, 0, target);  
    for (int i = 0; i < res.size(); i++)  
    {  
        for (int j = 0; j < res[i].size(); j++)  
        {  
            cout << res[i][j] << " ";  
        }  
        cout << endl;  
    }  
    return 0;  
}  
```
