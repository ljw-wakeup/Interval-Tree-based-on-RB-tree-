#include "RBTree.h"
#include<iostream>
using namespace std;

void RBTree::RB_SetRoot(RB_Node* z, RB_Root** root) {
	*root = z;
	(*root)->color = BLACK;
	(*root)->parent = NULL;
}
RB_Root* RBTree::Get_Root() {
	return Root;
}
RB_Node* RBTree::RB_Delect(RB_Node* z, RB_Root** root)
{
	RB_Node* y = NULL; //y point to the node which will be delected
	RB_Node* x = NULL;
	if (z->left == NULL || z->right == NULL)  y = z;           //case1,2
	else y = TreeSuccessor(z);                    //case 3(have right and left children)
	// for now, y is the x's parent and y should be delected
	// x is the node which will be link to y's parent
	if (y->left != NULL) x = y->left;
	else if (y->right != NULL) x = y->right;   
	else x = NULL;    //case 1; //注意 此时x可能为空
	if (x != NULL) x->parent = y->parent;
	if (y->parent == NULL) {       //y is root
		if (x != NULL) RB_SetRoot(x, root);
		else *root = NULL;    //the empty tree;
		return y;
	}
	else {    //y is not the root
		if ( y == y->parent->left) y->parent->left = x;
		else y->parent->right = x;
	}
	if (y != z) z->key = y->key;   //case 3
	if (y->color == BLACK) RB_Delect_Fixup(x,y->parent, root);
	return y;
}
void RBTree::RB_Delect_Fixup(RB_Node* x, RB_Node* px, RB_Root** root) {
	//px is x's parent, used in the case which the x is null
	if (x == NULL) {
		if (px->left == NULL) {               // x is the px's left child. case 1, 2
			RB_Node* w = px->right;    
			if (w->color == RED) {           //case 1
				w->color = BLACK;
				px->color = RED;
				Left_Rotate(px, root);
				w = px->right;               //case 1 to case 2
			}
			// case 2   //don't have the case 3,4
			w->color = RED;
			x = px;
		}
		else {               // x is the px's right child. case 5, 6
			RB_Node* w = px->left;
			if (w->color == RED) {           //case 5
				w->color = BLACK;
				px->color = RED;
				Right_Rotate(px, root);
				w = px->left;               //case 5 to case 6
			}
			// case 6   //don't have the case 7,8
			w->color = RED;
			x = px;
		}
	}
	while (x->parent != NULL && x->color == BLACK) {
		if (x == x->parent->left) {
			RB_Node* w = x->parent->right;
			if (w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				Left_Rotate(x->parent, root);
				w = x->parent->right;                  //case 1 to 234
			}
			if (w->left->color == BLACK && w->right->color == BLACK) {    //case 2
				w->color = RED;
				x = x->parent;
			}
			else{
				if (w->right->color == BLACK) {                 //case 3
					w->left->color = BLACK;
					w->color = RED;
					Right_Rotate(w, root);
					w = x->parent->right;                //to case 4
				}
				//case 4
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->right->color = BLACK;
				Left_Rotate(x->parent, root);
				x = *root;  //stop
			}
		}
		else {
			RB_Node* w = x->parent->left;
			if (w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				Right_Rotate(x->parent, root);
				w = x->parent->left;                
			}
			if (w->left->color == BLACK && w->right->color == BLACK) {  
				w->color = RED;
				x = x->parent;
			}
			else {
				if (w->left->color == BLACK) {                 
					w->right->color = BLACK;
					w->color = RED;
					Left_Rotate(w, root);
					w = x->parent->left;             
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->left->color = BLACK;
				Right_Rotate(x->parent, root);
				x = *root;  //stop
			}
		}
	}
	x->color = BLACK;
}

RB_Node* RBTree::TreeSuccessor(RB_Node* z) {
	//the most leftdown leaf in the subrighttree 
	RB_Node* y = z->right;
	while (y->left != NULL) y = y->left;
	return y;
}

void RBTree::RB_Insert(RB_Node* z, RB_Root** root)
{
	RB_Node* y = NULL;
	RB_Node* x = *root;
	while (x != NULL) {
		y = x;
		if (z->key < x->key)
			x = x->left;
		else x = x->right;
	}   //when it is end, the x points to the insert position and y points to the x's parent
	z->parent = y;
	if (y == NULL) {  // if the tree is empty, then the z is the root
		RB_SetRoot(z, root);
	}
	else if (z->key < y->key)
		y->left = z;
	else y->right = z;
	z->left = z->right = NULL;
	z->color = RED;
	RB_Insert_Fixup(z, root);
}

void RBTree::RB_Insert_Fixup( RB_Node* z, RB_Root** root) {
	if (*root == z) {
		z->color = BLACK;
		return;
	}
	while (z != *root && z->parent->color == RED){
		//color(p(z)) is red so the p(z) can't be the root and p(p(z)) is black
		// case 123
		if (z->parent == z->parent->parent->left) {
			RB_Node* y = z->parent->parent->right;   //y is z's uncle
			if (y != NULL && y->color == RED) {          //case1 
				y->color = BLACK;
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
			else   //case 2 or case 3: y is black
			{
				if (z == z->parent->right) {   //case 2: to case 3
					z = z->parent;
					Left_Rotate(z, root);
				}
				// case 3
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				Right_Rotate(z->parent->parent, root);//p(z) is black, the circle is eneded.
			}//end 2 or 3
		}//end 1,2,3
		else    // case 4,5,6
		{
			RB_Node* y = z->parent->parent->left;   //y is z's uncle
			if (y!=NULL && y->color == RED) {          //case4
				y->color = BLACK;
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
			else   //case 5 or case 6: y is black
			{
				if (z == z->parent->left) {   //case 5: to case 3
					z = z->parent;
					Right_Rotate(z, root);
				}
				// case 6
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				Left_Rotate(z->parent->parent, root);//p(z) is black, the circle is eneded.
			}//end 5 or 6

		}// end 456
	}// end while
	(*root)->color = BLACK;
}

int RBTree::Left_Rotate(RB_Node* x, RB_Root** root)
{
	if (x->right == NULL) return false;
	RB_Node* y = x->right;
	x->right = y->left;
	if (y->left != NULL)
		y->left->parent = x;
	y->parent = x->parent;
	if (x->parent == NULL)     //if x is root
		RB_SetRoot(y, root);
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;
	y->left = x;
	x->parent = y;
	return true;
}
int RBTree::Right_Rotate(RB_Node* x, RB_Root** root)
{
	if (x->left == NULL) return false;
	RB_Node* y = x->left;
	x->left = y->right;
	if (y->right != NULL)
		y->right->parent = x;
	y->parent = x->parent;
	if (x->parent == NULL)    //if x is root, then y is root
		RB_SetRoot(y, root);
	else if (x == x->parent->left)
		x->parent->left = y;
	else x->parent->right = y;
	y->right = x;
	x->parent = y;
	return true;
}

void RBTree:: In_Order(RB_Node** root) {
	if (*root == NULL) return;
	RB_Node* p = *root;
	In_Order_Traversal(p);
}

void RBTree::In_Order_Traversal(RB_Node* p) {
	if (p == NULL) return;
	In_Order_Traversal(p->left);
	in_order_operation(p);
	In_Order_Traversal(p->right);
}

void RBTree :: in_order_operation(RB_Node* p) {
	cout << p->key << '\t';
}
int RBTree::Check_RB(RB_Node** root) {
	if (*root == NULL) return 0;
	if ((*root)->color == RED) return -1;
	else {
		RB_Node* p = *root;
		return Check_RB_LRD(p);
	}
}

int RBTree::Check_RB_LRD(RB_Node* p) {
	int BHeight;
	if (p == NULL) return 1;
	int left_BHeight = Check_RB_LRD(p->left);
	if (left_BHeight == -1) return -1;
	int right_BHeight = Check_RB_LRD(p->right);
	if (right_BHeight == -1) return -1;
	if (left_BHeight != right_BHeight) return -1;
	p->color == RED ? BHeight = left_BHeight : BHeight = left_BHeight + 1;
	return BHeight;
}

RB_Node* RBTree::RB_Search(key_type key, RB_Node** root) {
	if (root == NULL) return NULL;
	else {
		RB_Node* p = *root;
		while (p != NULL) {
			if (p->key == key) return p;
			else if (p->key > key) p = p->left;
			else p = p->right;
		}
		return NULL;
	}
}


RBTree::RBTree(void)
{
	Root = NULL;
}


RBTree::~RBTree()
{
}
