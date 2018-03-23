## 基础算法
* 查找算法：二分查找
* 排序算法：快速排序、归并排序
* 指针操作：前后差一步指针、快慢指针、左右指针
* 树的算法：树的遍历(前/中/后/层序)、树的恢复(前+中/中+后恢复树)、树的分解(树转数组、树转链表)
* 链表操作：链表遍历(链表环)、链表变形(链表转数组、链表头插)

---

### 查找算法
#### 二分查找

* 基本二分查找框架
```cpp
class Solution {
  int binarySearch(vector<int> E, int T)
  {
    //判断边界条件
    if((int S = E.size()) == 0)
    {
      return -1;
    }

    //声明二分查找辅助变量：左边界和右边界和中间节点
    int L = 0, R = S - 1, pivot = 0;

    //二分查找主循环体，出口条件必须是left <= right
    //L<=R结合pivot+-1可以推导出的最后结果是L与R一定会在
    //查找失败时交叉
    while(L <= R)
    {
      //每次循环更新pivot
      pivot = L + (R - L) / 2;
      //根据题目查找要求确定不同的E[pivot]与T间的比较关系
      if (E[pivot] ? T)
      {
        //更新Left或Right或返回结果
      }
      else
      {
        //更新Right或Left或返回结果
      }
    }
    //返回查找失败的结果
  }
}
```

* 在无重复有序数组中查找
```cpp
class Solution{
  int binarySearch(vector<int> E, int T)
  {
    if((int S = E.size()) == 0)
    {
      return -1;
    }
    int L = 0, R = S - 1, pivot = 0;
    while (L <= R)
    {
      pivot = L + (R - L) / 2;
      if(E[pivot] == T)
      {
        return pivot;
      }
      else if(E[pivot] < T)
      {
        L = pivot + 1;
      }
      else
      {
        R = pivot - 1;
      }
    }
    return -1;
  }
}
```

* 在有重复有序数组中查找（那就是查找区间了）
```cpp
class Solution{
  vector<int> binarySearch(vector<int> E, int T)
  {
    if ((int S = E.size()) == 0)
    {
      return -1;
    }

    //初始化变量，先查找左边界
    int L = 0, R = S - 1, pivot = 0, A = -1, B = -1;
    while (L <= R)
    {
      pivot = L + (R - L) / 2;
      //左右游标回向目标值的左边界靠拢
      if (E[pivot] >= T)
      {
        R = pivot - 1;
      }
      else
      {
        L = pivot + 1;
      }
    }
    //注意这里的判断条件
    //因为允许可重复查找则有可能会查找出边界或者结果事实上是大于Target的值
    if (L < S && E[L] == T)
    {
      A = L;
    }
    else
    {
      return new vector<int>{-1, -1};
    }
    L = 0, R = S - 1, pivot = 0;
    while (L <= R)
    {
      pivot = L + (R - L) / 2;
      if (E[pivot] <= T)
      {
        L = pivot + 1;
      }
      else
      {
        R = pivot - 1;
      }
    }
    //注意这里的判断条件
    //因为允许可重复查找则有可能会查找出边界或者结果事实上是小于Target的值
    if (R > = 0 && E[R] == T)
    {
      return new vector<int>{L, R};
    }
    else
    {
      return new vector<int>{-1, -1};
    }
  }
}
```
