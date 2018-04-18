#pragma once

#include "basic.h"

template <typename T>  struct BTNode
{
	T data;
	BTNode<T> *lchild;
	BTNode<T> *rchild;
};

template <typename T> void CreateBTree(BTNode<T> *&b, T *str)
{
	BTNode<T> *St[MAX_SIZE], *p;
	int top = -1, k, j = 0;
	T ch;
	b = NULL;
	ch = str[j];
	while (ch != '\0') {
		switch (ch) {
		case '(': top++; St[top] = p; k = 1; break;
		case ')': top--; break;
		case ',': k = 2; break;
		default:
			p = new BTNode<T>;
			p->data = ch;
			p->lchild = p->rchild = NULL;
			if (b == NULL) {
				b = p;
			}
			else {
				switch (k) {
				case 1: St[top]->lchild = p; break;
				case 2: St[top]->rchild = p; break;
				}
			}
		}
		j++;
		ch = str[j];
	}

}

template <typename T> void DestroyBTree(BTNode<T> *&b)
{
	if (b != NULL) {         /*if b is empty,do nothing*/
		DestroyBTree(b->lchild);
		DestroyBTree(b->rchild);
		delete b;
	}
}

template <typename T>  BTNode<T>* FindNode(BTNode<T> *b, T x)
{
	BTNode<T> *p;
	if (b == NULL) {
		return NULL;
	}
	else if (b->data == x) {
		return b;
	}
	else {
		p = FindNode(b->lchild, x);
		if (p != NULL) {
			return p;
		}
		else {
			return (FindNode(b->rchild, x));
		}
	}
}

template <typename T>  BTNode<T>* LchildNode(BTNode<T> *p)
{
	return p->lchild;
}

template <typename T> BTNode<T>* RchildNode(BTNode<T> *p)
{
	return p->rchild;
}

template <typename T> int BTNodeDepth(BTNode<T> *b)
{
	int lchilddeep, rchilddeep;
	if (b == NULL) {
		return 0;
	}
	else {
		lchilddeep = BTNodeDepth(b->lchild);
		rchilddeep = BTNodeDepth(b->rchild);;
		return (lchilddeep > rchilddeep) ? (lchilddeep + 1) : (rchilddeep + 1);
	}

}

template <typename T> void DispBTree(BTNode<T> *b)
{
	if (b != NULL) {
		cout << b->data;
		if (b->lchild != NULL || b->rchild != NULL) {
			cout << '(';
			DispBTree(b->lchild);
			if (b->rchild != NULL) {
				cout << ',';
				DispBTree(b->rchild);
				cout << ')';
			}
		}
	}
}



/*  traversal methods of a tree  */


template <typename T> void PreOrder(BTNode<T> *b)	//��������ݹ��㷨 
{
	if (b != 0)
	{
		cout << b->data;
		PreOrder(b->lchild);
		PreOrder(b->rchild);
	}
}

template <typename T> void InOrder(BTNode<T> *b)	//��������ݹ��㷨 
{
	if (b != NULL)
	{
		InOrder(b->lchild);
		cout << b->data;
		InOrder(b->rchild);
	}
}

template <typename T> void PostOrder(BTNode<T> *b)	//��������ݹ��㷨 
{
	if (b != NULL)
	{
		PostOrder(b->lchild);
		PostOrder(b->rchild);
		cout << b->data;
	}
}

template <typename T> int Nodes(BTNode<T> *b)	//������ ����7.11�� 
{
	if (b == NULL)
		return 0;
	else
		return Nodes(b->lchild) + Nodes(b->rchild) + 1;
}

template <typename T> void DispLeaf(BTNode<T> *b)	//�������Ҷ�ӽ�㣨�����ң�����7.12�� 
{
	if (b != NULL)
	{
		if (b->lchild == NULL && b->rchild == NULL)
			cout << b->data;
		DispLeaf(b->lchild);
		DispLeaf(b->rchild);
	}
}

template <typename T> void DispLeaf1(BTNode<T> *b)	//�������Ҷ�ӽ�㣨���ҵ��󣩡���7.12�� 
{
	if (b != NULL)
	{
		if (b->lchild == NULL && b->rchild == NULL)
			cout << b->data;
		DispLeaf(b->rchild);
		DispLeaf(b->lchild);
	}
}

template<typename T> int Level(BTNode<T> *b, char x, int h)	//����Ľ��ֵ���ڵĲ�� 
{
	int l;
	if (b == NULL)
		return 0;
	else if (b->data == x)
		return h;
	else
	{
		l = Level(b->lchild, x, h + 1);
		if (l != 0)
			return (l);
		else
			return(Level(b->rchild, x, h + 1));
	}
}

template <typename T> void Lnodenum1(BTNode<T> *b, int h, int k, int &n)
{
	if (b == NULL)
		return;
	else
	{
		if (h == k)
			n++;
		else if (h<k)
		{
			Lnodenum1(b->lchild, h + 1, k, n);
			Lnodenum1(b->rchild, h + 1, k, n);
		}
	}
}

template <typename T> bool Like(BTNode<T> *b1, BTNode<T> *b2)	//p217����7.15�� ���Ŷ������Ƿ����� 
{
	bool like1, like2;
	if (b1 == NULL && b2 == NULL)
		return true;
	else if (b1 == NULL || b2 == NULL)
		return false;
	else
	{
		like1 = Like(b1->lchild, b2->lchild);
		like2 = Like(b1->rchild, b2->rchild);
		return (like1 && like2);
	}
}

template <typename T> bool ancestor(BTNode<T> *b, T x)	//p218����7.15�����ֵΪx������������ 
{
	if (b == NULL)
		return false;
	else if (b->lchild != NULL && b->lchild->data == x || b->rchild != NULL && b->rchild->data == x)
	{
		cout << b->data;
		return true;
	}
	else if (ancestor(b->lchild, x) || ancestor(b->rchild, x))
	{
		cout << b->data;
		return true;
	}
	else
		return false;
}

void BTreeTraversalExample()
{
	BTNode<char> *T = 0;
	char str[] = "A(B(D(,G)),C(E,F))";
	CreateBTree(T, str);
	cout << "��ʾ��������" << endl;
	DispBTree(T);
	cout << endl << "��������ݹ飺" << endl;
	PreOrder(T);
	cout << endl << "��������ݹ飺" << endl;
	InOrder(T);
	cout << endl << "��������ݹ飺" << endl;
	PostOrder(T);
	cout << endl << "������:" << endl;
	cout << Nodes<char>(T) << endl;
	cout << "�������Ҷ�ӽ�㣨�����ң�" << endl;
	DispLeaf(T);
	cout << endl << "�������Ҷ�ӽ�㣨���ҵ���" << endl;
	DispLeaf1(T);
	cout << endl;
	//p215����7.13��
	int h;
	char x;
	cout << "���ֵ��" << endl;
	cin >> x;
	h = Level<char>(T, x, 1);
	if (h == 0)
		cout << "T�в�����" << x << "���" << endl;
	else
		cout << "��T��" << x << "���Ĳ��Ϊ" << h << endl;
	//p216����7.14��
	int k;
	cout << "�ڼ��㣿" << endl;
	cin >> k;
	int  n = 0;	// p216��7.14ȫ�ֱ��� 
	Lnodenum1(T, 1, k, n);
	cout << n << endl;
	//p217����7.15��
	BTNode<char> *G;
	CreateBTree(G, str);
	if (Like(T, G) == true)
		cout << "���ƣ�" << endl;
	else
		cout << "�����ƣ�" << endl;
	//p218����7.16��
	char y;
	cout << "����ֵy" << endl;
	cin >> y;
	ancestor<char>(T, y);

}

void BTNodeexample()
{
	BTNode<char> *b;
	char str[MAX_SIZE] = "A(B(D(,G)),C(E,F))";
	CreateBTree(b, str);
	DispBTree(b);
}







