#include <stdio.h>

int main() {
    int opcion;
    
    do {
    	
        // Mostrar el men�
        printf("\n=== Menu ===\n");
        printf("1. Opcion 1\n");
        printf("2. Opcion 2\n");
        printf("3. Opcion 3\n");
        printf("4. Salir\n");
        printf("============\n");
        printf("Seleccione una opcion: ");
        
        // Leer la opci�n del usuario
        scanf("%i", &opcion);
        
        // Manejar la opci�n seleccionada
        switch(opcion) {
            case 1:
                printf("Ha seleccionado la Opcion 1.\n");
                break;
            case 2:
                printf("Ha seleccionado la Opcion 2.\n");
                break;
            case 3:
                printf("Ha seleccionado la Opcion 3.\n");
                break;
            case 4:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion no v�lida. Por favor, seleccione una opci�n valida.\n");
        }
    } while(opcion != 4); // Continuar mostrando el men� hasta que se seleccione la opci�n de salir
    
    return 0;
}

