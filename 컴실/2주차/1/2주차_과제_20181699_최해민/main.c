#include "header.h"

int main(){
	int tc;//�׽�Ʈ���̽� ����
	long long int t;//�׽�Ʈ�� ��
	long long int arr[10];//�ڸ����� ��
	scanf("%d",&tc);
for(int i=0;i<tc;i++){
	scanf("%lld",&t);//�׽�Ʈ�Ҽ��޴´�
	for(int i=0; i<10; i++) arr[i]=0;//�ʱ�ȭ
	count(t,arr);//�ڸ�������
	print(arr);//����Ʈ�Ѵ�
}
return 0;
}
