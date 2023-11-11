#include "my_malloc_manager.h"

// unsigned char *bitmap: Este argumento es un puntero a un array de
// caracteres sin signo (unsigned char), lo que significa que apunta a
// un área de memoria que contiene bytes. En este contexto, se espera
// que este array represente un bitmap en el que se realizarán operaciones. 

int first_fit(unsigned char *bitmap, size_t bitmap_size, size_t units_needed) {

    size_t consecutive_zeros = 0;
    size_t first_zero_index = 0;

    for (size_t i = 0; i < bitmap_size * 8; i++) {

        size_t byte_index = i / 8;
        size_t bit_index = i % 8;

        // Verificamos si el bit actual es 0.
        if (!(bitmap[byte_index] & (1 << (7 - bit_index)))) {
            if (consecutive_zeros == 0) {
                first_zero_index = i;
            }
            consecutive_zeros++;

            // Marcamos los bits como asignados si encontramos 
            // suficientes bits consecutivos para guardar la información que queremos guardar
            if (consecutive_zeros == units_needed) {
                // Utilizamos set_or_clear_bits para establecer los bits necesarios
                set_or_clear_bits(1, bitmap, first_zero_index / 8, first_zero_index % 8, units_needed);
                // Retornamos el índice donde comenzó la asignación
                return first_zero_index;
            }
        } else {
            consecutive_zeros = 0;
        }
    }
    // Si no hay suficiente espacio, retornamos -1
    return -1;
}