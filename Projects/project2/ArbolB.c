#include <stdlib.h>
#include <string.h>
#include <stdio.h>
/*
Structs que usa el arbol B
*/
//Struct nodoB, se usa como los nodos de la listaB
typedef struct nodoB{
    char* NombreArchivo;
    struct nodoB* sig;
} nodoB;
//Struct listaB, es una lista que guarda nombres de archivos, que corresponden a los nombres de las noticias de algun termino 
typedef struct listaB{
    struct nodoB* inicio;
    struct nodoB* ultimoNodo;
} listaB;
//Struct llave, corresponde a una llave de los nodos del arbol B (tambien llamados paginas).
typedef struct llave{
    char* termino;
    struct listaB* ListaArchivos;
} llave;
//Struct pagina, corresponde a un nodo del arbol B, que tiene llaves y paginas hijas.
typedef struct pagina{
    struct llave** llaves;
    int NumeroLlaves;
    struct pagina** hijos;
} pagina;
//Struct nodoH, utilizado en la lista del struct historial
typedef struct nodoH{
    struct llave* key;
    struct nodoH* sig;
} nodoH;
//Struct historial, se usa para llevar un registro de las llaves que se han ido annadiendo al arbol
typedef struct historial{ 
    struct nodoH* inicio;
    struct nodoH* ultimo;
} historial;
//Struct arbolB, tiene un puntero a la raiz del arbol B, y un historial de las llaves que se han ido metiendo
typedef struct arbolB{
    struct pagina* raizDelArbol;
    struct historial* Historial;
} arbolB;
//Struct EstaTerminoConPagina, la idea es que contenga informacion si un termino esta en el arbol, 
//y en caso que si, tenga la pagina en la que se encuentra
struct EstaTerminoConPagina{
    int TerminoEnArbol;
    struct pagina* PaginaConTermino;
};
/*
*Arreglo de caracteres deseados para crear terminos.
*/
char char_deseados[]= {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'á', 'b', 'c', 'd',
                       'e', 'é', 'f', 'g', 'h', 'i', 'í', 'j', 'k', 'l', 'm', 'n', 'ñ', 'o', 'ó',
                       'p', 'q', 'r', 's', 't', 'u', 'ú', 'ü', 'v', 'w', 'x', 'y', 'z', 'A', 'Á',
                       'B', 'C', 'D', 'E', 'É', 'F', 'G', 'H', 'I', 'Í', 'J', 'K', 'L', 'M', 'N',
                       'Ñ', 'O', 'Ó', 'P', 'Q', 'R', 'S', 'T', 'U', 'Ú', 'Ü', 'V', 'W', 'X', 'Y',
                       'Z', '-', '_', '@'};
/*
*Funciones para que comparan caracteres y strings
*/
int ASCII_comparison(char *string1, char *string2)
{
    int value;
    value = strcmp(string1, string2);
    return value;
}
/* Funcion que verifica si un caracter enviado se encuentra en el arreglo anterior.
*  Retorna 1 si esta, 0 sino.
*/
int verificar_char(char caracter){
    for(int i = 0; i < 79; i++){
        if(char_deseados[i] == caracter){
            return 1;
        }
    }
    return 0;
}

/*
*Funciones sobre la lista de nombres de archivos.
*/
nodoB* crearNodoB(char* filename){
    struct nodoB* nodoNvo = calloc(1,sizeof(struct nodoB));
    nodoNvo->NombreArchivo= filename;
    return nodoNvo;
}
//Funcion que crea una lista B con el nombre del archivo inicial
listaB* crearListaB(char* firstFileName){
    listaB* listaNva = calloc(1,sizeof(listaB));
    nodoB* primernodo = calloc(1,sizeof(nodoB));
    primernodo->NombreArchivo = firstFileName;
    listaNva->inicio=primernodo;
    listaNva->ultimoNodo=primernodo;
    return listaNva;
}
//Funcion que crea una lista B sin el nombre del archivo inicial
struct listaB* crearListaBVacia(){
    struct listaB* listaNva = calloc(1,sizeof(struct listaB));
    return listaNva;
}
//Metodo que inserta el nombre de un archivo en una lista B
void InsertarEnListaB(struct listaB* lista,char* filename){
    struct nodoB* nodoInsertar = crearNodoB(filename);
    if (lista->inicio==NULL){ //Si la lista esta vacia, insertarlo al inicio
        lista->inicio = nodoInsertar;
        lista->ultimoNodo = nodoInsertar;
    }
    else{ //Si la lista no esta vacia, llegar al ultimo nodo y meterlo.
        if (strcmp(lista->ultimoNodo->NombreArchivo,filename) == 0){
            //Si ya estaba annadido no hacer nada
        }
        else{
            lista->ultimoNodo->sig=nodoInsertar;//Ponerlo al final
            lista->ultimoNodo=nodoInsertar;//Actualizar el ultimo nodo
        }
    }
}

/*
*Funciones sobre los structs de historial de claves metidas al arbol B.
*/
nodoH* crearNodoH(llave* clave){
    struct nodoH* nodoNvo = calloc(1,sizeof(struct nodoB));
    nodoNvo->key = clave;
    return nodoNvo;
}

struct historial* CrearHistorial(){
    struct historial* resp = calloc(1,sizeof(struct historial));
    return resp;
}
void meterLlaveHistorial(struct historial* histo, struct llave* Clave){
    struct nodoH* nodo_insertar = crearNodoH(Clave);
    if (histo ->inicio == NULL){
        histo->inicio = nodo_insertar;
        histo->ultimo = nodo_insertar;
    }
    else{
        histo->ultimo->sig = nodo_insertar; //Ponerlo al final
        histo->ultimo = nodo_insertar; //Actualizar el puntero al ultimo
    }
}

/*
Funciones del arbol B
*/

//Funcion de crear una llave para el arbol.
struct llave* crearLlave(char* Termino,struct listaB* ListaDeArchivos){
    struct llave* resp = calloc(1,sizeof(struct llave));
    resp->termino = Termino;
    resp->ListaArchivos = ListaDeArchivos;
    return resp;
}
//Funcion de crear una pagina de llaves vacia.
struct pagina* crearPagina(){
    struct pagina* raiz = calloc(1,sizeof(struct pagina));
    raiz->llaves = calloc(5,sizeof(struct llave)); //Cada pagina tiene 4 claves, pero se annade 1 para hacer particiones
    raiz->hijos = calloc(6,sizeof(struct pagina)); //Cada pagina tiene 5 hijos, pero se annade 1 para las particiones
    return raiz;
}
//Funcion que imprime una pagina del arbol B.
void ImprimirPagina(struct pagina* pagina){
    printf("[|");
    for (int i =0;i<5;i++){
        if (pagina->llaves[i] != NULL){
                    printf("%s",pagina->llaves[i]->termino);
                    printf("|");
        }
        else{
            printf(" |");
        }
    }
    printf("] \n");
}
//Funcion que crea un arbol B con una raiz ya creada.
struct arbolB* crearArbolB(struct pagina* RaizInicial){
    struct arbolB* resp = calloc(1,sizeof(struct arbolB));
    resp->raizDelArbol = RaizInicial;
    struct historial* nvoHistorial = CrearHistorial();//Empezar el historial con la primera llave.
    resp->Historial=nvoHistorial;
    return resp;
}
//Funcion que crea un arbol B vacio.
struct arbolB* crearArbolBVacio(){
    struct arbolB* resp = calloc(1,sizeof(struct arbolB));
    return resp;
}
//Funcion que crea un struct que indica si un termino esta en una 
struct EstaTerminoConPagina* crearStructTerminoConPagina(struct pagina* raiz,int Boolean){
    struct EstaTerminoConPagina* Respuesta = calloc(1,sizeof(struct EstaTerminoConPagina));
    Respuesta->TerminoEnArbol = Boolean;
    Respuesta->PaginaConTermino = raiz;
    return Respuesta;
}
//Funcion que determina si una pagina es hoja
int EsHoja(struct pagina* Arbol){
    for (int i=0;i<6;i++){
        if (Arbol->hijos[i] !=NULL){
            return 0;
        }
    }
    return 1;
}
//Despeja un espacio a meter una pagina, mueve hijos si es que tiene.
void CorrerALaDerecha(struct pagina* pagina, int PosClaveACorrer){
    int posACorrer = 4;
    while (posACorrer !=PosClaveACorrer-1){ //Este while corre lo que hay en PosACorrer, se detiene cuando se haya corrido la pos deseada
        if (pagina->llaves[posACorrer] != NULL){
            struct llave* act = pagina->llaves[posACorrer];
            pagina->llaves[posACorrer+1] = act;
        }
        if (pagina->hijos[posACorrer] != NULL){
            struct pagina* act = pagina->hijos[posACorrer];
            pagina->hijos[posACorrer+1] = act;
        }
        posACorrer--;
    }
}
//Buscar la pagina en la que se tiene que meter la llave
struct pagina* UltimaPagina(struct pagina* Arbol,struct llave* LlaveAMeter){
    int esHoja = EsHoja(Arbol);
    if (esHoja == 1){ //Si es un nodo hoja, ahi se tiene que meter la llave.
        return Arbol;
    }
    struct llave** Llaves = Arbol->llaves;
    //En este punto, se tiene que buscar la UltimaPagina en los hijos.
    for (int i=0;i<Arbol->NumeroLlaves;i++){
        char* TerminoAct = Llaves[i]->termino;
        char* TerminoAMeter = LlaveAMeter->termino;
        int ComparacionTerminos = ASCII_comparison(TerminoAMeter,TerminoAct);
        if (ComparacionTerminos < 0){ //Si es menor al termino 0, buscar en el hijo 0, si es menor al termino 1, buscar en hijo 1 etc.
            return UltimaPagina(Arbol->hijos[i],LlaveAMeter);
        }
        //Caso de que el arbol tenga 4 llaves, y 5 hijos, y el termino a meter sea menor al termino en la posicion 3.
        if (ComparacionTerminos>0 && Llaves[i+1]==NULL){
            return UltimaPagina(Arbol->hijos[i+1],LlaveAMeter);
        }
    }
}
//Dado una llave y un arbol, determina la posicion en la que se debe meter esa llave
int PosAMeterLLave(struct pagina* Arbol,struct llave* Clave){
    struct llave** LlavesArbol = Arbol->llaves;
    char* TerminoAMeter = Clave->termino;
    int PosicionResp = 0;
    while (PosicionResp <4){ //Ve si va en alguno de los 4 espacios disponibles
        if (LlavesArbol[PosicionResp] == NULL){//Si no hay clave en esa posicion, se mete ahi
            return PosicionResp;
        }
        char* TerminoMetido = LlavesArbol[PosicionResp]->termino;
        int ComparacionTerminos = ASCII_comparison(TerminoAMeter,TerminoMetido);
        if (ComparacionTerminos <0){//Si el termino a meter es menor a la clave en esa posicion, ahi debe ir
            return PosicionResp;
        }
        PosicionResp++;
        
    }
    return PosicionResp;
}
//Funcion que retorna 1 si un termino esta en una pagina, 0 sino.
int TerminoEnPagina(struct pagina* raiz,char* Termino){
    for (int i =0;i<4;i++){
        if (raiz->llaves[i] == NULL){
            return 0;
        }
        if (Termino == raiz->llaves[i]->termino){
            return 1;
        }
    }
    return 0;
}
//Retorna 1 si el termino esta en el arbol, 0 sino.
int TerminoEnArbol(struct pagina* raiz, char* Termino){
    //printf("termino buscandose %s, comparacion con de %d\n",Termino,strcmp(Termino,"de"));
    if (raiz == NULL)
    {
        //printf("El termino sin raiz es %s \n",Termino);
        return 0;
    }
    if (EsHoja(raiz)){
       // printf("eshojita\n");
        int x = 0;
        while (raiz->llaves[x]!=NULL){
            if (strcmp(raiz->llaves[x]->termino,Termino) == 0){ //Si son iguales
                //printf("%s y %s son iguales \n",raiz->llaves[i]->termino,Termino);
                return 1;
            }
            x++;
        }
        return 0;
    }
    for(int i =0;i<4;i++){
        if (raiz->llaves[i] != NULL){
            char* TerminoMetido = raiz->llaves[i]->termino;
            int ComparacionTerminos = ASCII_comparison(Termino,TerminoMetido);
            //printf("termino: %s, terminoMetido %s\n",Termino,TerminoMetido);
            //printf("comparacion: %d\n",ComparacionTerminos);
            //printf("comparacion2: %d\n",strcmp(Termino,TerminoMetido));
            if (ComparacionTerminos<0){ //Si es menor, buscar en su hijo.
                return TerminoEnArbol(raiz->hijos[i],Termino);
            }
            if (ComparacionTerminos == 0){ //Si es igual, retornar 1.
                return 1;
            }
            if (ComparacionTerminos>0 && raiz->llaves[i+1]==NULL){ //Si esta en el ultimo elemento, irse al hijo derecho
                //printf("proqui\n");
                return TerminoEnArbol(raiz->hijos[i+1],Termino);
            }

        }
    }
    return 0;
}

struct EstaTerminoConPagina* TerminoEnArbolConPagina(struct pagina* raiz, char* Termino){
    //printf("termino buscandose %s, comparacion con de %d\n",Termino,strcmp(Termino,"de"));
    if (raiz == NULL)
    {
        return crearStructTerminoConPagina(raiz,0);
    }
    if (EsHoja(raiz)){
       // printf("eshojita\n");
        int x = 0;
        while (raiz->llaves[x]!=NULL){
            if (strcmp(raiz->llaves[x]->termino,Termino) == 0){ //Si son iguales
                //printf("%s y %s son iguales \n",raiz->llaves[i]->termino,Termino);
                return crearStructTerminoConPagina(raiz,1);
            }
            x++;
        }
        return crearStructTerminoConPagina(raiz,0);
    }
    for(int i =0;i<4;i++){
        if (raiz->llaves[i] != NULL){
            char* TerminoMetido = raiz->llaves[i]->termino;
            int ComparacionTerminos = ASCII_comparison(Termino,TerminoMetido);
            //printf("termino: %s, terminoMetido %s\n",Termino,TerminoMetido);
            //printf("comparacion: %d\n",ComparacionTerminos);
            //printf("comparacion2: %d\n",strcmp(Termino,TerminoMetido));
            if (ComparacionTerminos<0){ //Si es menor, buscar en su hijo.
                return TerminoEnArbolConPagina(raiz->hijos[i],Termino);
            }
            if (ComparacionTerminos == 0){ //Si es igual, retornar 1.
                return crearStructTerminoConPagina(raiz,1);
            }
            if (ComparacionTerminos>0 && raiz->llaves[i+1]==NULL){ //Si esta en el ultimo elemento, irse al hijo derecho
                //printf("proqui\n");
                return TerminoEnArbolConPagina(raiz->hijos[i+1],Termino);
            }

        }
    }
    return crearStructTerminoConPagina(raiz,0);
}
//Retorna la pagina que tiene un termino. 
//Como requisitos, el termino tiene que estar en el arbol.
struct pagina* encontrarPaginaConTermino (struct pagina* raiz,char* Termino){
    if (EsHoja(raiz)){
        return raiz;
    }
    for (int i=0;i<5;i++){
        char* TerminoMetido = raiz->llaves[i]->termino;
        int ComparacionTerminos = ASCII_comparison(Termino,TerminoMetido);
        if (ComparacionTerminos < 0){
            return encontrarPaginaConTermino(raiz->hijos[i],Termino);
        }
        if (ComparacionTerminos == 0){
            return raiz;
        }
        if (ComparacionTerminos >0 && raiz->llaves[i+1]==NULL){
            return encontrarPaginaConTermino(raiz->hijos[i+1],Termino);
        }
    }
}

//Esta funcion se llama cuando el arbol hijo no es la raiz del arbol
struct pagina* encontrarArbolPadre(struct arbolB* miArbolB, struct pagina* raizAct,struct pagina* ArbolHijo){
    char* TerminoAuxiliar = ArbolHijo->llaves[0]->termino; //Termino que va a ayudar a la busqueda del nodo padre.
    for (int i=0;i<4;i++){
        if (raizAct->llaves[i]!=NULL){
            char* TerminoMetido = raizAct->llaves[i]->termino;
            int ComparacionTerminos = ASCII_comparison(TerminoAuxiliar,TerminoMetido);
            if (ComparacionTerminos<0){
                if (raizAct->hijos[i] == ArbolHijo){ //Si se encuentra el hijo, se retorna este arbol padre
                    return raizAct;
                }
                else{
                    return encontrarArbolPadre(miArbolB,raizAct->hijos[i],ArbolHijo); //Se busca mas abajo
                }
            }
            if (ComparacionTerminos>0 && raizAct->llaves[i+1]==NULL){
                    if (raizAct->hijos[i+1] == ArbolHijo){
                        return raizAct;
                    }
                    else{
                        return encontrarArbolPadre(miArbolB,raizAct->hijos[i+1],ArbolHijo);
                    }
                }
            }
        }
    }

//Se sabe que al partir la vara es que hay 5 claves, cuando el maximo es de 4.
void Restructurar_arbol(struct arbolB* miArbolB, struct pagina* ArbolAPartir){
    struct pagina* Izquierda = crearPagina();
    struct pagina* Derecha = crearPagina();
    struct llave* LlaveASubir = ArbolAPartir->llaves[2];
    Izquierda->llaves[0] = ArbolAPartir->llaves[0]; //Al partir el arbol, sube la clave en la pos 2.
    Izquierda->llaves[1] = ArbolAPartir->llaves[1];
    Izquierda->NumeroLlaves = 2;
    Derecha->llaves[0] = ArbolAPartir->llaves[3];
    Derecha->llaves[1] = ArbolAPartir->llaves[4];
    Derecha->NumeroLlaves = 2;
    if (ArbolAPartir == miArbolB->raizDelArbol){ //Si la particion va a ser en la raiz
        struct pagina* nvaRaiz = crearPagina();
        nvaRaiz->llaves[0]= LlaveASubir;
        nvaRaiz->NumeroLlaves = 1;
        nvaRaiz->hijos[0]= Izquierda;
        nvaRaiz->hijos[1] = Derecha;
            Izquierda->hijos[0]=ArbolAPartir->hijos[0];
            Izquierda->hijos[1]=ArbolAPartir->hijos[1];
            Izquierda->hijos[2]=ArbolAPartir->hijos[2];
            Derecha->hijos[0]=ArbolAPartir->hijos[3];
            Derecha->hijos[1]=ArbolAPartir->hijos[4];
            Derecha->hijos[2]=ArbolAPartir->hijos[5];
        miArbolB->raizDelArbol=nvaRaiz;
    }
    else{//Si la particion no va a ser en la raiz
        struct pagina* NodoPadre = encontrarArbolPadre(miArbolB,miArbolB->raizDelArbol,ArbolAPartir);
        //printf("Imprimiendo nodo padre viejo:\n");
        //ImprimirPagina(NodoPadre);
        //printf("cantidad de claves vieja %d \n",NodoPadre->NumeroLlaves);
        int posASubirLlave = PosAMeterLLave(NodoPadre,LlaveASubir);
        CorrerALaDerecha(NodoPadre,posASubirLlave);
        NodoPadre->llaves[posASubirLlave]=LlaveASubir;
        NodoPadre->hijos[posASubirLlave]=Izquierda;
        NodoPadre->hijos[posASubirLlave+1]=Derecha;
        NodoPadre->NumeroLlaves+=1;
            Izquierda->hijos[0]=ArbolAPartir->hijos[0];
            Izquierda->hijos[1]=ArbolAPartir->hijos[1];
            Izquierda->hijos[2]=ArbolAPartir->hijos[2];
            Derecha->hijos[0]=ArbolAPartir->hijos[3];
            Derecha->hijos[1]=ArbolAPartir->hijos[4];
            Derecha->hijos[2]=ArbolAPartir->hijos[5];
        //printf("Imprimiendo nodo padre nuevo:\n");
        //ImprimirPagina(NodoPadre);
        //printf("cantidad de claves nueva %d \n",NodoPadre->NumeroLlaves);
        
    }

}

//Mete una llave en una hoja raiz.
void meterLlave(struct pagina* Arbol,struct llave* Clave){
    int posAMeter = PosAMeterLLave(Arbol,Clave); //Obtiene la posicion en la que debe ir la llave
    CorrerALaDerecha(Arbol,posAMeter); //Despeja esa posicion
    Arbol->llaves[posAMeter] = Clave; //Mete la llave
    Arbol->NumeroLlaves++; //Aumenta el numero de llaves
}

void insertar_llave_arbol_B(struct arbolB* ArbolPrincipal, struct llave* Clave){
    if (ArbolPrincipal->raizDelArbol == NULL){ //Arbol no iniciado
        struct pagina* nvaRaiz = crearPagina();
        nvaRaiz->llaves[0]= Clave;
        nvaRaiz->NumeroLlaves=1;
        ArbolPrincipal->raizDelArbol=nvaRaiz;
        ArbolPrincipal->Historial = CrearHistorial();
        meterLlaveHistorial(ArbolPrincipal->Historial,Clave);
    }
    else{
        meterLlaveHistorial(ArbolPrincipal->Historial,Clave);
        struct pagina* raizPrincipal = ArbolPrincipal->raizDelArbol;
        struct pagina* PaginaAInsertarle = UltimaPagina(raizPrincipal,Clave);
        meterLlave(PaginaAInsertarle,Clave);
        struct pagina* PaginaProblematica = encontrarPaginaConTermino(ArbolPrincipal->raizDelArbol,Clave->termino);
        while (PaginaProblematica->NumeroLlaves==5){
            Restructurar_arbol(ArbolPrincipal,PaginaProblematica);
            PaginaProblematica = encontrarPaginaConTermino(ArbolPrincipal->raizDelArbol,PaginaProblematica->llaves[2]->termino);
        }
    }
}


void Imprimir_preorden_B(struct pagina* raiz,int espacios){
    if (raiz==NULL){
        //hacer nada
    }
    else{
        for (int i=0;i<espacios;i++){
            printf("    ");
        }
        ImprimirPagina(raiz);
        for (int i =0;i<6;i++){
            Imprimir_preorden_B(raiz->hijos[i],espacios+1);
        }
    }
}
char* StringHeap(char* termino){
    int longitud = strlen(termino);
    char* nvo = calloc(longitud,sizeof(char));
    strcpy(nvo,termino);
    for (int i=0;i<20;i++){
        termino[i] = 0;
    }
    return nvo;
}
char* PegarStringsConFree(char *string1,char *string2)
{
    int tamaño1= strlen(string1);
    int tamaño2= strlen(string2);
    int tamañototal = tamaño1+tamaño2;

    char *new_String = calloc(tamañototal,sizeof(char));
    for(int i=0;i<tamaño1;i++)
    {
        new_String[i] = string1[i];
    }
    for(int j=0;j<tamaño2;j++)
    {
        new_String[j+tamaño1] = string2[j];
    }
    free(string1);
    free(string2);
    return new_String;
}
void meterStringEnString(char* principal, char* secundario){
    int posAInsertar = 0;
    while (principal[posAInsertar] != 0){ //Termina cuando posAInsertar es 0
        posAInsertar++;
    }
    for (int i=0;i<strlen(secundario);i++){
        principal[i+posAInsertar] = secundario[i];
    }
}
int longitudIdealLista(struct listaB* Lista){
    int resp = 0;
    struct nodoB* act = Lista->inicio;
    while (act != NULL){
        resp+=strlen(act->NombreArchivo);
        resp+=2;
        act=act->sig;
    }
    return resp;
}

int cantidadStringsListaB(struct listaB* Lista){
    int resp = 0;
    struct nodoB* act = Lista->inicio;
    while (act != NULL){
        resp+=1;
        act=act->sig;
    }
    printf("Cantidad de strings: %d",resp);
    return resp;
}
char* StringDeArchivosLista(struct listaB* Lista){
    struct nodoB* act = Lista->inicio;
    int longitudString = longitudIdealLista(Lista);
    //Y la cantidad debido a que van a ser separados por un | entre ellos
    char* resp = calloc(longitudString,sizeof(char));
    while (act != NULL){
        meterStringEnString(resp,act->NombreArchivo);
        meterStringEnString(resp,"|");
        act = act->sig;
    }
    return resp;
}
char* StringArbol(struct historial* h){
    if (h->inicio->key->termino==NULL){
        return "";
    }
    struct nodoH* act = h->inicio;
    int tamannoString = 0;
    while(act!=NULL){
        tamannoString+=strlen(act->key->termino);
        tamannoString++;
        tamannoString+= longitudIdealLista(act->key->ListaArchivos);
        act=act->sig;
    }
    char* resp = calloc(tamannoString,sizeof(char));
    act = h->inicio;
    while (act!=NULL){
        meterStringEnString(resp,act->key->termino);
        //printf("termino %s \n",act->key->termino);
        meterStringEnString(resp,"|");
        char* StringDeNombresArchivos = StringDeArchivosLista(act->key->ListaArchivos);
       // printf("archivos: %s \n",StringDeNombresArchivos);
        meterStringEnString(resp,StringDeNombresArchivos);
        meterStringEnString(resp,"*");
        act = act->sig;

    }
    return resp;
}
void GuardarArbol(struct arbolB* arbol){
    FILE *fp;
    fp = fopen("MiArbolB.txt", "w");
    char* stringEnArchivo = StringArbol(arbol->Historial);
    fputs(stringEnArchivo,fp);
    fclose(fp);

}


//Recorre un string desde un inicio especifico, y busca un caracter, si lo encuentra, retorna su posicion, si no
//retorna -1
long PosCharInString(char* stringGrande,long tamannoString,long inicio, char caracter){
    for (int i=inicio;i<tamannoString;i++){
        if (stringGrande[i] == caracter){
            return i;
        }
    }
    return -1;
}
//Verifica que un char alrededor de un separador sea valido
int VerificarCharArbolB(char Caracter){
    if (Caracter == '*' || verificar_char(Caracter) != 0){
        return 1;
    }
    return 0;
}
//Valida que un separador sea correcto al leer un archivo del arbol
int ValidarSeparador(char* StringArchivo,long lenString, long posSeparador){
    if (posSeparador==lenString-1){
        //Si esta al puro final, retornar -1
        return -1;
    }
    if (posSeparador==0){
        //Si esta al inicio, retornar -1
        return -1;
    }
    if (StringArchivo[posSeparador-1]==' ' ||StringArchivo[posSeparador+1] ==' '){
        //Si los caracteres alrededor del separador son invalidos, retornar -1
        return -1;
    }
}
//Verifica que todos los separadores de termino con archivos de lista de un archivo esten bien
int ValidarSeparadores(char* StringArchivo,long lenString){
    long SeparadorActual = PosCharInString(StringArchivo,lenString,0,'|');
    if (SeparadorActual ==-1){//Si no hay separador en todo el archivo, retornar -1
        return -1;
    }
    while (SeparadorActual !=-1){
        if (ValidarSeparador(StringArchivo,lenString,SeparadorActual) == -1){ //Si un separador no es valido, retornar -1
            return -1;
        }
        SeparadorActual = PosCharInString(StringArchivo,lenString,SeparadorActual+1,'|');//Que el separador no este al final ya fue validado anteriormente
    }
    return 1;

}
//Si el archivo correspondiente al arbol a cargar es valido, retorna 1, si no, retorna -1
int ArchivoValido(){
    FILE* archivo = fopen("MiArbolB.txt","r");
    if (archivo == NULL){
        return -1;//Si el archivo no existe, retornar -1
    }
    fseek(archivo, 0L, SEEK_END);
    long numbytes = ftell(archivo); //Guardar en numbytes la cantidad de bytes del archivo.
    fseek(archivo, 0L, SEEK_SET);//Poner el puntero en el inicio
    char* text = (char*)calloc(numbytes, sizeof(char)); //Dar memoria suficiente a text para almacenar el archivo
    if(text == NULL){
        return -1; //Si el archivo no tenia caracteres, terminar el programa con -1
    }
    fread(text, sizeof(char), numbytes, archivo); //Guardar todo el texto en un string
    int resp = ValidarSeparadores(text,numbytes); //Si todos los separadores estan bien, retorna 1, sino -1.
    free(text); //Liberar text.
    return resp;
}
//Mete el string desde el inicio hasta el final, inicio incluido, final incluido
char* CrearNuevoStringHeap(char* StringPadre, long inicio, long final){
    char* respuesta = calloc(final-inicio+2,sizeof(char));
    long posCharRespuesta = 0;
    for(long i=inicio; i<=final; i++){
        respuesta[posCharRespuesta] = StringPadre[i];
        posCharRespuesta++;
    }
    return respuesta;

}
//Dado un termino encuentra su llave en el arbol.
//El termino debe estar en el arbol.
struct llave* EncontrarLLaveConTermino(struct pagina* raizConTermino,char* Termino){
    int posclavecontermino = 0;
    //ImprimirPagina(paginacontermino);
    //printf("Termino buscado = %s longitud %ld \n",Termino,strlen(Termino));
    while (strcmp(raizConTermino->llaves[posclavecontermino]->termino,Termino)!=0){//While que busca la posicion de la clave con el termino buscado
        //printf("i = %d termino, longitud termino %ld = %s \n",posclavecontermino,strlen(paginacontermino->llaves[posclavecontermino]->termino),paginacontermino->llaves[posclavecontermino]->termino);
        posclavecontermino++;
    }
    return raizConTermino->llaves[posclavecontermino];
}
//El termino debe estar en el arbol
//Obtiene la lista de la llave que tiene un termino en especifico.
struct listaB* obtenerListaConTermino(struct pagina* raizConTermino,char* termino){
    return EncontrarLLaveConTermino(raizConTermino,termino)->ListaArchivos;
}
//El termino debe estar en el arbol
//Annade el el nombre del archivo a la lista de archivos de un termino.
void AnnadirNombreNoticiaEnTermino(struct pagina* raizConTermino, char* termino, char* nombrearchivo){
    InsertarEnListaB(obtenerListaConTermino(raizConTermino,termino),nombrearchivo);
}

/*Pasa de un string correspondiente al archivo de texto donde se guardo el arbol, y construye
*un arbol B a partir de este.
*/
void De_string_a_arbol(char* StringPadre, long tamanno,struct arbolB* arbol){
    int posAstericosAnterior=-1; //Se pone en -1 porque el archivo no inicia con asterisco
    int posSeparadorAnterior=-10; //Se pone en -10 para el caso de que se lea el primer termino
    char* termino;
    struct listaB* lista;
    struct llave* clave = NULL;
    for (long i=0;i<tamanno;i++){
        if (StringPadre[i] == '|'){//Fin de un termino o nombre de archivo     
            //El separador anterior esta mas adelante que el asterisco anterior. Lo que significa que es un nombre de archivo
            if (posSeparadorAnterior>posAstericosAnterior){
                char* nombrearchivo = CrearNuevoStringHeap(StringPadre,posSeparadorAnterior+1,i-1);
                InsertarEnListaB(lista,nombrearchivo);
            }

            //El asterisco anterior esta mas adelante que el separador anterior. Lo que significa que es un termino nuevo
            if (posAstericosAnterior>posSeparadorAnterior){
                if (clave !=NULL){ //Como se esta trabajando con un nuevo termino, se va a meter la llave anterior al arbol
                    insertar_llave_arbol_B(arbol,clave);
                }
                termino = CrearNuevoStringHeap(StringPadre,posAstericosAnterior+1,i-1); //Como es termino nuevo, se genera lista nueva
                lista = crearListaBVacia();
                clave = crearLlave(termino,lista); //Crea la llave con el termino y una lista vacia
            }
        posSeparadorAnterior = i;
        }
        if (StringPadre[i]=='*'){
            posAstericosAnterior = i;
        }
        
    }
}
//Funcion que retorna un arbol B creado a partir del archivo "MiArbol.txt" ubicado en el mismo folder del progorama
struct arbolB* Cargar_Arbol_B(){
    FILE* archivo = fopen("MiArbolB.txt", "r");
    fseek(archivo, 0L, SEEK_END); //Poner el puntero al final
    long numbytes = ftell(archivo); //Guardar la cantidad de bytes del archivo.
    fseek(archivo, 0L, SEEK_SET);//Poner el puntero en el inicio
    char* texto = (char*)calloc(numbytes, sizeof(char)); //Dar memoria suficiente a text para almacenar el archivo
    fread(texto, sizeof(char), numbytes, archivo);//Guardar todo el texto en un string
    struct arbolB* arbol = crearArbolBVacio();
    De_string_a_arbol(texto,numbytes,arbol);
    return arbol;
}