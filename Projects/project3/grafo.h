#ifndef GRAFO_H
#define GRAFO_H

#include <stdbool.h>

/**
 * @brief Se crea un estruc nodo para crear el Grafo
 * Se encarga de crear la estructura del Grafo
 * @param nodo
 */
struct nodo{
    struct nodo* nodo ;
    struct nodo *Grafo;
    int vertices,conexion;
    int *arista;
    int **matriz_adyacencia;
}nodo;

/**
 * @brief Inicializar grafo
 * Se encarga de solicitar el numero de vertices para crear la matriz de adyacencia para el grafo
 * @param Grafo 
 */
void inicializar(struct nodo* Grafo);

/**
 * @brief Generar conexiones
 * Se encarga de definir las conexiones en el grafo
 * Se marcan en la matriz de adyacencia con el valor de la arista (totalmente al azar)
 * @param Grafo 
 */
void generar_conexiones(struct nodo* Grafo);


/**
 * @brief Imprime la matriz
 * Se encarga de imprimir la matriz de adyacencia con los valores
 * @param Grafo 
 */
void imprimir_matriz(struct nodo* Grafo);

/**
 * @brief recorrido en profundidad del grafo
 * Se hace un recorrido en profundidad del grafo
 * Un recorrido en profundidad permite recorrer los nodos del grafo
 */
void recorrido_Profundidad(int i, struct nodo* Grafo);

/**
 * @brief Algoritmo de dijkstra
 * Se encarga de buscar el camino mas corto de un nodo inicial al resto de nodos en el grafo
 * @param nodo_inicial 
 * @param Grafo 
 */
void dijkstra(int nodo_inicial, struct nodo* Grafo);


/**
 * @brief arbol de expansion minima de prim
 * Se encarga de encontrar un arbol que incluya todos los vertices del grafo, donde el peso total de las aristas del arbol es el minimo posible
 * @param Grafo 
 */
void arbol_expansion_minima_Prim(struct nodo* Grafo);


#endif
