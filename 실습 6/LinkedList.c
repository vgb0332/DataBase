
#include "stdio.h"
#include "stdlib.h"
#pragma warning(disable:4996)

typedef struct NODE {
	int data;
	struct NODE* link;
}node;
void printList(node *L) //List L의 모든 자료 출력
{
	node *p = L;

	printf("\nL");
	while (p != NULL)
	{
		printf(" -> %d", p->data);
		p = p->link;
	}
	printf(" -> NULL \n\n");
}
void returnNode(node *old) //old가 가리키는 node 메모리 삭제
{
	free(old);
}
node* getNode() //새로운 노드 생성
{
	node *p;
	p = (node*)malloc(sizeof(node));
	// if( p == NULL) Error();

	return p;
}
node* insertFirstNode(node *L, int x) //리스트 L에 첫 노드에 삽입
{
	node *N = getNode();
	N->data = x;
	N->link = L;
	L = N;
	return L;
}
node* insertLastNode(node *L, int x) //리스트 L에 마지막 노드에 삽입
{
	node *p; node *q;

	p = getNode();
	p->data = x;
	p->link = NULL;

	if (L == NULL)
		L = p;
	else {
		q = L;
		while (q->link != NULL)
			q = q->link;
		q->link = p;
	}
	return L;
}
node* deleteNode(node *L, node *pre) //pre가 가르키는 다음 노드를 삭제
{
	node *old;
	if (L == NULL) return L;
	old = pre->link;
	if (old != NULL)
	{
		pre->link = old->link;
		returnNode(old);
	}
	return L;
}
node* reverseList(node *L) //리스트 L의 역순
{
	node *p; node *q; node *temp;
	p = L;
	q = NULL;
	while (p != NULL)
	{
		temp = q;
		q = p;
		p = p->link;
		q->link = temp;
	}
	L = q;
	return L;
}
node* searchDeleteNode(node *L, int x) //리스트 L에서 x의 값을 가지는 노드 삭제
{
	node *p; 
	node *pre;

	//리스트 L이 비어있을 때,
	if (L == NULL) 
		return L;
	//리스트 L의 첫 노드에 x값이 있을 때,
	if (L->data == x)
	{
		p = L;
		L = L->link;
		returnNode(p);
		return L;
	}
	//pre는 L의 첫 노드를, P는 L의 두번째 노드를 가리킨다.
	pre = L;
	p = L->link;
	while (p != NULL) //첫 노드부터 끝 노드까지 탐색
	{
		/* p가 가리키는 노드에 x값이 있을 시
		   pre를 p가 가리키는 다음 노드에 연결시킨 후,
		   p가 가리키는 노드 삭제, 리턴 L         */
		if (p->data == x) 
		{
			pre->link = p->link;
			returnNode(p);
			return L;
		}
		pre = p;
		p = p->link;
	}
	return L;
}
node* deleteFirstNode(node *L) //리스트 L의 첫번째 노드 삭제
{
	//List가 비어있을 때, 리턴 L
	if (L == NULL)
		return L;

	/*L의 첫번째 노드를 temp가 가리키고,
	  L를 두번쨰 노드와 연결시킨후,
	  L의 첫번째 노드 삭제, 리턴 L      */
	node* temp = L;
	L = temp->link;
	returnNode(temp);
	return L;
}
node* deleteLastNode(node*L) //리스트 L의 마지막 노드 삭제
{
	//p는 L의 첫 노드를 가리킨다.
	node *p = L;

	//리스트 EMPTY
	if (L == NULL)
		return L;
	//리스트에 노드 1개
	if (L->link == NULL)
	{
		returnNode(L->link);
		L = NULL;
		return L;
	}
	//리스트에 노드 2개 이상
	while (p != NULL)
	{
		/* 리스트 L를 탐색하면서, p의 다음다음 노드가 마지막 노드일 시,
		         deleteNode(L, p)                             */
		if (p->link->link == NULL)
			deleteNode(L, p);
		p = p->link;
	}
	return L;
}

int main()
{
	node *L;
	int menu, data;
	int done = 0;

	L = NULL;
	printList(L);

	while (!done)
	{
		printf("<List Menu>\n");
		printf(" 1 data - Insert first node\n");
		printf(" 2 data - Insert last node\n");
		printf(" 3      - Reverse list\n");
		printf(" 4 data - Delete [data] node\n");
		printf(" 5      - Delete first node\n");
		printf(" 6      - Delete last node\n");
		printf(" 0      - Exit\n");
		printf("Enter menu and data : ");
		scanf("%d", &menu);

		switch (menu)
		{
		case 1: // Insert first node
			scanf("%d", &data);
			L = insertFirstNode(L, data);
			printList(L);
			break;
		case 2: // Insert last node
			scanf("%d", &data);
			L = insertLastNode(L, data);
			printList(L);
			break;
		case 3:
			L = reverseList(L);
			printList(L);
			break;
		case 4:
			scanf("%d", &data);
			L = searchDeleteNode(L, data);
			printList(L);
			break;
		case 5:
			L = deleteFirstNode(L);
			printList(L);
			break;
		case 6:
			L = deleteLastNode(L);
			printList(L);
			break;
		case 0:
			done = 1;
		}
	}


	return 0;
}