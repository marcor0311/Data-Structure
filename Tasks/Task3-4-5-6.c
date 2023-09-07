#include <string.h>
#include <stdlib.h>
#include <stdio.h> 
/* Investigar strcpy y strtok
* La funcion strcpy recibe dos parametros, primero el string donde se va a copiar
* el contenido, y segundo el string del cual sera copiado su contenido.
* La funcion strtok permite dividir una cadena usando un delimitador.
*/

// El codigo esta comentado para que se pueda probar cada funcion por separado
// solo se debe descomentar la funcion que se quiere probar y comentar las demas
// Peticion del asistente, para facilitar la revision del codigo
int main(void) { 
   
   //Eliminar el caracter c de un texto
   /*
   printf("Bienvenido \n"); 
   char string[] = "camaca";
   eliminar_c(string, 'c');
   printf("%s\n", string); */
   
   
   //Invertir un texto
   /*
   char* texto_no_invertido = "Hola";
   printf("Bienvenido \n"); 
   invertir(texto_no_invertido);
   return 0; */
   
   //Copiar un texto literal a un texto en el heap
   /*
   char texto[8] = "caballos";
   char* copiar_texto(texto);

   return 0;
   */
   }
/*  
char* invertir(char* texto_no_invertido){
    //declaramos variables para no tener errores
   int texto_largo=0, pos=0;
   //un ciclo que se detiene cuando se llegue al final
   while (texto_no_invertido[pos] !='\0'){
   //contador de largo y aumento de posicion
   texto_largo++;
   pos++; }
   char* texto_invertido= calloc(texto_largo+1,sizeof(char));
   // se declara el valor invertido
   int pos_invertido=0;
   // un ciclo que recorra el largo
   while (texto_largo){
   pos--;
   //se encarga de intercambiar posiciones
   texto_invertido[pos_invertido]=texto_no_invertido[pos];
   pos_invertido++;
   texto_largo--; }
   printf("Invertir: %s\n", texto_invertido);
   }*/
/*
void eliminar_c(char* string, char c)
{
    //declarar la variable
    int pos=0;
    //ciclo que se detiene cuando se llega al final
    while (string[pos] !='\0')
    {
        //si la posicion es igual a el caracter
        if (string[pos] == c)
        {// declarar una segunda pos por si hay caracteres juntos
            int pos2 = pos;
            while (string[pos2] !='\0')
            {
                string[pos2] = string[pos2+1];
                pos2++;
            }
        }
        //si no se encuentra el caracter seguiremos buscando
        else pos++;
    }
}
*/
/*
char* copiar_texto(char* texto){
    //definir variables
    int largo=0;
    //un ciclo que recorra el largo
    while (texto[largo])
    //se va sumando el contador
    largo++;
    //proceso para guardar en el heap con calloc
    char* texto_heap = calloc(largo+1, sizeof(char));
    while (*texto) *texto_heap++ = *texto++;
    //se guarda en el heap de manera exitosa
    return texto_heap - largo;
    return 0;
}*/