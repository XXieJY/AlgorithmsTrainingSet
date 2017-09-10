//
//  midNumberHeap.cpp
//  Main
//
//  Created by pg on 2017/9/9.
//  Copyright © 2017年 jingyu. All rights reserved.
//
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
		if (v[j] <= pivot)
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
	int i = l, j = h, pivot = v[l + (h - l) / 2];
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
