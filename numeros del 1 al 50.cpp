#include<stdio.h>

int main(){
	
	printf("Numeros del 1 al 50:\n");
	for(int i = 1;i<=50;i++){
		printf("%d",i);
		if(i%10==0){
			printf("\n");
			
		}else{
				printf(" ");
		}
		
		
		
	}
	
	return 0;
}
