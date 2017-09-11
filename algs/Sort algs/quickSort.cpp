//
//  quickSort.cpp -快速排序代码
//  快速排序的定义：
//  1. 进行每一趟排序时， 从数据中选出一个pivot，然后将大于等于或小于等于pivot的数值分别调整到pivot的左右两侧
//  2. 然后再分别对pivot左右两部分数据再进行快速排序。 重复上述操作，直到待排序数据长度等于1.
//  快速排序的特点：
//  1. 时间复杂度O(nlogn) 空间复杂度O(1) 是不稳定排序算法
//  2. 快速排序通常需要实现一个 quick函数（用来调用快速排序算法，分割排序后数据以及重复调用自身）
//  和一个 partition函数（实现快速排序算法。每次调用它，都先确定一个pivot，然后将大于等于或小于等于pivot的数据分别放在pivot两侧）
//  3. 快速排序有Lomuto 和 Hoare两种常见的实现方式。
//  Lomuto快速排序:
//  选择数据中的首个元素 或者 最后一个元素作为pivot。
//  将大于或者小于pivot的数据 放到pivot前面 （这里看是升序还是降序）
//  然后将当前pivot放到它的最终位置上。
//  输出pivot的位置给quick函数，quick函数根据pivot的位置，调用两次quick函数，将pivot前后的待排序数据进行排序
//  重复上述排序操作 直到待排序序列大小等于1
//  Hoare快速排序：
//  选择数据中的中间元素 作为pivot
//  对整个数据设定头指针和尾指针，使用头尾指针相向遍历整组数据。
//  在遍历过程中，将(head=大于等于pivot, tail=小于等于pivot) 或者 (head=小于等于pivot, tail=大于等于pivot)的逆序对交换位置，
//  此番操作在head和tail相遇或者错开时结束。 不需要再调整pivot的位置。
//  quick3way quicksort: The fastest quick sort code.

#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

int lpartition(vector<int> &v, int l, int h);
int hpartition(vector<int> &v, int l, int h);
void swap(int &f, int &b);

//Lomuto quick sort
void lquick(vector<int> &v, int l, int h)
{
	// h is the sequence number of v, not the size of v
	// execute quick sort entil the size of v is 1
	if (l < h)
	{
		int p = lpartition(v, l, h);
		//The Lomuto quick sort can specify the final position of one pivot in one partition
		lquick(v, l, p - 1);
		lquick(v, p + 1, h);
	}
}

int lpartition(vector<int> &v, int l, int h)
{
	// i指定了当前pivot在排序后最终位置的前一个元素
	int pivot = v[h], i = l - 1;
	for (int j = l; j < h; j++)
	{
		if (v[j] < pivot)
		{
			swap(v[++i], v[j]);
		}
		else
		{
			//do nothing
		}
	}
	swap(v[++i], v[h]);
	return i;
}

//Hoare quick sort
void hquick(vector<int> &v, int l, int h)
{
	if (l < h)
	{
		int p = hpartition(v, l, h);
		// hoare partition在每轮quick sort中并不能确定一个pivot的最终位置
		hquick(v, l, p);
		hquick(v, p + 1, h);
	}
}

int hpartition(vector<int> &v, int l, int h)
{
	int i = l, j = h, pivot = v[l + (h - l) / 2]; // 取中间一个数还可以是v[(h+l)/2]
	while (i < j)   //Hoare快排 在头尾指针相遇或者错过时结束
	{
		while (v[i] < pivot)
		{
			++i;
		}
		while (v[j] > pivot)
		{
			--j;
		}
		if (i < j) {
			swap(v[i++], v[j--]);
		}
	}
	return i;
}



void quick3way(vector<int> &v, int l, int h) 
{
	if (l >= h) return;
	int la = lo, i = lo + 1, hb = h;
	int pivot = v[lo];
	while (i <= hb)
	{
		int cmp = v[i] <= pivot ? -1 : 1;
		if (v[i] == pivot) cmp = 0;
		if (cmp < 0) swap(v[la++], v[i++]);
		else if (cmp > 0) swap(v[i], v[hb--]);
		else i++;
	}
	quick3way(v, l, la - 1);
	quick3way(v, hb + 1， h);
}

void swap(int &f, int &b)
{
	int tmp = f;
	f = b;
	b = tmp;
}


/*测试，对给定数组做堆排序*/
int main(int argc, char* argv[])
{
	int A[] = {19, 1, 10, 14, 16, 4, 7, 9, 3, 2, 8, 5, 11};
	vector<int> a(A, A+(sizeof(A)/sizeof(A[0])));
	hquick(a, 0, 12);
	for (vector<int>::iterator b = a.begin(), e = a.end(); b != e; ++b)
	{
		cout << *b << " ";
	}
	return 0;
}
