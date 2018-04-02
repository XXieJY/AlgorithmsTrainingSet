#### 验证数值回文
比如 1221 这个数字，如果 计算 1221 / 1000， 则可得首位1， 如果 1221 % 10， 则可得到末尾1，进行比较，然后把中间的22取出继续比较。代码如下：
```cpp
class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) return false;
        int div = 1;
        while (x / div >= 10) div *= 10;
        while (x > 0) {
            int left = x / div;
            int right = x % 10;
            if (left != right) return false;
            x = (x % div) / 10;
            div /= 100;
        }
        return true;
    }
};
```

####  生成杨辉三角的二维数组
http://www.cnblogs.com/grandyang/p/4031536.html
```cpp
class Solution {
public:
    vector<vector<int> > generate(int numRows) {
        vector<vector<int> > res;
        if (numRows <= 0) return res;
        res.assign(numRows, vector<int>(1));
        for (int i = 0; i < numRows; ++i) {
            res[i][0] = 1;
            if (i == 0) continue;
            for (int j = 1; j < i; ++j) {
                res[i].push_back(res[i-1][j] + res[i-1][j-1]);
            }
            res[i].push_back(1);
        }
        return res;
    }
};
```
