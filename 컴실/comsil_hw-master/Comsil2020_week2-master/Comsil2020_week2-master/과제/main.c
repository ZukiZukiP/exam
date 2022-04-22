#include "header.h"

int main(void)
{
	int test_case;

	int *arr;
	printf("Enter your test case number : ");
	scanf("%d",&test_case);

	arr=(int*)malloc(test_case*sizeof(int));

	for(int i=0;i<test_case;i++){
		scanf("%d",&arr[i]);
		//각각의 case에 해당하는 조건을 불러오면 
		count(arr[i]);
	}

	return 0;

}
