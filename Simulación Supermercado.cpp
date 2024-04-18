/* Universidad de La Frontera
* 
* IIE344-1: ESTRUCTURA DE DATOS Y ALGORITMOS
*
* Tarea 1 
*
* Autores: Nicolás Oyarzo Rubilar   n.oyarzo02@ufromail.cl
*          Jorge Guaiquil Vidal     j.guaiquil01@ufromail.cl 
*
* Fecha: 08 de Diciembre, 2020
*
* Descripción general del programa: ( LEER ANTES DE EJECUTAR ) 

Este programa simula el funcionamiento de una plataforma administrador-cliente.
Está realizado con archivos y funciones ( recursivas ) en su mayoria.

FUNCIONES ADMINISTRADOR:
1)Registrar nuevo administrador ( con un nombre de usuario y contraseña alfanúmerica ( ejemplo hola123)

2)admin es una estructura, por lo tanto se pueden añadir-modificar-eliminar y visualizar los administradores existentes.
el limite de administradores es variado, ya que se almacenan en un archivo (.dat y txt )

3)Al iniciar sesión, el administrador puede añadir,modificar,eliminar,buscar y listar los productos.
los productos contienen: código,nombre del producto,cantidad y precio ( variable flotante, acepta valores decimales ejemplo 29,99 ) 

FUNCIONES CLIENTE:
1)Puede ver que productos están disponibles para comprar. ( misma función listar_producto usada en el administrador, solo que modificada )

2)Al comprar productos, el cliente puede decidir cuantas unidades desea comprar. ( existe un limite de stock, el cliente no puede comprar cuando ya no hay stock ) 

3)Puede acceder a un carro de compras, para ver que lleva comprado hasta el momento. ( se crea un archivo de texto con los productos, además de almacenarlos en el sistema ( .dat)

4)finalizar compra vacía el carro de compras y los datos del sistema. ( fflush ) 

DATO EXTRA PARA MANEJO DE ARCHIVOS 
Para actualizar los archivos de textos generados:

Archivo de texto Administrador-> ingresar como admin -> Visualizar administradores existentes -> Guardar reporte 
Archivo de texto productos(Bodega) -> ingresar como admin -> iniciar sesion -> listar productos -> Guardar reporte
Archivo de texto carrito de compras(Boleta) -> ingresar como cliente -> ver carrito de compras -> Guardar reporte
*/

             //     LIBRERIAS UTILIZADAS      //
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <locale.h> // palabras con tilde 

            //             MACROS            //
#define MAX 20
#define CONTADOR -1

           //          ESTRUCTURAS          //

//Estructura que almacena la información de un producto
struct producto {
    int codigo; // codigo de barras del producto 
    char nombre[MAX]; // nombre del producto 
    float precio; // valor del producto $
    int cantidad; // stock del producto 
    int unidades; // variable para el cliente ( cantidad que va a comprar ) 
}; 

typedef struct producto Producto; // variable para manejar la estructura 

//Estructura de administrador 

struct admin{
	
	int numero; // admin 1, admin 2, etc
	char nAdmin[MAX]; // nombre del administrador
	char clave[MAX]; // clave del admin 
};

typedef struct admin Admin; // variable para manejar la estructura

              //  VARIABLES GLOBALES          //
              
// Variables del menu ( switch ) 
int opcion_usuario;
char temp[10];              
 
// Variable para lectura de cadenas 
char linea[MAX];
             
			 // PROTOTIPO DE FUNCIONES        //


//FUNCIONES ADMINISTRADOR
void opciones_admin();  // contiene un switch para llevar al admin a registrarse o iniciar sesión  			 
void registrarse(); // función para registrar un nuevo administrador 
void inicio_sesion(); // comparación de cadenas 			 
void modificar_admin(); // modifica los datos del administrador
void eliminar_admin(); // elimina un administrador existente
void visualizar_admins(); // muestra por pantalla todos los administradores existentes

//FUNCIONES PARA MANEJAR EL ARCHIVO ADMINISTRADOR
char existeAdmin(int numeroAdmin, Admin *admin); // verifica si existe el admin en el sistema 
char insertarAdmin(Admin admin); // agrega los datos del administrador al sistema 
char eliminarAdmin(int numeroAdmin); // elimina un administrador especifico 
char modificarAdmin(Admin admin); // modifica los datos del administrador 
Admin *obtenerAdmins(int *n); // Obtiene la cantidad de administradores en el sistema
char guardarAdmins(); // Genera un archivo de texto con el reporte de los administradores
char existeNombre(char const *ingresoAdmin, Admin *admin); // verifica que el nombre de usuario exista
char existeClave(char const *ingresoClave, Admin *admin); // verifica que la contraseña exista


//FUNCIONES PARA PRODUCTOS
void agregar_producto(); // funcion para agregar un producto 
void modificar_producto(); // funcion para modificar un producto ( codigo-nombre-cantidad-precio)
void eliminar_producto(); // funcion que elimina un producto 
void listar_producto(); // muestra por pantalla la lista de productos almacenados 
void buscar_producto(); // busca por codigo un producto en especifico


// FUNCIONES PARA MANEJAR EL ARCHIVO PRODUCTOS
Producto *obtenerProductos(int *n); // Obtiene un vector dinámico de productos 
char existeProducto(int codigoProducto, Producto *producto); // Busca si existe el producto en el archivo de productos 
char insertarProducto(Producto producto); // Inserta el producto al final del archivo 
char eliminarProducto(int codigoProducto); // Elimina el producto con el codigo del producto 
char modificarProducto(Producto producto); // Modifica el producto en el archivo 
char guardarReporte(); // Genera un archivo de texto con el reporte de los productos 


//FUNCIONES CLIENTE
void opciones_cliente(); // contiene un switch para llevar al cliente a ver el stock disponible o comprar.
void listar_producto_cliente(); // misma funcion que listar_producto, solo que esta funcion solo muestra la lista por pantalla ( no crea archivo de texto )
void comprar_producto(); // funcion para que el cliente pueda comprar productos de la lista ( incluye boleta ) 
void mostrar_boleta_cliente(); // muestra el carro de compras del cliente
void finalizar_compra(); // vacía el archivo txt y el sistema .dat

//FUNCIONES PARA MANEJAR EL ARCHIVO CLIENTES
char compra_cliente(Producto producto); // agrega los productos que va a comprar el cliente a un archivo 2
Producto *obtener_compras(int *n); // Obtiene un vector dinámico de productos ( archivo 2 )  
char boleta_cliente(); // genera un archivo de texto de la boleta ( detalle de compra ) 


//FUNCIONES DE MENÚ
void menu_bienvenida(); // mensaje de bienvenida al usuario 
void menu_admin(); // pregunta al admin si desea registrarse o iniciar sesion 
void menu_cliente(); // imprime por pantalla las opciones de ver listado-comprar
void menu_listado_admin(); // contiene las opciones que posee el admin, es decir, añadir-modificar-eliminar-listar-buscar productos.
void titulo(); // funcion que contiene el encabezado del programa 


//FUNCIÓN DE AYUDA PARA MANEJAR CADENAS 
int leecad(char *cad, int n);


                    //   PROGRAMA PRINCIPAL   //
int main(){
	
	setlocale(LC_ALL, "spanish"); // Permite imprimir caracteres con tilde 
	do{
		
		menu_bienvenida();
	
	 switch(opcion_usuario){
	 	
	 	case 1: // usuario selecciona administrador 
	 	opciones_admin();
	 	break;
	 	
	 	case 2: // usuario selecciona cliente
	 	opciones_cliente();
	 	break;
	 	
	    case 3 : // salir del programa
	    break;
	 
	    default : printf("OPCIÓN NO VÁLIDA, PRUEBE DE NUEVO.\n"); // opcion incorrecta, pide al usuario reintentar para ingresar un numero valido de acuerdo al menu.
	 }
	 	
}while(opcion_usuario != 3); // si el usuario selecciona la opcion 3, el programa finaliza.
	
	return 0;
}

//-------------------------------------------------------------------------------------------------------------------

// COMIENZO DE IMPLEMENTACION DE FUNCIONES 

void menu_bienvenida(){
	titulo();
	printf("\t\tA continuación se presentan las opciones disponibles.\n");
	printf("\t\tpara continuar, seleccione la opción deseada.\n\n");
	printf("\t\tOpción 1 : Ingresar como administrador.\n");
	printf("\t\tOpción 2 : Ingresar como cliente.\n");
	printf("\t\tOpción 3 : Salir del programa.\n");
	
	
		fgets(temp,10,stdin); //leer la cadena, almacenar en la variable temp (temporal con un maximo de 10 caracteres) y viene de la entrada stdin.
opcion_usuario = atoi(temp); // transforma lo que se leyo nteriormente ( tipo char ) en un numero ( tipo int ).
     system("cls"); // limpiar pantalla 
} // cierre void menu bienvenida 

void menu_admin(){
	
	 titulo();
	printf("\t\tA continuación se presentan las opciones disponibles.\n");
	printf("\t\tpara continuar, seleccione la opción deseada.\n\n");
	printf("\t\tOpción 1 : Iniciar sesión.\n");
	printf("\t\tOpción 2 : Registrar nuevo administrador.\n");
	printf("\t\tOpción 3 : Modificar administrador existente.\n");
	printf("\t\tOpción 4 : Eliminar administrador existente.\n");
	printf("\t\tOpción 5 : Visualizar administradores existentes.\n");
	printf("\t\tOpción 6 : Volver al menú anterior.\n");
	
		fgets(temp,10,stdin); //leer la cadena, almacenar en la variable temp (temporal con un maximo de 10 caracteres) y viene de la entrada stdin.
opcion_usuario = atoi(temp); // transforma lo que se leyo nteriormente ( tipo char ) en un numero ( tipo int ).
		system("cls"); // limpiar pantalla 
} // cierre menu admin 

void opciones_admin(){ // PROGRAMA PRINCIPAL 
	
	do{
		
		menu_admin();
	
	 switch(opcion_usuario){
	 	
	 	case 1: // usuario selecciona iniciar sesión
	 	inicio_sesion();
	 	break;
	 	
	 	case 2: // usuario selecciona registrar nuevo administrador 
	 	registrarse();
	 	break;
	 	
	 	case 3: // Modificar admin existente
	 	modificar_admin();
	 	break;
	 	
	 	case 4: // Eliminar admin existente
	 	eliminar_admin();
	 	break;
	 	
	 	case 5: // visualizar admins existentes
	 	visualizar_admins();
	 	break;
	 	
	    case 6 : // salir del programa
	    break;
	 
	    default : printf("OPCIÓN NO VÁLIDA, PRUEBE DE NUEVO.\n"); // opcion incorrecta, pide al usuario reintentar para ingresar un numero valido de acuerdo al menu.
	 }
	 	
}while(opcion_usuario != 6); // si el usuario selecciona la opcion 7, el programa finaliza.
	
	
	
	
} // cierre void menu admin 

void registrarse(){
	

    char repite = 1;
    char respuesta[MAX];
   
    Admin admin;
    int numeroAdmin = 0;
    
    do {
        system("cls");
        titulo();
        printf("\n\t\t\t REGISTRAR NUEVO ADMINISTRADOR \n\n");
 
        // numero de administrador
        printf("\n\tNúmero del administrador(1-2-3 etc): ");
        leecad(linea, MAX);
        sscanf(linea, "%d", &numeroAdmin);
       
 
        // Se verifica que el número no haya sido almacenado anteriormente 
        if (!existeAdmin(numeroAdmin, &admin)) {
 
            admin.numero = numeroAdmin;
 
            // Se piden los demás datos del administrador 
            printf("\tNombre del administrador: ");
            leecad(admin.nAdmin, MAX);
            
            printf("\tClave del administrador: ");
            leecad(admin.clave, MAX);
 
            
 
            // Se inserta el administrador en el archivo 
            if (insertarAdmin(admin)) {
                printf("\n\tEl administrador fue registrado exitosamente.\n\n");
                
            } else {
                printf("\n\tOcurrió un error al intentar registrar el administrador\n");
                printf("\tInténtelo mas tarde\n");
            }
        } else {
            // El admin ya existe
            printf("\n\tEl administrador %d ya está registrado.\n", numeroAdmin);
            
        }
 
        printf("\n\t¿Desea seguir registrando administradores? [S/N]: ");
        leecad(respuesta, MAX);
 
        if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)) {
            repite = 0;
        }
 system("cls"); // limpiar pantalla 
    } while (repite);
	
	

	
} // cierre funcion registro 

void inicio_sesion(){ // PROGRAMA PRINCIPAL 

	Admin admin;
    char repite = 1;
    char respuesta[MAX];
    
    // variables para el nombre de usuario y la contraseña del admin
    char ingresoAdmin[MAX];
    char ingresoClave[MAX];
    
    int contador = 0;
bool ingresa = false;
	
	do{
	 	titulo();
	    printf("\t\t\t\tINICIO DE SESIÓN\n\n");
	 	printf("\t\tINGRESE SU NOMBRE DE ADMINISTRADOR :\n\n");

	 	leecad(linea, MAX);
        sscanf(linea, "%s", ingresoAdmin);
        
	 	printf("\t\tINGRESE SU CONTRASEÑA :\n");
	 
	 	leecad(linea, MAX);
        sscanf(linea, "%s", ingresoClave);
        
	 	if(existeNombre(ingresoAdmin,&admin) && existeClave(ingresoClave,&admin)){
	 	
	 	ingresa = true;
	 	}
	 	else{ // admin ingresa mal la contraseña 
	 		
	 		contador++;
	 		system("cls"); // limpiar pantalla 
	 		
	 	}
	 }while((ingresa == false) && (contador<3)); // luego de 3 intentos fallidos, vuelve al menu principal.
	 
	 if(ingresa == false){
	 	titulo();
	 	printf("\tLimite de intentos fallidos alcanzado.\n");
	 	printf("\tPulse cualquier tecla para volver al menú anterior.\n");
	 	system("pause>nul");
	 	system("cls");
	 	  
	 }
	 else{
	 	system("cls");
	 	// BIENVENIDO AL SISTEMA ( ADMIN ENTRA A LA PLATAFORMA ) 
	 	do{
	 		// MENSAJE CON OPCIONES DEL ADMIN 
	 		menu_listado_admin();
	 		
	 		switch(opcion_usuario){
	 			
	 			case 1: // añadir producto 
	 			agregar_producto();
	 				break;
	 				
	 			case 2:// modificar producto 
	 			modificar_producto();
				 break;
				 
				 case 3: // eliminar producto 
				 eliminar_producto();
				 break;
				 
				 case 4: // listar producto 
				 listar_producto();
				 break;	
	 			
	 			case 5 : // buscar producto 
	 			buscar_producto();
	 			break;
	 			
	 			case 6 : // salir 
	 			break;
	 			
	 			default : printf("OPCIÓN NO VÁLIDA, PRUEBE DE NUEVO.\n");
	 			
	 			
	 			
	 			
	 			
	 			
			 } // switch 
	 		
	 		
	 		
	 		
	 		
		 }while(opcion_usuario !=6);
	 	
	 	
	 }
	
	
	
	
} // cierre funcion inicio sesion 

void menu_listado_admin(){
	titulo();
	printf("\t\tA continuación se presentan las opciones disponibles.\n");
	printf("\t\tpara continuar, seleccione la opción deseada.\n\n");
	printf("\t\tOpción 1 : Añadir productos.\n");
	printf("\t\tOpción 2 : Modificar productos.\n");
	printf("\t\tOpción 3 : Eliminar productos.\n");
	printf("\t\tOpción 4 : Listar productos.\n");
	printf("\t\tOpción 5 : Buscar productos.\n");
	printf("\t\tOpción 6 : Volver al menú anterior.\n");
	
		fgets(temp,10,stdin); //leer la cadena, almacenar en la variable temp (temporal con un maximo de 10 caracteres) y viene de la entrada stdin.
opcion_usuario = atoi(temp); // transforma lo que se leyo nteriormente ( tipo char ) en un numero ( tipo int ).
	system("cls"); // limpiar pantalla 
	
} // cierre menu listado admin 


int leecad(char *cad, int n){
	
	int i, c;
 
    /* Hay que verificar si el buffer está limpio o si hay un '\n'
      dejado por scanf y, en ese caso, limpiarlo:
    */
 
    /* 1 COMPROBACIÓN DE DATOS INICIALES EN EL BUFFER */
 
    /* Empezamos leyendo el primer caracter que haya en la entrada. Si es
      EOF, significa que no hay nada por leer, así que cerramos la cadena,
      dejándola "vacía" y salimos de la función retornando un valor de 0
      o falso, para indicar que hubo un error */
    c = getchar();
    if (c == EOF) {
        cad[0] = '\0';
        return 0;
    }
 
    /* Si el valor leído es '\n', significa que había un caracter de nueva línea
    dejado por un scanf o función similar. Simplemente inicializamos i a 0,
    para indicar que los siguientes caracteres que leamos iremos asignando a
    partir del primer caracter de la cadena. */
    if (c == '\n') {
        i = 0;
    } else {
    /* Si no había un '\n', significa que el caracter que leímos es el primer
      caracter de la cadena introducida. En este caso, lo guardamos en la
      posición 0 de cad, e inicializamos i a 1, porque en este caso, como ya
      tenemos el primer caracter de la cadena, continuaremos agregando 
      caracteres a partir del segundo.
 
    */
        cad[0] = c;
        i = 1;
    }
 
    // 2 .- lectura cadena 
 
    /* El for empieza con un ; porque estamos omitiendo la inicialización del contador,
    ya que fue inicializado en el punto anterior.
    Este código lee un caracter a la vez,lo agrega a cad, y se repite hasta que
    se encuentre un fin de línea, fin de archivo, o haya leído la cantidad máxima
    de caracteres que se le indicó. Luego, cierra la cadena agregando un '\0'
    al final. Todo esto es muy similar a la forma en que los compiladores suelen
    implementar la función fgets, sólo que en lugar de getchar usan getc o fgetc
    */
    for (; i < n - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
        cad[i] = c;
    }
    cad[i] = '\0';
 
    // 3.- limpieza buffer
 
    // para limpiar el buffer si es necesario 
    if (c != '\n' && c != EOF) // si es un caracter 
        while ((c = getchar()) != '\n' && c != EOF);
 
    /* La variable c contiene el último caracter leído. Recordemos que había 3 formas
    de salir del for: que hayamos encontrando un '\n', un EOF, o que hayamos llegado
    al máximo de caracteres que debemos leer. Si se da cualquiera de los dos
    primeros casos, significa que leímos todo lo que había en el buffer, por lo que
    no hay nada que limpiar. En el tercer caso, el usuario escribió más caracteres
    de los debidos, que aún están en el buffer, por lo que hay que quitarlos, para
    lo cual usamos el método que vimos poco más arriba
    */
 
    return 1;
	
	
	
	
} // cierre leer cadenas

Producto *obtenerProductos(int *n)
{
    FILE *archivo;
    Producto producto;
    Producto *productos; 
    int i;
 
    // Abre el archivo en modo lectura 
    archivo = fopen("productos.dat", "rb");
 
    if (archivo == NULL) { // Si no puede abrir el archivo, el valor es NULL 
        *n = 0; 
        productos = NULL;
 
    } else {
 
        fseek(archivo, 0, SEEK_END); // Posiciona el cursor al final del archivo 
        *n = ftell(archivo) / sizeof(Producto); // numero de productos almacenados en el archivo
        productos = (Producto *)malloc((*n) * sizeof(Producto)); // Se reserva memoria para todos los productos almacenados en el archivo 
 
        // Se recorre el archivo secuencialmente 
        fseek(archivo, 0, SEEK_SET); // Posiciona el cursor al principio del archivo 
        fread(&producto, sizeof(producto), 1, archivo);
        i = 0;
        while (!feof(archivo)) {
            productos[i++] = producto;
            fread(&producto, sizeof(producto), 1, archivo);
        }
 
        // Cierra el archivo 
        fclose(archivo);
    }
 
    return productos;
} // cierre 
 
char existeProducto(int codigoProducto, Producto *producto)
{
    FILE *archivo;
    char existe;
 
    // Abre el archivo en modo lectura 
    archivo = fopen("productos.dat", "rb");
 
    if (archivo == NULL) { // Si no se pudo abrir el archivo, el valor de archivo es NULL 
        existe = 0;
 
    } else {
        existe = 0;
 
        // Se busca el producto cuyo código coincida con codigoProducto 
        fread(&(*producto), sizeof(*producto), 1, archivo);
        while (!feof(archivo)) {
            if ((*producto).codigo == codigoProducto) {
                existe = 1;
                break;
            }
            fread(&(*producto), sizeof(*producto), 1, archivo);
        }
 
        // Cierra el archivo 
        fclose(archivo);
    }
 
    return existe;
} // cierre 
 
char insertarProducto(Producto producto)
{
    FILE *archivo;
    char insercion;
 
    // Abre el archivo para agregar datos al final 
    archivo = fopen("productos.dat", "ab");    // Añade datos al final. Si el archivo no existe, es creado 
 
    if (archivo == NULL) { // Si no se pudo abrir el archivo, el valor de archivo es NULL 
        insercion = 0;
 
    } else {
        fwrite(&producto, sizeof(producto), 1, archivo);
        insercion = 1;
 
        // Cierra el archivo 
        fclose(archivo);
    }
 
    return insercion;
} // cierre 
 

char eliminarProducto(int codigoProducto) // Eliminacion de un producto
{
    FILE *archivo;
    FILE *auxiliar;
    Producto producto;
    char elimina;
 
    // Abre el archivo para leer
    archivo = fopen("productos.dat", "r+b");    // Modo lectura/escritura. Si el archivo no existe, es creado 
 
    if (archivo == NULL) { // Si no se pudo abrir el archivo, el valor de archivo es NULL 
        elimina = 0;
 
    } else {
        // Se busca el registro que se quiere borrar
        
 
        elimina = 0;
        fread(&producto, sizeof(producto), 1, archivo);
        while (!feof(archivo)) {
            if (producto.codigo == codigoProducto) {
                fseek(archivo, ftell(archivo) - sizeof(producto), SEEK_SET);
                producto.codigo = CONTADOR;
                fwrite(&producto, sizeof(producto), 1, archivo);
                elimina = 1;
                break;
            }
            fread(&producto, sizeof(producto), 1, archivo);
        }
 
        // Cierra el archivo 
        fclose(archivo);
    }
 
    return elimina;
} // cierre 

char guardarReporte()
{
    FILE *archivo;
    char guardado;
    Producto *productos;
    int numeroProductos;
    int i;
    
    productos = obtenerProductos(&numeroProductos); // Retorna un vector dinámico de productos 
 
    if (numeroProductos == 0) {
        guardado = 0;
 
    } else {
        // Abre el archivo en modo texto para escritura 
        archivo = fopen("bodega.txt", "w");
 
        if (archivo == NULL) { // Si no se pudo abrir el archivo, el valor de archivo es NULL 
            guardado = 0;
 
        } else {
            fprintf(archivo,"\n\t\t     LISTADO DE PRODUCTOS REGISTRADOS \n\n");
 
            // Se recorre el vector dinámico de productos 
            
            for (i = 0; i < numeroProductos; i++) {
                if (productos[i].codigo != CONTADOR) {
                       
            fprintf(archivo,"\tIdentificador del producto: %d\n", productos[i].codigo);
            fprintf(archivo,"\tNombre del producto: %s\n", productos[i].nombre);  
            fprintf(archivo,"\tStock del producto: %d\n", productos[i].cantidad);   
            fprintf(archivo,"\tPrecio del producto: %.1f $\n\n", productos[i].precio);   
               
                }
            }
           
            guardado = 1;
 
            // Cierra el archivo 
            fclose(archivo);
        }
    }
 
    return guardado;
} // cierre 

char modificarProducto(Producto producto)
{
    FILE *archivo;
    char modifica;
    Producto producto2;
 
    // Abre el archivo para lectura/escritura 
    archivo = fopen("productos.dat", "rb+");
 
    if (archivo == NULL) { // Si no se pudo abrir el archivo, el valor de archivo es NULL 
        modifica = 0;
 
    } else {
        modifica = 0;
        fread(&producto2, sizeof(producto2), 1, archivo);
        while (!feof(archivo)) {
            if (producto2.codigo == producto.codigo) {
                fseek(archivo, ftell(archivo) - sizeof(producto), SEEK_SET);
                fwrite(&producto, sizeof(producto), 1, archivo);
                modifica = 1;
                break;
            }
            fread(&producto2, sizeof(producto2), 1, archivo);
        }
 
        fclose(archivo);
    }
 
    // Cierra el archivo 
    return modifica;
}

//-----------------------------------------------------------------------------------------------------

// FUNCIONES PRINCIPALES

void agregar_producto(){
	
	Producto producto;
    int codigoProducto = 0;
    char repite = 1;
    char respuesta[MAX];
 
    do {
        system("cls");
        titulo();
        printf("\n\t\t\t AGREGAR PRODUCTO A LISTADO \n\n");
 
        // Se pide el código del producto a agregar
        printf("\n\tCódigo de producto: ");
        leecad(linea, MAX);
        sscanf(linea, "%d", &codigoProducto);
 
        // Se verifica que el producto no haya sido almacenado anteriormente 
        if (!existeProducto(codigoProducto, &producto)) {
 
            producto.codigo = codigoProducto;
 
            // Se piden los demás datos del producto a insertar 
            printf("\tNombre del producto: ");
            leecad(producto.nombre, MAX);
 
            printf("\tPrecio del producto ($): ");
            leecad(linea, MAX);
            sscanf(linea, "%f", &producto.precio);
 
            printf("\tStock del producto: ");
            leecad(linea, MAX);
            sscanf(linea, "%d", &producto.cantidad);
 
            // Se inserta el producto en el archivo 
            if (insertarProducto(producto)) {
                printf("\n\tEl producto fue agregado correctamente.\n");
 
            } else {
                printf("\n\tOcurrió un error al intentar agregar el producto\n");
                printf("\tInténtelo mas tarde\n");
            }
        } else {
            // El producto ya existe, no puede ser agregado
            printf("\n\tEl producto de código %d ya existe.\n", codigoProducto);
            printf("\tNo puede ingresar dos productos distintos con el mismo código.\n");
        }
 
        printf("\n\t¿Desea seguir ingresando productos? [S/N]: ");
        leecad(respuesta, MAX);
 
        if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)) {
            repite = 0;
        }
 system("cls"); // limpiar pantalla 
    } while (repite);
	
	
	
} // cierre añadir productos 
 
 void modificar_producto(){
 	
 	Producto producto;
    int codigoProducto;
    char repite = 1;
    char respuesta[MAX];
 
    do {
        system("cls");
        titulo();
        
        printf("\n\t\t\tMODIFICAR PRODUCTO POR CÓDIGO \n\n");
 
        // Se pide el código del producto a modificar 
        printf("\n\tCódigo de producto: ");
        leecad(linea, MAX);
        sscanf(linea, "%d", &codigoProducto);
 
        // Se verifica que el producto a buscar exista 
        if (existeProducto(codigoProducto, &producto)) {
 
            // Se muestran los datos del producto 
            printf("\n\tNombre del producto: %s\n", producto.nombre);
            printf("\tPrecio del producto ($): %.1f\n", producto.precio);
            printf("\tStock: %d\n", producto.cantidad);
 
            printf("\n\tElija los datos a modificar\n");
 
            // Modificación del nombre del producto 
            printf("\n\tNombre del producto actual: %s\n", producto.nombre);
            printf("\t¿Desea modificar el nombre del producto? [S/N]: ");
            leecad(respuesta, MAX);
            if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0) {
                printf("\tNuevo nombre del producto: ");
                leecad(producto.nombre, MAX);
            }
 
            // Modificación del precio del producto 
            printf("\n\tPrecio del producto actual: %.1f\n", producto.precio);
            printf("\t¿Desea modificar el precio del producto? [S/N]: ");
            leecad(respuesta, MAX);
            if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0) {
                printf("\tNuevo precio del producto: ");
                leecad(linea, MAX);
                sscanf(linea, "%f", &producto.precio);
            }
 
            // Modificación de la cantidad del producto 
            printf("\n\tStock del producto actual: %d\n", producto.cantidad);
            printf("\t¿Desea modificar el stock del producto? [S/N]: ");
            leecad(respuesta, MAX);
            if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0) {
                printf("\tNuevo stock del producto: ");
                leecad(linea, MAX);
                sscanf(linea, "%d", &producto.cantidad);
            }
 
            printf("\n\t¿Está seguro que desea modificar los datos del producto? [S/N]: ");
            leecad(respuesta, MAX);
 
            if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0) {
                // Se modifica el producto en el archivo 
                if (modificarProducto(producto)) {
                    printf("\n\tEl producto fue modificado correctamente.\n");
 
                } else {
                    printf("\n\tOcurrió un error al intentar modificar el producto\n");
                    printf("\tInténtelo mas tarde\n");
                }
            }
        } else {
            // El producto no existe 
            printf("\n\tEl producto de código %d no existe.\n", codigoProducto);
        }
 
        printf("\n\tDesea modificar algún otro producto? [S/N]: ");
        leecad(respuesta, MAX);
 
        if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)) {
            repite = 0;
        }
 system("cls"); // limpiar pantalla 
    } while (repite);
 	
 	
 } // cierre modificar producto 
 
 void eliminar_producto(){
 	
 	Producto producto;
    int codigoProducto;
    char repite = 1;
    char respuesta[MAX];
 
    do {
        system("cls");
        titulo();
        
        printf("\n\t\t\t ELIMINAR PRODUCTO POR CÓDIGO \n\n");
 
        // Se pide el código del producto a eliminar 
        printf("\n\tCódigo de producto: ");
        leecad(linea, MAX);
        sscanf(linea, "%d", &codigoProducto);
 
        // Se verifica que el producto a buscar, exista 
        if (existeProducto(codigoProducto, &producto)) {
 
            // Se muestran los datos del producto 
            printf("\n\tCódigo del producto: %d\n", producto.codigo);
            printf("\tNombre del producto: %s\n", producto.nombre);            
            printf("\tPrecio del producto: %.1f $\n", producto.precio);
            printf("\tCantidad: %d\n", producto.cantidad);
 
            printf("\n\t¿Seguro que desea eliminar el producto? [S/N]: ");
            leecad(respuesta, MAX);
            if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0) {
                if (eliminarProducto(codigoProducto)) {
                    printf("\n\tProducto eliminado satisfactoriamente.\n");
                } else {
                    printf("\n\tEl producto no pudo ser eliminado\n");
                }
            }
 
        } else {
            // El producto no existe 
            printf("\n\tEl producto de código %d no existe.\n", codigoProducto);
        }
 
        printf("\n\t¿Desea eliminar otro producto? [S/N]: ");
        leecad(respuesta, MAX);
 
        if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)) {
            repite = 0;
        }
 system("cls"); // limpiar pantalla 
    } while (repite);
 	
 	
 	
 	
 } // cierre void eliminar producto 
 
 void listar_producto(){
 	
 	Producto *productos;
    int numeroProductos;
    int i;
    char respuesta[MAX];
 
    system("cls");
    titulo();
    
    productos = obtenerProductos(&numeroProductos); // Retorna un vector dinámico de productos 
 
    if (numeroProductos == 0) {
        printf("\n\tEl archivo esta vacío.\n");
        printf("\n\tIngrese datos para poder listar.\n");
        printf("\n\tPresione cualquier tecla para volver al menú anterior.\n"); 
        system("pause>nul");
 
    } else {
        // titulo de la lista 
        printf("\n\t\t     LISTADO DE PRODUCTOS REGISTRADOS \n\n");
 
        // Se recorre el vector dinámico de productos 
        
        for (i = 0; i < numeroProductos; i++) {
            if (productos[i].codigo != CONTADOR) {
                
                	// Se muestran los datos del producto
            printf("\t\tIdentificador del producto: %d\n", productos[i].codigo);
            printf("\t\tNombre del producto: %s\n", productos[i].nombre);  
            printf("\t\tStock del producto: %d\n", productos[i].cantidad);   
            printf("\t\tPrecio del producto: %.1f $\n\n", productos[i].precio);  
            
          
            }
        }
        
        printf("\n\t¿Desea guardar el reporte en un archivo de texto? [S/N]: ");
        leecad(respuesta, MAX);
 
        if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0) {
            if (guardarReporte()) {
                printf("\n\tEl reporte fue guardado con éxito\n");
                printf("\n\tPresione cualquier tecla para volver al menú anterior\n");
            } else {
                printf("\n\tOcurrió un error al guardar el reporte\n");
            }
 
            system("pause>nul");
        }
    }
 	
 	
 	
 	system("cls"); // limpiar pantalla 
 } // cierre listar producto 
 
 void buscar_producto(){
 	
 	Producto producto;
    int codigoProducto;
    char repite = 1;
    char respuesta[MAX];
 
    do {
        system("cls");
        titulo();
        
        printf("\n\t\t\t BUSCAR PRODUCTO POR CÓDIGO \n\n");
 
        // Se pide el código del producto a buscar 
        printf("\n\tCódigo de producto: ");
        leecad(linea, MAX);
        sscanf(linea, "%d", &codigoProducto);
 
        // Se verifica que el producto a buscar, exista 
        if (existeProducto(codigoProducto, &producto)) {
 
            // Se muestran los datos del producto 
            printf("\n\tCódigo del producto: %d\n", producto.codigo);
            printf("\tNombre del producto: %s\n", producto.nombre);            
            printf("\tPrecio del producto: %.1f $\n", producto.precio);
            printf("\tStock: %d\n", producto.cantidad);
 
        } else {
            // El producto no existe 
            printf("\n\tEl producto de código %d no existe.\n", codigoProducto);
        }
 
        printf("\n\t¿Desea seguir buscando algún producto? [S/N]: ");
        leecad(respuesta, MAX);
 
        if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)) {
            repite = 0;
        }
 system("cls"); // limpiar pantalla 
    } while (repite);
 	
 	
 	
 	
 } // cierre buscar producto 

void opciones_cliente(){ // MENU PRINCIPAL 2
	
	do{
		
		menu_cliente();
	
	 switch(opcion_usuario){
	 	
	 	case 1: // usuario selecciona ver listado de productos
	 	listar_producto_cliente();
	 	break;
	 	
	 	case 2: // usuario selecciona comprar producto ( PROGRAMA PRINCIPAL 2 ) 
	 	comprar_producto(); 
	 	break;
	 	
	 	case 3: // ver carrito de compras
	 	mostrar_boleta_cliente();
	 	break;
	 	
	 	case 4: // finalizar compra
	 	finalizar_compra();
	 	break;
	 	
	    case 5 : // salir del programa
	    break;
	 
	    default : printf("OPCIÓN NO VÁLIDA, PRUEBE DE NUEVO.\n"); // opcion incorrecta, pide al usuario reintentar para ingresar un numero valido de acuerdo al menu.
	 }
	 	
}while(opcion_usuario != 5); // si el usuario selecciona la opcion 5, el programa finaliza.
	
	
	
	
	
	
} // cierre void opciones clientes

void menu_cliente(){
	titulo();
	printf("\t\tA continuación se presentan las opciones disponibles.\n");
	printf("\t\tpara continuar, seleccione la opción deseada.\n\n");
	printf("\t\tOpción 1 : Ver listado de productos.\n");
	printf("\t\tOpción 2 : Comprar productos.\n");
	printf("\t\tOpción 3 : Ver carrito de compras.\n");
	printf("\t\tOpción 4 : Finalizar compra.\n");
	printf("\t\tOpción 5 : Volver al menú anterior.\n");
	
	
		fgets(temp,10,stdin); //leer la cadena, almacenar en la variable temp (temporal con un maximo de 10 caracteres) y viene de la entrada stdin.
opcion_usuario = atoi(temp); // transforma lo que se leyo nteriormente ( tipo char ) en un numero ( tipo int ).
	system("cls"); // limpiar pantalla 
	
	
} // cierre void menu cliente 

void listar_producto_cliente(){
	
	Producto *productos;
    int numeroProductos;
    int i;
    char respuesta[MAX];
 
    system("cls");
    titulo();
    productos = obtenerProductos(&numeroProductos); // Retorna un vector dinámico de productos 
 
    if (numeroProductos == 0) {
        printf("\n\tEl archivo esta vacío\n");
        printf("\n\tIngrese datos para poder listar.\n");
        printf("\n\tPRESIONE ENTER PARA VOLVER AL MENÚ\n"); 
        system("pause>nul");
 
    } else {
        // titulo de la lista 
        printf("\t\t\t        LISTADO DE PRODUCTOS \n\n\n");
 
        // Se recorre el vector dinámico de productos 
        
        for (i = 0; i < numeroProductos; i++) {
            if (productos[i].codigo != CONTADOR) {
                
                	// Se muestran los datos del producto
            printf("\tIdentificador del producto: %d\n", productos[i].codigo);
            printf("\tNombre del producto: %s\n", productos[i].nombre);  
            printf("\tStock del producto: %d\n", productos[i].cantidad);   
            printf("\tPrecio del producto: %.1f $\n\n", productos[i].precio);  
          
            }
        }
        
        printf("\n\tPresione cualquier tecla para volver al menú anterior.\n\n");
            system("pause>nul");
       
    } 
 	
 	
	
	
	system("cls"); // limpiar pantalla 
} // cierre void listar producto cliente 

void titulo(){
	
	 
    printf("\n     ======================================================================\n\n");
    printf("\t\t\t    ESTRUCTURA DE DATOS Y ALGORITMOS\n");
    printf("\t\t     plataforma de simulación administrador-cliente\n");
    printf("\n     ======================================================================\n");
    printf("\n\n");
    
} // cierre void titulo 

void comprar_producto(){  

		Producto producto;
    int codigoProducto;
    char repite = 1;
    char respuesta[MAX];
    
    do {
        
        titulo();
        
        printf("\n\t\t\t BÚSQUEDA PRODUCTO\n\n");
 
        // Se pide el código del producto a buscar 
        printf("\n\tIngrese el código del producto: ");
        leecad(linea, MAX);
        sscanf(linea, "%d", &codigoProducto);
 
        // Se verifica que el producto a buscar, exista 
        if (existeProducto(codigoProducto, &producto)) {
 
            // Se muestran los datos del producto 
            printf("\n\tCódigo del producto: %d\n", producto.codigo);
            printf("\tNombre del producto: %s\n", producto.nombre);            
            printf("\tPrecio del producto: %.1f $\n", producto.precio);
            printf("\tStock: %d\n\n", producto.cantidad);
            
            printf("\t¿Desea comprar este producto?[S/N]:\n");
            leecad(respuesta, MAX);
            
            if ((strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)) {
            	system("cls");
            	titulo();
            printf("\tCuantas unidades desea comprar? :\n");
           leecad(linea, MAX);
            sscanf(linea, "%d", &producto.unidades);
            
             producto.cantidad = producto.cantidad - producto.unidades;
             if(producto.cantidad>0){ // mientras exista stock, se puede comprar 
             modificarProducto(producto); // modifica en el archivo el nuevo stock 
            
            printf("\n\tCódigo del producto: %d\n", producto.codigo);
            printf("\tNombre del producto: %s\n", producto.nombre);            
            printf("\tPrecio del producto: %.1f $\n", producto.precio);
            printf("\tUnidades compradas: %d\n",producto.unidades);
            compra_cliente(producto); // se añade el producto al archivo 2
           
            printf("\t¿Desea seguir comprando algún producto?[S/N]: ");
            leecad(respuesta, MAX);
            if((strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)){
            system("cls");	 
			}
			else{ // cliente pasa al detalle de compra 
			mostrar_boleta_cliente();
				repite=0;
			}	
             	
             	
             	
		}else{
			printf("\tERROR,no hay stock suficiente.\n");
			printf("\tPulse cualquier tecla para volver a comprar.\n");
			system("pause>nul");
			system("cls");
			
		}
		
            
           
    
           
            
        } 
        else{ 
        	
        	system("cls");
		}
              
 
 
 
 
 
 
        } else {
            // El producto no existe 
            printf("\n\tEl producto de código %d no existe.\n", codigoProducto);
            printf("\tPresione cualquier tecla para volver a comprar.\n");
            system("pause>nul");
            system("cls");
        }
        
       
 
    } while (repite);
 	
	
	
} // cierre void comprar producto 

//------------------------------------------------------------------------------------------------------
// comienzo implementaciones funciones cliente 

char compra_cliente(Producto producto){ // insertar producto 
	
	FILE *archivo2;
    char insercion;
 
    // Abre el archivo2 para agregar datos al final 
    archivo2 = fopen("cliente.dat", "ab");    // Añade datos al final. Si el archivo no existe, es creado 
 
    if (archivo2 == NULL) { // Si no se pudo abrir el archivo, el valor de archivo es NULL 
        insercion = 0;
 
    } else {
        fwrite(&producto, sizeof(producto), 1, archivo2);
        insercion = 1;
 
        // Cierra el archivo 
        fclose(archivo2);
    }
 
    return insercion;
	
} // cierre char compra cliente 

 

Producto *obtener_compras(int *n){
	
	FILE *archivo2;
    Producto producto;
    Producto *productos; // Vector dinámico de productos 
    int i;
 
    // Abre el archivo en modo lectura 
    archivo2 = fopen("cliente.dat", "rb");
 
    if (archivo2 == NULL) { // Si no se pudo abrir el archivo, el valor de archivo es NULL 
        *n = 0; 
        productos = NULL;
 
    } else {
 
        fseek(archivo2, 0, SEEK_END); // Posiciona el cursor al final del archivo 
        *n = ftell(archivo2) / sizeof(Producto); // # de productos almacenados en el archivo. 
        productos = (Producto *)malloc((*n) * sizeof(Producto)); // Se reserva memoria para todos los productos almacenados en el archivo 
 
        // Se recorre el archivo secuencialmente 
        fseek(archivo2, 0, SEEK_SET); // Posiciona el cursor al principio del archivo 
        fread(&producto, sizeof(producto), 1, archivo2);
        i = 0;
        while (!feof(archivo2)) {
            productos[i++] = producto;
            fread(&producto, sizeof(producto), 1, archivo2);
        }
 
        // Cierra el archivo 
        fclose(archivo2);
    }
 
    return productos;
	
	
	
} // cierre obtener compra 

char boleta_cliente(){
	
	FILE *archivo2;
    char guardado;
    Producto *productos;
    int numeroProductos;
    int i;
    float precioTotal;
    
    productos = obtener_compras(&numeroProductos); // Retorna un vector dinámico de productos 
 
    if (numeroProductos == 0) {
        guardado = 0;
 
    } else {
        // Abre el archivo en modo texto para escritura 
        archivo2 = fopen("boleta.txt", "w");
 
        if (archivo2 == NULL) { // Si no se pudo abrir el archivo, el valor de archivo es NULL 
            guardado = 0;
 
        } else {
            fprintf(archivo2,"\n\t\t     DETALLE DE COMPRA \n\n");
 
            // Se recorre el vector dinámico de productos 
            precioTotal = 0;
            for (i = 0; i < numeroProductos; i++) {
                if (productos[i].codigo != CONTADOR) {
                       
            fprintf(archivo2,"\tIdentificador del producto: %d\n", productos[i].codigo);
            fprintf(archivo2,"\tNombre del producto: %s\n", productos[i].nombre);   
            fprintf(archivo2,"\tPrecio del producto: %.1f $\n", productos[i].precio);
            fprintf(archivo2,"\tUnidades compradas: %d\n\n", productos[i].unidades);
			 precioTotal += productos[i].unidades * productos[i].precio; 
                
                }
            }
           fprintf(archivo2,"\t\tTotal a pagar : %.2f\n\n",precioTotal);
            guardado = 1;
 
            // Cierra el archivo 
            fclose(archivo2);
        }
    }
 
    return guardado;
	
	
} // cierre char boleta cliente 

void mostrar_boleta_cliente(){
	
	Producto *productos;
    int numeroProductos;
    int i;
    char respuesta[MAX];
    float precioTotal;
 
    system("cls");
    titulo();
    
    productos = obtener_compras(&numeroProductos); // Retorna un vector dinámico de productos 
 
    if (numeroProductos == 0) {
        printf("\n\tEl carro de compras está vacío,no ha comprado nada aún.\n");
        printf("\n\tPresione cualquier tecla para volver al menú anterior.\n"); 
        system("pause>nul");
        system("cls");
    } else {
        // titulo de la lista 
        printf("\n\t\t     DETALLE DE COMPRA \n\n");
 
        // Se recorre el vector dinámico de productos 
        precioTotal = 0;
        for (i = 0; i < numeroProductos; i++) {
            if (productos[i].codigo != CONTADOR) {
                
                	// Se muestran los datos del producto
            printf("\t\tIdentificador del producto: %d\n", productos[i].codigo);
            printf("\t\tNombre del producto: %s\n", productos[i].nombre);  
            printf("\t\tPrecio del producto: %.1f $\n", productos[i].precio); 
			printf("\t\tUnidades compradas: %d\n\n", productos[i].unidades); 
			precioTotal += productos[i].unidades * productos[i].precio;
          
            }
            
        }
        printf("\t\tTotal a pagar : %.2f\n\n",precioTotal);
        
        printf("\n\tDesea guardar el detalle de compra(boleta)? [S/N]: ");
        leecad(respuesta, MAX);
 
        if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0) {
            if (boleta_cliente()) {
                printf("\n\tLa boleta fue guardada con éxito\n");
                printf("\n\tPresione cualquier tecla para volver al menú anterior\n");
            } else {
            	
                printf("\n\tOcurrió un error al intentar guardar la boleta\n");
                system("cls");
            }
 
            system("pause>nul");
            system("cls");
        }
        else{
        	printf("\n\tno se guardó la boleta.\n");
            printf("\n\tPresione cualquier tecla para volver al menú anterior\n");
        	system("pause>nul");
        	system("cls");
		}
    }
 	
 	
 	
 	
	
	
} // cierre void mostrar boleta cliente 

void finalizar_compra(){ // borrar carrito de compras y boleta 

FILE *archivo2;

	char respuesta[MAX];
	titulo();
	printf("\n\t¿Desea finalizar su compra? [S/N]:\n ");
        leecad(respuesta, MAX);
 
        if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0) {
        	
        archivo2 = fopen("cliente.dat", "w"); // vacia los datos en el sistema del cliente ( cliente.dat)
        fflush(archivo2);
        fclose(archivo2);
        
        archivo2 = fopen("boleta.txt", "w"); // vacia la boleta del cliente ( archivo de texto ) 
         fflush(archivo2);
        fclose(archivo2);
        
        
        printf("\tCompra finalizada.\n");
		printf("\tPresione cualquier tecla para volver al menú anterior.\n");	
        system("pause>nul");
        system("cls");
        }
        else{
        system("cls");
		}
	
	
	
	
} // cierre finalizar compra
//--------------------------------------------------------------------------------------
//nuevas funciones administrador
char existeAdmin(int numeroAdmin, Admin *admin){
	
	FILE *archivo3;
    char existe;
 
    // Abre el archivo en modo lectura 
    archivo3 = fopen("admin.dat", "rb");
 
    if (archivo3 == NULL) { // Si no se pudo abrir el archivo, el valor de archivo es NULL 
        existe = 0;
 
    } else {
        existe = 0;
 
        // Se busca que el admin exista en el archivo 
        fread(&(*admin), sizeof(*admin), 1, archivo3);
        while (!feof(archivo3)) {
            if ((*admin).numero == numeroAdmin) {
                existe = 1;
                break;
            }
            fread(&(*admin), sizeof(*admin), 1, archivo3);
        }
 
        // Cierra el archivo 
        fclose(archivo3);
    }
 
    return existe;
	
	
} // cierre char existe admin 

char insertarAdmin(Admin admin){
	
	FILE *archivo3;
    char insercion;
 
    // Abre el archivo para agregar datos al final 
    archivo3 = fopen("admin.dat", "ab");    // Añade datos al final. Si el archivo no existe, es creado 
 
    if (archivo3 == NULL) { // Si no se pudo abrir el archivo, el valor de archivo es NULL 
        insercion = 0;
 
    } else {
        fwrite(&admin, sizeof(admin), 1, archivo3);
        insercion = 1;
 
        // Cierra el archivo 
        fclose(archivo3);
    }
 
    return insercion;
	
	
} // cierre insertar admin 

char eliminarAdmin(int numeroAdmin){
	
	FILE *archivo3;
    FILE *auxiliar2;
    Admin admin;
    char elimina;
 
    // Abre el archivo para leer
    archivo3 = fopen("admin.dat", "r+b");    // Modo lectura/escritura. Si el archivo no existe, es creado 
 
    if (archivo3 == NULL) { // Si no se pudo abrir el archivo, el valor de archivo es NULL 
        elimina = 0;
 
    } else {
        // Se busca el registro que se quiere borrar
        
 
        elimina = 0;
        fread(&admin, sizeof(admin), 1, archivo3);
        while (!feof(archivo3)) {
            if (admin.numero == numeroAdmin) {
                fseek(archivo3, ftell(archivo3) - sizeof(admin), SEEK_SET);
                admin.numero = CONTADOR;
                fwrite(&admin, sizeof(admin), 1, archivo3);
                elimina = 1;
                break;
            }
            fread(&admin, sizeof(admin), 1, archivo3);
        }
 
        // Cierra el archivo 
        fclose(archivo3);
    }
 
    return elimina;
	
	
} // cierre char eliminar admin 

char modificarAdmin(Admin admin){
	
	FILE *archivo3;
    char modifica;
    Admin admin2;
 
    // Abre el archivo para lectura/escritura 
    archivo3 = fopen("admin.dat", "rb+");
 
    if (archivo3 == NULL) { // Si no se pudo abrir el archivo, el valor de archivo es NULL 
        modifica = 0;
 
    } else {
        modifica = 0;
        fread(&admin2, sizeof(admin2), 1, archivo3);
        while (!feof(archivo3)){
            if (admin2.numero == admin.numero) {
                fseek(archivo3, ftell(archivo3) - sizeof(admin), SEEK_SET);
                fwrite(&admin, sizeof(admin), 1, archivo3);
                modifica = 1;
                break;
            }
            fread(&admin2, sizeof(admin2), 1, archivo3);
        }
 
        fclose(archivo3);
    }
 
    // Cierra el archivo 
    return modifica;
	
} // cierre char modificar admin 

char existeNombre(char const *ingresoAdmin, Admin *admin){
	
	FILE *archivo3;
    char existe;
 
    // Abre el archivo en modo lectura 
    archivo3 = fopen("admin.dat", "rb");
 
    if (archivo3 == NULL) { // Si no se pudo abrir el archivo, el valor de archivo es NULL 
        existe = 0;
 
    } else {
        existe = 0;
 
        // se busca si existe el nombre del admin en el archivo  
        fread(&(*admin), sizeof(*admin), 1, archivo3);
        while (!feof(archivo3)) {
        	if(strcmp(ingresoAdmin,(*admin).nAdmin)== 0){
                existe = 1;
                break;
            }
            fread(&(*admin), sizeof(*admin), 1, archivo3);
        }
 
        // Cierra el archivo 
        fclose(archivo3);
    }
 
    return existe;
	
	
	
} // cierre existe nombre

char existeClave(char const *ingresoClave, Admin *admin){
	
	FILE *archivo3;
    char existe;
 
    // Abre el archivo en modo lectura 
    archivo3 = fopen("admin.dat", "rb");
 
    if (archivo3 == NULL) { // Si no se pudo abrir el archivo, el valor de archivo es NULL 
        existe = 0;
 
    } else {
        existe = 0;
 
        // se busca si existe la contraseña en el archivo  
        fread(&(*admin), sizeof(*admin), 1, archivo3);
        while (!feof(archivo3)) {
        	if(strcmp(ingresoClave,(*admin).clave)== 0){
                existe = 1;
                break;
            }
            fread(&(*admin), sizeof(*admin), 1, archivo3);
        }
 
        // Cierra el archivo 
        fclose(archivo3);
    }
 
    return existe;
	
	
	
}// cierre existe clave

Admin *obtenerAdmins(int *n){
	
	FILE *archivo3;
    Admin admin;
    Admin *admins; 
    int i;
 
    // Abre el archivo en modo lectura 
    archivo3 = fopen("admin.dat", "rb");
 
    if (archivo3 == NULL) { // Si no puede abrir el archivo, el valor es NULL 
        *n = 0; 
        admins = NULL;
 
    } else {
 
        fseek(archivo3, 0, SEEK_END); // Posiciona el cursor al final del archivo 
        *n = ftell(archivo3) / sizeof(Admin); // numero de administradores almacenados en el archivo
        admins = (Admin *)malloc((*n) * sizeof(Admin)); // Se reserva memoria para todos los administradores almacenados en el archivo 
 
        // Se recorre el archivo secuencialmente 
        fseek(archivo3, 0, SEEK_SET); // Posiciona el cursor al principio del archivo 
        fread(&admin, sizeof(admin), 1, archivo3);
        i = 0;
        while (!feof(archivo3)) {
            admins[i++] = admin;
            fread(&admin, sizeof(admin), 1, archivo3);
        }
 
        // Cierra el archivo 
        fclose(archivo3);
    }
 
    return admins;
	
	
	
	
} // cierre obtener admins 

char guardarAdmins(){
	
	FILE *archivo3;
    char guardado;
    Admin *admins;
    int numeroAdmins;
    int i;
    
    admins = obtenerAdmins(&numeroAdmins); // Retorna un vector dinámico de administradores
 
    if (numeroAdmins == 0) {
        guardado = 0;
 
    } else {
        // Abre el archivo en modo texto para escritura 
        archivo3 = fopen("admins.txt", "w");
 
        if (archivo3 == NULL) { // Si no se pudo abrir el archivo, el valor de archivo es NULL 
            guardado = 0;
 
        } else {
            fprintf(archivo3,"\n\t\t     LISTADO DE ADMINISTRADORES REGISTRADOS \n\n");
 
            // Se recorre el vector dinámico de productos 
            
            for (i = 0; i < numeroAdmins; i++) {
                if (admins[i].numero != CONTADOR) {
                       
            fprintf(archivo3,"\tAdministrador número %d :\n\n", admins[i].numero);
            fprintf(archivo3,"\tNombre del Administrador: %s\n", admins[i].nAdmin); 
            fprintf(archivo3,"\tContraseña del Administrador: %s\n\n", admins[i].clave);
			 
               
       
                }
            }
           
            guardado = 1;
 
            // Cierra el archivo 
            fclose(archivo3);
        }
    }
 
    return guardado;
	
	 
} // cierre guardar admins

// NUEVAS FUNCIONES ADMIN 

void modificar_admin(){
	
Admin admin;
    int idAdmin;
    char repite = 1;
    char respuesta[MAX];
 
    do {
        system("cls");
        titulo();
        
        printf("\n\t\t\tMODIFICAR DATOS DE ADMINISTRADOR \n\n");
 
        // Se pide el número del administrador 
        printf("\n\tIngrese el número del administrador(1-2-3 etc): ");
        leecad(linea, MAX);
        sscanf(linea, "%d", &idAdmin);
 
        // Se verifica que el administrador exista
        if (existeAdmin(idAdmin, &admin)) {
 
            // Se muestran los datos del administrador
            printf("\n\tNombre del administrador: %s\n", admin.nAdmin);
            printf("\n\tclave del administrador: %s\n", admin.clave);
            
 
            printf("\n\tElija los datos a modificar\n");
 
            // Modificación del nombre del administrador
            printf("\n\tNombre del administrador actual: %s\n", admin.nAdmin);
            printf("\t¿Desea modificar el nombre del administrador? [S/N]: ");
            leecad(respuesta, MAX);
            if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0) {
                printf("\tNuevo nombre del administrador: ");
                leecad(admin.nAdmin, MAX);
                 
            }
            
            // Modificación de la contraseña 
            printf("\n\tClave actual del administrador: %s\n", admin.clave);
            printf("\t¿Desea modificar la clave del administrador? [S/N]: ");
            leecad(respuesta, MAX);
            if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0) {
                printf("\tNueva clave del administrador: ");
                leecad(admin.clave, MAX);
                 
            } // cierre 
            
            
            printf("\n\tEstá seguro que desea modificar los datos del administrador? [S/N]: ");
            leecad(respuesta, MAX);
 
            if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0) {
                // Se modifica el admin en el archivo 
                if (modificarAdmin(admin)) {
                    printf("\n\tLos datos del administrador fueron modificados correctamente\n");
 
                } else {
                    printf("\n\tOcurrió un error al intentar modificar los datos del administrador.\n");
                    printf("\tInténtelo mas tarde\n");
                }
            }
        } else {
            // El admin no existe
            printf("\n\tEl administrador %d no ha sido registrado.\n", idAdmin);
        }
 
        printf("\n\tDesea modificar algún otro administrador? [S/N]: ");
        leecad(respuesta, MAX);
 
        if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)) {
            repite = 0;
        }
 system("cls"); // limpiar pantalla 
    } while (repite);
 	
 	

} // cierre 

void eliminar_admin(){
	
	Admin admin;
    int idAdmin;
    char repite = 1;
    char respuesta[MAX];
 
    do {
        system("cls");
        titulo();
        
        printf("\n\t\t\t ELIMINAR ADMINISTRADOR \n\n");
 
        // Se pide el número del admin a eliminar 
        
        printf("\n\tIngrese el número del administrador(1-2-3 etc): ");
        leecad(linea, MAX);
        sscanf(linea, "%d", &idAdmin);
 
        // Se verifica que el admin exista
        if (existeAdmin(idAdmin, &admin)) {
 
            // Se muestran los datos del administrador
			printf("\tAdministrador %d :\n", admin.numero); 
			printf("\n\tNombre del administrador: %s\n", admin.nAdmin);
            printf("\n\tclave del administrador: %s\n", admin.clave);
            
			    
            printf("\n\t¿Seguro que desea eliminar el administrador? [S/N]: ");
            leecad(respuesta, MAX);
            if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0) {
                if (eliminarAdmin(idAdmin)) {
                    printf("\n\tAdministrador eliminado satisfactoriamente.\n");
                } else {
                    printf("\n\tEl administrador no pudo ser eliminado\n");
                }
            }
 
        } else {
            // El admin no existe
            printf("\n\tEl administrador %d no ha sido registrado.\n", idAdmin);
        }
 
        printf("\n\tDesea eliminar otro administrador? [S/N]: ");
        leecad(respuesta, MAX);
 
        if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)) {
            repite = 0;
        }
 system("cls"); // limpiar pantalla 
    } while (repite);
	
	
} // cierre eliminar admin 

void visualizar_admins(){
	
	Admin *admins;
    int numeroAdmins;
    int i;
    char respuesta[MAX];
 
    system("cls");
    titulo();
    
    admins = obtenerAdmins(&numeroAdmins); // Retorna un vector dinámico de productos 
 
    if (numeroAdmins == 0) {
        printf("\n\tEl archivo esta vacío.\n");
        printf("\n\tPresione cualquier tecla para volver al menú anterior.\n");
        system("pause>nul");
 
    } else {
        // titulo de la lista 
        printf("\n\t\t     LISTADO DE ADMINISTRADORES REGISTRADOS \n\n");
        
        // Se recorre el vector dinámico de productos 
        
        for (i = 0; i < numeroAdmins; i++) {
            if (admins[i].numero != CONTADOR) {
                
                	// Se muestran los datos del producto
             printf("\tAdministrador %d :\n\n", admins[i].numero); 
			printf("\tNombre del administrador: %s\n", admins[i].nAdmin);
            printf("\tclave del administrador: %s\n\n", admins[i].clave);
            
            }
        }
        
        printf("\n\t¿Desea guardar el listado en un archivo de texto? [S/N]: ");
        leecad(respuesta, MAX);
 
        if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0) {
            if (guardarAdmins()) {
                printf("\n\tEl listado fue guardado con éxito\n");
                printf("\n\tPresione cualquier tecla para volver al menú anterior\n");
            } else {
                printf("\n\tOcurrió un error al guardar el reporte\n");
            }
 
            system("pause>nul");
        }
    }
 	
 	
 	
 	system("cls"); // limpiar pantalla
	
	
} // cierre visualizar admins
