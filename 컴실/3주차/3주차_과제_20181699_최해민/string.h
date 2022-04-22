#ifndef STR
#define STR

class Str {
private:
	char *str; 	// string의 내용
	int len; 	// stirng의 길이

public:
	Str(int leng); // leng은string의 길이
	Str(char *neyong); // neyong은 초기화할 내용이 들어감 
	~Str(); // 소멸자
	int length(void); // string의 길이를 리턴하는 함수
	char *contents(void); // string의 내용을 리턴하는 함수
	int compare(class Str& a); // 입력받은 Str의 내용과 strcmp
	int compare(char *a); // 입력받은 string의 내용과 strcmp
	void operator=(char *a); // string의 값을 대입
	void operator=(class Str& a); // Str의 내용을 대입
};

#endif
