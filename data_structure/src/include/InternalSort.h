#pragma once

#include "basic.h"
#include "Search.h"


template<typename T, typename K> void ResetSort(RecType<T,K> R[], int n)
{
	int i, j = 0;
	for (i = n - 1; i >= 0; i--) {
		R[j].key = i;
		j++;
	}

}

template<typename T, typename K> void DispSort(RecType<T, K> R[], int n)
{
	for (int i = 0; i < n; i++) {
		cout << R[i].key << " ";
	}
	cout << endl;
}

//Straight insertion sort
template<typename T, typename K> void InsertSort(RecType<T, K> R[], int n)
{
	int i, j;
	RecType<T, K> tmp;
	for (i = 1; i < n; i++) {             //��ʼʱ������ֻ��R[0]
		if (R[i].key < R[i - 1].key) {    //����ʱ
			tmp = R[i];
			j = i - 1;
			do {                         //Ѱ��R[i]�Ĳ���λ��
				R[j + 1] = R[j];         //����
				j--;
			} while (j >= 0 && R[j].key>tmp.key);
			R[j + 1] = tmp;             //j+1������
		}
	}
}


//Binary insertion sort
template<typename T, typename K> void BinInsertSort(RecType<T, K> R[], int n)
{
	int i, j, low, high, mid;
	RecType<T, K> tmp;
	for (i = 1; i < n; i++) {
		if (R[i].key < R[i - 1].key) {        //����ʱ
			tmp = R[i];
			low = 0;
			high = i - 1;
			while (low <= high) {           //�۰���Ҳ���λ��
				mid = (low + high) / 2;
				if (tmp.key < R[mid].key) {
					high = mid - 1;
				}
				else {
					low = mid + 1;
				}
			}
			for (j = i - 1; j >= high + 1; j--) {  //�ҵ�λ��high������
				R[j + 1] = R[j];
			}
			R[high + 1] = tmp;          //����tmp
		}
	}
}

//Shell sort
template<typename T, typename K> void ShellSort(RecType<T, K> R[], int n)
{
	int i, j, d;
	RecType<T, K> tmp;
	d = n / 2;           //�����ó�ֵ
	while (d > 0) {
		for (i = d; i < n; i++) {     //��ÿһС�����ֱ�Ӳ�������
			tmp = R[i];
			j = i - d;
			while (j >= 0 && tmp.key < R[j].key) {
				R[j + d] = R[j];
				j = j - d;
			}
			R[j + d] = tmp;
		}
		d = d / 2;     //��С����
	}
}



void InternalSortExmaple()
{
	RecType<int,int> R[MAX_SIZE];
	int n = 10;
	ResetSort(R, n);

	cout << "Original sequence is : "; DispSort(R, n);

	InsertSort(R, n);
	cout << "After Straight insertion sort : "; DispSort(R, n);

	ResetSort(R, n);
	BinInsertSort(R, n);
	cout << "After Binary insertion sort : "; DispSort(R, n);

	ResetSort(R, n);
	ShellSort(R, n);
	cout << "After Shell sort : "; DispSort(R, n);
}
