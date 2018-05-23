/*
*
* Create By Kaijin Cui,2018
*
*/


#pragma once
#include"basic.h"
#include"BTree.h"


template <typename T, typename K>struct RecType
{
	K key;	//�ؼ�����
	T data;		//����������
};		//����Ԫ�ص�����


//HashTable
#define NULLKEY -1//����չؼ���ֵ
#define DELKEY -2//���屻ɾ�ؼ���ֵ


template <typename T>struct HashTable
{
	T key;//�ؼ�����
	int count;//̽�������
};



template <typename T, typename K>int SeqSreach(RecType<T, K> R[], int n, K k)
{
	int i = 0;
	while (i < n && R[i].key != k)		//�ӱ�ͷ������
		i++;
	if (i > n)							//δ�ҵ�����0
		return 0;
	else
		return i + 1;					//�ҵ������߼����i + 1
}

template <typename T, typename K>int SeqSreach1(RecType<T, K> R[], int n, K k)
{
	int i = 0;
	R[n].key = k;
	while (R[i].key != k)		//�ӱ�ͷ������
		i++;
	if (i == n)
		return 0;				//δ�ҵ�������
	else
		return i + 1;			//�ҵ������߼����i + 1
}


/*
*  Binary search tree, by CXD, 2018
*/

template<typename T> bool InsertBST(BTNode<T> *&bt, T k)
{
	if (bt == 0) {
		bt = new BTNode<T>;
		bt->data = k; bt->lchild = bt->rchild = 0;
		return true;
	}
	else if (k == bt->data) {
		return false;
	}
	else if (k < bt->data) {
		return InsertBST(bt->lchild, k);
	}
	else {
		return InsertBST(bt->rchild, k);
	}
}

template<typename T> BTNode<T>*  CreateBST(T *A, int n)
{
	BTNode<T> *bt = 0;
	int i;
	for (i = 0; i<n; i++) {
		InsertBST(bt, A[i]);   //��A[i]�������������bt��
	}
	return bt;
}

template<typename T> BTNode<T>* SearchBST(BTNode<T> *bt, T k)
{
	if (bt == 0 || bt->data == k) {
		return bt;
	}
	else if (k<bt->data) {
		return SearchBST(bt->lchild, k);
	}
	else {
		return SearchBST(bt->rchild, k);
	}
}

//f is the  parents node
template<typename T> BTNode<T>* SearchBSTf(BTNode<T> *bt, T k, BTNode<T> *f1, BTNode<T> *&f)
{
	if (bt == 0) {
		f = 0;
		return 0;
	}
	else if (k == bt->data) {
		f = f1;
		return bt;
	}
	else if (k < bt->data) {
		return SearchBSTf(bt->lchild, k, bt, f);
	}
	else {
		return SearchBSTf(bt->rchild, k, bt, f);
	}
}

//The deleted p is only the right subtree
template<typename T> bool deletek(BTNode<T> *&bt, T k)
{
	if (bt != 0) {
		if (k == bt->data) {     //���ҵ��˱�ɾ���bt
			deletep(bt);         //����deletep����ɾ�����P
			return true;
		}
		else if (k < bt->data) {
			deletek(bt->lchild, k);  //���������в���
		}
		else {
			deletek(bt->rchild, k);  //������������
		}
	}
	else return false;
}

//P only has a right subtree
template<typename T> void deletep(BTNode<T> *&p)
{
	BTNode<T> *q;
	q = p;   //��qָ��p���
	p = p->rchild;    //pָ���Һ���
	delete q;
}

//P is unkonwn
template<typename T> bool DeleteBST(BTNode<T> *&bt, T k)
{
	if (bt == 0) {
		return false;
	}
	else {
		if (k < bt->data) {         // //�ݹ�����������ɾ��Ϊk�Ľ��
			return DeleteBST(bt->lchild, k);
		}
		else if (k > bt->data) {    //�ݹ�����������ɾ��Ϊk�Ľ��
			return DeleteBST(bt->rchild, k);
		}
		else {             //�ҵ���Ҫɾ���Ľ��bt
			Delete(bt);    //����Delete����ɾ�����bt
			return true;   //ɾ���ɹ���������
		}
	}
}

template<typename T> void Delete(BTNode<T> *&p)
{
	BTNode<T> *q;
	if (p->lchild == 0) {     //���Pû������
		q = p;
		p = p->rchild;              //�ý��P���Һ��Ӵ�����
		delete q;
	}
	else if (p->rchild == 0) {  //���Pû���Һ���
		q = p;
		p = p->lchild;                  //�ý��P���Һ��Ӵ�����
		delete q;
	}
	else {
		Deletel(p, p->lchild);    //���P�������������Һ���
	}
}

template<typename T> void Deletel(BTNode<T> *p, BTNode<T> *&r)
{
	BTNode<T> *q;
	if (r->rchild != 0) {
		Deletel(p, r->rchild);    //�ݹ��ҽ��r�������½��
	}
	else {                        //�ҵ��������½��r����û����������
		p->data = r->data;        //�����r��ֵ��ŵ����p�У����ֵ�����
		q = r;                    //ɾ�����r
		r = r->lchild;            //�ý��r�����������
		delete q;                 //�ͷŽ��q�Ŀռ�
	}
}


/*
*Example
*/

//P329 ����9.4�� find the maxlnode and the minrnode
template<typename T> void MaxMinnode(BTNode<T>* bt)
{
	if (bt != 0) {
		if (bt->lchild != 0) {
			cout << "The maxlnode is " << Maxlnode(bt->lchild) << endl;
		}
		if (bt->rchild != 0) {
			cout << "The maxrnode is " << Minrnode(bt->rchild) << endl;
		}
	}
}

template<typename T> T Maxlnode(BTNode<T>* bt)
{
	while (bt->rchild != 0) {
		bt = bt->rchild;
	}
	return bt->data;
}

template<typename T> T Minrnode(BTNode<T>* bt)
{
	while (bt->lchild != 0) {
		bt = bt->lchild;
	}
	return bt->data;
}


//Insert k to HashTable
template <typename T> void InsertHT(HashTable<T> ha[], int &n, int m, int p, T k)
{
	int i, adr;
	adr = k%p;//�����ϣ����ֵ
	if (ha[adr].key == NULLKEY || ha[adr].key == DELKEY)
	{
		ha[adr].key = k; //k����ֱ�ӷ��ڹ�ϣ����
		ha[adr].count = 1;
	}
	else//������ͻʱ��������̽�ⷨ�����ͻ
	{
		i = 1;//i��¼k������ͻ�Ĵ���
		do
		{
			adr = (adr + 1) % m;//����̽��
			i++;
		} while (ha[adr].key != NULLKEY && ha[adr].key != DELKEY);
		ha[adr].key = k;//��adr������k
		ha[adr].count = i;//����̽�����
	}
	n++;//��ϣ������Ԫ�ظ�����1
}


//Create HashTable
template<typename T> void CreateHT1(HashTable<T> ha[], int &n, int m, int p, T keys[])
{
	int n1 = n, i;
	for (i = 0; i < m; i++)//��ϣ���ÿյĳ�ֵ
	{
		ha[i].key = NULLKEY;
		ha[i].count = 0;
	}
	n = 0;//��ϣ������Ԫ�ظ�����0��ʼ����
	for (i = 0; i < n1; i++)
		InsertHT(ha, n, m, p, keys[i]);//����n���ؼ���
}
//Delete k in HashTable
template <typename T> bool DeleteHT(HashTable<T> ha[], int &n, int m, int p, T k)
{
	int adr;
	adr = k%p;//�����ϣ����ֵ
	while (ha[adr].key != NULLKEY&&ha[adr].key != k)
		adr = (adr + 1) % m;//����̽��
	if (ha[adr].key == k)//���ҳɹ�
	{
		ha[adr].key = DELKEY;//ɾ���ؼ���k
		return true;
	}
	else//����ʧ��
		return false;//���ؼ�
}



//Search k in HashTable
template <typename T> void SearchHT(HashTable <T> ha[], int m, int p, T k)
{
	int i = 1, adr;
	adr = k%p;
	while (ha[adr].key != NULLKEY&& ha[adr].key != k)
	{
		i++;
		adr = (adr + 1) % m;
	}
	if (ha[adr].key == k)
		cout << "�ɹ����ؼ���" << k << "���Ƚ�" << i << "��" << endl;
	else
		cout << "ʧ�ܣ��ؼ���" << k << "���Ƚ�" << i << "��" << endl;

}

template<typename T> void ASL(HashTable<T> ha[], int n, int m, int p)
{
	int i, j;
	int succ = 0, unsucc = 0, s;
	for (i = 0; i < m; i++)
		if (ha[i].key != NULLKEY)
			succ += ha[i].count;
	cout << "�ɹ������ASL(" << n << ")=" << succ*1.0 / n << endl;

	for (i = 0; i < p; i++)
	{
		s = 1; j = i;
		while (ha[i].key != NULLKEY)
		{
			s++;
			j = (j + 1) % m;
		}
		unsucc += s;
	}
	cout << "���ɹ������ASL(" << n << ")=" << unsucc*1.0 / p << endl;
}


template <typename T>void DispHT(HashTable<T> ha[], int n, int m)    //�����ϣ��  
{
	int i;
	cout << " ��ϣ���ַ:" << "\t";
	for (i = 0; i < m; i++)
		cout << setw(3) << setfill(' ') << i;
	cout << endl;
	cout << " ��ϣ��ؼ���:" << "\t";
	for (i = 0; i<m; i++)
		if (ha[i].key == NULLKEY || ha[i].key == DELKEY)
			cout << "    ";         //���3���ո�  
		else
			cout << setw(3) << setfill(' ') << ha[i].key;
	cout << endl;
	printf(" ��������:\t");
	for (i = 0; i<m; i++)
		if (ha[i].key == NULLKEY || ha[i].key == DELKEY)
			cout << "    ";         //���3���ո�  
		else
			cout << setw(3) << setfill(' ') << ha[i].count;
	cout << endl;

}



void SearchExample()
{
	RecType<int, int> R[MAX_SIZE];
	for (int i = 0; i < 6; i++)
	{
		R[i].key = i;
	}

	cout << "The position of the order finding 2 is: " << SeqSreach(R, 6, 2) << endl;
	cout << "The position of the order finding 3 is: " << SeqSreach(R, 6, 3) << endl;


	BTNode<int> *bt;
	BTNode<char> *bf;

	//P329 ����9.3��
	int A[MAX_SIZE] = { 25,18,46,2,53,39,32,4,74,67,60,11 };
	bt = CreateBST(A, 12);
	cout << endl << "The Binary search tree is: ";
	DispBTree(bt); cout << endl;

	//P329 ����9.4�� 
	MaxMinnode(bt);

	DeleteBST(bt, 25);
	cout << "Delete the 25 node: ";
	DispBTree(bt); cout << endl;
	DestroyBTree(bt);

	//P332 ͼ��9.13��
	char k = '1';
	char B[MAX_SIZE] = "3(1(,2))";
	CreateBTree(bf, B);
	cout << endl << "The Binary search tree is: "; DispBTree(bf);
	deletek(bf, k);
	cout << endl << "Delete the 1 node: "; DispBTree(bf);
	DestroyBTree(bf);

	//HashTable
	int x[] = { 16,74,60,43,54,90,46,31,29,88,77 };
	int n = 11, m = 13, p = 13, t = 29;
	HashTable<int> ha1[MAX_SIZE];
	CreateHT1(ha1, n, m, p, x);
	cout << endl;
	DispHT(ha1, n, m);
	SearchHT(ha1, m, p, t);
	k = 77;
	cout << " ɾ���ؼ���" << t << endl;
	DeleteHT(ha1, n, m, p, t);
	DispHT(ha1, n, m);
	SearchHT(ha1, m, p, t);
	cout << " ����ؼ���" << t << endl;
	InsertHT(ha1, n, m, p, t);
	DispHT(ha1, n, m);
	cout << endl;
	ASL(ha1, n, m, p);


}
