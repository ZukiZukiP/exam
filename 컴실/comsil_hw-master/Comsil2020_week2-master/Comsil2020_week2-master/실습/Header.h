#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#define BNUM 256		//한줄을 읽을 입력 버퍼의 크기
#define LIMIT 72		//출력 줄의 글자 수 제한(프로그램 작성시 작게 설정하여 테스트)

void Remove_Blanks_At_The_End( char *line );
void Print_Line( char *line, int *Count, int *B_Flag );
void Get_Blanks_Chars( char *line, int Start, int *N_Blanks, int *N_Chars );
