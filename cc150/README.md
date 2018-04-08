### 字符串

#### 不用额外的数据结构确定字符串互异(摩尔投票法 Moore Voting)
请实现一个算法，确定一个字符串的所有字符是否全都不同。这里我们要求不允许使用额外的存储结构。

解题思路：  
* 查找重复，要么hash记录，要么排序+遍历
* 遍历查找重复使用摩尔投票法，初始化 record = E[0]; i = 1; 如果下一个数字不等于当前记录数字时，--i，如果i==0则替换记录数字为当前数字，
然后重置i=1,最后如果i>0则说明字符串不是互异的，返回false;

```cpp
class Different {
public:
    bool checkDifferent(string iniString) {
        int S = iniString.size();
        if (S == 0)
        {
            return false;
        }
        if (S == 1)
        {
            return true;
        }

        sort(iniString.begin(), iniString.end());
        int i = 1;
        char record = iniString[0];
        for (int j = 1; j < S; ++j)
        {
            if (i > 1)
            {
                return false;
            }
            if (record == iniString[j])
            {
                ++i;
            }
            else
            {
                --i;
                if (i <= 0)
                {
                    record = iniString[j];
                    i = 1;
                }
            }
        }
        return true;
    }
};
```

#### 字符串翻转操作(字符串对称位置字符串翻转，注意字符串奇数偶数大小)

```cpp
class Reverse {
public:
    string reverseString(string iniString) {
	 // write code here
	 int S = iniString.size();
	 if (S == 0 || S == 1)
	 {
		 return iniString;
	 }

	 int i = 0, j = S - 1;
	 char tmp;
	 while (i < j)
	 {
		 tmp = iniString[i];
		 iniString[i] = iniString[j];
		 iniString[j] = tmp;
		 ++i;
		 --j;
	 }
	 return iniString;
 }
};
```

#### 字符串字符乱序同构(使用散列表记录每个字符在字符串中出现的次数，然后相互比较即可)
给定两个字符串，请编写程序，确定其中一个字符串的字符重新排列后，能否变成另一个字符串。这里规定大小写为不同字符，且考虑字符串重点空格。

给定一个string stringA和一个string stringB，请返回一个bool，代表两串是否重新排列后可相同。保证两串的长度都小于等于5000。

```cpp
class Same {
public:
    bool checkSam(string stringA, string stringB) {
        // write code here
        int sizA = stringA.size();
        int sizB = stringB.size();

        if(sizA != sizB) return false;

        char A[256] = {0};
        char B[256] = {0};
        for(int i = 0; i < sizA; i++){
            A[stringA[i]]++;
            B[stringB[i]]++;
        }

        for(int i = 0; i < 256; i++){
            if(A[i] != B[i]) return false;
        }

        return true;
    }
};
```

#### 回文链表的判断(快慢指针+栈对回文的应用)

思路：利用快慢指针，找到中间节点；将慢指针节点的值压入栈，到达中间节点后，依次出栈与后续节点的值比较。特别注意长度奇偶数。

```cpp


class Palindrome {
public:
    bool isPalindrome(ListNode* pHead) {
        // write code here
        if(pHead == NULL)
            return true;
        stack<int> ss;
        ListNode* p = pHead;
        ListNode* q = pHead;
        ss.push(p->val);
        while(q->next != NULL && q->next->next != NULL)
            {
            p = p->next;
           ss.push(p->val);
            q = q->next->next;
        }
        if(q->next == NULL)    //此时链表长度为奇数
            ss.pop();
        p = p->next;
        while(!ss.empty())
            {
            if(ss.top() != p->val)
                break;
            p = p->next;
            ss.pop();
        }
        if(ss.empty())
            return true;
        else
            return false;
    }
};
```
