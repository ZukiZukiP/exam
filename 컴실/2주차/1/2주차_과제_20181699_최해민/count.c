#include "header.h"
void count(long long int t,long long int *arr){//�� �׽�Ʈ ���̽����� �ڸ��� ��}

	long long int temp=0;
	for(long long int i=1;i<=t;i++){
	temp=i;//1����k������ ������ temp�� ��
	while(temp!=0)
	{
		arr[temp%10]++;//1���ڸ����� �ڸ��� ����
			
		temp=temp/10;//�ڸ����ϳ������� �״��� �ڸ��� ����
		
	}
	}




}
