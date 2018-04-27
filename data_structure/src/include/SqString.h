#pragma once
#include "basic.h"
#include "SqList.h"

//typedef struct
//{
//	char data[MAX_SIZE];
//	int length;
//} SqString;

typedef SqList<char> SqString;


/*Algorithm by CXD*/

// Brute-Force
int BruteForce(SqString s, SqString t)
{
	int j = 0, i = 0;
	while (i<s.length&&j < t.length) {
		if (s.data[i] == t.data[j]) {
			i++;
			j++;
		}
		else {
			i = i - j + 1;//�Ƶ�i����һ��
			j = 0;
		}
	}
	if (j >= t.length) {
		return (i - t.length);//����i���±��ȥģʽ�����ȣ����ڵ�һ���ַ����ڵ��±�
	}
	else {
		return -1;
	}
}

// KMP
void GetNext(SqString t, int *next)
{
	int  j = 0, k = -1;
	next[0] = -1;//next[j]����jǰ�м����뿪ͷ��ͬ����
	while (j < t.length - 1) {//��j=length-1ʱ���Ѿ���ÿ���ַ���next��ע��
		if (k == -1 || t.data[k] == t.data[j]) {
			j++;
			k++;
			next[j] = k;
		}
		else {
			k = next[k];
		}
	}
}

int KMPIndex(SqString s, SqString t)
{
	int i = 0, j = 0;
	int next[MAX_SIZE];
	GetNext(t, next);
	while (i < s.length&&j < t.length) {
		if (j == -1 || s.data[i] == t.data[j]) {
			i++;
			j++;
		}
		else {
			j = next[j];
		}
	}
	if (j >= t.length) {
		return (i - t.length);
	}
	else {
		return -1;
	}
}

// better KMP
void GetNextval(SqString t, int *nextval)
{
	int j = 0, k = -1;
	nextval[0] = -1;
	while (j < t.length) {
		if (k == -1 || t.data[k] == t.data[j]) {
			k++;
			j++;
			if (t.data[k] == t.data[j]) {
				nextval[j] = nextval[k];
			}
			else {
				nextval[j] = k;
			}
		}
		else {
			k = nextval[k];
		}
	}
}

int KMPIndex1(SqString s, SqString t) {
	int nextval[MAX_SIZE];
	int i = 0, j = 0;
	GetNextval(t, nextval);
	while (i < s.length&&j < t.length) {
		if (j == -1 || s.data[i] == t.data[j]) {
			i++;
			j++;
		}
		else {
			j = nextval[j];
		}
	}
	if (j >= t.length) {
		return (i - t.length);
	}
	else {
		return -1;
	}
}


void SqStringexample()
{
	int i;
	SqString t, s;
	char a[5] = "abab";
	char b[13] = "abbaababbaab";
	for (i = 0; i < 4; i++) {
		t.data[i] = a[i];
	}
	t.length = 4;
	for (i = 0; i < 12; i++) {
		s.data[i] = b[i];
	}
	s.length = 12;
	cout << "The position of the substring is:"<<endl;
	cout << BruteForce(s, t)<< endl;
	cout << KMPIndex(s, t)<< endl;
	cout << KMPIndex1(s, t)<< endl;
}