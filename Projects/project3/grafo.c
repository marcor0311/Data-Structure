///Bibliotecas necesarias para el correcto funcionamiento
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>
#include<assert.h>
#include<time.h>

//Incluir structs de grafo.h
#include"grafo.h"

#define RELLENO 9999

/**
 * @file grafo.c
 * @author Marco Rodriguez Vargas 2022149445
 * @author Angel Vargas Varela
 * @date 27 de noviembre del 2022
 * @brief Proyecto del curso de Estructuras de Datos
 */

/**
 * @brief Inicializar grafo
 * Se encarga de solicitar el numero de vertices para crear la matriz de adyacencia para el grafo
 * @param Grafo 
 */
void inicializar(struct nodo* Grafo){
    /// Se pide al usuario la longitud del grafo
    printf("Escriba el numero de vertices\n");
    scanf("%d", &Grafo->vertices);

    /// Se reserva memoria limpia y siempre que no sea nulo se crea el grafo
    Grafo -> matriz_adyacencia = calloc(Grafo -> vertices * Grafo -> vertices, sizeof(int));
    assert(Grafo->matriz_adyacencia != NULL);
    for (int i=0; i<Grafo->vertices; i++){
        Grafo->matriz_adyacencia[i] = calloc(Grafo->vertices, sizeof(int));
        assert(Grafo->matriz_adyacencia[i] != NULL);
    }
}

/**
 * @brief Generar conexiones
 * Se encarga de definir las conexiones en el grafo
 * Se marcan en la matriz de adyacencia con el valor de la arista (totalmente al azar)
 * @param Grafo 
 */
void generar_conexiones(struct nodo* Grafo){
    /// conexion se refiere al par de nodos que se quieran unir
    int conexion;

    /// se pide al usuario la cantidad de conexiones que desea ingresar
    printf("Ingrese la cantidad de conexiones: \n");
    scanf("%d", &conexion);

    /// for para solicitar la cantidad de conexiones
    for(int i=0; i < conexion;i++){

        /// nodo A y nodo B se refiere a los nodos que se quieran conectar
        int nodo_A, nodo_B;
        /// el posible valor de las aristas tiene dominio {1,2,3,4,5,6,7,8,9}
        int arista_maxima=9, arista_minima=1;
        /// por medio de la generacion de un numero random, se crea el valor del arista
        int arista_random = rand()%((arista_maxima+1)-arista_minima) + arista_minima;

        /// solicita al usuario las conexiones y las lee
        printf("Nodo Desde que nodo A a nodo B: ");
        scanf("%d%d", &nodo_A, &nodo_B);

        /// imprime el valor del arista para esa conexion
        printf("valor de arista: %d\n",arista_random);
        /// se asigna el valor del arista a las conexiones en la matriz de adyacencia
        Grafo->matriz_adyacencia[nodo_A][nodo_B] = arista_random;
        Grafo->matriz_adyacencia[nodo_B][nodo_A] = arista_random;
    }
}

/**
 * @brief Imprime la matriz
 * Se encarga de imprimir la matriz de adyacencia con los valores
 * @param Grafo 
 */
void imprimir_matriz(struct nodo* Grafo){
    printf("Matriz de adyacencia\n");
    printf("   ");
    /// se encarga de imprimir la enumeracion de la parte de arriba en la matriz
    for(int i=0; i<Grafo->vertices;i++){
        printf("%d  ",i);
    }
    printf("\n");

    /// se encarga de impimir la enumeracion del lado izquiero de la matriz
    for(int i=0; i<Grafo->vertices;i++){
        printf("%d| ", i);
        /// se encarga de imprimir las conexiones con el valor de las aristas en la matriz
        for(int j=0; j<Grafo->vertices; j++){
          printf("%d  ", Grafo->matriz_adyacencia[i][j]);
        }
        printf("\n");
    }
}

/**
 * @brief recorrido en profundidad del grafo
 * Se hace un recorrido en profundidad del grafo
 * Un recorrido en profundidad permite recorrer los nodos del grafo
 */
//para almacenar los nodos que ya fueron visitados
int nodos_visitados[50];
void recorrido_Profundidad(int nodo_inicio, struct nodo* Grafo){
    /// para imprimir el nodo inicial
    nodos_visitados[nodo_inicio]=1;
    printf("%d->",nodo_inicio);

    /// recorre hasta que se haya pasado por todos los nodos del grafo
    for(int j=0;j<Grafo->vertices;j++){
        ///si hay una conexion y no ha sido visitado entonces se envia de manera recursiva
        if(Grafo->matriz_adyacencia[nodo_inicio][j] != 0 && nodos_visitados[j]==0){
            recorrido_Profundidad(j, Grafo);
        }
    }
}

/**
 * @brief Algoritmo de dijkstra
 * Se encarga de buscar el camino mas corto de un nodo inicial al resto de nodos en el grafo
 * @param nodo_inicial 
 * @param Grafo 
 */
void dijkstra(int nodo_inicial, struct nodo* Grafo){
    /// costo total para llegar al nodo final, distancia guarda la distancia para llegar al nodo final, predecesor guarda los nodos para imprimirlos en el camino
    int costo_total[Grafo->vertices][Grafo->vertices],distancia[Grafo->vertices],predecesor_grafo[Grafo->vertices];
    /// nodos visitados es para guardar los nodos a los que ya se accedio, contador es la cantidad de nodos que han sido accedidos
    int nodos_visitados[Grafo->vertices],contador,distancia_minima,siguiente_nodo,i,j;


    /// dos for para recorrer la matriz de adyacencia
    for(i=0;i<Grafo->vertices;i++){
        for(j=0;j<Grafo->vertices;j++){
            /// si la matriz de adyacencia no tiene una conexion entonces la marcamos con 9999
            if(Grafo->matriz_adyacencia[i][j]==0){
                costo_total[i][j]=RELLENO;
            }
            /// sino agregamos la arista al costo total
            else{
                costo_total[i][j]=Grafo->matriz_adyacencia[i][j];
            }
        }
    }
    
    /// for para inicializar distancia, predecesor de cada grafo y los nodos visitados
    for(i=0;i<Grafo->vertices;i++){
        distancia[i]=costo_total[nodo_inicial][i];
        predecesor_grafo[i]=nodo_inicial;
        nodos_visitados[i]=0;
    }

    distancia[nodo_inicial]=0;
    nodos_visitados[nodo_inicial]=1;
    contador=1;

    while(contador<Grafo->vertices-1){
        distancia_minima=RELLENO;
        //siguiente nodo se asigna la distancia minima una vez encontrado
        for(i=0;i<Grafo->vertices;i++)
            if(distancia[i]<distancia_minima&&!nodos_visitados[i]){
                distancia_minima=distancia[i];
                siguiente_nodo=i;
            }

    /// se encarga de revisar si existe un mejor camino
    nodos_visitados[siguiente_nodo]=1;
    for(i=0;i<Grafo->vertices;i++)
        if(!nodos_visitados[i]){
            if(distancia_minima+costo_total[siguiente_nodo][i]<distancia[i]){
                distancia[i]=distancia_minima+costo_total[siguiente_nodo][i];
                predecesor_grafo[i]=siguiente_nodo;
            }
        }
    contador++;
    }
    
    /// se encarga de imprimir la distancia y camino hacia cada nodo final
    for(i=0;i<Grafo->vertices;i++)
        if(i!=nodo_inicial){
        printf("\nDistancia hacia el nodo %d = %d",i,distancia[i]);
        printf("\nCamino = %d",i);
        j=i;
        do{
            j=predecesor_grafo[j];
            printf("<-%d",j);
        } while(j!=nodo_inicial);
    }
}

/**
 * @brief encontar arista minima
 * para seguir con la construccion del arbol se ocupa encontrar el arista con el menor peso
 * @param Grafo 
 * @param valor_minimo_arista 
 * @param vertices_faltantes 
 * @return int 
 */
int encontrar_arista_min(struct nodo* Grafo, int valor_minimo_arista[], int vertices_faltantes[]) {
    int valor_minimo = INT_MAX, arista_min;
    /// compara la arista de menor peso que tiene actualmente con el resto de aristas, si encuentra una de menor valor se guarda como la nueva arista de menor peso
    for (int v = 0; v < Grafo->vertices; v++){
        if (vertices_faltantes[v] == 0 && valor_minimo_arista[v] < valor_minimo)
            valor_minimo = valor_minimo_arista[v], arista_min = v;
    }
    /// se devuelve la arista con el menor peso
    return arista_min;
}
 
 /**
  * @brief imprimir el arbol de expansion minima de prim
  * 
  * @param Grafo 
  * @param nodo_padre 
  * @param nodo 
  * @return 0 
  */
int imprimir_arbol_expansion_minima_prim(struct nodo* Grafo, int nodo_padre[], int nodo) {
    /// se encarga de imprimir la conexion entre dos nodos (nodo padre y nodo actual) y su respectivo peso del arista
    printf("Conexion   Peso\n");
    for (int nodo_actual = 1; nodo_actual < Grafo->vertices; nodo_actual++){
        printf("%d - %d      %d \n", nodo_padre[nodo_actual], nodo_actual, Grafo->matriz_adyacencia[nodo_actual][nodo_padre[nodo_actual]]);
    }
    return 0;
}

/**
 * @brief arbol de expansion minima de prim
 * Se encarga de encontrar un arbol que incluya todos los vertices del grafo, donde el peso total de las aristas del arbol es el minimo posible
 * @param Grafo 
 */
void arbol_expansion_minima_prim(struct nodo* Grafo){
    /// se encarga de ir guardando el arbol
    int nodo_padre[Grafo->vertices];
    /// se encarga de buscar la arista con menor peso
    int valor_minimo_arista[Grafo->vertices], i, contador;
    /// para aquellos vertices que aun no se han incluido dentro del arbol de expansion minima
    int vertices_faltantes[Grafo->vertices]; // To represent set of vertices not yet included in MST
 
    /// todos los valores minimos de las aristas se rellenan hasta que se acceda a ellas
    for (i = 0; i < Grafo->vertices; i++)
        valor_minimo_arista[i] = INT_MAX, vertices_faltantes[i] = 0;
 
    /// para siempre incluir el nodo padre y que se elegido como tal a la hora de imprimirlo
    valor_minimo_arista[0] = 0; 
    nodo_padre[0] = -1; 
 
    /// for que se extiende en la cantidad de vertices
    for (contador = 0; contador < Grafo->vertices - 1; contador++) {
        /// para encontrar el proximo nodo que se vaya a visitar se ocupa encontrar el arista con menor valor
        int arista = encontrar_arista_min(Grafo, valor_minimo_arista, vertices_faltantes);
        vertices_faltantes[arista] = 1;
 
        /// for para comprobar si se ha encontrado finalmente el arbol de expansion minima
        for (int vertice = 0; vertice < Grafo->vertices; vertice++)
            if (Grafo->matriz_adyacencia[arista][vertice] && vertices_faltantes[vertice] == 0 && Grafo->matriz_adyacencia[arista][vertice] < valor_minimo_arista[vertice])
                nodo_padre[vertice] = arista, valor_minimo_arista[vertice] = Grafo->matriz_adyacencia[arista][vertice];
    }
 
    /// imprime el arbol de expansion minima de prim
    imprimir_arbol_expansion_minima_prim(Grafo, nodo_padre, Grafo->vertices);
}

/**
 * @brief main del programa
 * 
 * @return 0
 */
int main(){
    struct nodo *Grafo = calloc(1, sizeof(struct nodo));
    //char aceptar;
    printf("                   Proyecto 3\n");
    printf("Tema: Grafo no dirigido fuertemente conexo y valorado\n\n"
    "Representaciones del grafo:\n"
    "1. Matriz de Adyacencia: representa las generar_conexiones entre pares de nodos\n"
    "2. Recorrido en profundidad: permite recorrer todos los nodos de un grafo\n\n"
    "Algoritmos:\n"
    "Arbol de expansion minima de Prim: un arbol que incluya todos los vertices del grafo, donde el peso total de las aristas del arbol es el minimo posible\n"
    "Dijkstra: sirve para encontrar el camino de costo_totale minimo desde un nodo origen a todos los demas nodos del grafo\n\n");
    int opcion;
    int nodo_inicial;
    int nodo_inicio;
   do
    {   //imprime el menu
        printf("\n1.Inicializar el grafo\n"
        "2.Generar conexiones en el grafo\n"
        "3.Imprimir Matriz Adyacencia con peso de aristas\n"
        "4.Recorrido en profundidad\n"
        "5.Algoritmo de Dijkstra\n"
        "6.Algoritmo del Arbol de expansion minima de Prim\n"
        "7.Salir\n");
        //apartir de este punto vamos a filtrar la entrada del usuario
        do{
        printf("\nEnter an option [1-7]: ");
        scanf("%d",&opcion);
        } while (opcion < 1 || opcion > 7);
        switch (opcion)
        {
        case 1: 
            inicializar(Grafo);
            break; 
        case 2: 
            generar_conexiones(Grafo);
            break;
        case 3:
            imprimir_matriz(Grafo);
            break;
        case 4:
            printf("Ingrese el nodo inicial \n");
            scanf("%d", &nodo_inicial);
            recorrido_Profundidad(nodo_inicial, Grafo);
            break;
        case 5:
            printf("Ingrese el nodo inicial \n");
            scanf("%d", &nodo_inicio);
            dijkstra(nodo_inicio, Grafo);
            break;
        case 6:
            arbol_expansion_minima_prim(Grafo);
            break;
        default: // en caso de que el usuario digite un input incorrecto
            //printf("enter a valid option\n");
            break;
        } 
    } while (opcion != 7);
    return 0;
}

