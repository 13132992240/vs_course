#pragma once
#include "basic.h"
#include "SqStack.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////                                                 �Թ����                                                          ////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////Solving with  SqStack////////////////////////////////////////////////

typedef struct
{
	int i;	//��ǰ������к�
	int j;	//��ǰ������к�
	int di;	//di����һ�������ڷ�λ�ķ�λ��
} Box;		//���巽������

int mg[8 + 2][8 + 2] =
{
	{ 1, 1,1,1,1,1,1,1,1,  1 },
	{ 1, 0,0,1,0,0,0,1,0,  1 },
	{ 1, 0,0,1,0,0,0,1,0,  1 },
	{ 1, 0,0,0,0,1,1,0,0,  1 },
	{ 1, 0,1,1,1,0,0,0,0,  1 },
	{ 1, 0,0,0,1,0,0,0,0,  1 },
	{ 1, 0,1,0,0,0,1,0,0,  1 },
	{ 1, 0,1,1,1,0,1,1,0,  1 },
	{ 1, 1,0,0,0,0,0,0,0,  1 },
	{ 1, 1,1,1,1,1,1,1,1,  1 }
};

bool mgpath1(int xi, int yi, int xe, int ye)	//���·��Ϊ:(xi,yi)->(xe,ye)
{
	Box path[MAX_SIZE], e;  int i, j, di, i1, j1, k;   bool find;
	SqStack<Box> *st = 0;			//����ջst
	InitStack(st);				//��ʼ��ջ��ָ��
	e.i = xi; e.j = yi; e.di = -1;			//����eΪ���
	Push(st, e);				//����e��ջ
	mg[xi][yi] = -1;	//��ڵ��Թ�ֵ��Ϊ-1�����ظ��ߵ��÷���

	while (!StackEmpty(st))		//ջ����ʱѭ��
	{
		GetTop(st, e);		//ȡջ������e
		i = e.i; j = e.j; di = e.di;
		if (i == xe && j == ye)		//�ҵ��˳���,�����·��
		{
			printf("һ���Թ�·������:\n");
			k = 0;
			while (!StackEmpty(st))
			{
				Pop(st, e);		//��ջ����e
				path[k++] = e;	//��e��ӵ�path������
			}
			while (k >= 1)
			{
				k--;
				printf("\t(%d,%d)", path[k].i, path[k].j);
				if ((k + 2) % 5 == 0)  //ÿ���ÿ5�������һ��
					printf("\n");
			}
			printf("\n");
			DestroyStack(st);//����ջ
			return true;	//���һ���Թ�·���󷵻�true
		}
		find = false;
		while (di<4 && !find)   //�����ڿ��߷���(i1,j1)
		{
			di++;
			switch (di)
			{
			case 0:i1 = i - 1; j1 = j;   break;
			case 1:i1 = i;   j1 = j + 1; break;
			case 2:i1 = i + 1; j1 = j;   break;
			case 3:i1 = i;   j1 = j - 1; break;
			}
			if (mg[i1][j1] == 0)  find = true;
			//�ҵ�һ�����ڿ��߷��飬����findΪ��
		}
		if (find)  		//�ҵ���һ�����ڿ��߷���(i1,j1)
		{
			st->data[st->top].di = di;	  //�޸�ԭջ��Ԫ�ص�diֵ
			e.i = i1; e.j = j1; e.di = -1;
			Push(st, e);		  //���ڿ��߷���e��ջ
			mg[i1][j1] = -1;
			//(i1,j1)�Թ�ֵ��Ϊ-1�����ظ��ߵ��÷���
		}
		else			//û��·������,����ջ
		{
			Pop(st, e);	//��ջ��������ջ
			mg[e.i][e.j] = 0;
			//����ջ�����λ�ñ�Ϊ����·�����߷���
		}
	}
	DestroyStack(st);	//����ջ
	return false;		//��ʾû�п���·��
}

void mgpath_SqStack()
{
	if (!mgpath1(1, 1, 8, 8)) {
		printf("���Թ�����û�н�!");
	}
}

//////////////////////////////////////////Solving with  SqQueue///////////////////////////////////////

typedef struct {
	int i;
	int j;
	int pre;
}Box1;

int mg1[8 + 2][8 + 2] =
{
	{ 1, 1,1,1,1,1,1,1,1,  1 },
	{ 1, 0,0,1,0,0,0,1,0,  1 },
	{ 1, 0,0,1,0,0,0,1,0,  1 },
	{ 1, 0,0,0,0,1,1,0,0,  1 },
	{ 1, 0,1,1,1,0,0,0,0,  1 },
	{ 1, 0,0,0,1,0,0,0,0,  1 },
	{ 1, 0,1,0,0,0,1,0,0,  1 },
	{ 1, 0,1,1,1,0,1,1,0,  1 },
	{ 1, 1,0,0,0,0,0,0,0,  1 },
	{ 1, 1,1,1,1,1,1,1,1,  1 }
};

template <typename T> void Disp(SqQueue<T> *qu, int front)
{
	int k = front, j, ns = 0;
	cout << endl;
	do {
		j = k;
		k = qu->data[k].pre;
		qu->data[j].pre = -1;
	} while (k != 0);
	cout << "һ���Թ�ͨ·���£�" << endl;
	k = 0;
	while (k < MAX_SIZE) {
		if (qu->data[k].pre == -1) {
			ns++;
			cout << '\t' << '(' << qu->data[k].i << ',' << qu->data[k].j << ')';
			if (ns % 5 == 0) {
				cout << endl;
			}
		}
		k++;
	}
	cout << endl;
}

bool mgpath2(int xi, int yi, int xe, int ye)
{
	Box1 e;
	int  i, j, di, i1, j1;
	SqQueue<Box1> *qu;
	InitQueue(qu);
	e.i = xi; e.j = yi; e.pre = -1;
	enQueue(qu, e);
	mg1[xi][yi] = -1;
	while (!QueueEmpty(qu)) {
		deQueue(qu, e);
		i = e.i;
		j = e.j;
		if (i == xe && j == ye) {
			Disp(qu, qu->front);
			DestroyQueue(qu);
			return true;
		}
		for (di = 0; di < 4; di++) {
			switch (di)
			{
			case 0:i1 = i - 1; j1 = j;   break;
			case 1:i1 = i;   j1 = j + 1; break;
			case 2:i1 = i + 1; j1 = j;   break;
			case 3:i1 = i;   j1 = j - 1; break;
			}
			if (mg1[i1][j1] == 0) {
				e.i = i1; e.j = j1;
				e.pre = qu->front;
				enQueue(qu, e);
				mg1[i1][j1] = -1;
			}
		}
	}
	DestroyQueue(qu);
	return false;
}

void mgpath_SqQueue()
{
	if (!mgpath2(1, 1, 8, 8)) {
		cout << "���Թ�û�н⣡" << endl;
	}
}