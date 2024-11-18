/*Ejercicio 2:
Escribir un programa que cree una lista enlazada considerando lo siguiente:
a) La lista debe ser de números enteros positivos al azar, respetando el criterio de que, si el
número es par se agrega al principio de la lista y si es impar se agrega al final de la lista.
b) Recorrer la lista para mostrar los elementos por pantalla.
c) Mostrar todos los números que superen un valor determinado */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct{
	int x;
}numero;
typedef struct A{
	numero dato;
	struct A *sig;
}rnum;
typedef rnum *Tptr;
void crear_lista(Tptr*);
Tptr crear_nodo(void);
void agrega_uno(Tptr*);
int aleatorio(void);
void mostrar(Tptr);
void mostrar_det(Tptr);
int par_impar(int);

int main() {
	srand(time(NULL));
	Tptr lista;
	lista=NULL;
	crear_lista(&lista);
	mostrar(lista);
	mostrar_det(lista);
	return 0;
}
void crear_lista(Tptr* lista){
	int n;
	printf("\nIngrese cuantos elementos tiene la lista: ");
	scanf("%d",&n);
	while(n!=0){
		agrega_uno(lista);
		n=n-1;
	}
}
Tptr crear_nodo(void){
	Tptr nue;
	nue=(Tptr)malloc(sizeof(rnum));
	if(nue!=NULL){
		nue->dato.x=aleatorio();
		nue->sig=NULL;
	}
	return nue;
}
void agrega_uno(Tptr *cab){
	Tptr nue,actual;
	nue=crear_nodo();
	if(*cab==NULL)
		*cab=nue;
	else{
		if(par_impar(nue->dato.x)){
			nue->sig=*cab;
			*cab=nue;
		}
		else{
			actual=*cab;
			while(actual->sig!=NULL)
				actual=actual->sig;
			actual->sig=nue;
		}
	}
}
int aleatorio(void){
	return (rand()%(100-1+1)+1);
}
void mostrar(Tptr cab){
	printf("\nValores de la lista: ");
	while(cab!=NULL){
		printf("\nValor: %d",cab->dato.x);
		cab=cab->sig;
	}
}
int par_impar(int aux){
	int val;
	if(aux%2==0) val=1;
	else val=0;
	return val;
}
void mostrar_det(Tptr cab){
	int aux,b=0;
	printf("\nIngrese numero para mostrar los demas: ");
	scanf("%d",&aux);
	while(cab!=NULL){
		if(cab->dato.x>aux){ 
			printf("\n %d > %d",cab->dato.x,aux);
			b=1;
		}
		cab=cab->sig;
	}
	if(b==0) printf("\nNo hay numeros mayores a %d en la lista.",aux);
}
