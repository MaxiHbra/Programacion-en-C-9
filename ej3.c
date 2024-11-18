/*Ejercicio 2:
Escribir un programa que cree una lista enlazada considerando lo siguiente:
a) La lista debe ser de números enteros positivos al azar, respetando el criterio de que, si el
número es par se agrega al principio de la lista y si es impar se agrega al final de la lista.
b) Recorrer la lista para mostrar los elementos por pantalla.
c) Mostrar todos los números que superen un valor determinado 
Ejercicio 3:
Retomar el ejercicio 2 agregando un menú que permita seleccionar las operaciones b) y c) y además
las siguientes:
a) Modificar cada número primo, transformándolo en negativo;
b) Insertar, en la lista, delante de cada número par, el número cero. 
*/
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
int menu();
void modificar(Tptr *lista);
void insertar_en_par(Tptr *lista);

int main() {
	srand(time(NULL));
	Tptr lista;
	int opc;
	lista=NULL;
	crear_lista(&lista);
	do{
		opc=menu();
		switch(opc){
			case 0 : printf("\nSaliste del programa."); break;
			case 1 : mostrar(lista); break;
			case 2 : mostrar_det(lista); break;
			case 3 : modificar(&lista); break;
			case 4 : insertar_en_par(&lista); break;
			default : break;
		}
	}while(opc!=0);
	return 0;
}
int menu(void){
	int opc;
	printf("\nIngrese 0 para salir del programa.");
	printf("\nIngrese 1 para mostrar la lista.");
	printf("\nIngrese 2 para mostrar numeros de la lista mayor a uno dado.");
	printf("\nIngrese 3 para hacer negativos los primos de la lista.");
	printf("\nIngrese 4 para insertar 0 delante de los pares en la lista.");
	scanf("%d",&opc);
	return opc;
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
int primo(int x){
	int ret,pd=2;
	while(pd<=(x/2) && x%pd!=0) pd++;
	if(pd>(x/2) && x!=1) ret=1;
	else ret=0;
	return ret;
}
void modificar(Tptr *cab){
	Tptr aux=*cab;
	while(aux!=NULL){
		if(primo(aux->dato.x)) aux->dato.x=0-aux->dato.x;
		aux=aux->sig;
	}
	printf("\nListo.");
}
void insertar_en_par(Tptr *cab){
	Tptr ant=NULL;
	Tptr act=*cab;
	Tptr aux;
	while(par_impar(act->dato.x)){
		aux=(Tptr)malloc(sizeof(rnum));
		aux->dato.x=0; 
		aux->sig=act;
		if(ant==NULL){
			ant=aux;
			*cab=ant;
		}
		else{
			ant->sig=aux;
			ant=ant->sig;
		}
		ant=ant->sig;
		act=act->sig;
	}
	printf("\nListo.");
}
