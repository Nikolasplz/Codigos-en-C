/* Universidad de La Frontera
*  Ingeniería Civil Telemática
*
* IIE344-1: ESTRUCTURA DE DATOS Y ALGORITMOS
*
* Tarea 3
*
* Autor: Nicolás Oyarzo   email: n.oyarzo02@ufromail.cl
*
* Fecha: 04 de marzo,2021.
*
* Descripción general del programa:
Este programa consiste en imprimir por pantalla un arbol genealógico mediante un TDA propio, con diversas opciones de busqueda para datos almacenados previamente.
Entre esas opciones, podemos encontrar:
-Buscar (mostrar los datos) el individuo más longevo de la familia.
-Buscar los hijos de una determinada persona.
-Buscar el padre de una determinada persona.
-Saber a qué generación pertenece una persona.
-Modificar los datos de un familiar, buscando por nombre.
-Mostrar los antecesores de una determinada persona.
-Saber cuántos familiares aún se encuentran con vida.
*/

//Librerias Utilizadas
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<locale.h> // palabras con tilde
#include<conio.h>	

//	manejo de cadenas
char*jdominCharsInts(const int);//designa un espacio de memoria 
char*jdominChars(const char*);//designa un espacio de memoria para una cadena y la retorna en un char*.
char*BuscarAlias=jdominCharsInts(15);///buffer de reserva para cadena.

// Estructuras utilizadas en el programa 

struct Fecha{///almacena la fecha de un familiar
int Year; // año = year, ya que el compilador no acepta la "ñ"
int Mes; // mes de nacimiento 
int dia; // dia de nacimiento 
	void print(){ printf("\n\t\t>%d/%d/%d<",Year,Mes,dia); }//imprimir los datos de nacimiento 
	void printDecay(bool f){ if(!f)print(); else printf("\n\t\t<\"\" \"\" \"\">"); }
	void setup(int A,int B, int C){ Year=A; Mes=B; dia=C; }//sin validaciones para fechas realistas.
	Fecha(int A,int B, int C){ setup(A,B,C); }//constructor especializado.
	Fecha(){ setup(1900,1,1); }//constructor por defecto.
};

struct Dato{
	
char*Nombre; //nombre del sujeto.
char Estado; //estado de vida -> 0 significa que no está vivo 
char Raiz; //raiz del arbol
Fecha muerte;//fecha de muerte
Fecha nacimiento;//fecha de nacimiento 

	// funciones para imprimir
	void printjViewEdadTrue(Dato*T){ if(viewEdadTrue(T))printf("\n\t%s es mayor",Nombre); else printf("\n\t%s es mayor",T->Nombre); }//imprimir familiar
	void printnacimiento(){ nacimiento.print(); }//imprimir dato.
	void printmuerte(){ muerte.printDecay(viewStateConVida()); }//imprime por pantalla la fecha de muerte, en el caso que siga vivo imprime comillas. 
	void printjState(){ printf("\t<%s>",Nombre); printnacimiento(); printmuerte(); }

	// funciones condicionales
	bool viewEdadTrueJoven(Dato*T){ if(nacimiento.Year<T->nacimiento.Year)return true; else return false; }///determina quien es mas joven 
	bool viewEdadTrue(Dato*T){ return viewEdadTrueYear(T); }///determina quien es mayor
	///comparar mayoria por año
	bool viewEdadTrueYear(Dato*T){ if(nacimiento.Year<T->nacimiento.Year)return true; else { if(nacimiento.Year==T->nacimiento.Year)return viewEdadTrueMes(T); else return false; } }
	bool viewEdadTrueMes(Dato*T){ if(nacimiento.Mes<T->nacimiento.Mes)return true; else { if(nacimiento.Mes==T->nacimiento.Mes)return viewEdadTrueDia(T); else return false; } }
	bool viewEdadTrueDia(Dato*T){ if(nacimiento.dia<T->nacimiento.dia)return true; else { if(nacimiento.dia>=T->nacimiento.dia)return false; return true; } }

	bool viewStatePushSetl(Dato*S){ if(S==this)return true; else return false; }
	bool viewStateConVida(){ if(Estado)return true; else return false; }

	// Funciones acciones:
	void exeSinVidaOff(){ Estado=1; muerte.setup(0,0,0); }
	void exeSinVida(int A,int B, int C){ Estado=0; muerte.setup(A,B,C); }
	void familiarVivo(int A,int B, int C){ nacimiento.setup(A,B,C); }
	void setAlias(const char*nuevo){ if(Nombre)free(Nombre); Nombre=jdominChars(nuevo); }

	// constructores
	Dato(const char*stName,int A,int B, int C){
		Nombre=jdominChars(stName);//nombre del familiar
		Estado=1;//estado actual vivo/muerto
		familiarVivo(A,B,C);//asigna la fecha de nacimiento 
		exeSinVidaOff();//asigna la fecha de muerte
		}
	Dato(const Dato*f){
		Nombre=jdominChars(f->Nombre); //nombre del familiar
		Estado=f->Estado; //estado actual vivo/muerto
		familiarVivo(f->nacimiento.Year,f->nacimiento.Mes,f->nacimiento.dia); //asigna la fecha de nacimiento
		muerte.setup(f->muerte.Year,f->muerte.Mes,f->muerte.dia); //asigna la fecha de muerte
		}
};

// estructura de datos que almacena una lista enlazada simple 
struct Nodo{
Dato*Id;     // numero de identidad
Nodo*NodoDer;  //siguiente hijo a la derecha
Nodo*NodoIzq; //siguiente hijo a la izquierda

// funciones libres
void printHijos(){

			if(!NodoDer&&!NodoIzq){
		printf("\t\t%s es una hoja.\n",Id->Nombre);
		return;
	}

	if(NodoIzq){
		printf("\t\tHijo/a izquierdo/a : \n\n");
			//printf("\t\tHijo/a izquierdo/a %p\n",NodoIzq);
			NodoIzq->Id->printjState();
	}
	else printf("\t\tSin hijo/a hacia la izquierda.\n\n");
		if(NodoDer){
			printf("\n");
			printf("\t\tHijo/a derecho/a : \n\n");
				//printf("\t\tHijo derecho : %s\n",NodoDer);
				NodoDer->Id->printjState();
		}
		else printf("\t\tSin hijo/a hacia la derecha\n\n");
	}
}; // cierre 

// declaración del arbol 
Nodo*Arbol=NULL;
Nodo*jBeras=NULL;

// Prototipos de funciones
void menu_bienvenida();
void titulo();
void agregar_familiares();

// Funciones recicladas para validad caracteres 
size_t ValidarCadenaOutRangeBase(int,int,int);
void ValidarCadenaOutRangeDecimalTrue(int&);
void ValidarCadenaOutRangeMinusculaTrue(char&);
void ValidarCadenaOutRangeMayusculaTrue(char&);
void ValidarCadenaBase(char*);
char*ValidarCadenaOutRangeMinusculaTrueReturn(const char*);
char*ValidarCadenaOutRangeMayusculaTrueReturn(const char*);
int ValidarCadenaEqual(const char*,const char*);

// Elementos de un arbol
Nodo*ArbolNew(Dato*);
void ArbolAgregar(Nodo*&,Dato*);
void ArbolAgregarIzq(Nodo*&,Dato*);
void ArbolAgregarDer(Nodo*&,Dato*);


// llamada a las funciones recursivas
bool ArbolNodoMasLongevo(Nodo*);
int ArbolNodoBuscarGeneracion(Nodo*&,const char*);
int ArbolNodoBuscarContarVivos(Nodo*);
void ArbolPrintfAntecesores(Nodo*,const char*);
bool ArbolNodoBuscarModificar(Nodo*&,const char*);
bool ArbolNodoBuscarHijos(Nodo*,const char*);
bool ArbolNodoBuscarPadres(Nodo*,const char*);


// funciones para recursividad
bool ArbolNodoMasLongevoBase(Nodo*,Dato*);
int ArbolNodoBuscarGeneracionBase(Nodo*&,int,const char*);
int ArbolNodoBuscarContarVivosBase(Nodo*);
void ArbolPrintfAntecesoresBase(Nodo*,int,const char*);
bool ArbolNodoBuscarModificarBase(Nodo*&,const char*);
int ArbolNodoBuscarHijosBase(Nodo*,const char*);
int ArbolNodoBuscarPadresBase(Nodo*,Dato*,const char*);

// Variables del menu (switch)
int opcion_usuario;
char temp[10];

// INTEGRANTES DE LA FAMILIA
Dato Raul("Raul",1901,1,27); // Raiz

Dato Maria("Maria",1925,9,12); // Hijo de raul
Dato Josefina("Josefina",1930,2,14); // Hijo de raul

Dato Tomas("Tomas",1950,5,22);//Hijo de Maria 
Dato Jose("Jose",1952,12,17);// Hijo de maria - Hoja
Dato Rafael("Rafael",1950,9,14);//Hijo de josefina
Dato Camila("Camila",1960,7,7);//Hijo de josefina - Hoja

Dato Josefa("Josefa",1984,8,2);//Hija de Tomas - Hoja
Dato Felipe("Felipe",1980,12,2);//Hijo de Rafael - Hoja 
Dato Valentina("Valentina",1982,4,4);//Hijo de Rafael 

Dato Ignacio("Ignacio",2009,12,12);//Hijo de Valentina - Hoja
Dato Pedro("Pedro",2011,3,24);//Hijo de Valentina - Hoja 


// PROGRAMA PRINCIPAL 

int main(){
		setlocale(LC_ALL, "spanish"); // Permite imprimir caracteres con tilde 
		
	agregar_familiares();

	do{
		
		menu_bienvenida();
	
	 switch(opcion_usuario){
	 	
	 	case 1: 
	 	titulo();
	 	printf("\t\t\tBÚSQUEDA DEL INDIVIDUO MÁS LONGEVO\n\n");
	 	ArbolNodoMasLongevoBase(Arbol,&Pedro);
	 	printf("\n");
	 	printf("\t\t");
	 	system("pause");
	 	system("cls");
	 	break;
	 	
	 	case 2:
	 	titulo();
		 printf("\t\t\tBÚSQUEDA DE HIJOS POR NOMBRE\n\n"); 
		printf("\t\tIngrese un nombre para buscar en el árbol : \n");
		printf("\t\t");
		fflush(stdin);
		scanf("%s",BuscarAlias);
		printf("\n");
		ArbolNodoBuscarHijos(Arbol,BuscarAlias);
		printf("\t\t");
		system("pause");
	 	break;
	 	
	    case 3:
		titulo();  
	    printf("\t\t\tBÚSQUEDA DE PADRES POR NOMBRE\n\n");
		printf("\t\tIngrese un nombre para buscar en el árbol : \n");
		printf("\t\t");
		fflush(stdin);
		scanf("%s",BuscarAlias);
		printf("\n");
		ArbolNodoBuscarPadres(Arbol,BuscarAlias);
		printf("\t\t");
		system("pause");
	    break;
	    
	    case 4: 
	    titulo();
	    printf("\t\t\tCONSULTA DE GENERACIÓN DE UNA PERSONA\n\n");
		printf("\t\tIngrese un nombre para buscar en el árbol : \n");
		printf("\t\t");
		fflush(stdin);
		scanf("%s",BuscarAlias);
		printf("\n");
		ArbolNodoBuscarGeneracion(Arbol,BuscarAlias);
		printf("\t\t");
		system("pause");
	    break;
	    
	    case 5:
	    titulo();
		printf("\t\t\tMODIFICACIÓN DE LOS DATOS DE UN FAMILIAR\n\n");  
		printf("\t\tIngrese un nombre para buscar en el árbol : \n");
		printf("\t\t");
		fflush(stdin);
		scanf("%s",BuscarAlias);
		printf("\n");
		ArbolNodoBuscarModificar(Arbol,BuscarAlias);
		printf("\t\t");
		system("pause");
	    break;
	    
	    case 6: 
	    titulo();
	    printf("\t\t\tMOSTRAR LOS ANTECESORES DE UNA DETERMINADA PERSONA\n\n");
		printf("\t\tIngrese un nombre para buscar en el árbol : \n");
		printf("\t\t");
		fflush(stdin);
		scanf("%s",BuscarAlias);
		printf("\n");
		ArbolPrintfAntecesoresBase(Arbol,0,BuscarAlias);
		printf("\t\t");
		system("pause");
	    break;
	    
	    case 7:	
	    titulo();	
	    printf("\t\t\tFAMILIARES CON VIDA\n\n");
		ArbolNodoBuscarContarVivos(Arbol);
		printf("\t\t");
		system("pause");
		system("cls");
	    break;
	    	
	    case 8 : // salir del programa
	    break;
	 
	    default : printf("\tOPCIÓN NO VÁLIDA.\n"); // opcion incorrecta, pide al usuario reintentar para ingresar un numero valido de acuerdo al menu.
	 }
	 	
}while(opcion_usuario != 8); // si el usuario selecciona la opcion 8, el programa finaliza.
	
	return 0;
}

//-------------------------------------------------------------------------------------------------------------------

// Comienzo de implementacion de funciones

void menu_bienvenida(){
	titulo();
	printf("\t\t\t\tBIENVENIDO AL SISTEMA\n\n"); 
	printf("\tA continuación se presentan las opciones disponibles.\n");
	printf("\tpara continuar, seleccione la opción deseada.\n\n");
	printf("\tOpción 1 : Buscar el individuo más longevo de la familia.\n");
	printf("\tOpción 2 : Buscar los hijos de una determinada persona.\n");
	printf("\tOpción 3:  Buscar el padre de una determinada persona.\n");
	printf("\tOpción 4:  Saber a qué generación pertenece una persona.\n");
	printf("\tOpción 5:  Modificar los datos de un familiar, buscando por nombre.\n");
	printf("\tOpción 6:  Mostrar los antecesores de una determinada persona.\n");
	printf("\tOpción 7:  Saber cuántos familiares aún se encuentran con vida.\n");
	printf("\tOpción 8:  Salir del programa.\n");
		fgets(temp,10,stdin); //leer la cadena, almacenar en la variable temp (temporal con un maximo de 10 caracteres) y viene de la entrada stdin.
opcion_usuario = atoi(temp); // transforma lo que se leyo nteriormente ( tipo char ) en un numero ( tipo int ).
system("cls");
} // cierre void menu bienvenida 

void titulo(){
	
	 
    printf("\n     ======================================================================\n\n");
    printf("\t\t\t   ESTRUCTURA DE DATOS Y ALGORITMOS\n");
    printf("\t\t      plataforma de simulación de arból genealógico\n");
    printf("\n     ======================================================================\n");
    printf("\n\n");
    
} // cierre void titulo 

void agregar_familiares(){
	
	// Familiares fallecidos 
Raul.exeSinVida(1985,4,15);
Maria.exeSinVida(1985,4,15);
Josefina.exeSinVida(1990,12,2);
Jose.exeSinVida(1957,7,29);

//Agregarando familiares al arbol 
ArbolAgregarIzq(Arbol,&Raul);

ArbolAgregarIzq(Arbol,&Maria);
ArbolAgregarDer(Arbol,&Josefina);

ArbolAgregarIzq(Arbol->NodoIzq,&Tomas);
ArbolAgregarDer(Arbol->NodoIzq,&Jose);

ArbolAgregarIzq(Arbol->NodoDer,&Rafael);
ArbolAgregarDer(Arbol->NodoDer,&Camila);

///3
ArbolAgregarDer(Arbol->NodoIzq->NodoIzq,&Josefa);

ArbolAgregarIzq(Arbol->NodoDer->NodoIzq,&Felipe);
ArbolAgregarDer(Arbol->NodoDer->NodoIzq,&Valentina);

ArbolAgregarIzq(Arbol->NodoDer->NodoIzq->NodoDer->NodoIzq,&Ignacio);
ArbolAgregarDer(Arbol->NodoDer->NodoIzq->NodoDer,&Pedro);
	
	
} // cierre 

//-------------------------IMPLEMENTACION MANEJO DE CADENAS----------------------------------
char*jdominChars(const char*f){
char*t=NULL;
if((t=(char*)malloc((strlen(f)+1)*sizeof(char)))){
strcpy(t,f); return t;
	} else printf("ERROR\n");
	return NULL;//retorno de control retorna null si ocurre algo extraño en el llamado de malloc
}
char*jdominCharsInts(const int tf){
char*t=NULL;
if((t=(char*)malloc((tf+1)*sizeof(char)))){
for(int v=0;v<tf;v++){ *(t+v)='X'; }
return t;
	} else printf("ERROR\n");
	return NULL;//retorno de control retorna null si ocurre algo extraño en el llamado de malloc
}
size_t ValidarCadenaOutRangeBase(int f,int abotRange,int atopRange){
if(abotRange<=f &&f<=atopRange){ return 1; }
else { return 0; }
}
void ValidarCadenaOutRangeDecimalTrue(int&f){ if(ValidarCadenaOutRangeBase(f,1,9)){ return; }  else { f=0; } }
void ValidarCadenaOutRangeMinusculaTrue(char&f){ if(ValidarCadenaOutRangeBase(f,97,122)){ return; } else { if(ValidarCadenaOutRangeBase(f,65,90))f+=32; } }
void ValidarCadenaOutRangeMayusculaTrue(char&f){ if(ValidarCadenaOutRangeBase(f,65,90)){ return; } else { if(ValidarCadenaOutRangeBase(f,97,122))f-=32; } }
void ValidarCadenaBase(char*f){ for(size_t i=0;i<strlen(f);i++){ ValidarCadenaOutRangeMinusculaTrue(*(f+i)); } }
char*ValidarCadenaOutRangeMinusculaTrueReturn(const char*f){ char*j=jdominChars(f); for(size_t i=0;i<strlen(j);i++){ ValidarCadenaOutRangeMinusculaTrue(*(j+i)); } return j; }
char*ValidarCadenaOutRangeMayusculaTrueReturn(const char*f){ char*j=jdominChars(f); for(size_t i=0;i<strlen(j);i++){ ValidarCadenaOutRangeMayusculaTrue(*(j+i)); } return j; }
int ValidarCadenaEqual(const char*f,const char*j){ if(strlen(f)!=strlen(j)){ return 0; } else for(size_t i=0;i<strlen(f);i++)if(*(f+i)==*(j+i))continue; else return 0; return 1; }
	
//---------------------IMPLEMENTACION FUNCIONES AGREGAR NODOS IZQUIERDA-DERECHA-------------------------------------	
// elementos de un arbol
Nodo*ArbolNew(Dato*d){
Nodo*jnew= new Nodo();

	jnew->Id=new Dato(d);
	jnew->NodoIzq=NULL;
	jnew->NodoDer=NULL;
	return jnew;
}

void ArbolAgregar(Nodo*&f,Dato*d){
if(!f){
f = ArbolNew(d); // si el nodo f es nulo se le asigna inmediatamente el valor d
	} else {// si el árbol contiene al menos un elemento 

		if(f->Id->nacimiento.Year<d->nacimiento.Year){
			ArbolAgregar(f->NodoIzq,d);//si el dato almacenado en f es mayor que d se asigna en el lado izquierdo 
		} else {
			ArbolAgregar(f->NodoDer,d); // se asigna en el lado derecho 
			}
	}
printf("\t\tElemento añadido con exito .../%s %p",d->Nombre,f);
return;
} // cierre 

void ArbolAgregarIzq(Nodo*&f,Dato*izq){
if(!f){
f = ArbolNew(izq); // si el nodo f es nulo se le asigna inmediatamente el valor d
	} else { // si el árbol contiene al menos un elemento el programa sigue 
		ArbolAgregarIzq(f->NodoIzq,izq);

	}
return;
} // cierre

void ArbolAgregarDer(Nodo*&f,Dato*der){
if(!f){
f = ArbolNew(der); // si el nodo f es nulo se le asigna inmediatamente el valor d
	} else {// si al arbol tiene almenos un elemento el programa sigue 
		ArbolAgregarDer(f->NodoDer,der);

	}
return;
} // cierre

//------------------------FUNCIONES PARA CASE ( SWITCH )------------------------------------------

//CASE 1 BÚSQUEDA DEL MÁS LONGEVO
bool ArbolNodoMasLongevo(Nodo*f){
if(!f){
printf("\n\tEl árbol está vacío"); // no hay datos en el árbol
	return false;
	}

ArbolNodoMasLongevoBase(f,f->Id);
return true;
}

// CASE 2 BÚSQUEDA DE HIJOS POR NOMBRE
bool ArbolNodoBuscarHijos(Nodo*f,const char*nm){
if(!f){
printf("\n\n\tEl árbol está vacío");
	return false;
	} else {
		printf("\t\tBuscando Hijos/as de %s...\n\n",nm);
		ArbolNodoBuscarHijosBase(f,nm);
		printf("\n\n");
		printf("\t\tProceso de Búsqueda existoso.\n");
	return true;
	}
return false;
} // cierre

// CASE 3 BÚSQUEDA DE PADRES POR NOMBRE
bool ArbolNodoBuscarPadres(Nodo*f,const char*nm){
if(!f){
printf("\n\n\tEl árbol está vacío");
	return false;
	} else {
		printf("\t\tBuscando Padre de %s...\n\n",nm);
		ArbolNodoBuscarPadresBase(f,f->Id,nm);
		printf("\t\tProceso de Búsqueda existoso.\n");

	return true;
	}
return false;
} // cierre 

// CASE 4 CONSULTA DE GENERACIÓN DE UNA PERSONA
int ArbolNodoBuscarGeneracion(Nodo*&f,const char*nm){
if(!f){
printf("\n\n\tEl árbol está vacío");
	return 0;
	} else {
		printf("\t\tBuscando generación de %s...\n\n",nm);
		ArbolNodoBuscarGeneracionBase(f,0,nm);
		printf("\t\tProceso de Búsqueda existoso.\n");
		return 1;
	}

return 0;
} // cierre 

// CASE 5 MODIFICACIÓN DE LOS DATOS DE UN FAMILIAR
bool ArbolNodoBuscarModificar(Nodo*&f,const char*nm){ 
if(!f){
printf("\n\n\tEl árbol está vacío");
	return false;
	}

printf("\t\t Modificación de familiar iniciado...\n\n");
ArbolNodoBuscarModificarBase(f,nm);
printf("\t\tModificación de familiar existosa.\n");
return true;
}

// CASE 6 MOSTRAR LOS ANTECESORES DE UNA DETERMINADA PERSONA
void ArbolPrintfAntecesores(Nodo*,const char*){

}

// CASE 7 FAMILIARES CON VIDA
int ArbolNodoBuscarContarVivos(Nodo*f){
if(!f){
printf("\n\n\tEl árbol está vacío");
	return 0;
	} else {
		printf("\t\tBúsqueda de familiares vivos iniciada...\n\n");
		int data_ConVida=ArbolNodoBuscarContarVivosBase(f);
		printf("\t\tActualmente existen %d familiares vivos.\n",data_ConVida);
	return data_ConVida;
	}
} // cierre

//-------------------------FUNCIONES PARA RECURSIVIDAD--------------------------------

//CASE 1 BÚSQUEDA DEL MÁS LONGEVO RECURSIVA 
bool ArbolNodoMasLongevoBase(Nodo*f,Dato*j){
if(!f)return 0;
if(f->Id->viewEdadTrue(j)){
	char*r=ValidarCadenaOutRangeMayusculaTrueReturn(f->Id->Nombre);
	printf("\t\tEl familiar más longevo es : %s\n",r);

return 1;
} else {
	ArbolNodoMasLongevoBase(f->NodoIzq,j);
		ArbolNodoMasLongevoBase(f->NodoDer,j);
		}

return 0;
} // cierre 

// CASE 2 BÚSQUEDA DE HIJOS POR NOMBRE RECUSRIVO 

int ArbolNodoBuscarHijosBase(Nodo*f,const char*nm){
if(!f)return false;///Si el arbol esta vacio cancelar busqueda.

if(ValidarCadenaEqual(ValidarCadenaOutRangeMinusculaTrueReturn(f->Id->Nombre),ValidarCadenaOutRangeMinusculaTrueReturn(nm))){
f->printHijos();

} else {
	ArbolNodoBuscarHijosBase(f->NodoIzq,nm);
		ArbolNodoBuscarHijosBase(f->NodoDer,nm);
}

return false;
} // cierre

// CASE 3 BÚSQUEDA DE PADRES POR NOMBRE RECURSIVO 

int ArbolNodoBuscarPadresBase(Nodo*f,Dato*j,const char*nm){
if(!f)return 0;///Si el arbol esta vacio cancelar busqueda.

if(ValidarCadenaEqual(ValidarCadenaOutRangeMinusculaTrueReturn(f->Id->Nombre),ValidarCadenaOutRangeMinusculaTrueReturn(nm))){
if(j==f->Id){
	printf("\t\t  %s es la raiz del árbol.\n",j->Nombre); 
	return 1;
	}

printf("\t\t  %s Es el/la padre/madre de %s\n",j->Nombre,f->Id->Nombre);
return 1;

} else {
	ArbolNodoBuscarPadresBase(f->NodoIzq,f->Id,nm);
		ArbolNodoBuscarPadresBase(f->NodoDer,f->Id,nm);
}

return 0;
} // cierre 

// CASE 4 CONSULTA DE GENERACIÓN DE UNA PERSONA RECURSIVO 

int ArbolNodoBuscarGeneracionBase(Nodo*&f,int jCount,const char*nm){
if(!f)return 0;///Si el arbol esta vacio cancelar busqueda.
if(ValidarCadenaEqual(ValidarCadenaOutRangeMinusculaTrueReturn(f->Id->Nombre),ValidarCadenaOutRangeMinusculaTrueReturn(nm))){
	
	printf("\t\t%s es de la generación %d\n",f->Id->Nombre,jCount);

return jCount;
} else {
	ArbolNodoBuscarGeneracionBase(f->NodoIzq,jCount+1,nm);
		ArbolNodoBuscarGeneracionBase(f->NodoDer,jCount+1,nm);
		}

return jCount;
} // cierre 

// CASE 5 MODIFICACIÓN DE LOS DATOS DE UN FAMILIAR RECURSIVO 

bool ArbolNodoBuscarModificarBase(Nodo*&f,const char*nm){
if(!f)return false;
if(ValidarCadenaEqual(ValidarCadenaOutRangeMinusculaTrueReturn(f->Id->Nombre),ValidarCadenaOutRangeMinusculaTrueReturn(nm))){
	int newYearConVida=0; // Nuevo año de nacimiento 
	int newMesConVida=0; // Nuevo mes de nacimiento 
	int newDiaConVida=0; // Nuevo día de nacimiento 
	int newYearSinVida=0; // Nuevo año de muerte
	int newMesSinVida=0; // Nuevo mes de muerte 
	int newDiaSinVida=0; // Nuevo día de muerte 
	int vivoMuerto=0; // Pregunta al usuario si ha muerto el familiar ( el nuevo familiar ingresado/modificado ) 
	char*newName=jdominCharsInts(15); //nuevo nombre.

	//imprimiendo referencia principal
	printf("\t\t Modificando datos de %s...\n\n",f->Id->Nombre);

	// Nuevo nombre del familiar
	printf("\t\tIngrese el nuevo nombre del familiar :\n");
	printf("\t\t");
	fflush(stdin);
	scanf("%s",newName);
	f->Id->setAlias(newName);

	// Modificando fecha de nacimiento 
	printf("\t\tNuevo año de nacimiento :\n");
	printf("\t\t");
	scanf("%d",&newYearConVida);
	printf("\t\tNuevo mes de nacimiento :\n");
	printf("\t\t");
	scanf("%d",&newMesConVida);
	printf("\t\tNuevo día de nacimiento :\n");
	printf("\t\t");
	scanf("%d",&newDiaConVida);
	f->Id->familiarVivo(newYearConVida,newMesConVida,newDiaConVida);

	// Modificando fecha de muerte -> en el caso que el usuario diga que el familiar ingresado está muerto
	do{
			if(vivoMuerto==7)break;
		printf("\t\t Opciones disponibles :\n");
		printf("\t\t [1] Familiar fallecido-Ingresar fecha de muerte del familiar\n"); // usuario ingresa la fecha de muerte del familiar 
	    printf("\t\t [2] Familiar vivo\n"); // el familiar se encuentra vivo 
	    printf("\t\t [3] Dejar en blanco\n\n");
	    printf("\t\tDigite su opción :\n");
	    printf("\t\t");
	    scanf("%d",&vivoMuerto);
	    
		switch(vivoMuerto){
		case 1:
		printf("\t\tAño de fallecimiento :\n");
		scanf("%d",&newYearSinVida);
		printf("\t\tMes de fallecimiento :\n");
		scanf("%d",&newMesSinVida);
		printf("\t\tDía de fallecimiento :\n");
		scanf("%d",&newDiaSinVida);	
		f->Id->exeSinVida(newYearSinVida,newMesSinVida,newDiaSinVida);
			vivoMuerto=7;
			break;

			case 2:
			printf("\t\tEl familiar se encuentra vivo para el sistema.\n");
			f->Id->exeSinVidaOff(); // cambiar estado de muerto a vivo 
			vivoMuerto=7;
			break;

			case 3:
			printf("\t\t El estado de defunción no ha tenido cambios.\n");
			vivoMuerto=7;
				break;
		default:
		printf("\t\tOPCIÓN NO VÁLIDA\n");
		}

	} while(true);

printf("\t\tModificación de los datos realizado con exito\n");
f->Id->printjState();
return true;
} else {
	ArbolNodoBuscarModificarBase(f->NodoDer,nm);
	ArbolNodoBuscarModificarBase(f->NodoIzq,nm);

}

return false;
} // cierre 

// CASE 6 MOSTRAR LOS ANTECESORES DE UNA DETERMINADA PERSONA RECURSIVO 

void ArbolPrintfAntecesoresBase(Nodo*f,int d,const char*nm){

if(!f)return;
if(ValidarCadenaEqual(ValidarCadenaOutRangeMinusculaTrueReturn(f->Id->Nombre),ValidarCadenaOutRangeMinusculaTrueReturn(nm))){
printf("\t\tBuscando los antecesores de %s...\n",f->Id->Nombre);

} else {

	printf("\t\tDatos del antecesor(Id-Nombre): %d# %s\n",d,f->Id->Nombre);
	ArbolPrintfAntecesoresBase(f->NodoIzq,d+1,nm);
		ArbolPrintfAntecesoresBase(f->NodoDer,d+1,nm);
		}

return;
} // cierre 

// CASE 7 FAMILIARES CON VIDA RECURSIVO 

int ArbolNodoBuscarContarVivosBase(Nodo*f){
if(!f)return 0;
int data_ConVida=0;

if(f->Id->viewStateConVida())data_ConVida+=1;
	data_ConVida+=ArbolNodoBuscarContarVivosBase(f->NodoDer);
		data_ConVida+=ArbolNodoBuscarContarVivosBase(f->NodoIzq);

return data_ConVida;
} // cierre 


//----------------------------------------------------------------------------------------------------------
/*
COMIENZO EXPLICACIÓN DE FUNCIONES

Nombre función: menu_bienvenida
Tipo de función: void 
Parámetros: sin parámetros
Dato de retorno: sin dato de retorno, imprime información
Descripción de función: imprime el menú de bienvenida al programa 

Nombre función: titulo
Tipo de función: void 
Parámetros: sin parámetros
Dato de retorno: sin dato de retorno, imprime información 
Descripción de función: imprime un encabezado al programa 

Nombre función: Agregar_familiares
Tipo de función: void
Parámetros: -
Dato de retorno: informacion 
Descripción de función: añade la información de la familia al árbol 

Nombre función: ValidarCadenaOutRangeBase
Tipo de función: size 
Parámetros: int int int 
Dato de retorno: 1 
Descripción de función: retorna 1 si el valor f esta dentro del rango.

Nombre función: ValidarCadenaOutRangeminuscula
Tipo de función: void 
Parámetros: char 
Dato de retorno:
Descripción de función: convertir caracteres a minuscula.

Nombre función: ValidarCadenaOutRangemayuscula
Tipo de función: void 
Parámetros: char
Dato de retorno:
Descripción de función: convertir caracteres a mayuscula 

Nombre función: ValidarCadenaBase
Tipo de función: void 
Parámetros: char
Dato de retorno:
Descripción de función: cambia las letras mayusculas en la cadena y las pone minusculas.

Nombre función: ValidarCadenaOutRangeminisculatruereturn
Tipo de función: void 
Parámetros: char
Dato de retorno:
Descripción de función: cambia las letras mayusculas en la cadena y las pone minusculas.

Nombre función: ValidarCadenaOutRangemayusculaTrueReturn 
Tipo de función: void 
Parámetros: char  
Dato de retorno:
Descripción de función: cambia las letras minusculas en la cadena y las pone en mayusculas

Nombre función: ValidarCadenaEqual
Tipo de función: void 
Párametros: char 
Dato de retorno:
Descripción de función: determima si dos cadenas son identicas. 

*/

