#### 698. Partition to K Equal Sum Subsets

Given an array of integers nums and a positive integer k, find whether it's possible to divide this array into knon-empty subsets whose sums are all equal.

Example 1:

Input: nums = [4, 3, 2, 3, 5, 2, 1], k = 4
Output: True
Explanation: It's possible to divide it into 4 subsets (5), (1, 4), (2,3), (2,3) with equal sums.


Note:

1 <= k <= len(nums) <= 16.
0 < nums[i] < 10000.

解题思路：  
这道题我们可以用递归来做:
* 首先我们还是求出数组的所有数字之和sum，首先判断sum是否能整除k，不能整除的话直接返回false。
* 然后需要一个visited数组来记录哪些数组已经被选中了，然后调用递归函数进行递归。  
* 对于递归函数：  
  * 我们的目标是组k个子集合，是的每个子集合之和为target = sum/k。
  * 我们还需要变量start，表示从数组的某个位置开始查找，curSum为当前子集合之和.
  * 如果k=1，说明此时只需要组一个子集合，那么当前的就是了，直接返回true。
  * 如果curSum等于target了，说明凑够一个k的子集合。此时递归传入k-1，并将start和curSum都重置为0，开始继续找下一个。参见代码如下：

```cpp
class Solution {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        //判断是否整除K
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % k != 0) return false;
        //创建一个访问数组标记
        vector<bool> visited(nums.size(), false);
        return helper(nums, k, sum / k, 0, 0, visited);
    }
    bool helper(vector<int>& nums, int k, int target, int start, int curSum, vector<bool>& visited) {
        if (k == 1) return true;
        if (curSum == target) return helper(nums, k - 1, target, 0, 0, visited);
        for (int i = start; i < nums.size(); ++i) {
            if (visited[i]) continue;
            visited[i] = true;
            if (helper(nums, k, target, i + 1, curSum + nums[i], visited)) return true;
            visited[i] = false;
        }
        return false;
    }
};
```
