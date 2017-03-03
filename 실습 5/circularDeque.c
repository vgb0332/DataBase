#include <stdio.h>
#include <stdlib.h>
#define Q_SIZE 5

typedef struct {
	char deque[Q_SIZE];
	int front, rear;
} Q_TYPE;

Q_TYPE *initDeque() //구조체를 할당 초기화하고, front와 rear모두 -1
{
	Q_TYPE *Q;
	Q = (Q_TYPE *)malloc(sizeof(Q_TYPE));
	Q->front = Q->rear = -1;
	return Q;
}
int isEmpty(Q_TYPE *Q) //front와 rear가 -1일 때 EMPTY
{
	if (Q->front && Q->rear == -1)
		return 1;
	else
		return 0;
}
int isFull(Q_TYPE *Q) //rear의 다음 배열이 front일 때 FULL
{
	//수정함
	if ((Q->rear + 1) % Q_SIZE == Q->front)
		return 1;
	else
		return 0;
}
void insertFront(Q_TYPE *Q, char item) //배열의 front방향으로 item 추가
{
	if (isFull(Q)) {
		printf("Deque is Full\n");
		exit(1);
	}
	else if (isEmpty(Q)) //배열이 EMPTY일 때, 배열[0]에 item 저장 후, front와 rear모두 0을 가리킨다.
	{
		Q->front = Q->rear = 0;
		Q->deque[Q->front] = item;
	}
	else
	{
		Q->front = ((Q->front) + Q_SIZE - 1) % Q_SIZE;
		Q->deque[Q->front] = item;
	}
} 
void insertRear(Q_TYPE *Q, char item) //배열의 rear방향으로 item 추가
{
	if (isFull(Q)) {
		printf("Deque is Full\n");
		exit(1);
	}
	else if (isEmpty(Q)) //배열이 EMPTY일 때, 배열[0]에 item 저장 후, front와 rear모두 0을 가리킨다.
	{
		Q->front = Q->rear = 0;
		Q->deque[Q->rear] = item;
		
	}
	else
	{
		Q->rear = (Q->rear + 1) % Q_SIZE;
		Q->deque[Q->rear] = item;
	}
}
char deleteFront(Q_TYPE *Q) //front의 자료 반환 후 삭제
{
	char temp;
	if (isEmpty(Q)) {
		printf("Error: Queue is Empty!\n");
		exit(1);
	}

	else if (Q->front == Q->rear) //배열에 저장된 자료가 1개일 때 자료 반환 후 EMPTY state
	{
		temp = Q->front;
		Q->front = Q->rear = -1;
		return temp;
	}
	
	else 
	{
		temp = Q->front;
		Q->front = (Q->front + 1) % Q_SIZE;
		return temp;
	}
}
char deleteRear(Q_TYPE *Q) //rear의 자료 반환 후 삭제
{
	char temp;
	if (isEmpty(Q)) 
	{
		printf("Error: Queue is Empty!\n");
		exit(1);
	}

	else if (Q->rear == Q->front) //배열에 저장된 자료가 1개일 때 자료 반환 후 EMPTY state
	{
		temp = Q->rear;
		Q->rear = Q->front = -1;
		return temp;
	}

	else 
	{
		temp = Q->rear;
		Q->rear = (Q->rear - 1) % Q_SIZE;
		return temp;
	}
}
void printQ(Q_TYPE *Q)
{
	int i, temp;
	printf("Deque: ");
	if (isEmpty(Q))
		printf("Deque Empty");
	else if (isFull(Q)) //배열이 FULL일 시, 모든 자료 출력
	{
		temp = 0;
		for (i = Q->front; temp != Q_SIZE; temp++){
			printf("[%d] %c ", (i) % Q_SIZE, Q->deque[(i) % Q_SIZE]);
			i++;
		}
	}
	else //배열이 FULL이 아닐 시, 저장된 자료만 출력
	{
		for (i = Q->front; i != (Q->rear + 1) % Q_SIZE; i = (i + 1) % Q_SIZE)
			printf("[%d] %c ", i, Q->deque[i]);

	}
	printf("\n");
}

void main(void)
{
	Q_TYPE *Q1 = initDeque();
	printf("createDeque \t"); printQ(Q1);
	printf("insertRear <- 'A' \t");
	insertRear(Q1, 'A');     printQ(Q1);
	printf("insertRear <- 'B' \t");
	insertRear(Q1, 'B');     printQ(Q1);
	printf("insertRear <- 'C' \t");
	insertRear(Q1, 'C');     printQ(Q1);
	printf("insertRear <- 'D' \t");
	insertRear(Q1, 'D');     printQ(Q1);
	printf("insertRear <- 'E' \t");
	insertRear(Q1, 'E');     printQ(Q1);
	printf("insertRear <- 'F' \t");
	insertRear(Q1, 'F');     printQ(Q1);
	
	/*
	printf("deleteFront \t\t");
	deleteFront(Q1);
	printQ(Q1);
	printf("deleteRear \t\t");
	deleteRear(Q1);
	printQ(Q1);
	printf("deleteRear \t\t");
	deleteRear(Q1);
	printQ(Q1);
	printf("insertFront <- 'F' \t");
	insertFront(Q1, 'F');
	printQ(Q1);
	printf("insertFront <- 'E' \t");
	insertFront(Q1, 'E');
	printQ(Q1);
	printf("insertFront <- 'H' \t");
	insertFront(Q1, 'H');
	printQ(Q1);
	*/
	free(Q1);
}