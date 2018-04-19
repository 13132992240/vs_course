#pragma once

#include "basic.h"
#include "SqQueue.h"


template <typename T>  struct BTNode
{
	T data;
	BTNode<T> *lchild;
	BTNode<T> *rchild;
};


template <typename T> void CreateBTree(BTNode<T> *& b, char *str)
{
	BTNode<T> *St[MAX_SIZE], *p;
	int top = -1, k, j = 0;
	T ch;
	b = 0;
	ch = str[j];
	while (ch != '\0') {
		switch (ch) {
		case '(': top++; St[top] = p; k = 1; break;
		case ')': top--; break;
		case ',': k = 2; break;
		default:
			p = new BTNode<T>;
			p->data = ch;
			p->lchild = p->rchild = 0;
			if (b == 0) {
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
	if (b != 0) {         /* if b is empty, do nothing */
		DestroyBTree(b->lchild);
		DestroyBTree(b->rchild);
		delete b;
	}
}

template <typename T> void DispBTree(BTNode<T> *b)
{
	if (b != 0) {
		cout << b->data;
		if (b->lchild != 0 || b->rchild != 0) {
			cout << '(';
			DispBTree(b->lchild);
			if (b->rchild != 0) {
				cout << ',';
				DispBTree(b->rchild);
				cout << ')';
			}
		}
	}
}

template <typename T>  BTNode<T>* FindNode(BTNode<T> *b, const T x)
{
	BTNode<T> *p;
	if (b == 0) {
		return 0;
	}
	else if (b->data == x) {
		return b;
	}
	else {
		p = FindNode(b->lchild, x);
		if (p != 0) {
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
	if (b == 0) {
		return 0;
	}
	else {
		lchilddeep = BTNodeDepth(b->lchild);
		rchilddeep = BTNodeDepth(b->rchild);;
		return (lchilddeep > rchilddeep) ? (lchilddeep + 1) : (rchilddeep + 1);
	}

}


/*  traverse methods of a tree: recursive traverse  */


template <typename T> void PreOrder(BTNode<T> *b)	//��������ݹ��㷨 
{
	if (b != 0)
	{
		cout << b->data << " ";
		PreOrder(b->lchild);
		PreOrder(b->rchild);
	}
}

template <typename T> void InOrder(BTNode<T> *b)	//��������ݹ��㷨 
{
	if (b != 0)
	{
		InOrder(b->lchild);
		cout << b->data << " ";
		InOrder(b->rchild);
	}
}

template <typename T> void PostOrder(BTNode<T> *b)	//��������ݹ��㷨 
{
	if (b != 0)
	{
		PostOrder(b->lchild);
		PostOrder(b->rchild);
		cout << b->data << " ";
	}
}

/*  traverse methods of a tree: non-recursive traverse  */


template <typename T> void LevelOrder(BTNode<T> *b)
{
	BTNode<T> *p;
	SqQueue<BTNode<T>* > *qu;                      
	InitQueue(qu);
	enQueue(qu, b);
	while (!QueueEmpty(qu)) {
		deQueue(qu, p);
		cout << p->data;
		if (p->lchild != 0) {
			enQueue(qu, p->lchild);
		}
		if (p->rchild != 0) {
			enQueue(qu, p->rchild);
		}
	}
}


template <typename T> int Nodes(BTNode<T> *b)	//������ ����7.11�� 
{
	if (b == 0) {
		return 0;
	}
	else {
		return Nodes(b->lchild) + Nodes(b->rchild) + 1;
	}		
}

// Display node value from left to right
template <typename T> void DispLeafL(BTNode<T> *b)	//�������Ҷ�ӽ�㣨�����ң�����7.12�� 
{
	if (b != 0)
	{
		if (b->lchild == 0 && b->rchild == 0) {
			cout << b->data;
		}
		DispLeafL(b->lchild);
		DispLeafL(b->rchild);
	}
}


// Display node value from right to left
template <typename T> void DispLeafR(BTNode<T> *b)	//�������Ҷ�ӽ�㣨���ҵ��󣩡���7.12�� 
{
	if (b != 0)
	{
		if (b->lchild == 0 && b->rchild == 0) {
			cout << b->data;
		}			
		DispLeafR(b->rchild);
		DispLeafR(b->lchild);
	}
}


template<typename T> int Level(BTNode<T> *b, char x, int h)	// ����Ľ��ֵ���ڵĲ�� 
{
	int l;
	if (b == 0) {
		return 0;
	}		
	else if (b->data == x) {
		return h;
	}		
	else
	{
		l = Level(b->lchild, x, h + 1);
		if (l != 0) {
			return (l);
		}
		else {
			return(Level(b->rchild, x, h + 1));
		}			
	}
}

// h = 1, n = 0
template <typename T> void Lnodenum(BTNode<T> *b, int h, int k, int &n) //���ĳ����εĽ����
{
	if (b == 0){
		return;
	}		
	else
	{
		if (h == k) {
			n++;
		}			
		else if (h < k)
		{
			Lnodenum(b->lchild, h + 1, k, n);
			Lnodenum(b->rchild, h + 1, k, n);
		}
	}
}

template <typename T> bool Like(BTNode<T> *b1, BTNode<T> *b2)	//p217����7.15�� ���Ŷ������Ƿ����� 
{
	bool like1, like2;
	if (b1 == 0 && b2 == 0) {
		return true;
	}		
	else if (b1 == 0 || b2 == 0) {
		return false;
	}		
	else
	{
		like1 = Like(b1->lchild, b2->lchild);
		like2 = Like(b1->rchild, b2->rchild);
		return (like1 && like2);
	}
}


template <typename T> bool Ancestor(BTNode<T> *b, const T x)	//p218����7.16�����ֵΪx������������ 
{
	if (b == 0) {
		return false;
	}		
	else if (b->lchild != 0 && b->lchild->data == x || b->rchild != 0 && b->rchild->data == x)
	{
		cout << b->data;
		return true;
	}
	else if (Ancestor(b->lchild, x) || Ancestor(b->rchild, x))
	{
		cout << b->data;
		return true;
	}
	else {
		return false;
	}		
}


/*���ò�α����������7.17���㷨*/
template <typename T> struct NodeType {
	T pt;
	int parent;
};

template <typename T> void AllPath2(BTNode<T> *b)
{
	int k;
	BTNode<T> *p;
	NodeType<BTNode<T>*> qelem;
	SqQueue<NodeType<BTNode<T>*>> *qu;
	InitQueue(qu);                     //�ǻ��ζ���
	qelem.pt = b;
	qelem.parent = -1;                 //����������Ӧ�Ķ���Ԫ��
	enQueue(qu, qelem);                //���ڵ����
	while (!QueueEmpty(qu)) {
		deQueue(qu, qelem);            //����Ԫ��qelem ���ڶ��е��±�Ϊqu->front
		p = qelem.pt;
		if (p->lchild == 0 && p->rchild == 0) {
			k = qu->front;
			while (qu->data[k].parent != -1) {
				cout << qu->data[k].pt->data <<" ";
				k = qu->data[k].parent ;
			}
			cout << qu->data[k].pt->data << endl;;
		}
		if (p->lchild != 0) {
			qelem.pt = p->lchild;
			qelem.parent = qu->front;
			enQueue(qu, qelem);
		}
		if (p->rchild != 0) {
			qelem.pt = p->rchild;
			qelem.parent = qu->front;
			enQueue(qu, qelem);
		}
	}
}


void BTreeTraversalExample()
{
	BTNode<char> *T = 0;
	char str[] = "A(B(D(,G)),C(E,F))";
	CreateBTree(T, str);
	cout << "��ʾ��������";
	DispBTree(T);
	cout << endl << "��������ݹ飺";
	PreOrder(T);
	cout << endl << "��������ݹ飺";
	InOrder(T);
	cout << endl << "��������ݹ飺";
	PostOrder(T);
	cout << endl << "������:" << Nodes<char>(T) << endl;
	cout << "�������Ҷ�ӽ�㣨�����ң�:";
	DispLeafL(T);
	cout << endl << "�������Ҷ�ӽ�㣨���ҵ���:";
	DispLeafR(T);
	cout << endl << "���������";
	LevelOrder(T);
	//p215����7.13��
	int h;
	char x;
	cout << endl << "���ֵ��";
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
	int  n = 0;	// p216��7.14 
	Lnodenum(T, 1, k, n);
	cout << "������Ϊ��"<<n << endl;
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
	cout << "����Ϊ��";
	Ancestor<char>(T, y);

	cout << "��·���У�" << endl; AllPath2(T);

	DestroyBTree(T);
}
