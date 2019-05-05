#include"RBTree.h"
#include"IntervalTree.h"
#include<iostream>
using namespace std;
IntervalTree intree;

void Insert(numtype num, int low, int high, string name) {
	I_Node* a = new I_Node(num, { low, high }, name);
	intree.IntervalTree_Insert(a);
}

void Show() {
	if (intree.In_Order() == false) cout << "there is no course!" << endl;
}

void Search_All(int low, int high) {
	I_NodePointlist  pointlist;
	intree.IntervalTree_Search_All({ low,high }, &(pointlist.head));
	if (pointlist.head.next == NULL) cout << "have no course!" << endl;
	else {
		I_NodePoint* r = pointlist.head.next;
		while (r != NULL) {
			intree.show_operation(r->p);
			r = r->next;
		}
	}
}
void SeqTraverse() {
	if (intree.Root == NULL) {
		cout << "have no course!" << endl;
		return;
	}
	intree.SeqTraverse();

}

void Delect_One(int low, int high) {
	I_Node* p;
	p = intree.IntervalTree_Search({ low,high });
	intree.IntervalTree_Delect(p);
}

void Delect_All(int low, int high) {
	I_Node* p;
	p = intree.IntervalTree_Search_Exist({ low,high });
	while (p) {
		intree.IntervalTree_Delect(p);
		p = intree.IntervalTree_Search_Exist({ low,high });
	}
}


int main(void) 
{
	char operation = '1';
	while(operation != '0') {
		cout << "------------------"<<'\t';
		cout << "课表管理系统" << '\t';
		cout << "------------------"<<endl;
		cout << "插入课程" << "  " << "-" << "  " << 'I' << endl;
		cout << "删除指定区间的课程" << "  " << "-" << "  " << 'D' << endl;
		cout << "删除区间内全部课程" << "  " << "-" << "  " << 'd' << endl;
		cout << "显示当前课程信息" << "  " << "-" << "  " << 'P' << endl;
		cout << "查询区间内所有课程" << "  " << "-" << "  " << 'S' << endl;
		cout << "层序遍历打印所有课程" << "  " << "-" << "  " << 's' << endl;
		cout << "退出系统" << "  " << "-" << "  " << '0' << endl;
		cout << "请选择操作：" << endl;
		cin >> operation;
		if (operation == '0') return 0;
		else if (operation == 'I') {
			numtype num;
			string name;
			cout << "请输入课程编号" << endl;
			cin >> num;
			cout << "请输入课程名字" << endl;
			cin >> name;
			int low, high;
			cout << "请输入课程区间，空格隔开" << endl;
			cin >> low >> high;
			Insert(num, low, high, name);
		}
		else if (operation == 'D') {
			cout << "请输入要删除课程的区间，空格隔开" << endl;
			int low, high;
			cin >> low >> high;
			Delect_One(low, high);
		}
		else if (operation == 'd') {
			cout << "请输入要删除的区间，空格隔开" << endl;
			int low, high;
			cin >> low >> high;
			Delect_All(low, high);
		}
		else if (operation == 'P') {
			Show();
		}
		else if (operation == 's') {
			SeqTraverse();
		}
		else if (operation == 'S') {
			cout << "请输入要查询的区间，空格隔开" << endl;
			int low, high;
			cin >> low >> high;
			Search_All(low, high);
		}
		else {
			cout << "请重新输入" << endl;
		}
	}
	
}