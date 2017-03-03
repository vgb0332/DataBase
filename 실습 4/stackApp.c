#include "myStack.h"
#include "stdio.h"
#include "string.h"
#pragma warning (disable : 4996)
#define MAX_LEN 101

typedef char Expression[MAX_LEN]; //char[MAX_LEN] 형식을 가진 Expression 자료형 선언


//입력: 문자열 str1, 최대 길이 MAX_LEN
//출력: 문자열 str1의 역순 문자열 str2
char *strRev(char *str1, char *str2)
{
	STACK s; 
	int len; 
	int i;
	initStack(&s);
	len = strlen(str1);

	for (i = 0; i < len; i++)
		push(&s, str1[i]);

	for (i = 0; i < len; i++)
		str2[i] = pop(&s);

	str2[i] = '\0'; // "\0"
	return str2;
}

//입력: Expression exp, 최대 길이 MAX_LEN
//출력: Expression exp의 현재 주소 값을 int로 반환
int getSymbol(Expression exp)
{
	return *exp;
}

//입력: Expression exp, 최대 길이 MAX_LEN
//출력: void
void testPair(Expression exp) //입력한 수식어의 괄호 검사
{
	STACK s;
	int symbol;   //현재 괄호 저장 변수
	int exit = 1; //while문 탈출 변수
	int left_sym; //가장 마지막으로 저장된 괄호 시작 기호
	int i = 0;
	initStack(&s);

	while (exit) //exit = 0이면 탈출
	{
		//while문이 다시 호출될 때마다 문자열의 다음 문자를 가르킨다.
		symbol = getSymbol(exp+i++); 
		switch (symbol){
		case '(':
			push(&s, symbol); //스택에 저장
			break;

		case '{':
			push(&s, symbol); //스택에 저장
			break;

		case '[':
			push(&s, symbol); //스택에 저장
			break;

		case ')': 
			if (isEmpty(s) == -1){ //스택이 비어있을 때(시작괄호가 없을때)
				printf("invalid ')'\n");
				exit = 0;
				break;
			}

			else if (isEmpty(s) == 0){ //스택에 정보가 있을때
				left_sym = pop(&s);

				switch (left_sym) { //스택에서 꺼내 괄호가 현재 괄호와 불일치시
				case '{':
					printf("Missing '%c' before ')'\n", (left_sym + 2));
					exit = 0;
					break;

				case '[':
					printf("Missing '%c' before ')'\n", (left_sym + 2));
					exit = 0;
					break;
				}
			}
			break;

		case '}': //스택이 비어있을 때(시작괄호가 없을때)
			if (isEmpty(s) == -1){
				printf("invalid '}'\n");
				exit = 0;
				break;
			}
			else if (isEmpty(s) == 0){ //스택에 정보가 있을때
				left_sym = pop(&s);
				switch (left_sym) { //스택에서 꺼내 괄호가 현재 괄호와 불일치시
				case '(':
					printf("Missing '%c' before '}'\n", (left_sym + 1));
					exit = 0;
					break;

				case '[':
					printf("Missing '%c' before '}'\n", (left_sym + 2));
					exit = 0;
					break;
				}
			}
			break;

		case ']':
			if (isEmpty(s) == -1){ //스택이 비어있을 때(시작괄호가 없을때)
				printf("invalid ']'\n");
				exit = 0;
				break;
			}

			else if (isEmpty(s) == 0){ //스택에 정보가 있을때
				left_sym = pop(&s);
				switch (left_sym) { //스택에서 꺼낸 괄호가 현재 괄호와 불일치시
				case '{':
					printf("Missing '%c' before ']'\n", (left_sym + 2));
					exit = 0;
					break;

				case '(':
					printf("Missing '%c' before ']'\n", (left_sym + 1));
					exit = 0;
					break;
				}
			}
			break;

		case 0: //문자열의 끝에 다달았을때,
			if (isEmpty(s) == -1){ //스택이 비어있으면 Correct
				printf("Correct!\n");
				exit = 0;
				break;
			}

			else if (isEmpty(s) == 0){ //스택에 무언가 있다면 오류 출력
				left_sym = pop(&s);
				switch (left_sym) {
				case '{':
					printf("Missing '%c' \n", (left_sym + 2));
					exit = 0;
					break;

				case '(':
					printf("Missing '%c' \n", (left_sym + 1));
					exit = 0;
					break;

				case '[':
					printf("Missing '%c' \n", (left_sym + 2));
					exit = 0;
					break;
				}
			}
			break;
		}
	}
	
}

int main()
{
	Expression exp;
	while (1) {
		printf("Type in Expression: ");
		scanf("%s", exp);
		testPair(exp);
	}
	return 0;
}