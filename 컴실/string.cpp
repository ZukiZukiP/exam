#include "string.h"
#include <cstring>
#include <iostream>
using namespace std;

// string의 길이를 입력받아 그만한 길이의 공백 문자열을 만듬
Str::Str (int leng) {
	// 예외처리: 길이가 0 미만이면 에러 메시지 출력
	if(leng < 0) {
		cout << "string length error\n";
		len = 0;
	}
	str = new char[leng+1];//새롭게 하나 만듬
	for(int i = 0; i <= leng; i++) { // 초기화
		str[i] = ' ';
	}
	str[leng] = '\0';
	len = leng; //길이 저장
}

// string의 내용을 입력받아 그대로 초기화함
Str::Str (char * neyong) {
	// 예외처리: 입력받은 char *가 NULL을 가리킴
	if(neyong == NULL) {
		cout << "char pointer error\n";;
		str = new char[1];//초기화
		str[0] = '\0';
		len = 0;
	}
	else {//len 새롭게 만들어서 내용 저장
		len = strlen(neyong);
		str = new char[len+1];
		strcpy(str, neyong);
	}
}

// 소멸자
Str::~Str () {
	delete[] str;
}

// string의 길이를 리턴하는 함수
int Str::length (void) {
	return len;
}

// string의 내용을 리턴하는 함수
char * Str::contents (void) {
	return str;
}

// string의 내용을 다른 string이랑  비교하는 함수
int Str::compare (class Str& a) {
	return strcmp(str, a.contents());//strcmp 보고서에 설명
}

int Str::compare(char *a) {
	return strcmp(str, a);
}

// 입력받은 a의 내용을 복사해오는 함수
void Str::operator=(char * a) {
	// 예외처리
	delete[] str;
	if(a == NULL) {
		len = 0;
		str = new char[0];
		str[0] = '\0';
	}
	else {//a의 길이 받은뒤, 길이 받은 만큼 스트링 배열 다시 만들어서 strcpy해줌
		len = strlen(a);
		str = new char[len+1];
		strcpy(str, a);
	}
}

void Str::operator=(class Str& a) { 
	delete[] str;
	len = a.length();
	str = new char[len+1];
	strcpy(str, a.contents());
}
