#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define max 15
typedef int tlis[max];
typedef struct B{
	tlis dato;
	struct B *sig;
}rcar;
typedef rcar *cartones;
typedef struct A{
	int dato;
	struct A *sig;
}rlis;
typedef rlis *Tptr;

int menu(void);
void crear_lista(cartones*);
void generar_carton(tlis);
void inicializar(Tptr*,cartones*,int*);
Tptr crear_nodo(int);
void agregar_uno(Tptr*,int*);
void verificar_carton(Tptr,cartones,int);
void eliminar_numero(Tptr*,int*);
void mostrar_cartones(cartones);
void mostrar_carton(tlis);
int main() {
	srand(time(NULL));
	cartones carton;
	Tptr sorteados;
	int cont;
	inicializar(&sorteados,&carton,&cont);
	crear_lista(&carton);
	int opc;
	do{
		opc=menu();
		switch(opc){
		case 0 : printf("\nSaliste del programa."); break;
		case 1 : agregar_uno(&sorteados,&cont); break;
		case 2 : verificar_carton(sorteados,carton, cont); break;
		case 3 : eliminar_numero(&sorteados, &cont); break;
		case 4 : mostrar_cartones(carton); break;
		default : break;
		}
	}while(opc!=0);
	return 0;
}

int menu(void){
	int opc;
	printf("\n------------------\n");
	printf("\nIngrese 0 para salir.");
	printf("\nIngrese 1 para registrar un numero sorteado.");
	printf("\nIngrese 2 para verificar el carton ganador.");
	printf("\nIngrese 3 para eliminar un numero sorteado.");
	printf("\nIngrese 4 para mostrar cartones.");
	printf("\n---> ");
	scanf("%d",&opc);
	printf("\n------------------\n");
	return opc;
}
cartones crear_carton(void){
	cartones nue;
	nue=(cartones)malloc(sizeof(rcar));
	if(nue!=NULL){
		generar_carton(nue->dato);
		nue->sig=NULL;
	}
	return nue;
}
void agrega_un_carton(cartones *cab2){
	cartones aux;
	aux=(cartones)malloc(sizeof(rcar));
	if(*cab2==NULL) *cab2=crear_carton();
	else{
		aux=*cab2;
		while(aux->sig!=NULL) aux=aux->sig;
		aux->sig=crear_carton();
	}
}
void crear_lista(cartones *cab2){
	int n,i;
	printf("\nIngresar cuantas personas tienen carton: ");
	scanf("%d",&n);
	for(i=1;i<=n;i++)
		agrega_un_carton(cab2);
}
int generar_numero(void){
	int r=(rand()%(99))+1;
	return r;
}
void generar_carton(tlis lis){
	int i;
	for(i=1;i<=15;i++)
		lis[i]=generar_numero();
	
}
void inicializar(Tptr *cab,cartones *carton, int *cont){
	*cab=NULL;
	*carton=NULL;
	*cont=0;
}
Tptr crear_nodo(int num){
	Tptr nue;
	nue=(Tptr)malloc(sizeof(rlis));
	if(nue!=NULL){
		nue->dato=num;
		nue->sig=NULL;
	}
	return nue;
}
int buscar(Tptr cab, int num){
	int b=0;
	while(cab!=NULL){
		if(cab->dato==num) b=1;
		cab=cab->sig;
	}
	return b;
}
void agrega_ordenado(Tptr *cab, Tptr nodo){
	Tptr aux=*cab,ant;
	if(aux->dato > nodo->dato){
		nodo->sig=*cab;
		*cab=nodo;
	}
	else{
		aux=*cab;
		ant=NULL;
		while(aux!=NULL && aux->dato < nodo->dato){
			ant=aux;
			aux=aux->sig;
		}
		nodo->sig=aux;
		ant->sig=nodo;
	}
}
void agregar_uno(Tptr *cab, int *cont){
	Tptr nue;
	int num;
	num=generar_numero();
	nue=crear_nodo(num);
	if(buscar(*cab,num)==0){
		printf("\nSe agregara %d en la lista. ",num);
		*cont=*cont+1;
		if(*cab==NULL) *cab=nue;
		else agrega_ordenado(cab,nue);}
	else printf("\nEl numero ya se encuentra en lista.");
}
int buscar_carton(Tptr cab, tlis lis){
	int b=0,i=1,c=0;
	while(i<=15 && c==0){
		if(buscar(cab,lis[i])==0) c=1;
		i++;
	}
	if(c==0) b=1;
	return b;
}
void verificar_carton(Tptr cab, cartones carton, int cont){
	int b=0;
	if(cont>=max){
		while(carton!=NULL && b==0){
			if(buscar_carton(cab,carton->dato)==1)b=1;
			carton=carton->sig;
		}
		if(carton!=NULL){
			printf("\nEl carton siguiente es el ganador.");
			mostrar_carton(carton->dato);
		}
		else printf("\nNingun carton es ganador aun.");
	}
	else printf("\nNo hay suficientes numeros en la lista.");
}	
void eliminar_numero(Tptr *cab, int *cont){
	Tptr aux=*cab,ant=NULL;
	int num;
	printf("\nIngresar numero a eliminar del sorteo: ");
	scanf("%d",&num);
	while(aux!=NULL && aux->dato!=num){
		ant=aux;
		aux=aux->sig;
	}
	if(aux!=NULL){
		*cont=*cont-1;
		if(aux->sig==NULL) ant->sig=NULL;
		else ant->sig=aux->sig;
	}
	else printf("\nNo se encontro el numero en la lista.");
}

void mostrar_cartones(cartones cab2){
	while(cab2!=NULL){
		mostrar_carton(cab2->dato);
		cab2=cab2->sig;
	}
}
void mostrar_carton(tlis lista){
	int i;
	printf("\nNumeros del carton: ");
	for(i=1;i<=15;i++){
		printf(" %d ",lista[i]);
	}
}
