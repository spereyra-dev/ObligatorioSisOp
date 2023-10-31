# ObligatorioSisOp
Proyecto de programación C

Desarrollar estas funciones:

int first_fit(unsigned char *bitmap, size_t bitmap_size, size_t units_needed)
void print_bitmap(unsigned char *bitmap, size_t bitmap_size)
y un programa principal que
1. defina el bitmap como un array de BITMAP_SIZE posiciones (siendo BITMAP_SIZE una constante definida con valor 16)
2. inicialice el bitmap con ceros
3. imprima el bitmap
4. haga varias invocaciones de first_fit con diversos tamaños e imprima cada vez el resultado del bitmap.
Un bitmap es un array de bytes, de tamaño bitmap_size, el cual trabajaremos a nivel de bits.
units_needed representa la cantidad de bits solicitada.
La función first_fit debe buscar un "hueco" de tamaño units_needed en el bitmap.  Si la encuentra (obviamente usando el algoritmo "first fit"), entonces debe escribir 1's en ese lugar y retornar el índice, o sea el número de bit a partir de 0.  En el caso de BITMAP_SIZE igual a 16 bytes, el índice será un número entre 0 y 127.  La función debe retornar -1 si no hay lugar.
La función print_bitmap debe escribir los bits del bitmap, byte a byte usando este formato:
11111111 00001111 11111111 00000000 00000000 11111111 11110000 00011111 11111111 11111111 11111111 11111111 11111111 00000000 00000000 00000000.
