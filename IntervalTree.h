#pragma once
#include "RBTree.h"
using namespace std;
typedef int maxtype;
typedef int numtype;

typedef struct Interval     //定义一个表示区间范围的结构体
{
	int low;                //区间的低端点（low endpoint）
	int high;               //区间的高端点（high endpoint）
}Interval;

typedef struct I_Node :RB_Node {
	Interval interval;
	maxtype max;  //子树中所有区间的端点的最大值
	numtype num;
	string coursename;
	I_Node(numtype num, Interval interval, string name) {
		this->interval = interval;
		this->num = num;
		this->coursename = name;
		this->max = this->interval.high;
		this->key = this->interval.low;
	}
	I_Node() {
		this->interval = { 0,0 };
		this->max = 0;
		this->num = 0;
	}
	~I_Node() {}
} I_Node, I_Root;
typedef struct I_NodePoint {
	I_Node* p;
	I_NodePoint* next;
}I_NodePoint;

typedef struct I_NodePointlist {
	I_NodePoint head;
	I_NodePointlist() {
		head.next = NULL;
		head.p = NULL;
	}
};

class IntervalTree :
	public RBTree
{
private:
	maxtype GetMax(I_Node* p);
	void Left_Rotate(I_Node* x);
	void Right_Rotate(I_Node* x);
	void RB_SetRoot(I_Node* z);
	bool OverLap(Interval a, Interval b);
	I_NodePoint* Search_All(Interval interval, I_Node* p, I_NodePoint* q);
	
	void In_Order_Traversal(I_Node* p);
public:
	I_Root* Root;
	void IntervalTree_Insert(I_Node* z);
	I_Node* IntervalTree_Delect(I_Node* z);
	I_Node* IntervalTree_Search(Interval interval);
	I_Node* IntervalTree_Search_Exist(Interval interval);
	void IntervalTree_Search_All(Interval interval, I_NodePoint* a);
	void show_operation(I_Node* p);
	void show_seq(I_Node* p);
	bool SeqTraverse();
	bool In_Order();
	I_Root* Get_Root();
	IntervalTree();
	~IntervalTree();
};

