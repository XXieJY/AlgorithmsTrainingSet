#### 315. Count of Smaller Numbers After Self
解题思路：  
这道题给定我们一个数组，让我们计算每个数字右边所有小于这个数字的个数，目测我们不能用brute force，OJ肯定不答应。
* 那么我们为了提高运算效率，首先可以使用用二分搜索法，思路是将给定数组从最后一个开始，用二分法插入到一个新的数组，这样新数组就是有序的，那么此时该数字在新数组中的坐标就是原数组中其右边所有较小数字的个数，参见代码如下：
```cpp
class Solution {
public:
    vector<int> countSmaller(vector<int>& nums)
    {
        vector<int> t, res(nums.size());
        for (int i = nums.size() - 1; i >= 0; --i)
        {
            int left = 0, right = t.size();
            while (left < right)
            {
                int mid = left + (right - left) / 2;
                if (t[mid] >= nums[i])
                {
                  right = mid;
                }
                else
                {
                  left = mid + 1;
                }
            }
            res[i] = right;
            t.insert(t.begin() + right, nums[i]);
        }
        return res;
    }
};
```
