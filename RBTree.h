#pragma once
#include<iostream>
#define RED 0
#define BLACK 1
using namespace std;

typedef int key_type;
typedef int color_type;

typedef struct RB_Node {
	RB_Node* parent = NULL;
	RB_Node* left = NULL;
	RB_Node* right = NULL;
	key_type key = 0;
	color_type color = BLACK;
}RB_Node, RB_Root;

class RBTree
{
private:
	void virtual in_order_operation(RB_Node* p);
protected:
	int Left_Rotate(RB_Node* x, RB_Root** root);
	int Right_Rotate(RB_Node* x, RB_Root** root);
	void RB_Insert_Fixup(RB_Node* z, RB_Root** root);
	void RB_Delect_Fixup(RB_Node* x, RB_Node* px, RB_Root** root);
	void RB_SetRoot(RB_Node* z, RB_Root** root);
	void In_Order_Traversal(RB_Node* p);
	RB_Node* TreeSuccessor(RB_Node* z);
	int Check_RB_LRD(RB_Node* p);       //检查红黑树性质，如果错误则返回-1，正确则返回树的黑高
public:
	
	RBTree();
	~RBTree();
	RB_Root* Root;
	RB_Root* Get_Root();
	void RB_Insert(RB_Node* z, RB_Root** root);
	RB_Node* RB_Search(key_type key, RB_Node** root);
	RB_Node* RB_Delect(RB_Node* z, RB_Root** root);
	void In_Order(RB_Node** root);
	int Check_RB(RB_Node** root);

};

