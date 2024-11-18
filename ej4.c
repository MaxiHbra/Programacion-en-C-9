/*
Ejercicio 4: Considere una pequeña biblioteca que posee un solo ejemplar por cada libro y cree un
programa que, a través de un menú de opciones, administre el registro de los libros. Es necesario
registrar por cada libro: ISBN del libro, Nombre del libro, Tipo de libro (Literatura, Consulta) y
Referencia del libro (Artísticos, Divulgativos, Descripción). El programa debe permitir:
a) Agregar un nuevo libro al inicio de la lista, considerar que el ISBN debe ser único;
b) Mostrar los datos de un libro, dado su número de ISBN;
c) Mostrar la lista de todos los libros;
d) Modificar el campo Tipo de libro, dado su número de ISBN.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 20
typedef char tcad[max];

typedef struct{
	long isbn;
	tcad nombre;
	int tl,rl;
}libro;

typedef struct A{
	libro dato;
	struct A *sig;
}biblioteca;

typedef biblioteca *Tptr;

Tptr crear_nodo(void);
void agrega_uno(Tptr*);
void mostrar(Tptr);
void mostrar_det(Tptr);
int menu();
void modificar(Tptr*);

int main() {
	Tptr lista;
	int opc;
	lista=NULL;
	do{
		opc=menu();
		switch(opc){
			case 0 : printf("\nSaliste del programa."); break;
			case 1 : agrega_uno(&lista); break;
			case 2 : mostrar_det(lista); break;
			case 3 : mostrar(lista); break;
			case 4 : modificar(&lista); break;
			default : break;
		}
	}while(opc!=0);
	return 0;
}
int menu(void){
	int opc;
	printf("\n-------------------------");
	printf("\nIngrese 0 para salir del programa.");
	printf("\nIngrese 1 para agregar libro a la lista.");
	printf("\nIngrese 2 para mostrar libro en particular.");
	printf("\nIngrese 3 mostrar todos los libros.");
	printf("\nIngrese 4 para modificar libro en particular.");
	printf("\n--> ");
	scanf("%d",&opc);
	printf("\n-------------------------\n");
	return opc;
}
void leecad(tcad cad, int tam){
	int i=0;
	char c;
	c=getchar();
	while(c!=EOF && c!='\n' && i<tam){
		cad[i]=c;
		i++;
		c=getchar();
	}
	cad[i]='\0';
	while(c!=EOF && c!='\n') c=getchar();
}
libro ingresar_libro(void){
	libro aux;
	printf("\nIngresar ISBN del libro: ");
	scanf("%ld",&aux.isbn);
	printf("\nIngresar nombre del libro: ");
	fflush(stdin);leecad(aux.nombre, max);
	printf("\nIngresar tipo de libro: 1 para literatura, 2 para consulta.");
	scanf("%d",&aux.tl);
	printf("\nIngresar referencia de libro: 1 para artistico, 2 para divulgacion y 3 para descripcion.");
	scanf("%d",&aux.rl);
	return aux;
}
Tptr crear_nodo(void){
	Tptr nue;
	nue=(Tptr)malloc(sizeof(biblioteca));
	if(nue!=NULL){
		nue->dato=ingresar_libro();
		nue->sig=NULL;
	}
	return nue;
}
int buscar(Tptr cab, long code){
	int aux=0;
	while(cab!=NULL && aux==0){
		if(cab->dato.isbn==code) aux=1;
		cab=cab->sig;
	}
	return aux;
}
void agrega_uno(Tptr *cab){
	Tptr nue,actual;
	nue=crear_nodo();
	if(*cab==NULL)
		*cab=nue;
	else{
		if(buscar(*cab,nue->dato.isbn)==0){
			actual=*cab;
			nue->sig=actual;
			*cab=nue;
		}
		else printf("\nCodigo de libro ya existente.");
	}
}

void mostrar_libro(libro aux){
	printf("\nISBN: %ld",aux.isbn);
	printf("\nNombre del libro: %s",aux.nombre);
	printf("\nTipo de libro: ");
	switch(aux.tl){
	case 1 : printf("Literatura.");break;
	case 2 : printf("Consulta.");break;
	default : printf("Invalido.");
	}
	printf("\nReferencia de libro: ");
	switch(aux.rl){
	case 1 : printf("Artistico.");break;
	case 2 : printf("Divulgativo.");break;
	case 3 : printf("Descrpición."); break;
	default : printf("\nInvalido.");
	}
}
void mostrar(Tptr cab){
	while(cab!=NULL){
		mostrar_libro(cab->dato);
		cab=cab->sig;
	}
}
void mostrar_det(Tptr cab){
	int aux,b=0;
	printf("\nIngrese ISBN para mostrar: ");
	scanf("%d",&aux);
	while(cab!=NULL){
		if(cab->dato.isbn==aux){ 
			mostrar_libro(cab->dato);
			b=1;
		}
		cab=cab->sig;
	}
	if(b==0) printf("\nNo existe libro con tal codigo.");
}
void modifica_libro(libro *aux){
	printf("\nIngresar nombre del libro: ");
	fflush(stdin);leecad(aux->nombre, max);
	printf("\nIngresar tipo de libro: 1 para literatura, 2 para consulta.");
	scanf("%d",&aux->tl);
	printf("\nIngresar referencia de libro: 1 para artistico, 2 para divulgacion y 3 para descripcion.");
	scanf("%d",&aux->rl);
}
void modificar(Tptr *cab){
	long code;
	Tptr aux;
	aux=*cab;
	printf("\nIngresar ISBN de libro a modificar: ");
	scanf("%ld",&code);
	while(aux!=NULL){
		if(aux->dato.isbn == code)
			modifica_libro(&aux->dato);
		aux=aux->sig;
	}
}
