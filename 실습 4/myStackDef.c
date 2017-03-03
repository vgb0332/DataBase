
#ifndef MY_STACK_H
#define MY_STACK_H
#include "myStack.h"
#include "stdio.h"

void initStack(STACK *s)
{
	s->top = -1;
}
// 스택 full 확인
// 리턴값: -1 = 스택 full, 0 = 스택 full 아님
int  isFull(STACK s)
{
	if (s.top == MY_STACK_SIZE - 1)
		return -1;
	else
		return 0;
}

// 스택 empty 확인
// 리턴값: -1 = 스택 empty, 0 = 스택 empty 아님
int  isEmpty(STACK s)
{
	if (s.top == -1)
		return -1;
	else
		return 0;
}

// 스택 push 함수 - value를 스택에 push
// overflow 발새시 "*** myStack overflow error" 출력
void push(STACK *s, int value)
{
	s->stack[++(s->top)] = value; 
	if (isFull(*s) == -1)
		printf("*** myStack overflow error ***\n");
}

// 스택 pop 함수 - 스택에서 데이터 추출
// 리턴값: 스택에서 꺼낸 데이터
// empty오류 발생시 "*** myStack empty error" 출력
int pop(STACK *s)
{
	if (isEmpty(*s) == -1)
		printf("*** myStack empty error ***\n");
	else
		return s->stack[s->top--];
}

#endif;