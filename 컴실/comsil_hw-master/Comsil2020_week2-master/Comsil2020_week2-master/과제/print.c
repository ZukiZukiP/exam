#include "header.h"

void print(int *arr)
{
	int i;
	for(i=0;i<10;i++){
		printf("%d ",arr[i]);
		arr[i]=0;
	
	}
	printf("\n");


}
