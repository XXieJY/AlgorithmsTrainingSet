// 代码实现了： 原地去重算法unique， 这个算法经常会用到。
/**
* Definition for singly-linked list.
* struct ListNode {
*     int val;
*     ListNode *next;
*     ListNode(int x) : val(x), next(NULL) {}
* };
*/

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}

};

class Solution {
private:



	void swap(ListNode* f, ListNode* a) {
		int tmp = f->val;
		f->val = a->val;
		a->val = tmp;
	}

	void quickSort(ListNode& b, ListNode& e, ListNode* l, ListNode* h) {
		if (l != h) {
			ListNode* i = NULL;
			partition(b, e, l, h, i);
			ListNode* watch = i, *b_ad = &b, *e_ad = &e;
			if (watch == b_ad) {
				watch = watch->next->next;
				quickSort(b, e, watch, h);
			}
			else if (watch->next->next != e_ad) {
				quickSort(b, *(i->next), l, i);
				quickSort(b, e, watch->next->next, h);
			}
			else {
				quickSort(b, *h, l, i);
			}

		}
	}

	void partition(ListNode& b, ListNode& e, ListNode* l, ListNode* h, ListNode* &i) {
		int pivot = h->val;
		i = &b;
		while (i->next != l) { //locate the place where before the start sorting point
			i = i->next;
		}
		ListNode* t = l;
		while (t != h && t != NULL) {
			if (t->val < pivot) {
				i = i->next;
				swap(i, l);
			}
			else {
				// donothing;
			}
			t = t->next;
		}
		swap(i->next, h);
	}


public:
	ListNode* sortList(ListNode* head) {
		if (head == NULL) return head;  //for empty and single element LinkedList
		else if (head->next == NULL) return head;
		else {
			ListNode b(0), e(0);
			ListNode* l = head, *i = head, *h; //赋值 ListNode i = *head；以后 i并不是传引用，而是传值，即head被复制了,i有自己的地址
			b.next = head;
			while (i->next != NULL) {
				i = i->next;
			}
			i->next = &e;
			h = i;
			quickSort(b, e, l, h);
			b.next = NULL;
			i->next = NULL;
		}
		return head;
	}
};


int main() {
	ListNode a = 3;
	ListNode b = 4;
	ListNode c = 1;
	ListNode* head = &a;
	a.next = &b;
	b.next = &c;
	Solution s;
	s.sortList(head);
	cout << head->val << ', ' << head->next->val;
	return 1;
}
