#include "header.h"

int main(){
	int tc;//테스트케이스 갯수
	long long int t;//테스트할 수
	long long int arr[10];//자릿수의 수
	scanf("%d",&tc);
for(int i=0;i<tc;i++){
	scanf("%lld",&t);//테스트할수받는다
	for(int i=0; i<10; i++) arr[i]=0;//초기화
	count(t,arr);//자릿수센다
	print(arr);//프린트한다
}
return 0;
}
