#pragma once

#include "basic.h"

typedef char ElemType;

typedef ElemType SqBinTree[MAX_SIZE];

typedef struct node
{
	ElemType data;	//����Ԫ�� 
	struct node *lchild;	//ָ�����ӽڵ� 
	struct node *rchild;	//ָ���Һ��ӽڵ� 
}BTNode;

int n = 0;	//p216��7.14ȫ�ֱ��� 

void CreateBTree(BTNode *&b, char *str)
{
	BTNode *St[MAX_SIZE], *p;	//St������Ϊ˳��ջ 
	int top = -1, k, j = 0;	//topΪջ��ָ�� 
	char ch;
	b = NULL; 	//��ʼʱ������Ϊ�� 
	ch = str[j];
	while (ch != '\0') 	//ѭ��ɨ��str�е�ÿ���ַ� 
	{
		switch (ch)
		{
		case '(': top++; St[top] = p; k = 1; break;	//��ʼ�������ӽ�� 
		case ')': top--; break;	//ջ����������������� 
		case ',': k = 2; break; 	//��ʼ�����Һ��ӽ�� 
		default: p = new BTNode; 	//����һ����㣬��pָ���� 
			p->data = ch; 	//��Ž��ֵ 
			p->lchild = p->rchild = NULL; 	//����ָ�붼����Ϊ�� 
			if (b == NULL) 	//��δ��������� 
				b = p;	//p��ָ������Ϊ����� 
			else 	//�ѽ�������������� 
			{
				switch (k)
				{
				case 1: St[top]->lchild = p; break; 	//�½������Ϊջ���������� 
				case 2: St[top]->rchild = p; break; 	//�½������Ϊջ�������Һ���
				}
			}
		}
		j++;	//����ɨ��str 
		ch = str[j];
	}
}


void DispBTree(BTNode *b)
{
	if (b != NULL)
	{
		cout << b->data;
		if (b->lchild != NULL || b->rchild != NULL)
		{
			cout << "(";
			DispBTree(b->lchild);
			if (b->rchild != NULL)
				cout << ",";
			DispBTree(b->rchild);
			cout << ")";
		}
	}
}

void PreOrder(BTNode *b)	//��������ݹ��㷨 
{
	if (b != NULL)
	{
		cout << b->data;
		PreOrder(b->lchild);
		PreOrder(b->rchild);
	}
}

void InOrder(BTNode *b)	//��������ݹ��㷨 
{
	if (b != NULL)
	{
		InOrder(b->lchild);
		cout << b->data;
		InOrder(b->rchild);
	}
}

void PostOrder(BTNode *b)	//��������ݹ��㷨 
{
	if (b != NULL)
	{
		PostOrder(b->lchild);
		PostOrder(b->rchild);
		cout << b->data;
	}
}

int Nodes(BTNode *b)	//������ ����7.11�� 
{
	int num1, num2;
	if (b == NULL)
		return 0;
	else
		return Nodes(b->lchild) + Nodes(b->rchild) + 1;
}

void DispLeaf(BTNode *b)	//�������Ҷ�ӽ�㣨�����ң�����7.12�� 
{
	if (b != NULL)
	{
		if (b->lchild == NULL && b->rchild == NULL)
			cout << b->data;
		DispLeaf(b->lchild);
		DispLeaf(b->rchild);
	}
}

void DispLeaf1(BTNode *b)	//�������Ҷ�ӽ�㣨���ҵ��󣩡���7.12�� 
{
	if (b != NULL)
	{
		if (b->lchild == NULL && b->rchild == NULL)
			cout << b->data;
		DispLeaf(b->rchild);
		DispLeaf(b->lchild);
	}
}

int Level(BTNode *b, ElemType x, int h)	//����Ľ��ֵ���ڵĲ�� 
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

void Lnodenum1(BTNode *b, int h, int k)
{
	if (b == NULL)
		return;
	else
	{
		if (h == k)
			n++;
		else if (h<k)
		{
			Lnodenum1(b->lchild, h + 1, k);
			Lnodenum1(b->rchild, h + 1, k);
		}
	}
}

bool Like(BTNode *b1, BTNode *b2)	//p217����7.15�� ���Ŷ������Ƿ����� 
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
		return (like1&&like2);
	}
}

bool ancestor(BTNode *b, ElemType x)	//p218����7.15�����ֵΪx������������ 
{
	if (b == NULL)
		return false;
	else if (b->lchild != NULL&&b->lchild->data == x || b->rchild != NULL&&b->rchild->data == x)
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

void BTreeExample()
{
	BTNode *T;
	CreateBTree(T, "A(B(D(,G)),C(E,F))");
	cout << "��ʾ��������" << endl;
	DispBTree(T);
	cout << endl;
	cout << "��������ݹ飺" << endl;
	PreOrder(T);
	cout << endl;
	cout << "��������ݹ飺" << endl;
	InOrder(T);
	cout << endl;
	cout << "��������ݹ飺" << endl;
	PostOrder(T);
	cout << endl;
	cout << "������:" << endl;
	cout << Nodes(T) << endl;
	cout << "�������Ҷ�ӽ�㣨�����ң�" << endl;
	DispLeaf(T);
	cout << endl;
	cout << "�������Ҷ�ӽ�㣨���ҵ���" << endl;
	DispLeaf1(T);
	cout << endl;
	//p215����7.13��
	int h;
	ElemType x;
	cout << "���ֵ��" << endl;
	cin >> x;
	h = Level(T, x, 1);
	if (h == 0)
		cout << "T�в�����" << x << "���" << endl;
	else
		cout << "��T��" << x << "���Ĳ��Ϊ" << h << endl;
	//p216����7.14��
	int k;
	cout << "�ڼ��㣿" << endl;
	cin >> k;
	Lnodenum1(T, 1, k);
	cout << n << endl;
	//p217����7.15��
	BTNode *G;
	CreateBTree(G, "A(B(D(,G)),C(E,F))");
	if (Like(T, G) == true)
		cout << "���ƣ�" << endl;
	else
		cout << "�����ƣ�" << endl;
	//p218����7.16��
	ElemType y;
	cout << "����ֵy" << endl;
	cin >> y;
	ancestor(T, y);

}



