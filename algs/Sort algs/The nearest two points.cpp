#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

struct Point {
	double m_x, m_y;
	Point() :m_x(0.0), m_y(0.0) {}
	Point(double x, double y) : m_x(x), m_y(y) {};
	bool operator==(const Point& p) const
	{
		return m_x == p.m_x && m_y == p.m_y;
	}
};

ostream& operator<<(ostream& os, const Point& p)
{
	return os << "(" << p.m_x << ", " << p.m_y << ")";
}

template<class T, class Pr>
void insert_sort(vector<T>& vec, int l, int r, Pr pred) {
	int i, j;
	for (i = l + 1; i <= r; i++) {
		T tmp = vec[i];
		for (j = i - 1; j >= l && pred(tmp, vec[j]); j--) {
			vec[j + 1] = vec[j];
		}
		vec[j + 1] = tmp;
	}
}

//find key
template<class T>
int get_position(vector<T>& vec, int l, int r, T key) {
	for (int i = l; i <= r; i++) {
		if (key == vec[i])
			return i;
		return -1;
	}
}

//dividing vec according to the first element?
//每次找到小于第一个元素的元素时，都将其调换到前面
template<class T, class Pr>
int partition(vector<T>& vec, int l, int r, Pr pred) {
	int i, j;
	for (i = l + 1, j = l; i <= r; i++) {
		if (pred(vec[i], vec[l])) {
			++j;
			swap(vec[i], vec[j]);
		}
	}
	swap(vec[j], vec[l]);
	return j;
}

//顺序统计Top k的值
template<class T, class Pr>
T select(vector<T>& vec, int l, int r, int k, Pr pred) {
	int n = r - l + 1;
	if (n == 1) {
		if (k != 0)
			printf("out of boundary\n");
		return vec[l];
	}
	//找中位数的中位数作为分割点
	int cnt = n / 5;
	int tcnt = (n + 4) / 5;
	int rem = n % 5;
	vector<T> group(tcnt);
	int i, j;
	for (i = 0, j = l; i < cnt; i++, j += 5) {
		insert_sort(vec, j, j + 4, pred);
		group[i] = vec[j + 2];
	}
	if (rem) {
		insert_sort(vec, j, j + rem - 1, pred);
		group[i] = vec[j + (rem - 1) / 2];
	}
	T key = select(group, 0, tcnt - 1, (tcnt - 1) / 2, pred);
	//找分割点位置
	int key_pos = get_position(vec, l, r, key);
	swap(vec[key_pos], vec[l]);
	//用分割点对数组进行划分，小的在左大的在右
	int pos = partition(vec, l, r, pred);
	int x = pos - l;
	if (x == k) return key;
	else if (x < k)
		return select(vec, pos + 1, r, k - x - 1, pred);
	else return select(vec, l, pos - 1, k, pred);
}

double dist(const Point& a, const Point& b) {
	double x = a.m_x - b.m_x;
	double y = a.m_y - b.m_y;
	return sqrt(x*x + y*y);
}

bool cmpX(const Point& a, const Point& b) {
	return a.m_x < b.m_x;
}

bool cmpY(const Point& a, const Point& b) {
	return a.m_y < b.m_y;
}

double minDifferent(vector<Point> p, int l, int r, vector<Point>& result) {
	//按中位数划分区域只会到2或者3，不会减小到1
	if ((r - l + 1) == 2) {
		result[0] = p[l];
		result[1] = p[r];
		if (cmpX(p[r], p[l])) swap(p[l], p[r]);
		return dist(p[l], p[r]);
	}
	if ((r - l + 1) == 3) {
		insert_sort(p, l, r, cmpX);
		double tmp1 = dist(p[l], p[l + 1]);
		double tmp2 = dist(p[l + 1], p[l + 2]);
		double ret = min(tmp1, tmp2);
		if (tmp1 == ret) {
			result[0] = p[l];
			result[1] = p[l + 1];
		}
		else {
			result[0] = p[l + 1];
			result[1] = p[l + 2];
		}
		return ret;
	}
	int mid = (r + l) >> 1;
	Point median = select(p, l, r, mid - l, cmpX);
	vector<Point> res1(2), res2(2);
	double min_l = minDifferent(p, l, mid, res1);
	double min_r = minDifferent(p, mid + 1, r, res2);
	double minum = min(min_l, min_r);
	if (minum == min_l) {
		result[0] = res1[0];
		result[1] = res1[1];
	}
	else {
		result[0] = res2[0];
		result[1] = res2[1];
	}
	//合并检查中间，使用鸽笼原理
	vector<Point> yvec;
	int i, j;
	for (i = mid + 1; i <= r; i++)
		if (p[i].m_x - p[mid].m_x < minum)
			yvec.push_back(Point(p[i]));
	for (i = mid; i >= l; i--)
		if (p[mid + 1].m_x - p[i].m_x < minum)
			yvec.push_back(Point(p[i]));
	sort(yvec.begin(), yvec.end(), cmpY);
	for (i = 0; i < yvec.size(); i++) {
		for (j = i + 1; i < yvec.size() && yvec[j].m_y - yvec[i].m_y < minum &&
			j <= i + 7; j++)
		{
			double delta = dist(yvec[i], yvec[j]);
			if (delta < minum) {
				minum = delta;
				result[0] = yvec[i];
				result[1] = yvec[j];
			}
		}
	}
	return minum;
}


//测试集
Point p1, p2 = { 0,0 }, p3 = { 1,2 }, p4 = { 2,3 }, p5 = { 3,3 }, p6 = { 2,7 }, p7 = { 1,6 }, p8 = { 5,5 }, p9 = { 6,2 }, p10 = { 4,1 }, p11 = { 4,6 }, p12 = { 6,6 };

vector<Point> pointset1{};
vector<Point> pointset2{p1};
vector<Point> pointset3{ p1, p2 };
vector<Point> pointset4{ p2, p2 };
vector<Point> pointset5{ p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12 };




int main()
{
	int n, i, j, x, y;
	vector<Point> result(2);
	vector<Point> input;
	cout << "please input the number of your data:" << endl;
	cin >> n;
	cout << "please input your data:" << endl;
	for (i = 0; i<n; i++)
	{
		cin >> x;
		cin >> y;
		input.push_back(Point(x, y));
	}
	double minum = minDifferent(input, 0, input.size() - 1, result);
	cout << "nearest point: " << result[0] << " and "
		<< result[1] << endl;
	cout << "distance: " << minum << endl;
	system("pause");
	return 0;
}
