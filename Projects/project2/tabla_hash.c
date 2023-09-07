#include <ctype.h>
#include <dirent.h> // Libreria encargada del tema de los directorios
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Se defina la estructura del nodo con llave y valor
 * Donde la llave corresponde al nombre del archivo
 * valor corresponde a la ruta en disco
 */
typedef struct nodo_tabla_hash
{
  char* llave;
  void* valor;
} nodo_tabla_hash;

typedef struct tabla_hash
{
  nodo_tabla_hash** tabla;
  int longitud;
} tabla_hash;
//struct del nodo
typedef struct nodo
{
    void *valor;
    struct nodo *siguiente;
} nodo;

//struct de la lista 
typedef struct lista
{
    struct nodo *inicio;
} lista;

typedef struct dupla
{
    void* valor_1;
    void* valor_2;
} dupla;

typedef struct dupla_char
{
    char valor_1;
    char valor_2;
} dupla_char;

typedef struct dupla_string
{
    char* valor_1;
    char* valor_2;
} dupla_string;

typedef struct dupla_archivo
{
    char* nombre;
    char* ruta;
} dupla_archivo;


char *strcombine(char *string1,char *string2)
{
    int tamaño1= strlen(string1);
    int tamaño2= strlen(string2);
    int tamañototal = tamaño1+tamaño2+1;

    char *new_String = calloc(tamañototal,sizeof(char));
    for(int i=0;i<tamaño1;i++)
    {
        new_String[i] = string1[i];
    }
    for(int j=0;j<tamaño2;j++)
    {
        new_String[j+tamaño1] = string2[j];
    }
    return new_String;
}

// Comprueba si un número es primo o no
int es_primo(int numero)
{
  int res=0;
  int divs=2;
  int mitad;
  if (numero>2)
    {
      mitad = numero/2;
      do
    {
      res=(numero%divs!=0);
      divs++;
    } while ((res!=0) && (divs<=mitad));
    }
  else 
  {
    if (numero==2)
    {
        res=1;
    }
  }
  return res;
}

int siguiente_primo(int numero)
{
    while(es_primo(numero) != 1)
    {
        numero++;
    }
    return numero;
}
/*
 * Funcion de hashing para separar las llaves por medio de las palabras
 * De esta manera no genera colisiones y se separan las llaves
 */
int Hash(char* llave, int longitud)
{
  //se inicializa el hash en 0
  int hash = 0;
  //mediante un for se recorre la llave (nombre del archivo)
  for(int i = 0; i < strlen(llave); i++)
  {
    //valor = llave[i] - 0, 48 es igual a 0
    int valor = llave[i] - 48;
    //se agregan los valores a la funcion de hash
    hash += valor;
  }
  //hash modulo de longitud sera igual a hash, esto para evitar colisiones
  hash = hash % longitud;
  return hash;

}

nodo_tabla_hash* inicializar_nodo_tabla_hash(char* Llave, void* Valor)
{
  nodo_tabla_hash* nuevo_nodo = calloc(1, sizeof(nodo_tabla_hash));
  nuevo_nodo -> llave = Llave;
  nuevo_nodo -> valor = Valor;
  return nuevo_nodo;
}

//inicializar la tabla de hash
tabla_hash* inicializar_tabla_hash(int tamaño)
{
  tamaño = siguiente_primo(tamaño);
  //calloc para crear una nueva tabla de hash en el heap
  tabla_hash* Tabla = calloc(1, sizeof(tabla_hash));
  Tabla -> tabla = calloc(tamaño, sizeof(nodo_tabla_hash));
  Tabla -> longitud = tamaño;

  //retornamos la tabla de hash
  return Tabla;

}

//para agregar llaves en la tabla de hash
void insertar_en_tabla_hash(nodo_tabla_hash* Nodo, tabla_hash* Tabla)
{

  int tamaño = Tabla -> longitud;
  int hash = Hash(Nodo -> llave, tamaño);
  int i = 0;

  while (Tabla->tabla[hash+i] != NULL)
  {
    //printf("Ha ocurrido una colisión en la tabla de hash. \n");
    i+=1;
    if(hash+i >= tamaño)
    {
      i = 0;
      hash = 0;
    }
  }

  Tabla->tabla[hash+i] = Nodo;

}

void* buscar_en_tabla_hash(char* Llave, tabla_hash* Tabla)
{

  int tamaño = Tabla -> longitud;
  int hash = Hash(Llave, tamaño);
  int i = 0;

  while (strcmp(Tabla->tabla[hash+i]->llave,Llave))
  {
    //printf("Ha ocurrido una colisión en la tabla de hash. \n");
    i+=1;
    if(hash+i >= tamaño)
    {
      i = 0;
      hash = 0;
    }
  }

  return (Tabla->tabla[hash+i])-> valor;

}

void borrar_tabla_hash(tabla_hash* Tabla)
{
  int Longitud = Tabla -> longitud;
  for (int i = 0; i < Longitud; i++)
  {
    //free(Tabla->tabla[i]);
  }
  free(Tabla->tabla);
  free(Tabla);
  Tabla = NULL;
}

/*
 * Funcion de redimensionamiento
 * Dependiendo de la cantidad de archivos cambiara su tamanno
 */
tabla_hash* redimensionar_tabla_hash(tabla_hash* Tabla, int tamaño)
{
  tabla_hash* nueva_tabla = inicializar_tabla_hash(tamaño);
  //tabla sin redimensionamiento
  int Longitud = Tabla -> longitud;
  nueva_tabla -> longitud = tamaño;
  //un for que recorre la tabla de hash
  for (int i = 0; i < Longitud; i++)
  {
    //si es necesario un redimensionamiento entonces
    if (Tabla->tabla[i] != NULL)
    {
      //se genera una nueva llava en la posicion i y se agrega a la tabla de hash
      insertar_en_tabla_hash(Tabla->tabla[i], nueva_tabla);
    }
  }
  borrar_tabla_hash(Tabla);
  //se devuelve la nueva tabla de hash redimensionada para la nueva cantidad de archivos
  return nueva_tabla;

}

tabla_hash* verificar_ocupamiento(tabla_hash* Tabla)
{
      int contador = 0;

    for(int i = 0; i < Tabla->longitud; i++)
    {
        if(Tabla -> tabla[i] != NULL)
        contador++;
    }

    int limite = (3*(Tabla -> longitud))/4;

    if(contador >= limite)
    {
      //printf("\n -------------------------------------------------------------------- \n");
      //printf(">>> En la tabla de hash hay: %d espacios ocupados, de %d espacios totales. \n", contador, Tabla -> longitud);
      //printf(">>> Se requiere redimensionar la tabla de hash. \n");
      //printf(" -------------------------------------------------------------------- \n \n");
      tabla_hash* nueva_tabla = redimensionar_tabla_hash(Tabla, 2*(Tabla -> longitud));
      return nueva_tabla;
    }

    return Tabla;

}


//inicializar el nodo con el valor
nodo* inicializar_nodo(void* Valor)
{
    nodo* nuevo_nodo = calloc(1,sizeof(nodo));
    //nuevo nodo apuntando a valor, para crear el nodo en la lista
    nuevo_nodo -> valor = Valor;
    //se retorna el nuevo nodo creado
    return nuevo_nodo;

}


//iniciar la lista enlazada simple
lista* inicializar_lista()
{
    lista* lista = calloc(1,sizeof(lista));
    //se retorna la lista
    return lista;

}

//para insertar cualquiera de los nodos anteriores
void insertar_nodo(lista* Lista, nodo* Nodo)
{
    //Si la lista es vacia
    if(Lista -> inicio == NULL)
    {
        //entonces el nodo sera introducido en el inicio
        Lista -> inicio = Nodo;

    }
    //sino sera introducido al final
    else
    {
        nodo* actual = Lista -> inicio;
        //un while hasta que lleguemos al puntero que apunta a NULL
        while(actual -> siguiente != NULL)
        {
            //entonces nodo actual apunta al siguiente nodo
            actual = actual -> siguiente;
        }
        actual -> siguiente = Nodo;
    }
}

lista* Buscar_en_directorio(char *path)
{
    struct dirent *entry;
    char* name;
    char* ruta;
    DIR *dp;
    dupla_archivo* info_archivo;
    lista* Lista = inicializar_lista();

    dp = opendir(path);

    if (dp == NULL) 
    {
        printf("Ruta en el codigo invalida, terminando programa.\n");
        exit(0);

    }

    while((entry = readdir(dp)))
    {
        name = entry -> d_name;
        char* heap_name = calloc(strlen(name)+1, sizeof(char));
        strcpy(heap_name, name);
        info_archivo = calloc(1, sizeof(dupla_string));
        if(heap_name[0] == '.')
        {
            printf("-> \n");

        }
        else
        {
            ruta = strcombine(path, "/");
            ruta = strcombine(ruta, heap_name);
            info_archivo -> nombre = heap_name;
            info_archivo -> ruta = ruta;
            nodo* Nodo = inicializar_nodo(info_archivo);
            insertar_nodo(Lista,Nodo);


            //printf("Nombre: %s \n", heap_name);
            //printf("Ruta: %s \n", ruta);
            //printf("Longitud: %d \n", strlen(ruta));
            //printf("--------------------------------------------------- \n");

        }

    }

  closedir(dp);

  return Lista;
}

tabla_hash* tabular(char* carpeta) {
    lista* Lista = Buscar_en_directorio(carpeta);
    tabla_hash* Tabla = inicializar_tabla_hash(211);

    nodo* actual = Lista -> inicio;
    while(actual -> siguiente != NULL)
    {
        dupla_archivo* Dupla = actual -> valor;
        nodo_tabla_hash* Nodo = inicializar_nodo_tabla_hash(Dupla->nombre, Dupla -> ruta);
        insertar_en_tabla_hash(Nodo, Tabla);
        Tabla = verificar_ocupamiento(Tabla);
        
        actual = actual -> siguiente;
    }
        dupla_archivo* Dupla = actual -> valor;
        nodo_tabla_hash* Nodo = inicializar_nodo_tabla_hash(Dupla->nombre, Dupla -> ruta);
        insertar_en_tabla_hash(Nodo, Tabla);

    int contador = 0;

    for(int i = 0; i < Tabla->longitud; i++)
    {
        if(Tabla -> tabla[i] != NULL)
        contador++;
    }

   // printf(">>> En la tabla de hash hay: %d archivos. \n", contador);

    //char* Valor = buscar_en_tabla_hash("84-investigacion-tec-hace-aplicada.html.txt", Tabla);
    //printf("Link: %s \n", Valor);

    return Tabla;

}


void imprimir_tabla_hash(tabla_hash *Tabla)
{
    nodo_tabla_hash** tabla_imprimir = Tabla -> tabla;
    for(int i = 0; i < Tabla->longitud; i++)
    {
      if(tabla_imprimir[i] != NULL)
      {
        printf("------------------------------- \n");
        printf("Posición en la tabla: %d \n", i);
        printf("Nombre del archivo: %s \n", tabla_imprimir[i]->llave);
        char* ruta = tabla_imprimir[i]->valor;
        printf("Ruta del archivo: %s \n", ruta);
        printf("------------------------------- \n");
      }
    }
}

