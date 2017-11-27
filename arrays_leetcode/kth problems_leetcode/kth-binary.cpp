#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

//题型：二分法求kth
//时间复杂度: O(n),可能有不均衡的partition，比如[1,n] --> [1, n-1] & [n]

//partition vector by the last element 
int lastPartition(vector<int> &vec, int l, int r) {
	int tmp = vec[r];
	int i = l - 1, j = l;
	for (; j <= r - 1; j++) {
		if (vec[j] <= tmp) {
			++i;
			swap(vec[i], vec[j]);
		}
	}
	++i;
	swap(vec[i], vec[j]);
	return i;
}

int dncKth(vector<int> &vec, int l, int r, int k) {
	if (l >= r) return vec[l];
	int pos = lastPartition(vec, l, r);
	if (pos ==  k - 1)
		return vec[pos];
	else if (pos < k - 1)
		return dncKth(vec, pos + 1, r, k);
	else
		return dncKth(vec, l, pos - 1, k);
}

int kthElement(vector<int> &vec, int l, int r, int k) {
	if (vec.empty()) return -1;
	else if (k <= 0) return -1;
	else if (vec.size() == 1 && k == 1) return vec[0];
	else if (vec.size() < k) return -1;
	else if (l >= r) return vec[l];
	else return dncKth(vec, l, r, k);
}



//测试集
vector<int> test1{};
vector<int> test2{ 2 };
vector<int> test3{ 2,1,5,3,12,6,7 };

int main()
{

	cout << kthElement(test3, 0, test3.size()-1, 5);
	system("pause");
	return 0;
}