#include "ArbolB.c"
#include <stdio.h>
#include <stdlib.h>

int compararString(int inicio_palabra, int fin_palabra, char* texto,char* termino){
    //Tamanno de una palabra del archivo.
    int longitud_palabra = fin_palabra - inicio_palabra;
    //Tamanno del termino Buscado
    int longitud_termino = strlen(termino);
    //Crear arreglo de caracteres donde se guarde la palabra del archivo.
    char palabra[longitud_palabra];
    //Guardar en arreglo palabra la palabra del archivo.
    strncpy(palabra, texto+inicio_palabra,longitud_palabra);
    //Pone en son_iguales 0 si lo son.
    int son_iguales = strcmp(palabra,termino);
    //Inicializa el arreglo en 0.
    for (int i=0;i<longitud_palabra;i++){
        palabra[i] = 0;
    }
    //Si son iguales retorna 1 (true) si los strings son iguales
    if(son_iguales == 0){
        return 1;
    }//sino retorna 0 (false) si no son iguales
    return 0;
}


//Crea un nuevo string tomando un string padre, el inicio y final incluidos
char* NuevoString(char* StringPadre,int inicio, int final){
    char* nvostring = calloc(final-inicio+2,sizeof(char));
    int posnvostring =0;
    for (int i=inicio;i<=final;i++){
        nvostring[posnvostring] = StringPadre[i];
        posnvostring++;
    }
    return nvostring;
}

//Recorre el archivo, y va anadiendo terminos al arbol B junto al nombre del archivo, si el termino
//ya se encuentra en el archivo, le mete el nombre del archivo a la lista de archivos
void RecorrerArchivo(char* nombre_archivo,char* ruta,struct arbolB* arbol){
    //archivo, texto y numero de bytes
    FILE* archivo;
    char* texto;
    int  numero_bytes;

    /*
     * Mediante fopen abre el archivo con la noticia
     * En caso de error al abrirlo retorna -1
     */
    archivo = fopen(ruta, "r");

    fseek(archivo, 0L, SEEK_END);
    //Guardar en numero_bytes la cantidad de bytes del archivo.
    numero_bytes = ftell(archivo); 
    fseek(archivo, 0L, SEEK_SET);
    //Dar memoria suficiente a texto para almacenar el archivo	
    texto = (char*)calloc(numero_bytes, sizeof(char)); 
    //Si el archivo no tenia caracteres, terminar el programa con -1
    /*
    if(texto == NULL) 
    {
        //Mensaje de error cuando no se puede abrir el archivo
        printf("Hubo un eror durante la lectura \n");
        return -1;
    }
    */

    //Guardar en texto un string con todo el texto del archivo.
    fread(texto, sizeof(char), numero_bytes, archivo); 
    //printf("%s \n",texto); //print para pruebas
    fclose(archivo);
    int inicio_palabra = 0;
    int fin_palabra = 0;
    int termino_en_archivo = 0;
    while(inicio_palabra < numero_bytes){
        while(verificar_char(texto[inicio_palabra]) == 0){ //Pone el inicio en un char valido.
            inicio_palabra+=1;
        }
        fin_palabra = inicio_palabra+1;
        while(verificar_char(texto[fin_palabra]) == 1){//Se detiene cuando llega a una palabra invalida
            fin_palabra+=1;
        }
        
        char* terminoencontrado = NuevoString(texto,inicio_palabra,fin_palabra-1);//Fin_palabra -1 porque termina en un caracter no deseado.
        //printf("El termino a meter es %s \n",terminoencontrado);
        struct EstaTerminoConPagina* TerminoEnArbolYPagina = TerminoEnArbolConPagina(arbol->raizDelArbol,terminoencontrado);
        if (TerminoEnArbolYPagina ->TerminoEnArbol == 1){//Si el termino esta en el archivo, agregarle la noticia.
            //printf("El termino anterior esta en el arbol \n");
            AnnadirNombreNoticiaEnTermino(TerminoEnArbolYPagina->PaginaConTermino,terminoencontrado,nombre_archivo);
        }
        else{//Si el termino no esta en el archivo, crearle una llave y meterlo.
            //printf("El termino anteior no esta en el arbol\n");
            struct listaB* listaNueva = crearListaB(nombre_archivo);
            struct llave* LlaveNueva = crearLlave(terminoencontrado,listaNueva);
            insertar_llave_arbol_B(arbol,LlaveNueva);
        }
        inicio_palabra=fin_palabra;
        //printf("\n");
        //ImprimirPreorden(arbol->raizDelArbol,0);
        //printf("\n");
    }
}   