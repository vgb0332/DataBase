#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int nCompare = 0;
int nMove = 0;

void makeRandomData(int *a, int n)
{
	int i;

	srand(time(NULL));
	for (i = 0; i < n; i++)
		a[i] = rand() % 1000;
}

void printData(char *title, int *a, int n)
{
	int i;

	printf("%s = {\n%3d", title, a[0]);
	for (i = 1; i < n; i++)
		printf(", %3d", a[i]);
	printf("\n}\n");
}

void swap(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
	nMove += 3; // 데이터 이동 카운터 증가
}
void selectionSort(int *a, int n) {
	int i, j;
	int min;

	for (i = 0; i < n - 1; i++) {
		min = i;
		for (j = i; j < n; j++) {
			nCompare++; //데이터 비교 카운터 증가
			if (a[j] < a[min])
				min = j;
		}
		swap(&a[i], &a[min]);
	}
}
void bubbleSort(int *a, int n) {
	int i, j;
	for (i = n - 1; i >= 0; i--)
	{
		for (j = 0; j < i; j++) {
			nCompare++; // 데이터 비교 카운터 증가
			if (a[j] > a[j + 1])
				swap(&a[j], &a[j + 1]);
		}
	}
}
int partition(int *a, int begin, int end)
{
	int p = begin;
	int L = begin;
	int R = end;
	while (L < R)
	{
		while (a[L] <= a[p] && L < end){
			nCompare++; // 데이터 비교 카운터 증가 
			L++;}
		while (a[R] > a[p]) { 
			nCompare++; // 데이터 비교 카운터 증가 
			R--;}
		if (L < R) {
			nCompare++; // 데이터 비교 카운터 증가
			swap(&a[L], &a[R]);
		}
	}
	swap(&a[p], &a[R]);
	return R;
}
void qSort(int *a, int begin, int end)
{
	int pivot;
	if (begin < end)
	{
		nCompare++; // 데이터 비교 카운터 증가
		pivot = partition(a, begin, end);
		qSort(a, begin, pivot - 1);
		qSort(a, pivot + 1, end);
	}
}
void quickSort(int *a, int n) {
	qSort(a, 0, n - 1);
}
void insertionSort(int *a, int n) {
	int i;
	int val;
	int pos;
	for (i = 1; i <n; i++)
	{
		val = a[i];
		for (pos = i; pos > 0; pos--) {
			nCompare++; // 데이터 비교 카운터 증가
			if (val < a[pos - 1]) {
				a[pos] = a[pos - 1];
				nMove++;
			}
			else
				break;
		}
		a[pos] = val;
		nMove++; // 데이터 이동 카운터 증가
	}
}
void shellSort(int *a, int n) {
	int interval;
	int i, pos, val;

	for (interval = n / 2; interval > 0; interval = interval / 2)
	{
		for (i = interval; i < n; i++)
		{
			val = a[i];
			for (pos = i; pos >= interval; pos -= interval)
			{
				nCompare++; // 데이터 비교 카운터 증가
				if (val < a[pos - interval]) {
					a[pos] = a[pos - interval];
					nMove++; // 데이터 이동 카운터 증가
				}
				else
					break;
			}
			a[pos] = val;
			nMove++; // 데이터 이동 카운터 증가
		}
	}
}

void printSort(int n) //n: 1~5까지 1.선택, 2.버블, 3.퀵, 4.삽입, 5.쉘 정렬
{
	switch (n) {
	case 1:
		printf("\t\tSelction Sort\t\t\n");
		break;
	case 2:
		printf("\t\tBubble Sort\t\t\n");
		break;
	case 3:
		printf("\t\tQuick Sort\t\t\n");
		break;
	case 4:
		printf("\t\tInserton Sort\t\t\n");
		break;
	case 5:
		printf("\t\tShell Sort\t\t\n");
		break;
	}
} 

void Sort(int n, int* work, int size) { //n: 1~5까지 1.선택, 2.버블, 3.퀵, 4.삽입, 5.쉘 정렬

	switch (n) {
	case 1:
		selectionSort(work, size);
		break;
	case 2:
		bubbleSort(work, size);
		break;
	case 3:
		quickSort(work, size);
		break;
	case 4:
		insertionSort(work, size);
		break;
	case 5:
		shellSort(work, size);
		break;
	}
}
void checkFunction()
{
	int *data, *work;
	int size = 100;
	int i;

	for (i = 1; i <= 5; i++) //i: 1~5까지 1.선택, 2.버블, 3.퀵, 4.삽입, 5.쉘 정렬
	{
		printf(" -------------------------------------------\n");
		printSort(i);
		printf("  size \t compare     move \tcomp+move\n");
		printf(" ------\t---------- ----------\t----------\n");

		while (size <= 1000) {
			//size 100 ~ 1000, nCompare, nMove, nCompare+nMove 출력
			data = (int*)malloc(size*sizeof(int));
			work = (int*)malloc(size*sizeof(int));
			makeRandomData(data, size);
			memcpy(work, data, size*sizeof(data));
			Sort(i, work, size);
			printf(" %5d\t%10d  %10d \t%10d\n", size, nCompare, nMove, nCompare + nMove);

			//증진 및 초기화
			size += 100;
			nCompare = 0;
			nMove = 0;
			free(work);
			free(data);
		}
		printf(" -------------------------------------------\n");
		printf("\n\n");
		size = 100;
	}
	
	
}

int main(int argc, char* argv[])
{
#define SIZE 15
	checkFunction();
	/*
	int data[SIZE], work[SIZE];

	makeRandomData(data, SIZE);
	printData("Unsorted Data", data, SIZE);

	memcpy(work, data, sizeof(data));
	selectionSort(work, SIZE);
	printData("Selection Sort", work, SIZE);

	memcpy(work, data, sizeof(data));
	bubbleSort(work, SIZE);
	printData("Bubble Sort", work, SIZE);

	memcpy(work, data, sizeof(data));
	quickSort(work, SIZE);
	printData("Quick Sort", work, SIZE);

	memcpy(work, data, sizeof(data));
	insertionSort(work, SIZE);
	printData("Insertion Sort", work, SIZE);

	memcpy(work, data, sizeof(data));
	shellSort(work, SIZE);
	printData("Shell Sort", work, SIZE);

	getchar();
	*/
	return 0;
}