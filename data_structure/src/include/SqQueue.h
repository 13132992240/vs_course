/*
 *
 * Create By TangNi,  20180408
 *
 */
 

#ifndef SQQUEUE_H
#define SQQUEUE_H 1

#include "basic.h"

template <typename T> struct SqQueue {
	T data[MAX_SIZE];
	int front;
	int rear;
};


template <typename T> void InitQueue(SqQueue<T> *&q)
{
	q = new SqQueue<T>;
	q->front = q->rear = -1;
}


template <typename T> void DestroyQueue(SqQueue<T> *&q)
{
	delete q;
}


template <typename T> bool QueueEmpty(SqQueue<T> *q)
{
	return(q->front == q->rear);
}


template <typename T> bool enQueue(SqQueue<T> *&q, T e)
{
	if (q->front == MAX_SIZE - 1) {  //���������
		return false;
	}
	q->rear++;
	q->data[q->rear] = e;
	return true;
}


template <typename T> bool deQueue(SqQueue<T> *&q, T &e)
{
	if (q->front == q->rear) {  //�ӿ������
		return false;
	}
	q->front++;
	e = q->data[q->front];
	return true;
}


//circular queue
template <typename T> void InitCQueue(SqQueue<T> *&q)
{
	q = new SqQueue<T>;
	q->front = q->rear = 0;
}


template <typename T> void DestroyCQueue(SqQueue<T> *&q)
{
	delete q;
}


template <typename T> bool CQueueEmpty(SqQueue<T> *q)
{
	return(q->front == q->rear);
}


template <typename T> bool enCQueue(SqQueue<T> *&q, T e)
{
	if ((q->rear + 1) % MAX_SIZE == q->front) {
		return false;
	}
	q->rear = (q->rear + 1) % MAX_SIZE;
	q->data[q->rear] = e;
	return true;
}


template <typename T> bool deCQueue(SqQueue<T> *&q, T &e)
{
	if (q->front == q->rear) {
		return false;
	}
	q->front = (q->front + 1) % MAX_SIZE;
	e = q->data[q->front];
	return true;
}


//��3.7 count�����βָ��
template <typename T> struct QuType
{
	T data[MAX_SIZE];
	int front;
	int count;
};

template <typename T> void InitQueue1(QuType<T> *&qu)
{
	qu = new QuType<T>;
	qu->front = 0;
	qu->count = 0;
}


template <typename T> bool EnQueue1(QuType<T>  *&qu, T x)
{
	int rear;
	if (qu->count == MAX_SIZE) {
		return false;
	}
	else {
		rear = (qu->front + qu->count) % MAX_SIZE;  //���βλ��
		rear = (rear + 1) % MAX_SIZE;
		qu->data[MAX_SIZE] = x;
		qu->count++;
		return true;
	}
}


template <typename T> bool DeQueue1(QuType<T>  *&qu, T &x)
{
	if (qu->count == 0) {
		return false;
	}
	else {
		qu->front = (q->front + 1) % MAX_SIZE;
		x = qu->data[qu->front];
		qu->count--;
		return true;
	}
}


template <typename T> bool QueueEmpty1(QuType<T>  *qu)
{
	return (qu->count == 0);
}


//��ⱨ������ P108
void number(int n)
{
	int i;
	int e=0;
	SqQueue<int> *q;        //���ζ���ָ��q
	InitCQueue(q);
	for (i = 1; i <=n; i++) {
		enCQueue(q, i);
	}
	cout << "��������˳��" << endl;
	while (!CQueueEmpty(q)) {
		deCQueue(q, e);
		cout << '\t' << e;
		if (!CQueueEmpty(q)) {
			deCQueue(q, e);
			enCQueue(q, e);
		}
	}
	cout << endl;
	DestroyCQueue(q);
}

//����Թ����� P109
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

bool mgpath1(int xi, int yi, int xe, int ye)
{
	Box1 e;
	int  i,j, di, i1, j1;
	SqQueue<Box1> *qu;
	InitQueue(qu);
	e.i = xi; e.j = yi; e.pre = -1;
	enQueue(qu, e);
	mg1[xi][yi] = -1;
	while (!QueueEmpty(qu)) {
		deQueue(qu, e);
		i = e.i;
		j = e.j;
		if ( i==xe && j == ye) {
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

void SqQueueExample()
{
	int n = 8;
	cout << "��ʼ����" << endl;
	for (int i = 1; i <= n; i++) {
		cout << '\t' << i;
	}
	cout << endl;
	number(n);

	if (!mgpath1(1, 1, 8, 8)) {
		cout << "���Թ�û�н⣡" << endl;
	}
}



#endif
