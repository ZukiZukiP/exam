#include "header.h"
void count(long long int t,long long int *arr){//각 테스트 케이스마다 자리수 셈}

	long long int temp=0;
	for(long long int i=1;i<=t;i++){
	temp=i;//1부터k까지의 모든수가 temp로 들어감
	while(temp!=0)
	{
		arr[temp%10]++;//1의자리부터 자릿수 센다
			
		temp=temp/10;//자릿수하나셌으면 그다음 자릿수 센다
		
	}
	}




}
