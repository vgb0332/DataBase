#include "stdio.h"
#include "stdlib.h"

#define Q_SIZE 5

typedef struct queue{
	char queue[Q_SIZE];
	int front, rear; 
}Q_TYPE;

void printQ(Q_TYPE *Q)
{
	int i;
	printf("Queue: ");
	for (i = Q->front + 1; i <= Q->rear; i++)
	printf("[%d] %c ",i, Q->queue[i]);
	printf("\n");
}
Q_TYPE *createQueue( )
{
	Q_TYPE *Q;
	Q = (Q_TYPE *)malloc(sizeof(Q_TYPE));
	Q->front = Q->rear = -1;
	return Q;
}
int isEmpty(Q_TYPE *Q)
{
	if (Q->front == Q->rear)
		return 1;
	else
		return 0;
}
int isFull(Q_TYPE *Q)
{
	if (Q->rear == Q_SIZE-1)
		return 1;
	else
		return 0;
} 
void enQueue(Q_TYPE *Q, char item)
{
	if (isFull(Q)) {
		printf("Error: Queue is Full!\n");
		exit(1);
		}
	else {
		Q->rear++;
		Q->queue[Q->rear] = item;
		}
}
char deQueue(Q_TYPE *Q) //DEQUEUE 수정
{
	int i; int deque_Item;
	if (isEmpty(Q)) {
		printf("Error: Queue is Empty!\n");
		exit(1);
		}
	else {
		//삭제할 자료를 저장한 뒤, 배열을 한칸 씩 앞으로 재배열하고 삭제한 자료를 출력
		deque_Item = Q->queue[(Q->front)+1];
		for(i = 1; i < Q->rear+1; i++)
			Q->queue[(Q->front)+i] = Q->queue[(Q->front)+1+i]; 
		Q->rear--;
		return deque_Item;
	}
}


void main()
{
Q_TYPE *Q1 = createQueue();

printf("createQueue \t");
printQ(Q1);
printf("enQueue <- 'A'\t");
enQueue(Q1, 'A'); printQ(Q1);
printf("enQueue <- 'B'\t");
enQueue(Q1, 'B'); printQ(Q1);
printf("enQueue <- 'C'\t");
enQueue(Q1, 'C'); printQ(Q1);
printf("enQueue <- 'D'\t");
enQueue(Q1, 'D'); printQ(Q1);
printf("enQueue <- 'E'\t");
enQueue(Q1, 'E'); printQ(Q1);
printf("enQueue <- 'F'\t");
enQueue(Q1, 'F'); printQ(Q1);
free(Q1);
}
