#include "my_malloc_manager.h"

void my_free(void *ptr) {
    if (ptr == NULL) {
        return;
    }

    // Obtenga el encabezado de la asignación 
    AllocationHeader *header = (AllocationHeader *)(((char *)ptr) - sizeof(AllocationHeader));

    // Obtener el encabezado del bloque de memoria
    MemoryChunkHeader *chunk = (MemoryChunkHeader *)(((char *)header) - header->bit_index * UNIT_SIZE);

    // Obtenemos el número de unidades de la asignación
    uint16_t units = header->nunits;

    // Actualiza las unidades disponibles en el chunk
    chunk->chunk_available_units += units;

    if (!chunk) {
        fprintf(stderr, "Invalid pointer passed to my_free.\n");
        exit(EXIT_FAILURE);
    }
    
    uint16_t byte = header->bit_index / 8;
    uint16_t bit = header->bit_index % 8;
    if (chunk->is_large_allocation){
        munmap(chunk->addr, chunk->chunk_total_units * UNIT_SIZE);
        printf("Freeing chunk %p\n", chunk); // No imprimimos units porque es 0
    }else{
        // Marcar con 0 los used_units del bitmap.
        set_or_clear_bits(0, chunk->bitmap, byte, bit, units);
        printf("\n");
        print_bitmap(chunk->bitmap, BITMAP_SIZE);
        printf("Freeing %d units from chunk %p\n", units, chunk);
    }
}