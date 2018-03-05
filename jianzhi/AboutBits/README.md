bits相关问题：





#### 010 二进制中1的个数
解题思路：  
循环左移测试数，flag一直左移（乘以2），当超出表示标识范围的时候，我们就可以终止了，但是这样子的话，最高位的符号位没有测试，因此要单独测试，同时由于会溢出，我们的flag需要用long来标识。

```cpp
class Solution
{
public:
    int NumberOf1(int n)
    {
        int count = 0;
        int i = 0;
        unsigned long flag = 1;

        while(flag <= INT_MAX)
        {
            debug <<n <<" & " <<flag <<" == "<<(n & flag) <<endl;
            if((n & flag) != 0)
            {
                count++;
            }
            flag <<= 1;
        }

        //  由于循环终结，我们使用的是flag <= INT_MAX
        //  因此前面的循环只会执行31次
        if((n & flag) != 0)    //  最后测试符号位
        {
            count++;
        }

        return count;
    }

};
```

#### *011 数值的整数次方

题目描述:  
给定一个double类型的浮点数base和int类型的整数exponent。求base的exponent次方。

解题思路：  
此题也是很爱在面试阶段考察的题目.
浮点数的次方主要考察计算时处理边界情况  
指数幂的所有边界包括:
  * 指数为0的情况，不管底数是多少都应该是1
  * 指数为负数的情况，求出的应该是其倒数幂的倒数
  * 指数为负数的情况下，底数不能为0

```cpp
class Solution
{
public:
    double Power(double base, int exponent)
    {
        //  指数为0的情况，不管底数是多少都应该是1.0
        if(exponent == 0)
        {
            return 1.0;
        }
        //  指数为负数的情况下，底数不能为0
        if(Equal(base, 0.0) == true && exponent < 0)
        {
            return 0.0;
        }

        double res = 1.0;
        if(exponent > 0.0)
        {
            res = PowerNormal(base, exponent);
        }
        else
        {
            res = PowerNormal(base, -exponent);
            res = 1 / res;
        }
        return res;
    }

private :
    double PowerNormal(double base, int exponent)
    {

        double res = 1;
        for(int i = 0; i < exponent; i++)
        {
            res *= base;
        }

        return res;

    }
    double Equal(double left, double right)
    {
        if(fabs(left - right) <  0.0000001)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};
```

#### 046 求1+2+3+...+n
解题思路:  
主要考察如何使用递归模拟乘法  使用短路模拟if语句.

```cpp
class Solution
{
public:
    int res;
    int Sum_Solution(int n)
    {
        res = 0;
        return (MultiRecursion(n, n + 1) >> 1);
    }

    int MultiRecursion(int a, int b)
    {
        a && MultiRecursion(a >> 1, b << 1);    //  递归的进行运算

        (a & 1) && (res += b);                  //  短路


        return res;
    }

};
```
#### 064 数据流之中的中位数
题目描述  

如何得到一个数据流中的中位数？如果从数据流中读出奇数个数值，那么中位数就是所有数值排序之后位于中间的数值。如果从数据流中读出偶数个数值，那么中位数就是所有数值排序之后中间两个数的平均值。

解题思路:  
对于数据流，对应的就是在线算法了，一道很经典的题目就是在1亿个数中找到最大的前100个数，这是一道堆应用题，找最大的前100个数，那么我们就创建一个大小为100的最小化堆，每来一个元素就与堆顶元素比较，因为堆顶元素是目前前100大数中的最小数，前来的元素如果比该元素大，那么就把原来的堆顶替换掉。

那么对于这一道题呢？如果单纯的把所有元素放到一个数组里，每次查找中位数最快也要O(n)，综合下来是O(n^2)的复杂度。我们可以利用上面例子中的想法，用一个最大堆来维护当前前n/2小的元素，那么每次找中位数只到取出堆顶就可以了。但是，有一个问题，数据要动态增长，有可能之前被替换掉的元素随着元素的增加又跑回来了，所以我们不能单纯得向上题一样把元素丢掉，我们可以再用一个最小化堆来存前n/2大的元素。

```cpp
class Solution
{
protected:
    vector<int>     m_min; //数组中的后一半元素组成一个最小化堆
    vector<int>     m_max; //数组中的前一半元素组成一个最大化堆

public:
    /*  将元素插入的堆中，　
     *  为了保证数据平均的分配到两个堆中, 两个堆的数据数目之差不能超过１
     *  插入的元素会两个堆元素的平衡, 因此两个堆都必须调整
     *
     *  比如将元素插在后半段(最小堆)中,
     *  则最小堆调整后的堆顶(最小值)需要弹出并压入到前半段中才能保证平衡
     *　也就是说,　在最小堆中插入元素, 最后完成调整后将导致最大堆中元素+1
     *
     *  因此我们可以假定, 0 <= m_min.size( ) - m_max.size( ) <= 1
     *  那么
     *
     *  插入前如果整个数组的元素个数为偶数, 说明两个堆中元素个数相等
     *  则最终元素应该插入m_min中,即先把元素插入到m_max中在调整到m_min中
     *
     *  插入前如果整个数组的元素个数为奇数, 说明m_max元素多了1个
     *  则最终元素应该插入m_max中,
     *  即先把元素插入到m_min中在调整到m_max中
     *  */
    void Insert(int num)
    {
        if(((m_min.size( ) + m_max.size( )) & 1) == 0)
        {
            /*  偶数数据的情况下
             *  直接将新的数据插入到数组的后半段
             *  即在最小堆中插入元素
             *
             *  此时最小堆中多出一个元素,
             *  即最小元素, 将其弹出后, 压入前半段(即最大堆中)
             *  */
            if(m_max.size( ) > 0 && num < m_max[0])
            {
                m_max.push_back(num);
                push_heap(m_max.begin( ), m_max.end( ), less<int>( ));

                num = m_max[0];
                pop_heap(m_max.begin(), m_max.end(), less<int>());
                m_max.pop_back();
            }
            m_min.push_back(num); //把前一半找到的最大值放到后一半中
            push_heap(m_min.begin( ), m_min.end( ), greater<int>( ));
            debug <<"left = " <<m_max.size( ) <<", " <<m_min.size( ) <<endl;
        }
        else
        {
            /*  否则数组中元素是奇数
             *  将
             *
             * */
            if(m_min.size( ) > 0 && num > m_min[0])    //  奇数数据的情况下，则在最大堆中插入元素
            {
                m_min.push_back(num);
                push_heap(m_min.begin(), m_min.end(), greater<int>());
                num=m_min[0];
                pop_heap(m_min.begin(), m_min.end(), greater<int>());
                m_min.pop_back();
            }
            m_max.push_back(num); //把后一半找到的最大值放到前一半中
            push_heap(m_max.begin(), m_max.end(), less<int>());
        }
    }

    /*  由于假定, 0 <= m_min.size( ) - m_max.size( ) <= 1
     *  因此
     *  当总元素个数为偶数时, 中位数即(m_max[0] + m_min[0]) / 2
     *  当总元素个数为奇数时, 中位数即m_min[0];  */
    double GetMedian()
    {
        int size = m_min.size( ) + m_max.size( );
        if(size==0) return -1;
        double median = 0;
        if((size & 1) != 0)
        {
            median = (double) m_min[0];
        }
        else
        {
            median = (double) (m_max[0] + m_min[0]) / 2;
        }
        return median;
    }
};
```
