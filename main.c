#include "my_malloc_manager.h"

int main() {
    // Creamos e inicializamos el mapa de bits a cero
    unsigned char bitmap[BITMAP_SIZE] = {0};

    printf("Bitmap Size: %d bytes\n", BITMAP_SIZE);

    while (1) {
        // Solicitamos al usuario que introduzca el número de bits que desea ocupar
        printf("Enter the number of bits to occupy (0 to exit): ");
        int units_needed;
        // Leemos la entrada del usuario y verificamos que es un número válido
        if(scanf("%d", &units_needed) != 1) {
            printf("Invalid input.\n");
            continue; // Si la entrada no es válida, volvemos al principio del bucle
        }

        // Si el usuario introduce 0, salimos del bucle y terminamos el programa
        if (units_needed == 0) {
            break;
        }
        else {
            // Verificamos si hay suficiente espacio en el mapa de bits para la cantidad de unidades solicitadas
            if(units_needed > BITMAP_SIZE*8) {
                printf("Not enough space in the bitmap.\n");
                continue; // Si no hay suficiente espacio, volvemos al principio del bucle
            }
            // Intentamos encontrar un espacio en el mapa de bits para las unidades solicitadas
            int index = first_fit(bitmap, BITMAP_SIZE, units_needed);

            // Si la función first_fit encuentra un espacio adecuado, imprime un mensaje de éxito
            if (index != -1) {
                printf("Allocated %d units starting at index %d.\n", units_needed, index);
            } 
            else { 
                // Si no se encontró espacio, imprime un mensaje de error
                printf("Failed to allocate %d units.\n", units_needed);
            }
        }
        // Imprimimos el estado actual del mapa de bits después de cada operación de asignación
        printf("Updated Bitmap: ");
        print_bitmap(bitmap, BITMAP_SIZE);
    }

    return 0;
}