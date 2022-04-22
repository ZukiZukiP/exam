#include "header.h"

void count(int n)
{
	//하나의  숫자에 대한 처리

	int temp;
	int i=0;
	int arr[10]={0};

	for(i=0;i<n;i++){
		temp=i+1;
		while(temp!=0){
			arr[temp%10]++;
			temp=temp/10;
		}


	}

	print(arr);
}
