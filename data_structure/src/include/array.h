#pragma once

// #include "basic.h"


template<typename T> void read_array(T a[], int n)
{
	for (int i = 0; i<n; i++)
	{
		cin >> a[i];
	}
}


template<typename T> void print_array(T a[], int n)
{
	for (int i = 0; i<n; i++)
	{
		cout << "\t" << a[i];
	}
	cout << endl;
}


template<typename T> void select_sort_array(T a[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (a[i] > a[j])
			{
				swap(a[i], a[j]);
			}
		}
	}
}


template<typename T> void buble_sort_array(T a[], int n)
{
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < n - i; j++) {
			if (a[j] > a[j + 1]) {
				swap(a[j], a[j + 1]);
			}
		}
	}
}


void  arrayExample()
{
	int n = 6;
	int a[8] = {1, 3, 3, 34, 2, 5};
	// read_array(a,n);
	buble_sort_array(a,n);//����ð������
	print_array(a, n);
	select_sort_array(a, n);//����ѡ������
	print_array(a, n);
}

