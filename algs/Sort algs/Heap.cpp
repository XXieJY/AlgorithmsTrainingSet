//
//  heap.cpp -最大最小堆的生成、堆排序。
//  二叉堆的定义:
//    1. 二叉堆是完全二叉树或者是近似完全二叉树。
//    2. 父结点的键值总是大于或等于（小于或等于）任何一个子节点的键值。
//    3. 每个结点的左子树和右子树都是一个二叉堆（都是最大堆或最小堆）。
//  二叉堆满足二个特性(假设以0为堆起点)
//    1. i结点的父结点下标为 (int)floor((i – 1) / 2)
//    2. i结点的左右子节点下标为 i * 2 + 1， i * 2 + 2
//  堆的复杂度：
//    1. 空间复杂度 O(n)
//    2. 时间复杂度 O(nlogn) 是基于比较的排序算法复杂度下界
//

#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;

int parent(int);
int left(int);
int right(int);
void HeapAdjust(int [], int, int);
void BuildHeap(int [], int);
void print(int [], int);
void HeapSort(int [], int);

/*返回父节点*/
int parent(int i)
{
	return (int)floor((i - 1) / 2);
}

/*返回左孩子节点*/
int left(int i)
{
	return (2 * i + 1);
}

/*返回右孩子节点*/
int right(int i)
{
	return (2 * i + 2);
}

/*对以某一节点为根的子树做堆调整(保证最大堆性质)*/
void HeapAdjust(int A[], int i, int heap_size)
{
	int l = left(i);
	int r = right(i);
	int largest;
	int temp;
	if(l < heap_size && A[l] > A[i])
	{
		largest = l;
	}
	else
	{
		largest = i;
	}
	if(r < heap_size && A[r] > A[largest])
	{
		largest = r;
	}
	if(largest != i)
	{
		temp = A[i];
		A[i] = A[largest];
		A[largest] = temp;
		HeapAdjust(A, largest, heap_size);
	}
}

/*建立最大堆*/
void BuildHeap(int A[], int heap_size)
{
	for(int i = heap_size / 2 - 1; i >= 0; i--)
	{
		HeapAdjust(A, i, heap_size);
	}
}

/*输出结果*/
void print(int A[], int heap_size)
{
	for(int i = 0; i < heap_size;i++)
	{
		printf("%d ", A[i]);
	}
	printf("\n");
}

/*堆排序*/
void HeapSort(int A[], int heap_size)
{
	BuildHeap(A, heap_size);
	int temp;
	for(int i = heap_size - 1; i >= 0; i--)
	{
		temp = A[0];
		A[0] = A[i];
		A[i] = temp;
		HeapAdjust(A, 0, i);
	}
	print(A, heap_size);
}


//  新加入i结点  其父结点为(i - 1) / 2
void HeapInsertionFixed(int a[], int i)
{
	int j, temp;
	
	temp = a[i];
	j = (i - 1) / 2;      //父结点
	while (j >= 0 && i != 0)
	{
		if (a[j] <= temp)
			break;
		
		a[i] = a[j];     //把较大的子结点往下移动,替换它的子结点
		i = j;
		j = (i - 1) / 2;
	}
	a[i] = temp;
}

/*测试，对给定数组做堆排序*/
int main(int argc, char* argv[])
{
	const int heap_size = 13;
	int A[] = {19, 1, 10, 14, 16, 4, 7, 9, 3, 2, 8, 5, 11};
	HeapSort(A, heap_size);
	system("pause");
	return 0;
}
