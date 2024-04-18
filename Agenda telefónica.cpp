/* Universidad de La Frontera
* Ingeniería Civil Electrónica
*
* ICC-202 PROGRAMACION DE COMPUTADORES
*
* Tarea 1
*
* Autor: Nicolas Oyarzo email: n.oyarzo02@ufromail.cl 
*
* Fecha: 12 de junio, 2020 
*
* Descripción general del programa:

Este programa realiza una simulacion de una agenda telefonica, en el cual se puede agregar,buscar,eliminar, modificar y listar los contactos ingresados,ademas de listar por grupo,traté de hacerlo lo mas amigable con el usuario posible.
las entradas de datos estan validadas.
Para generar el archivo indice.txt -> menu -> opcion 2. listar agenda -> responder 'si' a generar archivo de texto.


Obs:para ser transparante, en busqueda de nombre-apellido, las funciones estan funcionando al 100%, pero por ejemplo si ingreso nicolas oyarzo, no me encuentra por el apellido ( oyarzo ), pero si ingreso cualquier otro apellido, por ejemplo, nicolas rubilar, si me encuentra ( rubilar ), lo cual lo encuentro raro.
*/

//Librerias utilizadas
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//Macros
#define MAX 80
#define CONTADOR -1

//Estructuras

//Estructura que almacena los datos de un contacto 

struct registro{
	
	int id;
	char grupo[MAX];
	char nombre[MAX];
	char apellido[MAX];
	char telefono[MAX];
	char correo[MAX];
	
	
};

//Prototipos de funciones del menu 


void menu_de_agenda();
void menu_agregar_contacto();
void menu_buscar_contacto();
void menu_eliminar_contacto();
void menu_listar_contactos();
void menu_modificar_contacto();
void menu_listar_grupo();


// Variables
typedef struct registro Registro;


// variables del menu 
int opcion_usuario;
char temp[10];

// Funciones especificas creadas para manejar el archivo 

Registro *obtenerRegistros(int *n); // Obtiene un vector dinámico de contactos
char existeRegistro(int idRegistro, Registro *registro); // Busca si existe el contacto en el archivo de 'contactos'
char insertarRegistro(Registro registro); // Inserta un nuevo contacto al final del archivo 
char eliminarRegistro(int idRegistro); // Elimina un contacto mediante el identificador idRegistro del archivo 
char modificarRegistro(Registro registro); // Modifica los datos del contacto en el archivo 
char guardarContactos(); // Genera un archivo TXT con el indice de los contactos ( el indice contiene los datos de los contactos) 
char existe_nombre_contacto(char const *nomBusqueda, Registro *registro); // funcion para buscar un contacto por el nombre
char existe_apellido_contacto(char const *apellidoBusqueda, Registro *registro); // funcion para buscar un contacto por el apellido 
char existe_grupo(char const *buscarGrupo, Registro *registro);

// Función reutilizada de lectura de cadenas 
int leecad(char *cad, int n);
 
 // Variable para lectura de cadenas 
char linea[MAX];

int main(){
	

		do{
		
		menu_de_agenda();
	
	 switch(opcion_usuario){
	 	
	 	case 1: // Crear registro 
	 	printf("Usted ha seleccionado crear registro.\n");
	 	menu_agregar_contacto();
	 	break;
	 	
	 	case 2: // Listar agenda
	 	printf("Usted ha seleccionado listar agenda.\n");
	 	menu_listar_contactos();
	 	break;
	 	
	    case 3: // Editar un contacto 
	    printf("Usted ha seleccionado editar un contacto.\n");
	    menu_modificar_contacto();
	    break;
	    
	    case 4: // Buscar por apellido 
	    printf("Usted ha seleccionado buscar contactos.\n");
	    menu_buscar_contacto();
	    break;
	    
	    case 5: // Eliminar un contacto
	    printf("Usted ha seleccionado eliminar un contacto.\n");
	    menu_eliminar_contacto();
	    break;
	    
	    case 6: // listar por grupo 
	    printf("Usted ha seleccionado listar por grupo.\n");
	    menu_listar_grupo();
	    break;
	    
	    case 7 : // salir del programa
	 
	    default : printf("ERROR - opcion no valida - reintentar.\n"); // opcion incorrecta, pide al usuario reintentar para ingresar un numero valido de acuerdo al menu.
	 }
	 	
}while(opcion_usuario != 7); // si el usuario selecciona la opcion 7, el programa finaliza.
	
	
	return 0;
}


//-----------------------------------------------------------------------------------------------------------------------------
//Comienzo implementaciones funciones 

void menu_de_agenda(){
	
	printf("\tBIENVENIDO A LA AGENDA TELEFONICA\n\n"); 
	printf("Este programa simula el funcionamiento de una agenda.\n");
	printf("A continuacion se presentan las opciones disponibles.\n");
	printf("para continuar, seleccione la opcion deseada.\n\n");
	printf("Opcion 1 : Crear registro.\n");
	printf("Opcion 2 : Listar agenda.\n");
	printf("Opcion 3: Editar un contacto.\n");
	printf("Opcion 4: Buscar contactos.\n");
	printf("Opcion 5: Eliminar un contacto.\n");
	printf("Opcion 6: Listar por grupo.\n");
	printf("Opcion 7: Salir del programa.\n");
		fgets(temp,10,stdin); //leer la cadena, almacenar en la variable temp (temporal con un maximo de 10 caracteres) y viene de la entrada stdin.
opcion_usuario = atoi(temp); // transforma lo que se leyo nteriormente ( tipo char ) en un numero ( tipo int ).

} // cierre void menu agenda

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

//---------------------------------------------------------------------------------------------------------------------------

// Comienzo funciones de menu 

void menu_agregar_contacto(){
	
	 Registro registro;
    int idRegistro = 0;
    char repite = 1;
    char respuesta[MAX];
 
    do {
        system("cls");
        
        printf("\n\t\t\t>>> AGREGAR CONTACTO <<<\n");
 
        // Se pide el identificador del contacto para agregarlo
        printf("\n\tDigite el identificador del contacto(algun numero): ");
        leecad(linea, MAX);
        sscanf(linea, "%d", &idRegistro);
 
        // Se verifica que el contacto no haya sido almacenado anteriormente 
        if (!existeRegistro(idRegistro, &registro)) {
 
            registro.id = idRegistro;
 
            // Se piden los demás datos del contacto a insertar 
            
            printf("\n");
            printf("\tEste programa asocia los grupos con ciudades.\n");
            printf("\tSi no desea pertenecer a un grupo(ciudad), escriba 'desconocido'.\n\n");
            printf("\tdigite su ciudad: ");
            
            leecad(registro.grupo, MAX);
            
            printf("\tDigite su nombre: ");
            leecad(registro.nombre, MAX);
            
            printf("\tDigite su apellido: ");
            leecad(registro.apellido, MAX);
            
            printf("\tDigite su telefono: ");
            leecad(registro.telefono, MAX);
            
            printf("\tDigite su correo: ");
            leecad(registro.correo, MAX);
            
            // Se inserta el contacto en el archivo 
            if (insertarRegistro(registro)) {
                printf("\n\tEl contacto fue ingresado correctamente\n\n");
 
            } else {
                printf("\n\tOcurrió un error al intentar ingresar el contacto\n");
                printf("\tIntentelo de nuevo\n");
            }
        } else {
            // El contacto ya existe
            printf("\n\tEl contacto de identificador %d ya existe.\n", idRegistro);
            printf("\tNo puede ingresar dos contactos distintos con el mismo identificador.\n");
        }
 // pregunta al usuario si desea seguir ingresando contactos 
        printf("\n\tDesea seguir ingresando contactos? [s/n]: ");
        leecad(respuesta, MAX);
 
        if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)) {
            repite = 0;
        }
 
    } while (repite);
	
} // cierre void agregar contacto 

void menu_buscar_contacto(){ 
	
// variables para el menu 
	int opcion;
	char temp[10];
	
	
	Registro registro;
    char repite = 1;
    char respuesta[MAX];
    
    // variables para buscar por nombre/apellido
    char nomBusqueda[MAX];
    char apellidoBusqueda[MAX];
    
    //variable para buscar por identificador
    int idRegistro;

 

	
	do{
		
	printf("Ingrese el metodo de busqueda de contactos :\n");
	printf("Opcion 1 : busqueda por nombre.\n");
	printf("Opcion 2 : busqueda por apellido.\n");
	printf("Opcion 3 : busqueda por identificador.\n");
	printf("Opcion 4 : Cancelar busqueda ( sera redirigido al menu anterior).\n");
	printf("Digite su opcion.\n");
	fgets(temp,10,stdin);
	opcion = atoi(temp);
	
	switch(opcion){
		
		case 1: printf("Usted selecciono busqueda por nombre.\n\n");
		
		// Se pide el nombre del contacto a buscar 
		
		 printf("\tDigite el Nombre del contacto a buscar: ");
		 
		  leecad(linea, MAX);
        sscanf(linea, "%s", nomBusqueda);
		 
            // buscar coincidencia entre el nombre ingresado y algun nombre en el archivo 
            
            if(existe_nombre_contacto(nomBusqueda, &registro)){
           
           // si encuentra el contacto por nombre 
           
		   /* Se muestran los datos del contacto */
            printf("\n\tIdentificador del contacto: %d\n", registro.id);
            printf("\tGrupo del contacto: %s\n", registro.grupo);  
            printf("\tNombre del contacto: %s\n", registro.nombre);   
            printf("\tApellido del contacto: %s\n", registro.apellido);  
            printf("\tTelefono del contacto: %s\n", registro.telefono);  
			printf("\tCorreo del contacto: %s\n", registro.correo);
			
			
		}
		
		else{
			
			 // El contacto no existe 
            printf("\n\tEl nombre %s no está registrado.\n", nomBusqueda);
			
		}
			
			
			 printf("\n\tDesea seguir buscando algún contacto? [S/N]: ");
        leecad(respuesta, MAX);
 
        if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)) {
            repite = 0;
        }
		
		break;
		
		case 2: printf("Usted selecciono busqueda por apellido.\n\n");
		
			
			 printf("\tDigite el apellido del contacto a buscar: ");
			 
			 leecad(linea, MAX);
        sscanf(linea, "%s", apellidoBusqueda);
           
            if(existe_apellido_contacto(apellidoBusqueda, &registro)){
            
           // si pilla el contacto por apellido 
           
		   /* Se muestran los datos del contacto */
            printf("\n\tIdentificador del contacto: %d\n", registro.id);
            printf("\tGrupo del contacto: %s\n", registro.grupo);  
            printf("\tNombre del contacto: %s\n", registro.nombre);   
            printf("\tApellido del contacto: %s\n", registro.apellido);  
            printf("\tTelefono del contacto: %s\n", registro.telefono);  
			printf("\tCorreo del contacto: %s\n", registro.correo);
			
			
		}
		else{
				 // El contacto no existe 
            printf("\n\tEl apellido %s no está registrado.\n", apellidoBusqueda);
			
		}
		
			 printf("\n\tDesea seguir buscando algún contacto? [S/N]: ");
        leecad(respuesta, MAX);
 
        if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)) {
            repite = 0;
        }
	
		break;
		
		case 3: printf("Usted selecciono busqueda por identificador.\n\n");
		
		// Se pide el identificador del contacto a buscar 
        printf("\n\tIdentificador del contacto: ");
        leecad(linea, MAX);
        sscanf(linea, "%d", &idRegistro);
 
        // se verifica que el contacto a buscar exista
        if (existeRegistro(idRegistro, &registro)) {
 
 
            // Se muestran los datos del contacto 
            printf("\n\tIdentificador del contacto: %d\n", registro.id);
            printf("\tGrupo del contacto: %s\n", registro.grupo);  
            printf("\tNombre del contacto: %s\n", registro.nombre);   
            printf("\tApellido del contacto: %s\n", registro.apellido);  
            printf("\tTelefono del contacto: %s\n", registro.telefono);  
			printf("\tCorreo del contacto: %s\n", registro.correo);
 
        } else {
            // El contacto no existe 
            printf("\n\tEl contacto de identificador %d no existe.\n", idRegistro);
        }
 
        printf("\n\tDesea seguir buscando algún contacto? [S/N]: ");
        leecad(respuesta, MAX);
 
        if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)) {
            repite = 0;
        }
		
		break;
		
		
		
		case 4: printf("Usted ha seleccionado volver al menu anterior.\n");
		
		repite = 0; // para salir del bucle 
		
		break;
		
		default: printf("Opcion incorrecta.\n");
		
		break;
	}
		
		
	}while(repite);
	

} // cierre void buscar contacto 

void menu_eliminar_contacto(){
	
	Registro registro;
    int idRegistro;
    char repite = 1;
    char respuesta[MAX];
 
    do {
        system("cls");
        
        printf("\n\t\t\t>>> ELIMINAR CONTACTO POR IDENTIFICADOR <<<\n");
 
        // Se pide el identificador del contacto a eliminar 
        printf("\n\tIdentificador del contacto: ");
        leecad(linea, MAX);
        sscanf(linea, "%d", &idRegistro);
 
        // Se verifica que el contacto a buscar, exista 
        
        if (existeRegistro(idRegistro, &registro)) {
 
            // Se muestran los datos del contacto 
            printf("\n\tIdentificador del contacto: %d\n", registro.id);
            printf("\tGrupo del contacto: %s\n", registro.grupo);  
            printf("\tNombre del contacto: %s\n", registro.nombre);   
            printf("\tApellido del contacto: %s\n", registro.apellido);  
            printf("\tTelefono del contacto: %s\n", registro.telefono);  
			printf("\tCorreo del contacto: %s\n", registro.correo);  
			
            printf("\n\tSeguro que desea eliminar el contacto? [s/n]: ");
            leecad(respuesta, MAX);
            if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0) {
                if (eliminarRegistro(idRegistro)) {
                    printf("\n\tContacto eliminado exitosamente.\n");
                } else {
                    printf("\n\tEl contacto no pudo ser eliminado\n");
                }
            }
 
        } else {
            /* El contacto no existe */
            printf("\n\tEl contacto de identificador %d no existe.\n", idRegistro);
        }
 
        printf("\n\tDesea eliminar otro contacto? [s/n]: ");
        leecad(respuesta, MAX);
 
        if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)) {
            repite = 0;
        }
 
    } while (repite);
	
	
} // cierre void eliminar contacto 

void menu_listar_contactos(){ 
	

	
	
	Registro *registros;
    int numeroContactos;
    int i;
    char respuesta[MAX];
 
    system("cls");
    
   // funcion 
    registros = obtenerRegistros(&numeroContactos); // Retorna la cantidad de contactos
 
    if (numeroContactos == 0) {
        printf("\n\tEl archivo esta vacio\n");
        printf("\n\tIngrese datos para poder listar.\n");
        printf("\n\tPRESIONE ENTER PARA VOLVER AL MENU\n");
        system("pause>nul");
 
    } 
    
	
	else {
		// titulo de la lista 
        printf("\n\t\t    >>> LISTADO DE CONTACTOS REGISTRADOS <<<\n\n");
     
        // Se recorre el vector dinámico de contactos 
        
        for (i = 0; i < numeroContactos; i++) {
            if (registros[i].id != CONTADOR) {
            	
            	// Se muestran los datos del contacto 
            printf("\n\tIdentificador del contacto: %d\n", registros[i].id);
            printf("\tGrupo del contacto: %s\n", registros[i].grupo);  
            printf("\tNombre del contacto: %s\n", registros[i].nombre);   
            printf("\tApellido del contacto: %s\n", registros[i].apellido);  
            printf("\tTelefono del contacto: %s\n", registros[i].telefono);  
			printf("\tCorreo del contacto: %s\n", registros[i].correo);  
            
            
           
            }
        }
       
        printf("\n\tDesea guardar en un archivo de texto? [S/N]: ");
        leecad(respuesta, MAX);
 
 // funcion 
        if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0) {
            if (guardarContactos()) {
                printf("\n\tEl indice fue guardado con exito\n");
                printf("\n\tPresione enter para continuar\n");
            } else {
                printf("\n\tOcurrió un error al guardar el indice\n");
            }
 
            system("pause>nul");
        }
    }
	
	
} // cierre void listar contactos

void menu_modificar_contacto(){
	
	Registro registro;
    int idRegistro;
    char repite = 1;
    char respuesta[MAX];
 
    do {
        system("cls");
        
        printf("\n\t\t\t==> MODIFICAR CONTACTO POR IDENTIFICADOR <==\n");
 
        /* Se pide el identificador del contacto a modificar */
        printf("\n\tIdentificador del contacto: ");
        leecad(linea, MAX);
        sscanf(linea, "%d", &idRegistro);
 
        /* Se verifica que el contacto a buscar exista */
        if (existeRegistro(idRegistro, &registro)) {
 
            // Se muestran los datos del contacto 
            
            printf("\n\tGrupo del contacto: %s\n", registro.grupo);
            printf("\n\tNombre del contacto: %s\n", registro.nombre);
            printf("\n\tApellido del contacto: %s\n", registro.apellido);
            printf("\n\tTelefono del contacto: %s\n", registro.telefono);
            printf("\n\tCorreo del contacto: %s\n", registro.correo);
            
            printf("\n\tSeleccione los datos a modificar\n");
 
            // Modificación del grupo del contacto 
            printf("\n\tGrupo del contacto actual: %s\n", registro.grupo);
            printf("\tDesea modificar el grupo del contacto? [S/N]: ");
            leecad(respuesta, MAX);
            if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0) {
                printf("\tNuevo grupo del contacto: ");
                leecad(registro.grupo, MAX);
            }
            
             /* Modificación del nombre del contacto */
            printf("\n\tNombre del contacto actual: %s\n", registro.nombre);
            printf("\tDesea modificar el nombre del contacto? [S/N]: ");
            leecad(respuesta, MAX);
            if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0) {
                printf("\tNuevo nombre del contacto: ");
                leecad(registro.nombre, MAX);
            }
            
             /* Modificación del apellido del contacto */
            printf("\n\tApellido del contacto actual: %s\n", registro.apellido);
            printf("\tDesea modificar el apellido del contacto? [S/N]: ");
            leecad(respuesta, MAX);
            if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0) {
                printf("\tNuevo apellido del contacto: ");
                leecad(registro.apellido, MAX);
            }
            
             /* Modificación del telefono del contacto */
            printf("\n\tTelefono del contacto actual: %s\n", registro.telefono);
            printf("\tDesea modificar el telefono del contacto? [S/N]: ");
            leecad(respuesta, MAX);
            if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0) {
                printf("\tNuevo telefono del contacto: ");
                leecad(registro.telefono, MAX);
            }
            
             /* Modificación del correo del contacto */
            printf("\n\tCorreo del contacto actual: %s\n", registro.correo);
            printf("\tDesea modificar el correo del contacto? [S/N]: ");
            leecad(respuesta, MAX);
            if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0) {
                printf("\tNuevo correo del contacto: ");
                leecad(registro.correo, MAX);
            }
            
            printf("\n\tEstá seguro que desea modificar los datos del contacto? [S/N]: ");
            leecad(respuesta, MAX);
 
            if (strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0) {
                /* Se modifica el contacto en el archivo */
                if (modificarRegistro(registro)) {
                    printf("\n\tEl contacto fue modificado correctamente\n");
 
                } else {
                    printf("\n\tOcurrió un error al intentar modificar el contacto\n");
                    printf("\tInténtelo mas tarde\n");
                }
            }
        } else {
            /* El contacto no existe */
            printf("\n\tEl contacto de identificador %d no existe.\n", idRegistro);
        }
 
        printf("\n\tDesea modificar algun otro contacto? [S/N]: ");
        leecad(respuesta, MAX);
 
        if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)) {
            repite = 0;
        }
 
    } while (repite);
	
	
} // cierre void modificar contacto 

void menu_listar_grupo(){ 

	
	// variables para el menu 
	int opcion;
	char temp[10];
	
	Registro registro;
    char repite = 1;
    char respuesta[MAX];
    
    //variables para filtrar grupo
    char buscarGrupo[MAX];
    
    	do{
		
	
	printf("Opcion 1 : Listar por grupo.\n");
	printf("Opcion 2 : Cancelar listado ( sera redirigido al menu anterior).\n\n");
	printf("Digite su opcion de listado.\n");
	fgets(temp,10,stdin);
	opcion = atoi(temp);
	
	switch(opcion){
		
		case 1: printf("\tDigite el grupo que desea buscar.\n");
		        printf("\tPara contactos sin grupo, digite 'desconocido'\n");
		
		  leecad(linea, MAX);
        sscanf(linea, "%s", buscarGrupo);
		 
            // buscar coincidencia entre el grupo ingresado y algun grupo en el archivo 
            
            if(existe_grupo(buscarGrupo, &registro)){
           
           // si encuentra el grupo se muestran los datos del contacto 
		  
            printf("\n\tIdentificador del contacto: %d\n", registro.id);
            printf("\tGrupo del contacto: %s\n", registro.grupo);  
            printf("\tNombre del contacto: %s\n", registro.nombre);   
            printf("\tApellido del contacto: %s\n", registro.apellido);  
            printf("\tTelefono del contacto: %s\n", registro.telefono);  
			printf("\tCorreo del contacto: %s\n", registro.correo);
			
			
		}
		
		else{
			
			 // El grupo no existe 
            printf("\n\tEl grupo %s no está registrado.\n", buscarGrupo);
            printf("\n\tIntroduzca un contacto con el grupo respectivo para que sea registrado.\n");
			
		}
			
			
			 printf("\n\tDesea seguir listando por grupo? [S/N]: ");
        leecad(respuesta, MAX);
 
        if (!(strcmp(respuesta, "S") == 0 || strcmp(respuesta, "s") == 0)) {
            repite = 0;
        }
		
		break;
		
	
		case 2: printf("Usted ha seleccionado volver al menu anterior.\n");
		
		repite = 0; // para salir del bucle 
		
		break;
		
		default: printf("Opcion incorrecta.\n");
		
		break;
	}
		
		
	}while(repite);
	
	
	
} // cierre void listar por grupo 



//----------------------------------------------------------------------------------------------------------------------------

// Comienzo funciones especificas

char existeRegistro(int idRegistro, Registro *registro){

FILE *archivo;
    char existe;
 
    // Abre el archivo en modo lectura 
    archivo = fopen("contactos.dat", "rb");
 
    if (archivo == NULL) { /* Si no se pudo abrir el archivo, el valor de archivo es NULL */
        existe = 0;
 
    } else {
        existe = 0;
 
        /* Se busca el contacto cuyo identificador coincida con idRegistro */
        fread(&(*registro), sizeof(*registro), 1, archivo);
        while (!feof(archivo)) {
            if ((*registro).id == idRegistro) {
                existe = 1;
                break;
            }
            fread(&(*registro), sizeof(*registro), 1, archivo);
        }
 
        /* Cierra el archivo */
        fclose(archivo);
    }
 
    return existe;



} // cierre void existe registro 



Registro *obtenerRegistros(int *n){
	
	FILE *archivo;
    Registro registro;
    Registro *registros; /* Vector dinámico de contactos */
    int i;
 
    /* Abre el archivo en modo lectura */
    archivo = fopen("contactos.dat", "rb");
 
    if (archivo == NULL) { /* Si no se pudo abrir el archivo, el valor de archivo es NULL */
        *n = 0; /* No se pudo abrir. Se considera n  */
        registros = NULL;
 
    } else {
 
        fseek(archivo, 0, SEEK_END); // Posiciona el cursor al final del archivo 
        *n = ftell(archivo) / sizeof(Registro); // numero de contactos almacenados en el archivo. 
        registros = (Registro *)malloc((*n) * sizeof(Registro)); // Se reserva memoria para todos los contactos almacenados en el archivo 
 
        // Se recorre el archivo secuencialmente 
        fseek(archivo, 0, SEEK_SET); // Posiciona el cursor al principio del archivo 
        fread(&registro, sizeof(registro), 1, archivo);
        i = 0;
        while (!feof(archivo)) {
            registros[i++] = registro;
            fread(&registro, sizeof(registro), 1, archivo);
        }
 
        // Cierra el archivo 
        fclose(archivo);
    }
 
    return registros;
	
	
	
} // cierre obtener registros


char insertarRegistro(Registro registro){
	FILE *archivo;
    char insercion;
 
    /* Abre el archivo para agregar datos al final */
    archivo = fopen("contactos.dat", "ab");    /* Añade datos al final. Si el archivo no existe, es creado */
 
    if (archivo == NULL) { /* Si no se pudo abrir el archivo, el valor de archivo es NULL */
        insercion = 0;
 
    } else {
        fwrite(&registro, sizeof(registro), 1, archivo);
        insercion = 1;
 
        /* Cierra el archivo */
        fclose(archivo);
    }
 
    return insercion;
	
	
	
} // cierre insertar registro 

char eliminarRegistro(int idRegistro){
	
	 FILE *archivo;
    FILE *auxiliar;
    Registro registro;
    char elimina;
 
    // Abre el archivo para leer 
    archivo = fopen("contactos.dat", "r+b");    // Modo lectura/escritura. Si el archivo no existe, es creado 
 
    if (archivo == NULL) { // Si no se pudo abrir el archivo, el valor de archivo es NULL 
        elimina = 0;
 
    } else {
    	//se busca el contacto que se quiere borrar
    	//si encuentra el contacto, se situa en su posicion mediante la funcion 'fseek'
    	
        elimina = 0;
        fread(&registro, sizeof(registro), 1, archivo);
        while (!feof(archivo)) {
            if (registro.id == idRegistro) {
                fseek(archivo, ftell(archivo) - sizeof(registro), SEEK_SET);
                registro.id = CONTADOR;
                fwrite(&registro, sizeof(registro), 1, archivo);
                elimina = 1;
                break;
            }
            fread(&registro, sizeof(registro), 1, archivo);
        }
 
        /* Cierra el archivo */
        fclose(archivo);
    }
 
    return elimina;
	
	
} // cierre eliminar registro 

char modificarRegistro(Registro registro){
	
	FILE *archivo;
    char modifica;
    Registro registro2;
 
    /* Abre el archivo para lectura/escritura */
    archivo = fopen("contactos.dat", "rb+");
 
    if (archivo == NULL) { /* Si no se pudo abrir el archivo, el valor de archivo es NULL */
        modifica = 0;
 
    } else {
        modifica = 0;
        fread(&registro2, sizeof(registro2), 1, archivo);
        while (!feof(archivo)) {
            if (registro2.id == registro.id) {
                fseek(archivo, ftell(archivo) - sizeof(registro), SEEK_SET);
                fwrite(&registro, sizeof(registro), 1, archivo);
                modifica = 1;
                break;
            }
            fread(&registro2, sizeof(registro2), 1, archivo);
        }
 
        fclose(archivo);
    }
 
    /* Cierra el archivo */
    return modifica;
	
	
	
} // cierre modificar registro 

char guardarContactos(){ 
	
	FILE *archivo;
    char guardado;
    Registro *registros;
    int numeroContactos;
    int i;

    registros = obtenerRegistros(&numeroContactos); // Retorna un vector dinámico de contactos 
 
    if (numeroContactos == 0) {
        guardado = 0;
 
    } else {
        /* Abre el archivo en modo texto para escritura */
        archivo = fopen("indice.txt", "w");
 
        if (archivo == NULL) { /* Si no se pudo abrir el archivo, el valor de archivo es NULL */
            guardado = 0;
 
        } else {
        	
        fprintf(archivo,"\n\t\t    >>> LISTADO DE CONTACTOS REGISTRADOS <<<\n\n");
        
          // actualizar registros en el archivo txt 
            for (i = 0; i < numeroContactos; i++) {
                if (registros[i].id != CONTADOR) {
                	
                	
                		// Se muestran los datos del contacto 
            fprintf(archivo,"\n\tIdentificador del contacto: %d\n", registros[i].id);
            fprintf(archivo,"\tGrupo del contacto: %s\n", registros[i].grupo);  
            fprintf(archivo,"\tNombre del contacto: %s\n", registros[i].nombre);   
            fprintf(archivo,"\tApellido del contacto: %s\n", registros[i].apellido);  
            fprintf(archivo,"\tTelefono del contacto: %s\n", registros[i].telefono);  
			fprintf(archivo,"\tCorreo del contacto: %s\n", registros[i].correo);  
                	
                	
                }
            }
            guardado = 1;
 
            //Cierra el archivo 
            fclose(archivo);
        }
    }
 
    return guardado;
	
	
	
	
} // cierre guardar contactos 

char existe_nombre_contacto(char const *nomBusqueda, Registro *registro){
	

FILE *archivo;
    char existe;
 
    /* Abre el archivo en modo lectura */
    archivo = fopen("contactos.dat", "rb");
 
    if (archivo == NULL) { /* Si no se pudo abrir el archivo, el valor de archivo es NULL */
        existe = 0;
 
    } else {
        existe = 0;
 
        // se busca si hay algun contacto con el nombre ingresado a buscar 
        fread(&(*registro), sizeof(*registro), 1, archivo);
        while (!feof(archivo)) {
        	if(strcmp(nomBusqueda,(*registro).nombre)== 0){
                existe = 1;
                break;
            }
            fread(&(*registro), sizeof(*registro), 1, archivo);
        }
 
        /* Cierra el archivo */
        fclose(archivo);
    }
 
    return existe;



} // cierre char existe nombre contacto 

char existe_apellido_contacto(char const *apellidoBusqueda, Registro *registro){
	
	FILE *archivo;
    char existe;
 
    /* Abre el archivo en modo lectura */
    archivo = fopen("contactos.dat", "rb");
 
    if (archivo == NULL) { /* Si no se pudo abrir el archivo, el valor de archivo es NULL */
        existe = 0;
 
    } else {
        existe = 0;
 
        // se busca si hay algun contacto con el apellido ingresado a buscar 
        fread(&(*registro), sizeof(*registro), 1, archivo);
        while (!feof(archivo)) {
        	if(strcmp(apellidoBusqueda,(*registro).apellido)== 0){
                existe = 1;
                break;
            }
            fread(&(*registro), sizeof(*registro), 1, archivo);
        }
 
        /* Cierra el archivo */
        fclose(archivo);
    }
 
    return existe;
	
	
	

} // cierre char existe apellido contacto 


char existe_grupo(char const *buscarGrupo, Registro *registro){
	
		FILE *archivo;
    char existe;
 
    /* Abre el archivo en modo lectura */
    archivo = fopen("contactos.dat", "rb");
 
    if (archivo == NULL) { /* Si no se pudo abrir el archivo, el valor de archivo es NULL */
        existe = 0;
 
    } else {
        existe = 0;
 
        // se busca si hay algun contacto con el nombre ingresado a buscar 
        fread(&(*registro), sizeof(*registro), 1, archivo);
        while (!feof(archivo)) {
        	if(strcmp(buscarGrupo,(*registro).grupo)== 0){
                existe = 1;
                break;
            }
            fread(&(*registro), sizeof(*registro), 1, archivo);
        }
 
        /* Cierra el archivo */
        fclose(archivo);
    }
 
    return existe;


	
	
} // cierre buscar grupo 

//-----------------------------------------------------------------------------------------------------------------------------------

/*
Comienzo de explicacion de funciones de menu ( voids) 

Nombre de la función: menu_de_agenda
-Tipo de función: void	
-Parámetros: sin parmetros ( void ) 
-Dato de retorno: sin retorno ( void ) 
-Descripción de la función: Esta funcion da el saludo inicial e imprime por pantalla el menu principal de la agenda.


Nombre de la función: menu_agregar_contacto
-Tipo de función: void	
-Parámetros: sin parmetros ( void ) 
-Dato de retorno: sin retorno ( void ) 
-Descripción de la función: Esta funcion le solicita al usuario llenar los campos solicitados ( id - grupo - nombre - apellido - telefono - correo), al terminar de llenar estos datos, los almacena en el archivo 'contactos.dat'. 
la funcion termina cuando el usuario ya no quiere ingresar mas contactos.

Nombre de la función: menu_buscar_contacto
-Tipo de función: void	
-Parámetros: sin parmetros ( void ) 
-Dato de retorno: sin retorno ( void ) 
-Descripción de la función: Esta funcion imprime el menu de busqueda ( buscar por nombre, apellido o identificador ), luego de que el usuario ingrese su preferencia, se hace una comparacion entre el nombre ingresado a buscar, con algun nombre en el archivo, si coinciden, imprime por pantalla todos los datos de ese contacto.

Nombre de la función: menu_eliminar_contacto
-Tipo de función: void	
-Parámetros: sin parmetros ( void ) 
-Dato de retorno: sin retorno ( void ) 
-Descripción de la función: Esta funcion solicita al usuario ingresar el identidicador ( id ) del contacto a borrar, si el id existe ( pertenece a algun contacto), la funcion elimina los datos del contacto.

Nombre de la función: menu_listar_contactos
-Tipo de función: void	
-Parámetros: sin parmetros ( void ) 
-Dato de retorno: sin retorno ( void ) 
-Descripción de la función: Esta funcion imprime por pantalla todos los contactos ingresados hasta el momento.

Nombre de la función: menu_modificar_contacto
-Tipo de función: void	
-Parámetros: sin parmetros ( void ) 
-Dato de retorno: sin retorno ( void ) 
-Descripción de la función: Esta funcion solicita al usuario ingresar el identificador ( id ) del contacto a modificar, si el id existe ( pertenece a algun contacto), se le pregunta al usuario que datos del contacto desea modificar, al final salta una confirmacion de si realmente quiere modificar el contacto, si presiona si ( s ) , el contacto es modificado.

Nombre de la función: menu_listar_grupo
-Tipo de función: void	
-Parámetros: sin parmetros ( void ) 
-Dato de retorno: sin retorno ( void ) 
-Descripción de la función: Esta funcion lista por grupo ( el grupo lo define el usuario ).


--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Comienzo de explicacion de funciones especificas

Nombre de la función: Registro *obtenerRegistros
-Tipo de función: struct 
-Parámetros: *n de tipo int 
-Dato de retorno: registros
-Descripción de la función: Esta funcion bbtiene un vector dinámico de contactos, es decir, indica cuantos contactos hay hasta el momento ( recorriendo el archivo ), ademas de reservar memoria para cada uno.

Nombre de la función: existeRegistro
-Tipo de función: char
-Parámetros: idRegistro de tipo int, Registro *registro ( struct ).
-Dato de retorno: existe de tipo char 
-Descripción de la función: Esta funcion busca si existe el contacto en el archivo de 'contactos'

Nombre de la función: insertarRegistro
-Tipo de función: char
-Parámetros: Registro registro ( struct ) 
-Dato de retorno: insercion de tipo char 
-Descripción de la función: Esta funcion inserta un nuevo contacto al final del archivo 

Nombre de la función: eliminarRegistro
-Tipo de función: char
-Parámetros: idRegistro de tipo int
-Dato de retorno: elimina de tipo char 
-Descripción de la función: Esta funcion elimina un contacto mediante el identificador idRegistro del archivo 

Nombre de la función: modificarRegistro
-Tipo de función: char
-Parámetros: Registro registro
-Dato de retorno: modifica de tipo char
-Descripción de la función: Esta funcion modifica los datos del contacto en el archivo 

Nombre de la función: guardarContactos
-Tipo de función: void
-Parámetros: sin parametros ( void ) 
-Dato de retorno: guardado de tipo char 
-Descripción de la función: Esta funcion genera un archivo TXT con el indice de los contactos ( el indice contiene los datos de los contactos) 

Nombre de la función: existe_nombre_contacto
-Tipo de función: char
-Parámetros: *nomBusqueda de tipo char const, Registro *registro ( struct ) 
-Dato de retorno: existe de tipo char 
-Descripción de la función: Esta funcion realiza una busqueda por nombre, comparando el nombre ingresado por el usuario, con algun nombre del archivo, si coinciden, imprime todos los datos del contacto.


Nombre de la función: existe_apellido_contacto
-Tipo de función: char
-Parámetros: *apellidoBusqueda de tipo char const, Registro *registro ( struct ) 
-Dato de retorno: existe de tipo char 
-Descripción de la función: Esta funcion realiza una busqueda por apellido, comparando el apellido ingresado por el usuario, con algun apellido del archivo, si coinciden, imprime todos los datos del contacto.


Nombre de la función: existe_grupo
-Tipo de función: char
-Parámetros: *buscarGrupo de tipo char const, Registro *registro ( struct ) 
-Dato de retorno: existe de tipo char 
-Descripción de la función: Esta funcion realiza una busqueda por grupo, comparando el grupo ingresado por el usuario, con algun grupo del archivo, si coinciden, imprime todos los datos del contacto.


Fin Explicacion de funciones 

*/ 


















