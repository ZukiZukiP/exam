#include "header.h"

int main(){
	int tc;
	long long int t;
	long long int arr[10];
	scanf("%d",tc);
for(int i=0;i<tc;i++){
	scanf("%lld",&t);
	count(t,arr);
	print(t);
}
return 0;
}
