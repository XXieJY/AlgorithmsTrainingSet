//  有序数组原地去重复
//  原理：
//  f指代无重复数组的最后一个元素，i指代已经搜索到的重复元素总个数，因此，每次得到一个新的unique元素，就让它往前跳i个位置，然后将f停到
这个新元素上
void unique(vector<int>& v) {
		int s = v.size();
		if (s == 0 || s == 1) return;
		int f = 0;
		for (int b = 1, i = 0, e = s; b != e; ++b) {
			if (v[b] != v[f]) {
				v[b - i] = v[b];
				++f;
			}
			else
			{
				++i;
			}
		}
		v.resize(f+1);
	}
