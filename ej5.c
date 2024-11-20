/*Ejercicio 5: Un Almacén de Ramos Generales requiere de un programa que permita administrar una
lista con los N artículos que comercializa, la información de cada artículo a registrar es: Código de
Artículo, Nombre de Artículo, Stock, Precio de venta.
El programa debe permitir ingresar la lista y que la misma se ordene por Código de Artículo a medida
que se ingresan. Luego debe presentar un menú de opciones que permita las siguientes operaciones:
a) Agregar un nuevo artículo conservando el orden.
b) Modificar el precio de venta de un Artículo, dado su Código de Artículo.
c) Dado el Nombre de un Artículo mostrar Código de Artículo, Stock y Precio de venta de cada
artículo que tenga ese nombre.
d) Eliminar un artículo, dado su Código de Artículo.
e) Crear una nueva lista con los Artículos cuyo Stock es menor a K, donde K es un número natural
generado aleatoriamente, entre los valores [prom, 2*prom], donde prom es el valor promedio del
Stock de los Artículos. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define max 20

typedef char tcad[max];
typedef struct{
	long code;
	tcad nombre;
	int stock;
	float precio;
}ramos;
typedef struct A{
	ramos dato;
	struct A *sig;
}tramos;
typedef tramos *Tptr;

int menu(void);
void inicializa(Tptr*);
void crear_lista(Tptr*);
void agrega_uno(Tptr*);
void modificar_uno(Tptr*);
void mostrar_por_nombre(Tptr);
void eliminar_por_codigo(Tptr*);
void generar_nueva_lista(Tptr,Tptr*);
void mostrar_todo(Tptr);
int main() {
	srand(time(NULL));
	Tptr lista,lista2;
	int opc;
	inicializa(&lista);
	inicializa(&lista2);
	crear_lista(&lista);
	do{
		opc=menu();
		switch(opc){
		case 0 : printf("\nSaliste del programa. ");break;
		case 1 : agrega_uno(&lista); break;
		case 2 : modificar_uno(&lista); break;
		case 3 : mostrar_por_nombre(lista); break;
		case 4 : eliminar_por_codigo(&lista); break;
		case 5 : generar_nueva_lista(lista,&lista2); break;
		case 6 : mostrar_todo(lista); break;
		default : break;
		}
	}while(opc!=0);
	return 0;
}
int menu(void){
	int opc;
	printf("\n-----------------\n");
	printf("\nIngrese 0 para salir.");
	printf("\nIngrese 1 para agregar un nuevo articulo.");
	printf("\nIngrese 2 para modificar el precio de un articulo.");
	printf("\nIngrese 3 para mostrar articulos por nombre.");
	printf("\nIngrese 4 para eliminar un articulo.");
	printf("\nIngrese 5 para generar nueva lista por stock.");
	printf("\nIngrese 6 para mostrar toda la lista.");
	printf("\n---> ");
	scanf("%d",&opc);
	printf("\n-----------------\n");
	return opc;
}
void inicializa(Tptr *cab){
	*cab=NULL;
}
void leecad(tcad cad, int tam){
	int i=0;
	char c;
	c=getchar();
	while(c!=EOF && c!='\n' && i<tam){
		cad[i]=c;
		c=getchar();
		i++;
	}
	cad[i]='\0';
	while(c!=EOF && c!='\n') c=getchar();
}
ramos crear_art(void){
	ramos aux;
	printf("\n-----------------\n");
	printf("\nIngresar codigo del articulo: ");
	scanf("%ld",&aux.code);
	printf("\nIngrese nombre del articulo: ");
	fflush(stdin);leecad(aux.nombre,max);
	printf("\nIngresar precio del articulo: ");
	scanf("%f",&aux.precio);
	printf("\nIngresar stock del producto: ");
	scanf("%d",&aux.stock);
	printf("\n-----------------\n");
	return aux;
}
Tptr crear_nodo(void){
	Tptr aux;
	aux=(Tptr)malloc(sizeof(tramos));
	if(aux!=NULL){
		aux->dato=crear_art();
		aux->sig=NULL;
	}
	return aux;
}
void crear_lista(Tptr *cab){
	int n,i;
	printf("\nIngrese cantidad de elementos de la lista: ");
	scanf("%d",&n);
	for(i=1;i<=n;i++)
		agrega_uno(cab);
	
}
void ordenar_seleccion(Tptr *cab){
	Tptr act,ant;
	ramos aux;
	ant=*cab;
	while(ant->sig!=NULL){
		act=ant->sig;
		while(act!=NULL){
			if(ant->dato.code > act->dato.code){
				aux=act->dato;
				act->dato=ant->dato;
				ant->dato=aux;
			}
			act=act->sig;
		}
		ant=ant->sig;
	}
}
void agrega_uno(Tptr *cab){
	Tptr nue,aux;
	nue=crear_nodo();
	if(*cab==NULL)
		*cab=nue;
	else{
		aux=*cab;
		while(aux->sig!=NULL) aux=aux->sig;
		aux->sig=nue;
		ordenar_seleccion(cab);
	}
}
void modificar_art(ramos *aux){
	printf("\nIngresar nombre nuevo: ");
	fflush(stdin);leecad(aux->nombre,max);
	printf("\nIngresar precio del articulo: ");
	scanf("%f",&aux->precio);
	printf("\nIngresar stock del producto: ");
	scanf("%d",&aux->stock);
}
void modificar_uno(Tptr *cab){
	Tptr aux=*cab;
	long x;
	int b=0;
	printf("\nIngresar codigo a modificar: ");
	scanf("%ld",&x);
	while(aux!=NULL && b==0){
		if(aux->dato.code==x){ 
			modificar_art(&aux->dato);
			b=1;
			printf("\nModificado.\n");
		}
		aux=aux->sig;
	}
	if(b==0)printf("\nNo se encontro articulo con tal codigo.\n");
}
void mostrar_art(ramos aux){
	printf("\nCodigo del articulo: %ld",aux.code);
	printf("\nNombre del articulo: %s",aux.nombre);
	printf("\nPrecio del articulo: %f",aux.precio);
	printf("\nStock del articulo: %d",aux.stock);
}
void mostrar_todo(Tptr lista){
	while(lista!=NULL){
		mostrar_art(lista->dato);
		lista=lista->sig;
	}
}
void mostrar_por_nombre(Tptr cab){
	tcad cad;
	int b=0;
	printf("\nIngrese nombre de articulo: ");
	fflush(stdin);leecad(cad,max);
	while(cab!=NULL){
		if(strcmp(cab->dato.nombre,cad)==0){
			mostrar_art(cab->dato);
			b=1;
		}
		cab=cab->sig;
	}
	if(b==0)printf("\nNo hay ningun articulo con ese nombre.\n");
}
void eliminar_por_codigo(Tptr *cab){
	Tptr aux=*cab;
	Tptr ant=NULL;
	long cod;
	int b=0;
	printf("\nIngresar codigo del articulo a eliminar: ");
	scanf("%ld",&cod);
	while(aux!=NULL && b==0){
		if(aux->dato.code==cod){
			if(ant==NULL) *cab=aux->sig;
			else ant->sig=aux->sig;
			free(aux);
			aux=NULL;
			printf("\nSe elimino el articulo.");
			b=1;
		}
		else{
			ant=aux;
			aux=aux->sig;
		}
	}
	if(b==0) printf("\nNo se elimino.");
}
int promedio(Tptr lista){
	int prom=0,cont=0;
	while(lista!=NULL){
		prom=prom+lista->dato.stock;
		cont++;
		lista=lista->sig;
	}
	return prom/cont;
}
int aleatorio(Tptr lista){
	int prom=promedio(lista);
	prom=(rand()%prom)+prom;
	return prom;
}
void generar_nueva_lista(Tptr lista,Tptr *lista2){
	int aleat=aleatorio(lista);
	Tptr aux,aux2;
	aux2=NULL;
	*lista2=NULL;
	printf("\n%d",aleat);
	while(lista!=NULL){
		aux2=(Tptr)malloc(sizeof(tramos));
		aux2->dato=lista->dato;
		aux2->sig=NULL;
		if(lista->dato.stock < aleat){
			if(*lista2==NULL){ 
				*lista2=aux2;
			}
			else{
				aux=*lista2;
				while(aux->sig!=NULL) aux=aux->sig;
				aux->sig=aux2;
			}
		}
		lista=lista->sig;
	}
	mostrar_todo(*lista2);
}
