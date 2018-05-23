#pragma once
#include"basic.h"

#define NULLKEY -1//����չؼ���ֵ
#define DELKEY -2//���屻ɾ�ؼ���ֵ


template <typename T>struct HashTable
{
	T key;//�ؼ�����
	int count;//̽�������
};

//Insert k to HashTable
template <typename T> void InsertHT(HashTable<T> ha[], int &n, int m, int p, T k)
{
	int i, adr;
	adr=k %p��//�����ϣ����ֵ
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
		ha[adr] =.key = k;//��adr������k
		ha[adr].count = i;//����̽�����
	}
	n++;//��ϣ������Ԫ�ظ�����1
}


//Create HashTable
template<typename T> void CreateHT(HashTable<T> ha[].int &n.int m, int p, T keys[], int nl)
{
	for (int i = 0; i < m; i++)//��ϣ���ÿյĳ�ֵ
	{
		ha[i].key == NULLKEY;
		ha[i].count = 0;
	}
	n = 0;//��ϣ������Ԫ�ظ�����0��ʼ����
	for (i = 0; i < nl; i++)
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
	while (ha[adr].key!=NULLKEY&& ha[adr].key!=k)
	{
		i++;
		adr = (adr + 1) % m;
	}
	if (ha[adr].key == k)
		cout << "�ɹ����ؼ���" << k << "���Ƚ�" << i << "��" << endl;
	else
		cout << "ʧ�ܣ��ؼ���" << k << "���Ƚ�" << i << "��" << endl;

}

