#include<stdio.h>

int main(){
	
	float nota_alumno = 0;
	
	printf("Ingrese la nota obtenida :");
	scanf("%f",&nota_alumno);
	
	if(nota_alumno > 10.5){
		
		printf("Aprobado");
		
		
	}else{
	printf("Reprobado");	
	}
	
	
	
	return 0;
}
