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


class Solution {
private:

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
		
};

void swap(ListNode* f, ListNode* a) {
	int tmp = f->val;
	f->val = a->val;
	a->val = tmp;
}

void quickSort(ListNode b, ListNode e, ListNode* l, ListNode* h) {
	if (l != h) {
		ListNode* i = NULL;
		partition(b, e, l, h, i);
		ListNode* watch = i;
		if (watch == &b) {
			watch = watch->next->next;
		}
		else if (watch != &e) {
			quickSort(b, e, l, i);
			quickSort(b, e, watch, h);
		}
		else {
			quickSort(b, e, l, i);
		}

	}
}

void partition(ListNode b, ListNode e, ListNode* l, ListNode* h, ListNode* i) {
	int pivot = h->val;
	i = &b;
	while (i->next != l) { //locate the place where before the start sorting point
		i = i->next;
	}
	while (l->next != h) {
		if (l->val < pivot) {
			i = i->next;
			swap(i, l);
		}
		else {
			// donothing;
		}
		l = l->next;
	}
	swap(i->next, h);
}
	

public:
	ListNode* sortList(ListNode* head) {
		if (head == NULL) return head;  //for empty and single element LinkedList
		else if (head->next == NULL) return head;
		else {
			ListNode b(0), e(0), i = *head;
			ListNode* l = head, *h;
			b.next = head;
			while (i.next != NULL) {
				i = *i.next;
			}
			i.next = &e;
			h = &i;
			quickSort(b, e, l, h);
			b.next = NULL;
			i.next = NULL;
		}
		return head;
	}
};

int main()
{
	
    return 0;
}

