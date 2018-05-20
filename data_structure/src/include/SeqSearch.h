/*
*
* Create By Kaijin Cui,2018
*
*/


#pragma once
#include"basic.h"

template <typename T, typename K>struct RecType
{
	K key;	//�ؼ�����
	T data;		//����������
};		//����Ԫ�ص�����

template <typename T, typename K>int SeqSreach(RecType<T,K> R[], int n, K k)
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

void SeqSearchExample()
{
	RecType<int, int> R[MAX_SIZE];
	for (int i = 0; i < 6; i++)
	{
		R[i].key = i;
	}
	
	cout << "˳�����2��λ��Ϊ��" << SeqSreach(R, 6, 2) << endl;
	cout << "˳�����3��λ��Ϊ��" << SeqSreach(R, 6, 3) << endl;
}