//bibliotecas necesarias para el proyecto
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//llamar al archivo que contiene la tabla de hash
#include "Tabla_de_HashFuncional.c"
char* ciudades_con_nombreYheroe[] = {"Gotham City, superheroe Batman","Atlantis, superheroe Aquaman","Coast City, superheroe Green Lantern","Metropolis, superheroe Superman","Central City, superheroe Flash"
	,"National City, superheroina Supergirl","Star City, superheroe Green Arrow","Midway City, superheroe Hawkman","Calvin City, superheroe Atom","Jump City, equipo Teen Titans"};
//este struct ciudad basicamente invoca un interes para comerciar, el char* nombre (de la ciudad), y un derivado proveniente del inventario de derivados
typedef struct ciudad {
	int interes_para_comerciar;
	char* p_nombre;
	derivado** inventario_derivados; 
} ciudad;
//este struct lista de ciudades con nodo basicamente tiene un puntero de ciudad con el struct anterior y una lista de ciudades con nodo apuntando al puntero siguiente
typedef struct lista_ciudades_nodo{
	ciudad* p_ciudad;
	struct lista_ciudades_nodo* p_siguiente;
}lista_ciudades_nodo;
/*
 *Con ayuda de los punteros consigue darle valores
 *Cantidad y precio fueron modificados para nerfear el juego
 *Compra o vende se visualiza como un boolean pero realmente si es uno o el otro
 */
void agregar_valores_derivados_ciudad(derivado** nvtr_prdturno_actual){
	srand(rand() * time(NULL) * (rand() % rand() + rand())); //rand del manual que ayuda a sacar numeros al azar
	//un for que recorra cada uno de los derivados empezando por la primera posicion
	for(int indice=1; indice<=4; indice++){
		//esta saca al azar los productos que se van a usar
		char* derivados_tabla = lista_derivados[rand()%7];
		//esta lo asigna a la tabla de hash en la seinput_Cant_Ciudadesion de inventarios
		derivado* puntero_derivado = nvtr_prdturno_actual[tabla_Hash(derivados_tabla,97)];
		//asigna un valor al precio, estos fueron los ajustes que mejor se acomodaron a mi juego
		puntero_derivado->precio=(rand()%97) + 30; //decidi usar el mismo numero primo porque me dio pereza ja
		//asigna la cantidad del derivado, estos fueron los ajustes que mejor se acomodaron a mi juego
		puntero_derivado->cantidad=(rand()%12) + 7;
		//asigna si ese derivado en especifico se compra o se vende
		puntero_derivado->compraVende=(rand()% 2);
	}
}
//Este es el invocador del struct (ciudad), en el que le asigna sus valores respectivos. Cabe destacar que son random
ciudad* invocar_ciudad(char* nombre) {
	ciudad* p_ciudad = calloc(1,sizeof(ciudad));
	derivado** tbl_hsh = invocar_tablahash(97);
	crear_derivados_tabla_hash(tbl_hsh, lista_derivados);
	p_ciudad->inventario_derivados = tbl_hsh;
	agregar_valores_derivados_ciudad(p_ciudad->inventario_derivados);
	p_ciudad->p_nombre = nombre;
	p_ciudad->interes_para_comerciar = (rand()%81)+20;
	return p_ciudad;
}

//Este es el encargado de colocar las ciudades en la lista con nodo para poder recorrerla
lista_ciudades_nodo* colocar_ciudades_lista(ciudad* cdd){
	lista_ciudades_nodo* nodo_con_nombres = calloc(1,sizeof(lista_ciudades_nodo));
	nodo_con_nombres->p_ciudad = cdd;
	return nodo_con_nombres;
}


//Un struct con la lista de ciudades con nodos que apunte al incio
typedef struct lista_ciudades{
	lista_ciudades_nodo* p_inicio;
}lista_ciudades;


//crea la lista con ciudades
lista_ciudades* invocar_lista_con_ciudades(){
	lista_ciudades* lista_con_nombres_ciudades = calloc(1,sizeof(lista_ciudades));
	return lista_con_nombres_ciudades;
}



//se encarga de insertar los nombres de las ciudades en la lista
int insertar_ciudades(lista_ciudades* p_lista_con_ciudades,ciudad* cdd){
	if(p_lista_con_ciudades == NULL){ printf("La lista es inexistente");
		return -1;
	}
	lista_ciudades_nodo* nodo_con_nombres = colocar_ciudades_lista(cdd);
	if(p_lista_con_ciudades->p_inicio == NULL) {
		p_lista_con_ciudades->p_inicio = nodo_con_nombres;
	}
	else{
		struct lista_ciudades_nodo* p_actual = p_lista_con_ciudades->p_inicio;
		while (p_actual->p_siguiente != NULL) {
		p_actual = p_actual->p_siguiente;
		}
		p_actual->p_siguiente = nodo_con_nombres;
	}
	return 0;
}
//para crear los derivados que va a usar el pinguino
void invocar_derivados_pinguino(derivado** derivados_pinguino){
	srand(rand()*time(NULL)*(rand()%rand()+rand())); //funcion del manual para sacar numeros al azar
	for(int indice=0; indice<7; indice++){
		char* derivados_tabla = lista_derivados[indice];
		derivado* p_derivado = derivados_pinguino[tabla_Hash(derivados_tabla,97)];
		p_derivado->precio=((rand()%45) + 27);
		p_derivado->cantidad=((rand()%19) + 21);
	}
}

//este struct lista ciudades con nodo basicamente le asigna al struct de pinguino sus derivados y su respectivos dolares inicales
struct lista_ciudades_nodo* p_inicio = NULL;
typedef struct pinguino{
	derivado** inventario;
	int dolares;
}pinguino;

//le coloca su dinero y propiedades al pinguino
pinguino* colocar_pinguino(){
	pinguino* p_pinguino = calloc(1,sizeof(pinguino));
	p_pinguino->dolares = 5000;
	derivado** tbl_hsh = invocar_tablahash(97);
	crear_derivados_tabla_hash(tbl_hsh, lista_derivados);
	p_pinguino->inventario=tbl_hsh;
	invocar_derivados_pinguino(p_pinguino->inventario);
	return p_pinguino;
}
//imprime los derivados de la tabla
void imprimir_derivados_tabla(derivado** tbl_hsh){
	for(int indice=0; indice < 7; indice++){
		char* derivados_nombre = lista_derivados[indice];
		int llave = tabla_Hash(derivados_nombre,97);
		derivado* derivado_puntero = tbl_hsh[llave];
		if(derivado_puntero->precio > 0){
			printf("	            %s: %d \n", derivado_puntero -> llave_nombre, derivado_puntero->cantidad);
		}
	}
}
//Imprime los dolares y propiedades del pinguino en la baticomputadora y llama a la funcion que imprime los derivados de la tabla
void print_pinguino(pinguino* p_pinguino){
	printf("<Gotham City National Bank> Fondo de inversion de Wayne Tech: $%d\n", p_pinguino->dolares);
	printf("<Wayne Enterprises> Propiedades:\n");
	imprimir_derivados_tabla(p_pinguino->inventario);
}
//se encarga de insertarle las tablas de hash a las ciudades
void monitorear_ciudad(ciudad* p_ciudad){
	//si es menor o igual a 30 el interes para comercial entonces la tabla de hash se elimina
	if(p_ciudad->inventario_derivados != NULL && p_ciudad->interes_para_comerciar <= 30){
		eliminar_derivado(p_ciudad->inventario_derivados);
		p_ciudad->inventario_derivados = NULL;
	}
	//si es mayor a 30 el interes para comercial entonces la tabla de hash se elimina
	if(p_ciudad->inventario_derivados == NULL && p_ciudad->interes_para_comerciar > 30){
		derivado** tbl_hsh = invocar_tablahash(97);
		crear_derivados_tabla_hash(tbl_hsh, lista_derivados);
		agregar_valores_derivados_ciudad(tbl_hsh);
		p_ciudad->inventario_derivados = tbl_hsh;
	}
}
//trae la lista de las ciudades con nombre y superheroe para imprimirlas en la consola
lista_ciudades* crea_lista_ciudades_nombreYsuperheroe(int cantidad){
	lista_ciudades* lista_ciudades = invocar_lista_con_ciudades();
	srand(rand()*time(NULL)*(rand()%rand()+rand()));
	for(int indice=0; indice < cantidad;){
		int variacion = rand()%10;
		char* nombre = ciudades_con_nombreYheroe[variacion];
		char* temp = "x";
		if(nombre != temp){
			ciudad* cdd = invocar_ciudad(nombre);
			insertar_ciudades(lista_ciudades, cdd);
			ciudades_con_nombreYheroe[variacion]="x";
			indice++;
		}
	}
	return lista_ciudades;
}
//aca imprimimos los derivados 
void imprimirderivados(derivado** tbl_hsh){
	for(int indice=0; indice < 7; indice++){
		char* derivados_nombre = lista_derivados[indice];
		int llave = tabla_Hash(derivados_nombre,97);
		derivado* puntero_derivado = tbl_hsh[llave];
		if(puntero_derivado->precio > 0){
			printf("    		derivado: %s\n", puntero_derivado -> llave_nombre);
			printf(" 			  Precio: $%d, ", puntero_derivado -> precio);
			if(puntero_derivado -> compraVende == 0){
			printf("El criminal vende, ");
			}
			else{
			printf("El criminal compra, ");
			}
			printf("Disponible: %d \n", puntero_derivado -> cantidad);
		}
	}
}
//imprime la ciudad a la que estamos apuntando
int imprimir_nsima_ciudad(ciudad* cdd){
	//imprime el nombre de la ciudad con su superheroe
	printf("<Batcomputer/Monitoring> Ciudad con la que se comunica: %s", cdd->p_nombre);
	//indica el interes de los criminales para comerciar
	printf(". Interes de los criminales para comerciar: %d\n", cdd->interes_para_comerciar);
	//si el interes de la ciudad es mayor o igual a 30 entonces imprimimos la tabla de la ciudad
	if(cdd->interes_para_comerciar >= 30){
		derivado** nvtr_prdturno_actual = cdd->inventario_derivados;
		imprimirderivados(nvtr_prdturno_actual);
		printf("\n");
	}
	// si el interes de la ciudad es menor a 30 entonces no imprimimos la tabla de la ciudad
	if(cdd->interes_para_comerciar < 30){
		printf("<<Batcomputer lost signal>> Los criminales no cuentan con el suficiente interes para comerciar o fueron atrapados.\n\n");
	}
	return 0;
}
//con la ayuda de imprimir la nsima ciudad recorre todas las ciudades hasta terminar de imprimirlas
int imprimir_lista_con_ciudades(lista_ciudades* p_lista){
	lista_ciudades_nodo* p_actual = p_lista->p_inicio;
	//hasta que no terminemos de recorrer la lista y lleguemos al null entonces continuara con la nsima ciudad
	while (p_actual->p_siguiente!= NULL) {
		imprimir_nsima_ciudad(p_actual->p_ciudad);
		p_actual = p_actual->p_siguiente;
	}
	//imprime la ciudad actual aka la nsima ciudad a la que estemos apuntando
	imprimir_nsima_ciudad(p_actual->p_ciudad);
	return 0;
}
//para comprar derivados de las ciudades
int comprar_derivados(int valor_compra_venta, derivado* p_derivado, pinguino* p_pinguino){
	char* derivados_tabla = p_derivado->llave_nombre;
	int costo_derivado = p_derivado->precio;
	int dinero = valor_compra_venta*costo_derivado;
	derivado* p_derivado2 = p_pinguino->inventario[tabla_Hash(derivados_tabla,97)];
	if (dinero > p_pinguino->dolares)
	{printf("<Gotham City National Bank> Usted (El pinguino) no tiene dinero suficiente\n\n"); return 0;}
	if (valor_compra_venta > p_derivado->cantidad)
	{printf("<Wayne Enterprises> El criminal no tiene esa cantidad \n\n"); return 0;}
	p_derivado->cantidad -= valor_compra_venta;
	p_derivado2->cantidad += valor_compra_venta;
	p_pinguino->dolares -= dinero;
	return 1;
}
//para vender derivados de las ciudades
int vender_derivados(int valor_compra_venta, derivado* p_derivado, pinguino* p_pinguino){
	char* derivados_tabla = p_derivado->llave_nombre;
	int costo_derivado = p_derivado->precio;
	int dinero = valor_compra_venta*costo_derivado;
	derivado* p_derivado2 = p_pinguino->inventario[tabla_Hash(derivados_tabla,97)];
	if (p_derivado2->cantidad < valor_compra_venta)
	{printf("<Wayne Enterprises> Usted (El pinguino) no cuenta con esa cantidad \n\n"); return 0;}
	p_derivado->cantidad += valor_compra_venta;
	p_derivado2->cantidad -= valor_compra_venta;
	p_pinguino->dolares += dinero;
	return 1;
}
//compra y venta por medio de la baticomputadora
int compra_venta(ciudad* cdd, pinguino* p_pinguino){
	if(cdd->interes_para_comerciar > 30){
		int turno_actual = 0;
		char* valor_entrada="a";
		int llave = tabla_Hash(valor_entrada,97);
		while(cdd->inventario_derivados[llave] == NULL || cdd->inventario_derivados[llave]->precio == 0){
		printf("<Wayne Enterprises> Digite el nombre de un derivado con el que deseas comerciar: ");
		char inputderivado[50];
		scanf("%s", inputderivado);
		llave = tabla_Hash(inputderivado, 97);
		}
		if(cdd->inventario_derivados[llave]->compraVende == 0){ printf("<Wayne Enterprises> cuanto derivado quieres comprar? ");
			int valor_compra_venta;
			scanf("%d", & valor_compra_venta);
			turno_actual = comprar_derivados(valor_compra_venta, cdd->inventario_derivados[llave], p_pinguino);
		}
		if(cdd->inventario_derivados[llave]->compraVende != 0){ printf("<Wayne Enterprises> cuanto derivado que quieres vender? ");
			int valor_compra_venta;
			scanf("%d", & valor_compra_venta);
			turno_actual = vender_derivados(valor_compra_venta, cdd->inventario_derivados[llave], p_pinguino); 
		}
		return turno_actual;
	}
	else{
		srand(rand()*time(NULL)*(rand()%rand()+rand()));
		cdd->interes_para_comerciar += rand()%14+23;
		return 1;
	}
}
//cambia la cantidad de turnos
void cambiar_cantidad_turnos(lista_ciudades* l){
	srand(rand()*time(NULL)*(rand()%rand()+rand()));
	int decay = rand()%5 +1;
	lista_ciudades_nodo* p_actual = l->p_inicio;
	while (p_actual->p_siguiente!= NULL) {
		p_actual->p_ciudad->interes_para_comerciar = p_actual->p_ciudad->interes_para_comerciar - decay;
		if((p_actual->p_ciudad->interes_para_comerciar)<0){
			p_actual->p_ciudad->interes_para_comerciar = 0;
		}
		monitorear_ciudad(p_actual->p_ciudad);
		p_actual = p_actual->p_siguiente;
	}
		p_actual->p_ciudad->interes_para_comerciar = p_actual->p_ciudad->interes_para_comerciar - decay;
		if((p_actual->p_ciudad->interes_para_comerciar)<0){
			p_actual->p_ciudad->interes_para_comerciar = 0;
		}
		monitorear_ciudad(p_actual->p_ciudad);
		p_actual = p_actual->p_siguiente;
}
//ciudad con la que se esta comerciando actualmente en esa cantidad_turnos
ciudad* ciudad_comercio_actualmente(lista_ciudades* ciudades){
	lista_ciudades_nodo* p_actual = ciudades->p_inicio;
	int longitud = 0;
	while(p_actual->p_siguiente!= NULL) {
		longitud+=1;
		p_actual = p_actual->p_siguiente;
		}
		longitud+=1;
	printf("<Wayne Enterprises> Digite el num de la ciudad con la que desea comunicarse: ");
	int indice = 1;
	int numero_ciudad;
	scanf("%d", & numero_ciudad);
	p_actual = ciudades->p_inicio;
	ciudad* cdd = p_actual->p_ciudad;
	cdd= p_actual->p_ciudad;
	//busca entre las ciudades hasta llegar a la ciudad que corresponda al numero
	while(indice != numero_ciudad){
		p_actual = p_actual->p_siguiente;
		cdd= p_actual->p_ciudad;
		indice++;
	}return cdd;
}
//contador de turnos
void contador_cantidad_turnos(lista_ciudades* ciudades, pinguino* p_pinguino){
	int  cantidad_turnos = 1;
}
//corre el juego
int main(){
	int input_Cant_Ciudades;
	printf("Sinopsis: Despues de los eventos de Crisis en Tierras Infinitas, el pinguino consigue robar el Linux de la Baticomputadora.\n");
	printf("	  Cuenta con escaneres de policia, redes de noticias para monitorear el crimen y ademas cuenta con la Base de Datos de Lex Corp.\n");
	printf("	  Para la suerte del pinguino, la baticomputadora contiene programas de C ya que Batman aprobo el curso de estructuras de datos con Aurelio.\n\n");
	printf("                                Linux Ubuntu [version 10.0.83925.234]\n");
	printf("                           (c) 2022 Wayne Enterprises. All rigtbl_hshs reserved.\n");
	printf("					Welcome to the Batcomputer\n");
	printf("					User:     Batman\n");
	printf("					Password: ***********\n\n");
	printf("<Batcomputer/Monitoring> Gotham City, Atlantis, Coast City, Metropolis, Central City, National City, Star City, Midway City, Calvin City, Jump City.\n\n");
	printf("<Batcomputer/Monitoring> Cantidad posible a monitorear, entre 3 y 10.\n\n");
	printf("<Batcomputer/Monitoring> Numero de ciudades que desea monitorear: ");
	scanf("%d", &input_Cant_Ciudades);
	//input no puede ser mayor a 10 ya que solo existen 10 ciudades
	if(input_Cant_Ciudades >= 11){input_Cant_Ciudades = 10;
	}
	printf("\n");
	printf("<Batcomputer/Monitoring> Cannamo: aceite, biocombustible, joyas, pintura, medicinas, leche, proteina\n\n");
	lista_ciudades* ciudades = crea_lista_ciudades_nombreYsuperheroe(input_Cant_Ciudades);
	pinguino* p_pinguino = colocar_pinguino();
		int  cantidad_turnos = 1;
	while(cantidad_turnos <= 20){
		printf("<Batcomputer/Monitoring> intento de comercio: %d \n\n", cantidad_turnos);
		imprimir_lista_con_ciudades(ciudades);
		print_pinguino(p_pinguino);
		ciudad* cdd = ciudad_comercio_actualmente(ciudades);
		int turno_contador = compra_venta(cdd,p_pinguino);
		if(turno_contador == 1){
		cambiar_cantidad_turnos(ciudades);
		cantidad_turnos++;
		}	
		while(turno_contador!=1){
			turno_contador = compra_venta(cdd,p_pinguino);
		}	
	}
	imprimir_lista_con_ciudades(ciudades);
	print_pinguino(p_pinguino);
	int dinero_al_finalizar = p_pinguino->dolares;
		if(30000 > dinero_al_finalizar) {
			printf("<Bad Ending> El pinguino ha sido descubierto por Batman. Esto porque no consiguio el suficiente dinero para sobornar al fiscal. Batman recupera la Baticomputadora\n");
		}
		if(30000 <= dinero_al_finalizar){
			printf("<Good Ending> El pinguino se ha vuelto el villano mas poderoso. Gotham City ahora es la capital del cannamo. Aunque Batamn consigue recuperar la baticomputadora\n");
		}
	return 0;
}