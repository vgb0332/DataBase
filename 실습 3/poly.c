/* 
이 름 : 다항식 (Polynomial)

데이터 : 지수 ei 와 계수 ai 의 순서쌍 <ei , ai>의 집합으로 표현된 다항식 (ei는 음이 아닌 정수)

연 산 :
zeroPoly(p) // 다항식 p를 0으로 초기화
isZeroPoly(p) // 다항식 p가 0이면 true, 0이 아니면 false
getCoef(p, e) // 지수 e인 계수 a를 반환, 지수 e가 없는 경우 0을 반환
getMaxExp(p) // 다항식 p에서 가장 큰 지수를 반환, p가 0인 경우 -1 반환
addTerm(p, a, e) // 지수 e항이 있는 경우 계수에 a를 더하고, 없는 경우 새로운 항<e, a> 추가
delTerm(p, e) // 지수가 e항을 삭제
addPoly(p1, p2) // 두 다항식 p1과 p2의 합을 반환
multPoly(p1, p2) // 두 다항식 p1과 p2의 곱을 반환

*/

#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable: 4996)
#define maxTerm 100

/* Boolean 자료형이 헤더파일이 없다는 오류에 직접 만들엇다.*/
#define true 1    
#define false 0
typedef int bool;

/*다항식의 지수가 maxTerm(100)이 한계인 정수형 배열 자료형 선언*/
typedef int POLY[maxTerm];

void zeroPoly(POLY p) //다항식을 0으로 초기화
{
	int exp;
	for (exp = 0; exp < maxTerm; exp++)
		p[exp] = 0;
} 
bool isZeroPoly(POLY p) // 다항식 p가 0이면 true, 0이 아니면 false
{
	int i;
	for (i = 0; i < maxTerm; i++)
	{
		if (p[i] != 0)
			return false;
	}
	return true;
}
int getCoef(POLY p, int exp) // 지수 e인 계수 a를 반환, 지수 e가 없는 경우 0을 반환
{
	return p[exp];
	if (exp > 100 || exp < 0)
		return 0;
}
int getMaxExp(POLY p) // 다항식 p에서 가장 큰 지수를 반환, p가 0인 경우 -1 반환
{
	int exp;
	for (exp = maxTerm-1; exp >= 0; exp--)
	{
		if (p[exp] != 0)
			return exp;
	}
	return -1;
}
void addTerm(POLY p, int coef, int exp) //다항식 p에 계수 coef, 지수가 exp인 항 추가
{
	p[exp] += coef;
}
void delTerm(POLY p, int exp) //다항식 p에 지수가 exp인 항 삭제
{
	p[exp] = 0;
}
void addPoly(POLY pC, POLY pA, POLY pB) //두 개의 다항식을 더함
{
	zeroPoly(pC); //더한값을 저장할 POLY 다항식 추가 및 초기화
	int exp;

	/* pCopy addPoly에 의해 삭제되는 pB 다항식을 미리 복사해 놓기 위한 복사본이다*/
	POLY pCopy;
	zeroPoly(pCopy);
	
	for (exp = 0; exp < maxTerm; exp++)
		addTerm(pCopy, pB[exp], exp);

	//다항식을 더하기 전, pC 다항시에 pA다항식 삽입
	for (exp = 0; exp < maxTerm; exp++)
		addTerm(pC, pA[exp], exp);

	/* pB의 최고차항 부터 1개씩 더한다*/
	while (!isZeroPoly(pB))
	{
		exp = getMaxExp(pB);
		addTerm(pC, pB[exp], exp);
		delTerm(pB, exp);
	}

	/*위의 더하기 과정 중 없어진 pB다항식을 다시 복원한다*/
	for (exp = 0; exp < maxTerm; exp++)
		addTerm(pB, pCopy[exp], exp);
}
void multPoly(POLY pD, POLY pA, POLY pB)
{
	zeroPoly(pD);
	int exp, i;

	//addPoly와 마친가지로 복사본 추가
	POLY pCopy;
	zeroPoly(pCopy);

	for (exp = 0; exp < maxTerm; exp++)
		addTerm(pCopy, pA[exp], exp);

	while (!isZeroPoly(pA)) //pA의 최고차항부터 최소차항까지 차례대로 연산실행
	{
		exp = getMaxExp(pA);
		for (i = 0; i < maxTerm; i++)
		{
			addTerm(pD, pA[exp] * pB[i], exp + i);
		}
		delTerm(pA, exp);
	}

	//없어진 pA 다항식 복원
	for (exp = 0; exp < maxTerm; exp++)
		addTerm(pA, pCopy[exp], exp);
}
void inputPoly(POLY p)
{
	int i, terms, exp, coef;
	zeroPoly(p);
	printf("Enter # of terms: ");
	scanf("%d", &terms);

	printf("Enter terms <coef,exp>*  :");

	for (i = 0; i < terms; i++)
	{
		scanf("%d %d", &coef, &exp);
		addTerm(p, coef, exp);
	}
}
void printPoly(POLY p)
{
	int coef, exp;

	for (exp = maxTerm - 1; exp >= 0; exp--)
	{
		coef = p[exp];
		
		if (coef > 0)
			printf("+%dx^%d ", coef, exp);
		else if (coef < 0)
			printf("%dx^%d ", coef, exp);
		else if (exp == 0 && p[exp] > 0)
			printf("+%dx^%d ", coef, exp);
		else if (exp == 0 && p[exp < 0])
			printf("%dx^%d ", coef, exp);
	}
	
}

int main(int argc, char* argv[])
{
	POLY polyA, polyB, polyC, polyD;
	
	inputPoly(polyA);
	printf("\n");
	inputPoly(polyB);
	
	printf("\n");
	printf("A(x) = ");
	printPoly(polyA);
	printf("\n");
	printf("B(x) = ");
	printPoly(polyB);
	printf("\n\n");

	//A + B
	printf("A + B = ");
	addPoly(polyC, polyA, polyB);
	printPoly(polyC);
	printf("\n");
	
	//A * B
	multPoly(polyD, polyA, polyB);
	printf("A * B = ");
	printPoly(polyD);
	printf("\n");
	return  0;
}