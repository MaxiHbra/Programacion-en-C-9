/*Ejercicio 1:
Cree un programa que declare tres pares ordenados (x,y) en variables de tipo puntero con asignación
de memoria en forma dinámica e indique cual par ordenado retorna el mínimo valor al ser evaluado en
la expresión (x2 - 10y). */
#include <stdio.h>
typedef struct{
	int x,y;
}pares;
typedef pares *puntos;

puntos ingreso();
int expresion(puntos);
void minimo(puntos,puntos,puntos);

int main() {
	puntos a,b,c;
	a=ingreso();
	b=ingreso();
	c=ingreso();
	minimo(a,b,c);
	return 0;
}
puntos ingreso(void){
	puntos aux;
	aux=NULL;
	printf("\nIngrese X: ");
	scanf("%d",&aux->x);
	printf("\nIngrese Y: ");
	scanf("%d",&aux->y);
	return aux;
}
int expresion(puntos aux){
	int exp=2*(aux->x)-10*(aux->y);
	return exp;
}
void minimo(puntos a,puntos b,puntos c){
	if(expresion(a)<expresion(b) && expresion(a)<expresion(c))
		printf("\nEl menor luego de la expresion x2-10y es el punto: (%d,%d)",a->x,a->y);
	else if(expresion(b)<expresion(a) && expresion(b)<expresion(c))
		printf("\nEl menor luego de la expresion x2-10y es el punto: (%d,%d)",b->x,b->y);
	else printf("\nEl menor luego de la expresion x2-10y es el punto: (%d,%d)",c->x,c->y);
}
