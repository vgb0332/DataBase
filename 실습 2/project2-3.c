/* 실습 2-3 동적메모리
 3과목에 대한 학생들의 성적이 들어
있는 텍스트 파일을 읽어, 개인 별
합계와 평균, 과목별 평균을 새로운
텍스트 파일에 저장하는 C프로그램
을 작성하시오.
 입력 파일(score.txt)의 구조와
출력 파일(report.txt)의 예는
오른쪽 그림과 같다.
 각자 적당한 크기의 입력파일을 만
들어 사용하는데, 학생 수는 10명 이
상으로 한다.
*/

#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

//학생 구조체 정의. 각 학생의 3개의 점수와 그 합과 평균을 저장할 수 있는 변수가 들어있다.
typedef struct STUDENT
{
	int score[3];
	int sum;
	int average;
}STUDENT;

int main()
{
	FILE* fp;
	int nStudent;     //학생수
	int nSubject = 3; //고정 과목수 3
	int i, j;
	int subjectAve[3]; //과목별 평균
	int subjectTot[3];   //과목별 총점
	int chaser = 0;   //score.txt의 실제 입력 된 학생 수 확인 용 변수.
	STUDENT* student; 

	fp = fopen("score.txt", "r"); //score파일 오픈

	if (fp == NULL)
		printf("ERROR!\n");
	else
		printf("   file successfully opened!\n\n");

	fscanf(fp, "%d", &nStudent); //총 학생수 저장

  //score.txt에서 알아낸 학생수만큼 동적할당 *sizeof(studnet) = 20 int형자료 5개!
	student = (STUDENT*)malloc(sizeof(STUDENT)*nStudent);
	
	for (i = 0; i < nStudent; i++)
	{
		if (feof(fp) != 0) //파일이 끝나면 반복문 종료
			break;
		chaser++;          //반복문이 몇 번 돌았나 확인 = 몇 명의 학생 수의 점수가 인식되었는지 확인
		student[i].sum = 0;//총합 초기화
		for (j = 0; j < nSubject; j++)
		{
			fscanf(fp, "%d", &student[i].score[j]);
			student[i].sum += student[i].score[j];
			student[i].average = student[i].sum / nSubject;
		}
	}

	//과목별 총 평균 및 총점 계산
	for (i = 0; i < nSubject; i++)
	{
		subjectTot[i] = 0;
		subjectAve[i] = 0;
		for (j = 0; j < chaser; j++) //실제 입력된 학생 수 만큼 반복
		{
			subjectTot[i] += student[j].score[i];
			subjectAve[i] = subjectTot[i] / nStudent; //실제 입력된 학생 수? 주어진 학생수?
		}
	}
	
	
	//score.txt의 학생수와 실제 입력된 학생점수와 불일치시 출력내용
	if (chaser != nStudent)
	{
		printf("  THE GIVEN NUMBER OF STUDENTS AND THE NUMBER OF SCORES DO NOT MATCH!!  \n\n");
		printf("  REPORT.TXT WILL BE WRITTEN WITH THE CURRENT NUMBER OF SCORES!!  \n\n");
	}

	fp = fopen("report.txt", "wt");

	if (fp == NULL)
		printf("ERROR!\n");

	fprintf(fp, "%d\n", nStudent); //학생수 적고
	
	//score.txt파일에 저장된 값 입력시 chaser만큼의 데이터만 입력하게 만들었다. 그 이후의 자료는 쓰레기
	//값으로 불필요함.
	for (i = 0; i < chaser; i++)
		fprintf(fp, "%d  %d\n", student[i].sum, student[i].average);

	for (i = 0; i < nSubject; i++)
		fprintf(fp, "%d  ", subjectAve[i]);

	//메모리 수거
	free(student);
	
	return 0;
}