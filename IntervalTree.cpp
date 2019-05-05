#include "IntervalTree.h"
#include <iostream>
#include <queue>
using namespace std;

maxtype IntervalTree::GetMax(I_Node* p)
{
	maxtype temp = p->interval.high;
	if (p->left != NULL && temp < (((I_Node*)(p->left))->max)) temp = ((I_Node*)(p->left))->max;
	else if(p->right != NULL && temp < ((I_Node*)(p->right))->max) temp = ((I_Node*)(p->right))->max;
	return temp;
}

I_Root* IntervalTree::Get_Root() {
	return Root;
}

void IntervalTree::Left_Rotate(I_Node* x) 
{ 
	if (RBTree::Left_Rotate(x,(RB_Root**)&Root) == 1) {
		I_Node* y;
		y = (I_Node*)x->parent;
		// update the max
		y->max = x->max;
		x->max = GetMax(x);
	}

}
void IntervalTree::RB_SetRoot(I_Node* z) {
	Root = z;
	Root->color = BLACK;
	Root->parent = NULL;
}
void IntervalTree::Right_Rotate(I_Node* x) 
{
	if (RBTree::Right_Rotate(x, (RB_Root **)&Root) == 1) {
		I_Node* y = (I_Node*)x->parent;
		//update the max
		y->max = x->max;
		x->max = GetMax(x);
	}
}
I_Node* IntervalTree::IntervalTree_Delect(I_Node* z) 
{
	I_Node* y = NULL; //y point to the node which will be delected
	I_Node* x = NULL;
	if (z->left == NULL || z->right == NULL)  y = z;           //case1,2
	else y = (I_Node*)TreeSuccessor(z);                    //case 3(have right and left children)
	// for now, y is the x's parent and y should be delected
	// x is the node which will be link to y's parent
	if (y->left != NULL) x = (I_Node*)y->left;
	else if (y->right != NULL) x = (I_Node*)y->right;
	else x = NULL;    //case 1; //注意 此时x可能为空
	if (x != NULL) x->parent = y->parent;
	if (y->parent == NULL) {       //y is root
		if (x != NULL) RB_SetRoot(x);
		else Root = NULL;    //the empty tree;
		return y;
	}
	else {    //y is not the root
		if (y == y->parent->left) y->parent->left = x;
		else y->parent->right = x;
	}
	if (y != z) {
		z->key = y->key;
		z->interval = y->interval;
		z->num = y->num;
		z->max = y->max;
		z->coursename = y->coursename;
	}//case 3
	//update the max;
	I_Node* w = (I_Node*)y->parent;
	while (w) {
		w->max = GetMax(w);
		w = (I_Node*)w->parent;
	}
	if (y->color == BLACK) RB_Delect_Fixup(x, y->parent, (RB_Root **)&Root);
	return y;

}
void IntervalTree::IntervalTree_Insert(I_Node* z) 
{
	I_Node* y = NULL;
	I_Node* x = Root;
	while (x != NULL) {
		y = x;
		// update the max of x
		if (z->max > x->max) x->max = z->max;
		if (z->key < x->key)
			x = (I_Node*)x->left;
		else x = (I_Node*)x->right;
	}   //when it is end, the x points to the insert position and y points to the x's parent
	z->parent = y;
	if (y == NULL) {  // if the tree is empty, then the z is the root
		RB_SetRoot(z);
	}
	else if (z->key < y->key)
		y->left = z;
	else y->right = z;
	z->left = z->right = NULL;
	z->color = RED;
	RB_Insert_Fixup(z, (RB_Root **)&Root);
};
I_Node* IntervalTree::IntervalTree_Search(Interval interval) {
	if (Root == NULL) return NULL;
	I_Node* p = Root;
	while (p != NULL) {
		if (p->interval.high == interval.high && p->interval.low == interval.low) return p;
		if (p->key > interval.low) p = (I_Node*)p->left;
		else p = (I_Node*)p->right;
	}
	return NULL;
}
I_Node* IntervalTree::IntervalTree_Search_Exist(Interval interval) {
	if (Root == NULL) return NULL;
	I_Node * p = Root;
	while (p != NULL && !OverLap(p->interval, interval)) {
		if (p->left != NULL && ((I_Node*)(p->left))->max >= interval.low)
			p = (I_Node*)p->left;
		else p = (I_Node*)p->right;
	}
	return p;
}
void IntervalTree::IntervalTree_Search_All(Interval interval, I_NodePoint* head) {
	if (Root == NULL) return;
	Search_All(interval, Root, head);
}
I_NodePoint* IntervalTree::Search_All(Interval interval, I_Node* p, I_NodePoint* q) {
	if (p == NULL) return q;
	if (OverLap(p->interval, interval)) {
		q->next = new I_NodePoint;
		q = q->next;
		q->p = p;
		q->next = NULL;
	}
	if (p->left != NULL && ((I_Node*)(p->left))->max >= interval.low)
	{
		q = Search_All(interval, (I_Node*)p->left, q);
		q = Search_All(interval, (I_Node*)p->right, q);
	}
	else q = Search_All(interval, (I_Node*)p->right, q);
	return q;
}

bool IntervalTree::OverLap(Interval a, Interval b) {
	if (a.low < b.high && b.low < a.high) return true;
	return false;
}

bool IntervalTree::In_Order() {
	if (Root == NULL) return false;
	I_Node * p = Root;
	In_Order_Traversal(p);
	return true;
}

void IntervalTree::In_Order_Traversal(I_Node* p)
{
	if (p == NULL) return;
	In_Order_Traversal((I_Node *) (p->left));
	show_operation(p);
	In_Order_Traversal((I_Node *) (p->right));
}

void IntervalTree::show_operation(I_Node* p) {
	cout << "课程编号:" << '\t';
	cout << p->num << '\t';
	cout << "课程名称：" << '\t';
	cout << p->coursename << '\t';
	cout << "课程区间: " << '\t';
	cout << "[" << p->interval.low << ',' << p->interval.high << ']' << endl;
}
void IntervalTree::show_seq(I_Node* p) {
	cout << "low:" << '\t' << p->key << '\t' << "color:" << '\t' << p->color <<endl;
	if (p->parent != NULL)cout << "parent's low:" << '\t' << p->parent->key << '\t' << "color:" << '\t' << p -> parent-> color << endl;
	else cout << "root hhh" << endl;
	cout << endl;
}
bool IntervalTree::SeqTraverse()
{
	I_Node* p;
	if (Root == NULL) return false;
	queue<I_Node*> queue;
	queue.push(Root);
	while (!queue.empty()) {
		p = queue.front();
		queue.pop();
		show_seq(p);
		if (p->left != NULL) queue.push((I_Node*)p->left);
		if (p->right != NULL) queue.push((I_Node*)p->right);
	}
}


IntervalTree::IntervalTree()
{
	Root = NULL;
}


IntervalTree::~IntervalTree()
{
}
