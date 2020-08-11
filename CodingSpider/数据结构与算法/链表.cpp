#include<iostream>
#include<vector>

using namespace std;

struct ListNode {
	int val;
	ListNode* next;

	ListNode(int x):val(x),next(NULL){}
};




////////////////////1、插入和删除链表////////////////////////
ListNode* deleteNode(ListNode* head, int val) {
	ListNode* pre = head;
	ListNode* cur = head->next;

	if (head->val == val)	return cur;

	while (cur) {
		if (cur->val == val) {
			pre->next = cur->next;
			return head;
		}
		else {
			cur = cur->next;
			pre = pre->next;
		}
	}
	return head;
}

///////////////////2、翻转链表////////////////////
ListNode* reverseList1(ListNode* head) {
	if (!head || !head->next)	return head;

	ListNode* pre = NULL, * cur = head, * nex = head->next;

	while (cur) {
		nex = cur->next;
		cur->next = pre;

		pre = cur;
		cur = nex;
	}
	return pre;
}

ListNode* reverseList2(ListNode* head) {
	if (!head || !head->next)	return head;

	ListNode* cur = reverseList2(head->next);
	head->next->next = head;
	head->next = nullptr;

	return cur;
}

///////////////////3、翻转[m,n]链表区间///////////////////////////////

ListNode* reverseBetween1(ListNode* head, int m, int n) {
	if (!head || !head->next)    return head;
	ListNode* dummy = new ListNode(-1);
	dummy->next = head;
	ListNode* pre = NULL, * cur = head;
	for (int i = 1; i < m; i++) {
		pre = cur;
		cur = cur->next;
	}
	ListNode* before = pre, * after = cur;
	for (int i = 0; i <= n - m; i++) {
		ListNode* nex = cur->next;
		cur->next = pre;

		pre = cur;
		cur = nex;
	}
	//连接m之前与反转的头
	if (before)  before->next = pre; //m==1的情况，前面完全反转
	else dummy->next = pre;
	//连接反转的尾和n之后
	after->next = cur;
	return dummy->next;
}



ListNode* nex;
ListNode* reverseN(ListNode* head, int n) {

	if (n == 1) {
		nex = head->next;
		return head;
	}
	// 以 head.next 为起点，需要反转前 n - 1 个节点
	ListNode* last = reverseN(head->next, n - 1);

	head->next->next = head;
	// 让反转之后的 head 节点和后面的节点连起来
	head->next = nex;
	return last;
}

ListNode* reverseBetween2(ListNode* head, int m, int n) {
	// base case
	if (m == 1) {
		return reverseN(head, n);
	}
	// 前进到反转的起点触发 base case
	head->next = reverseBetween2(head->next, m - 1, n - 1);
	return head;
}


///////////////////////////4、K个一组翻转链表/////////////////////
ListNode* myReverse1(ListNode* hair, int k) {
	if (k == 1)	return hair;

	ListNode* cur = myReverse1(hair->next, k - 1);
	hair->next->next = hair;
	hair->next = nullptr;

	return cur;
}

ListNode* reverseKGroup1(ListNode* head, int k) {
	if (!head || k <= 1)	return head;
	ListNode* hair = head;
	ListNode* tail = head;

	int count = 0;
	while (tail && count < k) {
		count++;
		tail = tail->next;
	}

	if (count < k)	return hair;

	ListNode* newHead = myReverse1(hair, k);
	hair->next = reverseKGroup1(tail, k);

	return newHead;
}




////////////////方法er/////////////////
ListNode* myReverse2(ListNode* hair, ListNode* tail) {
	ListNode* pre = NULL, * cur = hair, * nex = hair;

	while (cur != tail) {
		nex = cur->next;
		cur->next = pre;

		pre = cur;
		cur = nex;
	}

	return pre;
}

ListNode* reverseKGroup2(ListNode* head, int k) {
	if (!head || k <= 1)	return head;
	ListNode* hair = head;
	ListNode* tail = head;

	int count = 0;
	while (tail && count < k) {
		count++;
		tail = tail->next;
	}

	if (count < k)	return hair;

	ListNode* newHead = myReverse2(hair, tail);
	hair->next = reverseKGroup2(tail, k);

	return newHead;
}




//////////////////5、两数相加//////////////////////
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
	ListNode* res = new ListNode(-1);	//添加虚拟头节点
	ListNode* cur = res;
	int carry = 0;
	while (l1 || l2) {
		int n1 = l1 ? l1->val : 0;
		int n2 = l2 ? l2->val : 0;
		int sum = n1 + n2 + carry;
		carry = sum / 10;
		cur->next = new ListNode(sum % 10);
		cur = cur->next;
		if (l1)	l1 = l1->next;
		if (l2)	l2 = l2->next;
	}
	if (carry)	cur->next = new ListNode(1);
	return res->next;
}


//////////////////////////6、相交链表////////////////////
ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {

	ListNode* fast = headA, * slow = headB;
	while (fast != slow) {
		fast = (fast) ? fast->next : headB;
		slow = (slow) ? slow->next : headA;
	}

	return fast;
}



////////////////////7、两个链表的第一个公共节点////////////////
int len(ListNode* head) {
	int len = 0;
	while (head) {
		len++;
		head = head->next;
	}
	return len;
}

ListNode* getIntersectionNode1(ListNode* headA, ListNode* headB) {
	if (headA == NULL || headB == NULL)  return NULL;
	int l1 = len(headA), l2 = len(headB);
	if (l1 >= l2) {
		int move = l1 - l2;
		while (move--)   headA = headA->next;
	}
	else {
		int move = l2 - l1;
		while (move--)   headB = headB->next;
	}
	while (headA != headB) {
		headA = headA->next;
		headB = headB->next;
	}
	return headA;

}




///////////////////8、排序链表（归并排序）////////////////////
ListNode* merge(ListNode* l1, ListNode* l2) {
	ListNode dummyHead(0);
	auto p = &dummyHead;
	while (l1 && l2) {
		if (l1->val < l2->val) {
			p->next = l1;
			p = l1;
			l1 = l1->next;
		}
		else {
			p->next = l2;
			p = l2;
			l2 = l2->next;
		}
	}
	p->next = l1 ? l1 : l2;
	return dummyHead.next;
}

ListNode* cut(ListNode* head, int n) {
	auto p = head;
	while (--n && p) {
		p = p->next;
	}
	if (!p)  return NULL;
	auto next = p->next;
	p->next = NULL;
	return next;
}

ListNode* sortList1(ListNode* head) {
	ListNode dummyHead(0);
	dummyHead.next = head;
	auto p = head;
	int length = 0;
	//确定链表长度
	while (p) {
		++length;
		p = p->next;
	}
	for (int size = 1; size < length; size <<= 1) {
		auto cur = dummyHead.next;
		auto tail = &dummyHead;

		while (cur) {
			auto left = cur;
			auto right = cut(left, size);
			cur = cut(right, size);

			tail->next = merge(left, right);
			while (tail->next) {
				tail = tail->next;
			}

		}
	}
	return dummyHead.next;
}




////////////////////////////9、回文链表/////////////////////
bool isPalindrome(ListNode* head) {
	if (!head || !head->next)	return true;
	ListNode* fast = head, * slow = head;
	ListNode* p=NULL, * pre = NULL;
	while (fast && fast->next) {
		//快慢遍历
		p = slow;
		slow = slow->next;
		fast = fast->next->next;

		//翻转前半部分
		p->next = pre;
		pre = p;
	}

	if (fast)	slow = slow->next;

	while (p) {
		if (p->val != slow->val)	return false;
		p = p->next;
		slow = slow->next;
	}
	return true;
}


////////////////////////10、合并两个有序链表/////////////////////
ListNode* mergeTwoLists1(ListNode* l1, ListNode* l2) {
	if (!l1)	return l2;
	if (!l2)	return l1;

	if (l1->val < l2->val) {
		l1->next = mergeTwoLists1(l1->next, l2);
		return l1;
	}
	l2->next = mergeTwoLists1(l1, l2->next);
	return l2;
}

ListNode* mergeTwoLists2(ListNode* l1, ListNode* l2) {

	ListNode* head = new ListNode(1);
	ListNode* res = head;
	while (l1 != NULL && l2 != NULL) {
		if (l1->val < l2->val) {
			head->next = l1;
			l1 = l1->next;
		}
		else {
			head->next = l2;
			l2 = l2->next;
		}
		head = head->next;
	}
	head->next = l1 == NULL ? l2 : l1;

	return res->next;
}


/////////////////////////11、合并k个有序链表///////////////////
//递归

ListNode* merge1(ListNode* l1, ListNode* l2) {
	if (!l1) return l2;
	if (!l2) return l1;
	if (l1->val <= l2->val) {
		l1->next = merge1(l1->next, l2);
		return l1;
	}
	else {
		l2->next = merge1(l1, l2->next);
		return l2;
	}
}

ListNode* merge2Lists(vector<ListNode*>& lists, int start, int end) {
	if (start == end)  return lists[start];
	ListNode* l1 = merge2Lists(lists, start, (start + end) / 2);
	ListNode* l2 = merge2Lists(lists, (start + end) / 2 + 1, end);
	return merge1(l1, l2);
}

ListNode* mergeKLists(vector<ListNode*>& lists) {
	if (lists.size() < 1) return NULL;
	return merge2Lists(lists, 0, lists.size() - 1);
}





