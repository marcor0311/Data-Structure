#include <stdio.h>
#include <stdbool.h>  // Include for boolean data type

// Function prototypes
int numero_impar(int numero);
int fibonacci(int numero);
int factorial(int numero);
int largo_de_n_for(int numero);
int largo_de_n_while(int numero);
int sumatoria_for(int numero);
bool is_palindrome(int numero);  // Changed to return a boolean

int main(void) {
    int numero = 0;
    int resultado = 0;
    int choice = 0;

    while (true) {
        // Menu to choose a function
        printf("\nSeleccione una funcion:\n");
        printf("1. Numero impar\n");
        printf("2. Fibonacci\n");
        printf("3. Factorial\n");
        printf("4. Largo de n (for)\n");
        printf("5. Largo de n (while)\n");
        printf("6. Sumatoria (for)\n");
        printf("7. Palindromo\n");
        printf("8. Salir\n");
        scanf("%d", &choice);

        if (choice == 8) {
            printf("Saliendo del programa.\n");
            break;  // Exit the program
        }

        if (choice >= 1 && choice <= 7) {
            printf("Ingrese un numero: ");
            scanf("%d", &numero);
        }

        switch (choice) {
            case 1:
                resultado = numero_impar(numero);
                break;
            case 2:
                resultado = fibonacci(numero);
                break;
            case 3:
                resultado = factorial(numero);
                break;
            case 4:
                resultado = largo_de_n_for(numero);
                break;
            case 5:
                resultado = largo_de_n_while(numero);
                break;
            case 6:
                resultado = sumatoria_for(numero);
                break;
            case 7:
                if (is_palindrome(numero)) {
                    printf("El numero es un palindromo.\n");
                } else {
                    printf("El numero no es un palindromo.\n");
                }
                continue;  // Skip displaying the result
            default:
                printf("Seleccion no valida. Por favor, elija una opcion valida.\n");
                continue;  // Skip displaying the result
        }

        printf("El resultado es: %d\n", resultado);
    }

    return 0;
}

int numero_impar(int numero){
    if(numero % 2 == 0){
        return 0;
    }
    else{
        return 1;
    }
}

int fibonacci(int numero){
    if(numero == 0){
        return 0;
    }
    else if(numero == 1){
        return 1;
    }
    else{
        return fibonacci(numero - 1) + fibonacci(numero - 2);
    }
}

int factorial(int numero){
    if(numero == 1){
        return 1;
    }
    else{
        return numero * factorial(numero - 1);
    }
}

int largo_de_n_for(int numero){
    int largo = 0;
    for(int i = 0; i < numero; i++){
        largo++;
    }
    return largo;
}

int largo_de_n_while(int numero){
    int largo = 0;
    while(numero != 0){
        largo++;
        numero--;
    }
    return largo;
}

int sumatoria_for(int numero){
    int sumatoria = 0;
    for(int i = 0; i < numero; i++){
        sumatoria = sumatoria + i;
    }
    return sumatoria;
}

bool is_palindrome(int numero) {
    int numero_invertido = 0;
    int numero_original = numero;
    while (numero != 0) {
        numero_invertido = numero_invertido * 10 + numero % 10;
        numero /= 10;
    }
    return numero_invertido == numero_original;
}