#include"include/basic.h"
#include"include/SqList.h"
#include"include/LinkNode.h"

int main()
{
	int a[] = {1, 2, 3, 4, 5};
	const int n = 5;
	print_array(a, n);

	// Sequence List
	SqList* sqlist = 0;

	InitList(sqlist);
	CreateList(sqlist, a, n);
	DisplayList(sqlist);
	// insert & delete


	// Linked list
	LinkNode *linkedlist = 0;
	CreateListF(linkedlist, a, n);
	DispList(linkedlist);
	DestroyList(linkedlist);	// note

	CreateListR(linkedlist, a, n);
	DispList(linkedlist);

	// insert & delete


	return 0;
}