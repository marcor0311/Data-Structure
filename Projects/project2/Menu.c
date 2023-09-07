#include "Lector.c"
#include "tabla_hash.c"
#include <stdio.h>
#include <unistd.h> 
#include "Arbol_Chaflaneado.c"

//Metodo que indiza un arbol B vacio usando la tabla de hash para obtener
//los nombres de archivos y sus rutas.
void Indizar(struct arbolB* arbolBprincipal, tabla_hash* Tabla){
    //recorrer cada nombre de archivo y ruta y por cada nombre aplicar 
    //RecorrerArchivo(,,arbol);
    int cant = 0;
    for(int i=0; i<Tabla->longitud; i++)
    {
        if(Tabla->tabla[i] != NULL)
        {
            //printf("Nodo de tabla valido \n");
            char* Nombre = Tabla->tabla[i] -> llave;
            char* Ruta = Tabla->tabla[i] ->  valor;
            RecorrerArchivo(Nombre,Ruta,arbolBprincipal);
            cant++;
            printf("se han indizado %d archivos.\n",cant);
        }
    }
}

//Funcion que todas las noticias de un termino del arbol B usando la lista de nombres de noticias y la tabla de hash
void Imprimir_lista_archivos_con_rutas(char* termino,struct listaB* lista, tabla_hash* Tabla){
    struct nodoB* nodoact = lista->inicio;
    while (nodoact != NULL){
        char* archivo_con_termino = nodoact->NombreArchivo;

        for (int i=0;i<Tabla->longitud;i++){
            if (Tabla->tabla[i] != NULL){
                char* llave_en_hash = Tabla->tabla[i]->llave;
                char* Ruta = Tabla->tabla[i]->valor;
                if (strcmp(llave_en_hash,archivo_con_termino) == 0){ //Si se encuentra la llave correcta
                    printf("%s - %s\n\n",termino,Ruta);
                }
            }
        }
        nodoact = nodoact->sig;
    }
}
//Funcion que busca las lista de las noticias de un termino y las imprime.
void Imprimir_Noticias_Termino(struct arbolB* arbol,char* termino, tabla_hash* Tabla){
    struct EstaTerminoConPagina* TerminoEnArbolYPagina = TerminoEnArbolConPagina(arbol->raizDelArbol,termino);

    if (TerminoEnArbolYPagina->TerminoEnArbol==1){
        Imprimir_lista_archivos_con_rutas(termino,obtenerListaConTermino(TerminoEnArbolYPagina->PaginaConTermino,termino),Tabla);
    }
    else{
        printf("%s no esta en el arbol.\n",termino);
    }
}
//Funcion que se usa al inicio, se encarga de cargar el arbol, ya sea desde 0 o usando el archivo
//"MiArbolB.txt"
struct arbolB* Iniciar_arbol_B(tabla_hash* Tabla){
    struct arbolB* ArbolBPrincipal = crearArbolBVacio();
    int se_puede_cargar = ArchivoValido();
    if (se_puede_cargar ==-1){//Si no se puede cargar
        printf("No es posible cargar el arbol B, se procedera a indizar desde 0. Porfavor espere.\n");
        sleep(3); //Esperar tres segundos.
        Indizar(ArbolBPrincipal,Tabla);
        return ArbolBPrincipal;
    }
    else{
        char entrada[500];
        printf("Es posible cargar el ArbolB.\n");
        printf("Para proceder a cargarlo, digite 1.\n");
        printf("Para indizarlo de 0, digite 0.\n");
        scanf("%s",entrada);
        if (strcmp(entrada,"1") == 0){ //Si se quiere cargar.
            ArbolBPrincipal = Cargar_Arbol_B();
            return ArbolBPrincipal;
        }
        else{
            Indizar(ArbolBPrincipal,Tabla);
            return ArbolBPrincipal;
        }
    }

}
void Buscar_Termino(arbolB* arbolBprincipal, tabla_hash* Tabla, arbol_chaflaneado* Splay){
    char termino [500];
    printf("Introduzca el termino a buscar: ");
    scanf("%s",termino);
    nodo_chaflaneado* Nodo_splay = buscar_arbol_chaflaneado(Splay->raiz,termino,Splay);
    if (Nodo_splay == NULL){ //No se encontro el termino en el arbol chaflaneado
        if (TerminoEnArbol(arbolBprincipal->raizDelArbol,termino) == 0){
            printf("El termino introducido no esta en el arbol B.\n");
        }
        else{
            Imprimir_Noticias_Termino(arbolBprincipal,termino,Tabla);
        }
        if (TerminoEnArbol(arbolBprincipal->raizDelArbol,termino) == 0){
            printf("El termino introducido no esta en el arbol B.\n");
        }
        else{
            Imprimir_Noticias_Termino(arbolBprincipal,termino,Tabla);
        }
    }
    else{

    }
}
//Imprime las opciones del menu principal.
void Imprimir_opciones_principales(){
    printf("Opciones a ejecutar:\n");
    printf("\t 0 - Salir del programa.\n");
    printf("\t 1 - Imprimir el preorden del arbol B.\n");
    printf("\t 2 - Imprimir el preorden del arbol Splay.\n");
    printf("\t 3 - Imprimir la tabla de hash.\n");
    printf("\t 4 - Buscar Termino.\n");
    printf("\t 5 - Guardar arbol B.\n");
}

void menu_principal(struct arbolB* arbolBprincipal, tabla_hash* Tabla, arbol_chaflaneado* arbol_splay){
    char opcion [500];
    Imprimir_opciones_principales();
    printf("Seleccione su opcion: ");
    scanf("%s",opcion);
    while(strcmp(opcion,"0") != 0){
        if (strcmp(opcion,"1")==0){ //Si strcmp da 0, es porque son iguales. Imprimir arbol B
            Imprimir_preorden_B(arbolBprincipal->raizDelArbol,0);
        }
        if (strcmp(opcion,"2")==0){ //Imprimir preorden splay
            imprimir_preorden(arbol_splay->raiz);
        }
        if (strcmp(opcion,"3") == 0){//Imprimir tabla hash
            imprimir_tabla_hash(Tabla);
        }
        if (strcmp(opcion,"4") == 0){//Buscar termino
            Buscar_Termino(arbolBprincipal,Tabla,arbol_splay);
        }
        if (strcmp(opcion,"5")==0){//Guardar Arbol B.
            GuardarArbol(arbolBprincipal);
        }
        else{
            if (strcmp(opcion,"4")!=0 && strcmp(opcion,"3")!=0 && strcmp(opcion,"2") !=0 && strcmp(opcion,"1") !=0){
                printf("Opcion invalida, porfavor ingrese una opcion valida.\n");
            }
        }
        Imprimir_opciones_principales();
        printf("Seleccione su opcion: ");
        scanf("%s",opcion);

    }
    exit(0);

}
void iniciar_menu()
{
    char* entrada = calloc(500,sizeof(char));
    scanf("Seleccione su opcion: %s",entrada);
}
void cargar_arbol(){

}

//Funcion principal
int main(){
    char* carpeta = "/home/santy/Documentos/Datos/Proyectos/P2/Github/Buscador-de-informacion-en-archivos-de-texto/TodasLasNoticias";
    tabla_hash* Tabla = tabular(carpeta);
    struct arbolB* Arbol_B_Indice = Iniciar_arbol_B(Tabla);
    struct arbol_chaflaneado* Arbol_Splay = inicializar_arbol_chaflaneado("");
    menu_principal(Arbol_B_Indice,Tabla,Arbol_Splay);

}