#include <stdio.h>

//prototipo funcion
void imprimirBinario(unsigned int num);

int main() {
    unsigned int numero;

    
    printf("Ingrese un numero: "); // pedir numero 
    scanf("%u", &numero);

    printf("El numero en binario es: ");
    imprimirBinario(numero);

    return 0;
}

void imprimirBinario(unsigned int num) {
    
    int tamano = sizeof(num) * 8; // Tamaño del número en bits
    
    
    unsigned int mascara = 1 << (tamano - 1); // mascara para obtener bit significativo
    
    
    int encontrar_bit = 0; // encontrar un bit de valor 1
    
    
    for (int i = 0; i < tamano; i++) {
        
        if (num & mascara) {
            printf("1");
           
            encontrar_bit = 1;
        } else if (encontrar_bit) {
            printf("0");
        }
       
        mascara >>= 1; // corrimiento de la mascara pa la derecha
    }
     //Si el número es 0, imprimir un solo 0
    if (!encontrar_bit) { 
        printf("0");
    }
    printf("\n");
}
