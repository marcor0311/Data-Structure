#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct nodo_lista{
    int hijo;
    char* NombreArchivo;
    struct nodo_lista* sig;
}nodo_lista;

typedef struct lista_chaflaneado{
    struct nodo_lista* inicio;
}lista_chaflaneado;

typedef struct nodo_chaflaneado{
    char* termino;
    lista_chaflaneado* ListaArchivos;

    struct nodo_chaflaneado* hijo_izquierdo;
    struct nodo_chaflaneado* hijo_derecho;
} nodo_chaflaneado;

nodo_lista* crearNodoLista(char* filename){
    struct nodo_lista* nodo_nuevo = calloc(1,sizeof(struct nodo_lista));
    nodo_nuevo->NombreArchivo= filename;
    return nodo_nuevo;
}


lista_chaflaneado* crearLista(char* firstFileName){
    struct lista_chaflaneado* listaNva = calloc(1,sizeof(struct lista_chaflaneado));
    struct nodo_lista* primernodo = calloc(1,sizeof(struct nodo_lista));
    primernodo->NombreArchivo = firstFileName;
    listaNva->inicio = primernodo;
    return listaNva;
}

int Comparacion_ascii(char* string1, char* string2){
  int value;
  value = strcmp (string1, string2);
  return value;
}

void InsertarEnLista(struct lista_chaflaneado* lista,char* filename){
    nodo_lista* nodoact = lista->inicio;
    while (nodoact->sig != NULL){ //Se detiene cuando el nodo siguiente es nulo
        nodoact = nodoact->sig;
    }
    nodo_lista* nodoInsertar = crearNodoLista(filename);
    nodoact->sig=nodoInsertar;
}


void ImprimirLista(struct lista_chaflaneado* lista){
    struct nodo_lista* nodoact = lista->inicio;
    while (nodoact != NULL){
        printf("%s -> ",nodoact->NombreArchivo);
        nodoact = nodoact->sig;
    }
    printf("\n");
}

nodo_chaflaneado* inicializar_nodo_chaflaneado(char* termino){
    nodo_chaflaneado* nodo = calloc(1, sizeof(nodo_chaflaneado));
    nodo->termino = termino;
    nodo-> hijo_izquierdo = NULL;
    nodo-> hijo_derecho = NULL;
    return nodo;
}

typedef struct arbol_chaflaneado{
    nodo_chaflaneado* raiz;
    struct arbol_chaflaneado* hijo_izq;
    struct arbol_chaflaneado* hijo_der;
} arbol_chaflaneado;


 arbol_chaflaneado* inicializar_arbol_chaflaneado(char* termino){
    arbol_chaflaneado* arbol = calloc(1, sizeof(arbol_chaflaneado));
    arbol -> raiz = inicializar_nodo_chaflaneado(termino);
    return arbol;
    //nodo_chaflaneado* hijo_izq = inicializar_nodo_chaflaneado(exampledata);
    //nodo_chaflaneado* hijo_der = inicializar_nodo_chaflaneado(exampledata);
    //arbol -> hijo_izq = hijo_izq;
    //arbol -> hijo_der = hijo_der;
    //arbol -> raiz -> hijo_izquierdo = hijo_izq;
    //arbol -> raiz -> hijo_derecho = hijo_der;
}

nodo_chaflaneado* buscar_nodo_padre(nodo_chaflaneado* raiz, nodo_chaflaneado* nodo){ //se debe llamar a "raiz" como la raíz del árbol
    if(raiz == NULL || raiz == nodo){
        return NULL;
    }
    if(raiz -> hijo_izquierdo == nodo || raiz -> hijo_derecho == nodo){
        return raiz;
    }
    else{
        return buscar_nodo_padre(raiz -> hijo_izquierdo,nodo);
        return buscar_nodo_padre(raiz -> hijo_derecho,nodo);
    }
    return NULL;
}

void rotacion_derecha(arbol_chaflaneado* arbol,nodo_chaflaneado* n){
    nodo_chaflaneado* n1 = buscar_nodo_padre(arbol -> raiz,n);
    n->hijo_izquierdo=n1->hijo_derecho;
    n1->hijo_derecho=n;
    n = n1;
}

void rotacion_izquierda(arbol_chaflaneado* arbol, nodo_chaflaneado* n){
    nodo_chaflaneado* n1 = buscar_nodo_padre(arbol -> raiz,n);
    n -> hijo_derecho = n1 -> hijo_izquierdo;
    n1 -> hijo_izquierdo = n;
    n = n1;
}

int determinar_caso(nodo_chaflaneado* nodo, nodo_chaflaneado* padre, nodo_chaflaneado* abuelo){
    if(abuelo){
        if((Comparacion_ascii(abuelo -> termino, padre -> termino) < 0 ) && (Comparacion_ascii(padre -> termino, nodo -> termino) < 0)){ //abuelo<padre<nodo
            return 3;
        }
        else if((Comparacion_ascii(abuelo -> termino, padre -> termino) > 0 ) && (Comparacion_ascii(padre -> termino, nodo -> termino) > 0)){ //abuelo>padre>nodo
            return 4;
        }
        else if((Comparacion_ascii(abuelo -> termino, padre -> termino) > 0 ) && (Comparacion_ascii(padre -> termino, nodo -> termino) < 0)){ //abuelo>padre<nodo
            return 2;
        }
        else if((Comparacion_ascii(abuelo -> termino, padre -> termino) < 0 ) && (Comparacion_ascii(padre -> termino, nodo -> termino) > 0)){ //abuelo<padre>nodo
            return 1;
        }
    }

    else{
        if(Comparacion_ascii(padre -> termino, nodo -> termino) < 0){ //padre < hijo
            return 6;
        }

        else if(Comparacion_ascii(padre -> termino, nodo -> termino) > 0){ //padre > hijo
            return 5;
        }
    }
}


void subir_nodo(arbol_chaflaneado* arbol, nodo_chaflaneado* nodo){
    nodo_chaflaneado* padre = buscar_nodo_padre(arbol -> raiz, nodo);
    nodo_chaflaneado* abuelo = buscar_nodo_padre(arbol -> raiz,padre);

    int caso = determinar_caso(nodo, padre, abuelo);

    if(caso ==1){
        rotacion_derecha(arbol, padre);
        rotacion_izquierda(arbol, abuelo);
    }

    else if(caso == 2){
        rotacion_izquierda(arbol, padre);
        rotacion_derecha(arbol, abuelo);

    }

    else if(caso == 3){
        rotacion_izquierda(arbol, abuelo);
        rotacion_izquierda(arbol, nodo);

    }

    else if(caso == 4){
        rotacion_derecha(arbol, abuelo);
        rotacion_derecha(arbol, padre);

    }

    else if(caso == 5){
        rotacion_derecha(arbol, padre);
        
    }

    else if(caso == 6){
        rotacion_izquierda(arbol, padre);

    }


}


void chaflanear_nodo(arbol_chaflaneado* arbol, nodo_chaflaneado* nodo){
    while(arbol -> raiz != nodo){
        subir_nodo(arbol, nodo);
    }
    return;
}


void insertar_arbol_chaflaneado(nodo_chaflaneado* nodo, char* termino, arbol_chaflaneado* arbol){ //se debe llamar al nodo como la raíz del árbol
    nodo_chaflaneado* nuevo_nodo = inicializar_nodo_chaflaneado(termino);
    if(nodo == NULL){
      nodo = nuevo_nodo;
      chaflanear_nodo(arbol, nodo);
      return;
    }

    else if(Comparacion_ascii(termino, nodo -> termino) < 0){
        insertar_arbol_chaflaneado(nodo -> hijo_izquierdo, termino, arbol);
    }

    else if(Comparacion_ascii(termino, nodo -> termino) > 0){
        insertar_arbol_chaflaneado(nodo -> hijo_derecho, termino, arbol);
    }

   
    
} 


nodo_chaflaneado* buscar_arbol_chaflaneado(nodo_chaflaneado* nodo, char* termino, arbol_chaflaneado* arbol){ //se debe llamar al nodo como la raíz del árbol
    if(nodo == NULL){
        chaflanear_nodo(arbol, buscar_nodo_padre(arbol -> raiz, nodo));
        return NULL;
    }
    else if((Comparacion_ascii(termino, nodo -> termino)) < 0){
        return buscar_arbol_chaflaneado(nodo -> hijo_izquierdo, termino, arbol);
    }
    else if((Comparacion_ascii(termino, nodo -> termino)) > 0){
        return buscar_arbol_chaflaneado(nodo -> hijo_derecho, termino, arbol);
    }
    else{
        chaflanear_nodo(arbol, nodo);
        return nodo;
    }
    
   
}

void imprimir_preorden(nodo_chaflaneado* nodo){//se debe llamar al nodo como la raíz del árbol
    if(nodo == NULL){
        return;
    }

    printf("%s\n", nodo -> termino);
    imprimir_preorden(nodo -> hijo_izquierdo);
    imprimir_preorden(nodo -> hijo_derecho);
}  
