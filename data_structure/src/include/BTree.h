#pragma once
#include "basic.h"
#include "SqQueue.h"


template<typename T>  struct BTNode
{
	T data;
	BTNode<T> *lchild;
	BTNode<T> *rchild;
};


/* The basic operation of the tree (by PHY) */

template<typename T> void CreateBTree(BTNode<T> *&b, char *str)
{
	BTNode<T> *St[MAX_SIZE], *p;       //St������Ϊ˳��ջ
	int top = -1, k, j = 0;            //topΪջ��ָ��
	T ch;
	b = 0;                             //��ʼ������Ϊ��
	ch = str[j];
	while (ch != '\0')                 //ѭ��ɨ��str�е�ÿ���ַ�
	{
		switch (ch)                    //A(B(D(,G)),C(E,F))
		{
		case'(':top++; St[top] = p; k = 1; break;    //��ʼ�������ӽ��
		case')':top--; break;                        //ջ�����������������
		case',':k = 2; break;                        //��ʼ�����Һ��ӽ��
		default:p = new BTNode<T>;
			p->data = ch;
			p->lchild = p->rchild = 0;
			if (b == 0) {                           //����δ�������ڵ㣬p��Ϊ���ڵ�
				b = p;
			}
			else {
				switch (k)
				{
				case 1:St[top]->lchild = p; break;
				case 2:St[top]->rchild = p; break;
				}
			}
		}
		j++;
		ch = str[j];
	}
}

template<typename T> void DestroyBTree(BTNode<T> *&b)
{
	if (b != 0) {         /* if b is empty, do nothing */
		DestroyBTree(b->lchild);
		DestroyBTree(b->rchild);
		delete b;
	}
}

template<typename T> void DispBTree(BTNode<T> *b)
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

template<typename T> BTNode<T>* FindNode(BTNode<T> *b, const T x)
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

template<typename T> BTNode<T>* LchildNode(BTNode<T> *p)
{
	return p->lchild;
}

template<typename T> BTNode<T>* RchildNode(BTNode<T> *p)
{
	return p->rchild;
}

template<typename T> int BTNodeDepth(BTNode<T> *b)
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


/* traverse methods of a tree: recursive traverse (by PHY) */

template<typename T> void PreOrderRecursively(BTNode<T> *b)	
{
	if (b != 0)
	{
		cout << b->data << " ";
		PreOrderRecursively(b->lchild);
		PreOrderRecursively(b->rchild);
	}
}

template<typename T> void InOrderRecursively(BTNode<T> *b)
{
	if (b != 0)
	{
		InOrderRecursively(b->lchild);
		cout << b->data << " ";
		InOrderRecursively(b->rchild);
	}
}

template<typename T> void PostOrderRecursively(BTNode<T> *b)
{
	if (b != 0)
	{
		PostOrderRecursively(b->lchild);
		PostOrderRecursively(b->rchild);
		cout << b->data << " ";
	}
}

/* traverse methods of a tree: non-recursive traverse (by CuiKaijin) */

template<typename T> void PreOrder(BTNode<T> *b)	
{
	BTNode<T> *p;
	SqStack<BTNode<T>*> *st;
	InitStack(st);
	if (b != 0)
	{
		Push(st, b);
		while (!StackEmpty(st))
		{
			Pop(st, p);
			cout << p->data << " ";
			if (p->rchild != 0)
				Push(st, p->rchild);
			if (p->lchild != 0)
				Push(st, p->lchild);
		}
		cout << endl;
	}
	DestroyStack(st);
}

template<typename T> void PreOrderV2(BTNode<T> *b)	
{
	BTNode<T> *p;
	SqStack<BTNode<T>*> *st;
	InitStack(st);
	p = b;
	while (!SqStackExample(st) || p != 0)
	{
		while (p != 0)
		{
			cout << p->data << " ";
			Push(st, p);
			p = p->lchild;
		}
		if (!StackEmpty(st))
		{
			Pop(st, p);
			p = p->rchild;
		}
	}
	cout << endl;
	DestroyStack(st);
}

template<typename T> void InOrder(BTNode<T> *b)
{
	BTNode<T> *p;
	SqStack<BTNode<T>*> *st;
	InitStack(st);
	p = b;
	while (!StackEmpty(st) || p != 0)
	{
		while (p != 0)
		{
			Push(st, p);
			p = p->lchild;
		}
		if (!StackEmpty(st))
		{
			Pop(st, p);
			cout << p->data << " ";
			p = p->rchild;
		}
	}
	cout << endl;
	DestroyStack(st);
}

template<typename T> void PostOrder(BTNode<T> *b)	//��������ǵݹ��㷨
{
	BTNode<T> *p, *r;
	bool flag;
	SqStack<BTNode<T>*> *st;
	InitStack(st);
	p = b;
	do
	{
		while (p != 0)
		{
			Push(st, p);
			p = p->lchild;
		}
		r = 0;
		flag = true;
		while (!StackEmpty(st) && flag)
		{
			GetTop(st, p);
			if (p->rchild == r)
			{
				cout << p->data << " ";
				Pop(st, p);
				r = p;
			}
			else
			{
				p = p->rchild;
				flag = false;
			}
		}
	} while (!StackEmpty(st));
	cout << endl;
	DestroyStack(st);
}

template<typename T> void LevelOrder(BTNode<T> *b)
{
	BTNode<T> *p;
	SqQueue<BTNode<T>* > *qu;                      
	InitQueue(qu);
	enQueue(qu, b);
	while (!QueueEmpty(qu)) {
		deQueue(qu, p);
		cout << p->data << " ";
		if (p->lchild != 0) {
			enQueue(qu, p->lchild);
		}
		if (p->rchild != 0) {
			enQueue(qu, p->rchild);
		}
	}
}


/*
 *  Examples
 */



//P213����7.11��The number of a tree
template<typename T> int Nodes(BTNode<T> *b)	
{
	if (b == 0) {
		return 0;
	}
	else {
		return Nodes(b->lchild) + Nodes(b->rchild) + 1;
	}		
}

// P214����7.12��Display leaf node value
//from left to right
template<typename T> void DispLeafL(BTNode<T> *b)	//�������Ҷ�ӽ�㣨�����ң�����7.12�� 
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

//from right to left
template<typename T> void DispLeafR(BTNode<T> *b)	//�������Ҷ�ӽ�㣨���ҵ��󣩡���7.12�� 
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

// P215����7.13��Display the level of X node
template<typename T> int Level(BTNode<T> *b, char x, int h)	
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

// P216����7.14��Display the level of X node
// h = 1, n = 0
// h: variable of level, k: given level
// return: #nodes of k-th level
template<typename T> int Lnodenum(BTNode<T> *b, int h, int k) //���ĳ����εĽ����
{
	int n = 0;
	if (b != 0) {
		if (h == k) {
			return 1;
		}
		else if (h < k) {
			return Lnodenum(b->lchild, h + 1, k) + Lnodenum(b->rchild, h + 1, k);
		}
		return 0;
	}
	else {
		return 0;
	}
}

// P217����7.15�� Judge two binary trees is similar
template<typename T> bool Like(BTNode<T> *b1, BTNode<T> *b2)	//p217����7.15�� ���Ŷ������Ƿ����� 
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

// P217����7.16�� Display all the parents node of X node
template<typename T> bool Ancestor(BTNode<T> *b, const T x)	//p218����7.16�����ֵΪx������������ 
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

// P225����7.17��Using binary tree(BTNode) display node value from leaf to root 
template<typename T> void AllPath1(BTNode<T> *b)
{
	BTNode<T> *p, *r;
	bool flag;
	SqStack<BTNode<T>*> *st;
	InitStack(st);
	p = b;
	do
	{
		while (p != 0)
		{
			Push(st, p);
			p = p->lchild;
		}
		r = 0;
		flag = true;
		while (!StackEmpty(st) && flag)
		{
			GetTop(st, p);
			if (p->rchild == r)
			{
				if (p->lchild == 0 && p->rchild == 0)
				{
					for (int i = st->top; i > 0; i--)
						cout << st->data[i]->data << "->";
					cout << st->data[0]->data << endl;
				}
				Pop(st, p);
				r = p;
			}
			else
			{
				p = p->rchild;
				flag = false;
			}
		}
	} while (!StackEmpty(st));
}

// P227����7.18��Using sequence queue(SqQueue) display node value from leaf to root 
template<typename T> struct NodeType {
	T pt;
	int parent;
};

template<typename T> void AllPath2(BTNode<T> *b)
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
				cout << qu->data[k].pt->data << "->";
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



// ��֪�����������й��������
// pre����������У�in����������У�nΪ�������ִ���귵�ظ��ڵ�
template<typename T> BTNode<T> *CreateBT1(T *pre, T *in, int n)
{
	BTNode<T> *b;
	T *p;
	int k;
	if (n <= 0) return NULL;
	b = new BTNode<T>;     //�������������*s
	b->data = *pre;
	for (p = in; p < in + n; p++) {           //�������������ҵ���*ppos��λ��k
		if (*p == *pre) {                    //preָ������
			break;                             //��in���ҵ����˳�ѭ��
		}
	}
	k = p - in;                                 //ȷ���������in�е�λ��
	b->lchild = CreateBT1(pre + 1, in, k);        //�ݹ鹹��������
	b->rchild = CreateBT1(pre + k + 1, p + 1, n - k - 1); //�ݹ鹹��������
	return b;
}


// ��֪�����������й��������
// pre��ź������У�in����������У�nΪ�������ִ���귵�ظ��ڵ�
template<typename T> BTNode<T> *CreateBT2(T *post, T *in, int n)
{
	BTNode<T> *b;
	char r, *p;
	int k;
	if (n <= 0) {
		return 0;
	}
	r = *(post + n - 1);
	b = new BTNode<T>;
	b->data = r;
	for (p = in; p < in + n; p++) {
		if (*p == r) {
			break;
		}
	}
	k = p - in;
	b->lchild = CreateBT2(post, in, k);
	b->rchild = CreateBT2(post + k, p + 1, n - k - 1);
	return b;
}


void BTreeTraversalExample()
{
	BTNode<char> *T = 0;
	char str[] = "A(B(D(,G)),C(E,F))";
	CreateBTree(T, str);
	cout << "Display the tree ��"; DispBTree(T);
	
	cout << endl <<"Height Of The Tree Is " << BTNodeDepth(T) << endl;

	cout << "Preorder Recursive Traversal��"; PreOrderRecursively(T);
	cout << endl << "Inorder Recursive Traversal��"; InOrderRecursively(T);
	cout << endl << "Postorder Recursive Traversal��"; PostOrderRecursively(T);

	cout <<endl<<"Preorder non-recursive Traversal��"; PreOrder(T);
	cout << "Inorder non-recursive Traversal��"; InOrder(T);
	cout << "Postorder non-recursive Traversal��"; PostOrder(T);
	cout << "Levelorder non-recursive Traversal: "; LevelOrder(T);

	cout << endl << "Num Of Nodes Is " << Nodes(T);
	cout << endl << "Display leaf node��form left to right��:"; DispLeafL(T);
	cout << endl << "Display leaf node��form right to left��:"; DispLeafR(T);
	
	// P215����7.13��
	int h;
	char x;
	cout <<endl << "which node's level do you want to know?";
	cin >> x;
	h = Level(T, x , 1);
	if (h == 0) {
		cout << "Can't find the " << x << " node" << endl;
	}
	else {
		cout  << x << "'s height is " << h << endl;
	}
	
	// P216����7.14��
	int k;
	cout << "which level'node do you want to know?";
	cin >> k;
	int n = 0;
	n = Lnodenum(T, 1, k);
	cout << "Num of node is��"<<n << endl;
	
	// P217����7.15��
	BTNode<char> *G;
	CreateBTree(G, str);
	if (Like(T, G) == true) {
		cout << "Similar��" << endl;
	}
	else {
		cout << "Not Similar��" << endl;
	}

	// p218����7.16��
	char y;
	cout << "Enter the node:";
	cin >> y;
	cout << "Parent's node is ��";
	Ancestor(T, y);

	// P226 ����7.17��
	cout << "Using BTNode display node value from leaf to root��" << endl; AllPath1(T);
	// P226 ����7.18��
	cout << "Using SqQueue display node value from leaf to root��" << endl; AllPath2(T);
	

	char pre[] = "ABDGCEF", in[] = "DGBAECF", post[] = "GDBEFCA";
	BTNode<char> *b1;
	b1 = CreateBT1(pre, in, 7);
	DispBTree(b1); cout << endl;

	BTNode<char> *b2;
	b2 = CreateBT1(post, in, 7);
	DispBTree(b1); cout << endl;


	DestroyBTree(T);
}

