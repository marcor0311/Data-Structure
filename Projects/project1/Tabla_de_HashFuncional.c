#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//struct de derivado el cual cuenta con cantidad, precio, si compra o vende y la llave del nombre
typedef struct derivado {
	int cantidad, precio, compraVende;
	char* llave_nombre;
} derivado;
int llave = 0;
//invoca los derivados del struct para inicializarlos
derivado* invocar_derivado(char* nombre) {
	derivado* derivado_puntero = calloc(1,sizeof(derivado));
	derivado_puntero -> cantidad = 0; //siempre en cero
	derivado_puntero -> precio = 0; //siempre en cero
	derivado_puntero -> compraVende = 0; //siempre en cero
	derivado_puntero -> llave_nombre = nombre; //la llave del nombre apunta al nombre
	return derivado_puntero; 
}
//crea la tabla de hash sin colisicones
int tabla_Hash(char* llave_nombre, int listaTablaHash){
	int longitud = sizeof(llave_nombre);
	for(int indice=1; indice < longitud; indice++){
		int character_val = llave_nombre[indice];
		llave += character_val;
	}
	llave = (llave/longitud)%listaTablaHash;
	return llave;
}
//7 productos por ser numero primo y el que no generaba colisiones
//fuente: tbl_hshtps://www.legalline.ca/legal-answers/what-products-can-be-made-from-hemp/
char* lista_derivados[] = {"aceite","biocombustible","joyas","pintura","medicinas","leche","proteina"};
//crea los derivados dentro de la tabla de hash
void crear_derivados_tabla_hash(derivado** tbl_hsh, char* lista_derivados[]){
	for(int indice = 0; indice < 7; indice++){
		char* derivados_nombre = lista_derivados[indice];
		int llave = tabla_Hash(derivados_nombre, 97);
		derivado* puntero_derivado = invocar_derivado(derivados_nombre);
		tbl_hsh[llave] = puntero_derivado;
	}
	char* derivados_nombre = lista_derivados[6];
	int llave = tabla_Hash(derivados_nombre, 97);
	derivado* puntero_derivado = invocar_derivado(derivados_nombre);
	tbl_hsh[llave] = puntero_derivado;
}
//eliminar derivado
void eliminar_derivado(derivado** tbl_hsh){
 	for(int i=0; i < 7; i++){
		char* derivados_nombre = lista_derivados[i];
		int llave = tabla_Hash(derivados_nombre, 97);
		free(tbl_hsh[llave]);
		tbl_hsh[llave] = NULL;
	}
	free(tbl_hsh); tbl_hsh= NULL; //limpiar memoria
}
//invoca a la tabla hash
derivado** invocar_tablahash(int longitud) {
	derivado** tbl_hsh = calloc(longitud,sizeof(derivado*));
	return tbl_hsh;
}