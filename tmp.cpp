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
			while(b_ad->next != l) {
				b_ad=b_ad->next;
			}
			if (watch == b_ad) {
				watch = watch->next->next;
				quickSort(b, e, watch, h);
			}
			else if (watch->next->next != e_ad) {
				quickSort(b, *(i->next), l, watch);
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
		ListNode* t = (ListNode*) malloc(sizeof(ListNode));
		t = l;
		while (t != h && t != NULL) {
			if (t->val < pivot) {
				i = i->next;
				swap(i, t);
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
-=-=-=-=-=-=-=-=-=-=-=9/27


#include "stdafx.h"
#include <iostream>  
#include <vector>
#include <assert.h>
#include <algorithm>

using namespace std;

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {};
};

class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
		if (nullptr == root) return root;
		TreeNode* p = root, *pre = p;
		do {
			if (key < p->val) {
				p = p->left;
			}
			else if (key > p->val) {
				p = p->right;
			}
			else break;
			pre = p;
		} while (nullptr != p);
		if (nullptr == p) {
			//key is not in BST
			return root;
		}
		else {
			if (nullptr == p->left && nullptr == p->right) (pre->left == p) ? pre->left = nullptr : pre->right = nullptr;
			else pre = nullptr;
			//key is in BST
			TreeNode* t = p;
			while (true)
			{
				t = (nullptr != t->right) ? t->right : t->left;
				if (nullptr == t) {
					//if t is leaf throw it directly
					(p->left == t) ? p->left = nullptr : p->right = nullptr;
					break;
				}
				else {
					//if not, move p to t
					*p = t->val;
					p = t;
				}
			}
			return root;
		}
    }
};



int main()
{
	TreeNode a(5);
	TreeNode b(3);
	TreeNode c(6);
	TreeNode d(2);
	TreeNode e(4);
	TreeNode f(7);
	a.left = &b;
	a.right = &c;
	b.left = &d;
	b.right = &e;
	c.right = &f;
	Solution s;
	s.deleteNode(&a, 3);
	return 0;
}
