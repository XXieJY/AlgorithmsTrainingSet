Problem 1.海量数据处理的 Top K大的数问题 from:http://www.cnblogs.com/xudong-bupt/archive/2013/03/20/2971262.html
  - 解答：
  中心思想：使用小顶堆存放海量数据中Top k大的数。
  步骤：首先取海量数据中前k个元素，作为size=k的小顶堆的初始数据。
  然后从第i = k+1个元素开始，按顺序遍历一次所有的数据。
  如果 data[i]的值小于或等于小顶堆的根结点，则i++，然后继续遍历余下数据。
  如果 data[i]的值大于小顶堆的根结点，则用data[i]替代小顶堆根节点，然后调整一趟小顶堆，最后令i++，继续遍历余下数据。
  
```cpp
#include<stdio.h>
int n;  ///数字个数，n很大(n>10000)
int dui[10];
#define K 10    ///Top K,K的取值

void create_dui();　　///建堆
void UpToDown(int);　　///从上到下调整
int main()
{
    int i;
    int tmp;
    while(scanf("%d",&n)!=EOF)
    {
        for(i=1;i<=K;i++) ///先输入K个
            scanf("%d",&dui[i]);
        create_dui();  ///建小顶堆
        for(i=K+1;i<=n;i++)
        {
            scanf("%d",&tmp);
            if(tmp>dui[1])  ///只有大于根节点才处理
            {
                dui[1]=tmp;
                UpToDown(1);    ///向下调整堆
            }
        }
    }
    return 1;
}

void create_dui()
{
    int i;
    int pos=K/2;      ///从末尾数，第一个非叶节点的位置K/2
    for(i=pos;i>=1;i--)
        UpToDown(i);
}

void UpToDown(int i)
{
    int t1,t2,tmp,pos;
    t1=2*i; ///左孩子(存在的话)
    t2=t1+1;    ///右孩子(存在的话)
    if(t1>K)    ///无孩子节点
        return;
    else
    {
        if(t2>K)  ///只有左孩子
            pos=t1;
        else
            pos=dui[t1]>dui[t2]? t2:t1;

        if(dui[i]>dui[pos]) ///pos保存在子孩子中，数值较小者的位置
        {
            tmp=dui[i];dui[i]=dui[pos];dui[pos]=tmp;
            UpToDown(pos);
        }
    }
}
```

Problem 2. 设计一个数据结构，其中包含两个函数，1.插入一个数字，2.获得中数。并估计时间复杂度。
- 解答：
  中心思想：使用小顶堆存放较大的一半数值， 大顶堆存放较小的一半数值， 那么大顶堆的根和小顶堆的根就是可能的中位数，并且在获取中位数时，时间复杂度为O(1), 只需要判定数据容量大小是奇数或者偶数。
  步骤：首先要对所有数据进行增序排序，然后将数据前半部分(较小的那一半)建立大顶堆，后半部分(较大的那一半)建立小顶堆。
  此外，还要在建堆过程中，分别对 数据整体大小=a、小顶堆大小=x和大顶堆=d大小进行维护。
  - 假设插入一个数值i，则判断：i 小于等于大顶堆根结点 则将i插入大顶堆；如果i大于等于小顶堆根结点，则将i插入小顶堆。
  - 假设要获得中数，则先判断a是奇数还是偶数，如果是a奇数则继续判断x>d:那么中数就是小顶堆根节点， 如果x<d：中数就是大顶堆根节点。
  - 如果a是偶数，则默认取大顶堆根节点作为中数。
  
