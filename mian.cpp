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
		cout << "�α����ϵͳ" << '\t';
		cout << "------------------"<<endl;
		cout << "����γ�" << "  " << "-" << "  " << 'I' << endl;
		cout << "ɾ��ָ������Ŀγ�" << "  " << "-" << "  " << 'D' << endl;
		cout << "ɾ��������ȫ���γ�" << "  " << "-" << "  " << 'd' << endl;
		cout << "��ʾ��ǰ�γ���Ϣ" << "  " << "-" << "  " << 'P' << endl;
		cout << "��ѯ���������пγ�" << "  " << "-" << "  " << 'S' << endl;
		cout << "���������ӡ���пγ�" << "  " << "-" << "  " << 's' << endl;
		cout << "�˳�ϵͳ" << "  " << "-" << "  " << '0' << endl;
		cout << "��ѡ�������" << endl;
		cin >> operation;
		if (operation == '0') return 0;
		else if (operation == 'I') {
			numtype num;
			string name;
			cout << "������γ̱��" << endl;
			cin >> num;
			cout << "������γ�����" << endl;
			cin >> name;
			int low, high;
			cout << "������γ����䣬�ո����" << endl;
			cin >> low >> high;
			Insert(num, low, high, name);
		}
		else if (operation == 'D') {
			cout << "������Ҫɾ���γ̵����䣬�ո����" << endl;
			int low, high;
			cin >> low >> high;
			Delect_One(low, high);
		}
		else if (operation == 'd') {
			cout << "������Ҫɾ�������䣬�ո����" << endl;
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
			cout << "������Ҫ��ѯ�����䣬�ո����" << endl;
			int low, high;
			cin >> low >> high;
			Search_All(low, high);
		}
		else {
			cout << "����������" << endl;
		}
	}
	
}