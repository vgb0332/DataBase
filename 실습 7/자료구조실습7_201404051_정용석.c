#include "stdio.h"
#include "stdlib.h"

typedef struct _dnode
{
	struct _node *prev,	*next;
	int          value;
}dnode;

typedef struct _deque
{
	int size;
	dnode *front, *rear;
}deque;

void pauseExit()
{
	system("pause");
	exit(0);
}

deque *createDeque()
{
	deque *deq = (deque*)malloc(sizeof(deque));

	deq->front = NULL;
	deq->rear = NULL;
	deq->size = 0;

	return deq;
}

dnode *getNode()
{
	dnode *a;

	a = (dnode*)malloc(sizeof(dnode));
	a->value = 0;
	a->prev = NULL;
	a->next = NULL;

	return a;
}

void returnNode(dnode *old)
{
	free(old);
}

void printDeque(deque *deq)
{
	dnode *temp = deq->front;
	printf("Deque: ");
	if (isEmpty(deq))
		printf("\n");
	else {
		//덱의 Front부터 Rear까지 출력
		while (temp != NULL) {
			printf("[%c] ", temp->value);
			temp = temp->next;
		}
		printf("\n");
	}

}

int isEmpty(deque *deq) //덱이 EMPTY면 1 출력
{
	
	if (deq->size == 0)
		return 1;
	else
		return 0;
}

void insertFront(deque *deq, int value)
{
	dnode* newNode = getNode();
	newNode->value = value;

	//덱이 EMPTY이면 FRONT와 REAR모두 newNode
	if (isEmpty(deq))
	{
		deq->front = newNode;
		deq->rear = newNode;
		deq->size++;
	}

	//덱이 EMPTY가 아닐시, 알맞게 연결
	else
	{
		newNode->next = deq->front;
		deq->front->prev = newNode;
		deq->front = newNode;
		deq->size++;
	}
}
int deleteFront(deque *deq)
{
	dnode* oldNode = deq->front;
	int value;
	//덱이 EMPTY일 시, 프로그램 종료
	if (isEmpty(deq)) { exit(0); }

	//덱에 노드가 1개일 시, front와 rear모두 NULL
	if (deq->size == 1)
	{
		value = oldNode->value;
		deq->front = NULL;
		deq->rear = NULL;
		returnNode(oldNode);
		deq->size--;
		return value;
	}
	else {
		value = oldNode->value;
		deq->front = oldNode->next;
		returnNode(oldNode);
		deq->front->prev = NULL;
		deq->size--;
		return value;
	}
}
void insertRear(deque *deq, int value)
{
	dnode* newNode = getNode();
	newNode->value = value;
	//덱이 EMPTY일 시, front와 rear모두 newNode
	if (isEmpty(deq))
	{
		deq->rear = newNode;
		deq->front = newNode;
		deq->size++;
	}
	else {
		newNode->prev = deq->rear;
		deq->rear->next = newNode;
		deq->rear = newNode;
		deq->size++;
	}

}
int deleteRear(deque *deq)
{
	dnode *oldNode = deq->rear;
	int value;
	//덱이 EMPTY일 시, 프로그램 종료
	if (isEmpty(deq)) { exit(0); }

	//덱의 노드가 1개일 시, rear와 front모두 NULL
	if (deq->size == 1)
	{
		value = oldNode->value;
		deq->rear = NULL;
		deq->front = NULL;
		returnNode(oldNode);
		deq->size--;
		return value;
	}
	else {
		value = oldNode->value;
		deq->rear = oldNode->prev;
		deq->rear->next = NULL;
		returnNode(oldNode);
		deq->size--;
		return value;
	}
}

void INSERTREAR(deque *D, char item)
{
	printf("insertRear <- '%c'\t", item);
	insertRear(D, item);
	printDeque(D);
}

void DELETEREAR(deque *D)
{
	printf("'%c' <- deleteRear\t",
		deleteRear(D));
	printDeque(D);
}

void INSERTFRONT(deque *D, char item)
{
	printf("insertFront <- '%c'\t", item);
	insertFront(D, item);
	printDeque(D);
}

void DELETEFRONT(deque *D)
{
	printf("deleteFront <= '%c'\t",
		deleteFront(D));
	printDeque(D);
}

int main()
{
	deque *D = createDeque();

	printf("createDeque    \t");
	printDeque(D);

	INSERTFRONT(D, 'O');
	INSERTREAR(D, 'V');
	INSERTREAR(D, 'E');
	INSERTFRONT(D, 'L');
	INSERTFRONT(D, ' ');
	INSERTFRONT(D, 'I');
	INSERTREAR(D, ' ');
	INSERTREAR(D, 'U');
	//I LOVE U
	printf("\n\n");

	DELETEFRONT(D);
	DELETEREAR(D);
	INSERTFRONT(D, 'U');
	INSERTREAR(D, 'M');
	INSERTREAR(D, 'E');
	//U LOVE ME
	printf("\n\n");

	DELETEFRONT(D);
	DELETEFRONT(D);
	DELETEREAR(D);
	DELETEREAR(D);
	DELETEREAR(D);
	
	printf("\n\n");
	DELETEFRONT(D);
	DELETEFRONT(D);
	DELETEREAR(D);
	DELETEREAR(D);
	
	return 0;

}