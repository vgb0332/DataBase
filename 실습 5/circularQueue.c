#include <stdio.h>
#include <stdlib.h>
#define Q_SIZE 5
typedef struct {
char queue[Q_SIZE];
int front, rear;
} Q_TYPE;
void printQ(Q_TYPE *Q) //수정
{
	int i;
	printf("Queue: ");
	//배열을 콘솔에 출력 시, front+1부터 rear까지 자료 출력
	for (i = Q->front+1; i != (Q->rear+1)%Q_SIZE; i=(i+1)%Q_SIZE)
		printf("[%d] %c ",i, Q->queue[i]);
	printf("\n");
}

Q_TYPE *createQueue( ) //수정
{
	Q_TYPE *Q;
	Q = (Q_TYPE *)malloc(sizeof(Q_TYPE));
	//수정함 front = rear = 0
	Q->front = Q->rear = 0;
	return Q;
}
int isEmpty(Q_TYPE *Q)
{
	if (Q->front == Q->rear)
		return 1;
	else
		return 0;
}
int isFull(Q_TYPE *Q) //수정
{
	//자료의 끝이 Front을 가리키면 FULL
	if ((Q->rear+1) % Q_SIZE == Q->front)
		return 1;
	else
		return 0;
} 

void enQueue(Q_TYPE *Q, char item) //수정
{
	if (isFull(Q)) {
		printf("Error: Queue is Full!\n");
		exit(1);
		}
	else {
		//rear을 통하여 자료 입력, mod를 통하여 한칸 씩 추가
		Q->rear = (Q->rear+1) % Q_SIZE;
		Q->queue[Q->rear] = item;
		}	
}
char deQueue(Q_TYPE *Q) //수정
{
	if (isEmpty(Q)) {
		printf("Error: Queue is Empty!\n");
		exit(1);
		}
	else {
		//자료 삭제 시, front+1 이 가르키는 자료 출력
		Q->front = (Q->front+1) % Q_SIZE;
		return Q->queue[Q->front];
	}
}

void main(void)
{
Q_TYPE *Q1 = createQueue();
printf("createQueue \t");

printf("enQueue <- 'A'\t");
enQueue(Q1, 'A'); printQ(Q1);
printQ(Q1);
printf("enQueue <- 'B'\t");
enQueue(Q1, 'B'); printQ(Q1);
printQ(Q1);
printf("enQueue <- 'C'\t");
enQueue(Q1, 'C'); printQ(Q1);
printQ(Q1);
printf("enQueue <- 'D'\t");
enQueue(Q1, 'D'); printQ(Q1);
printQ(Q1);
printf("enQueue <- 'F'\t");
enQueue(Q1, 'F'); printQ(Q1);
printQ(Q1);
printf("enQueue <- 'E'\t");
enQueue(Q1, 'E'); printQ(Q1);
printQ(Q1);

/*
printf("enQueue <- 'A'\t");
enQueue(Q1, 'A'); printQ(Q1);
printf("enQueue <- 'B'\t");
enQueue(Q1, 'B'); printQ(Q1);
printf("enQueue <- 'C'\t");
enQueue(Q1, 'C'); printQ(Q1);
printf("'%c' <- deQueue\t",
deQueue(Q1)); printQ(Q1);
printf("'%c' <- deQueue\t",
deQueue(Q1)); printQ(Q1);
printf("enQueue <- 'D'\t");
enQueue(Q1, 'D'); printQ(Q1);
printf("enQueue <- 'E'\t");
enQueue(Q1, 'E'); printQ(Q1);
printf("'%c' <- deQueue\t",
deQueue(Q1)); printQ(Q1);
printf("enQueue <- 'F'\t");
enQueue(Q1, 'F'); printQ(Q1);
*/
free(Q1);
}