#include "my_malloc_manager.h"

//*mmap(void *, size_t, int, int, int, off_t)
void* create_new_chunk(uint16_t units_needed, int is_large_allocation, MemoryChunkHeader *next) {
    // Usamos mmap para asignar un bloque de memoria del tamaño necesario
    void *mem = mmap(NULL, units_needed * UNIT_SIZE, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (mem == MAP_FAILED) {
        printf("boom"); //TODO borrar esto para cuando este subido al servidor y descomentar la linea de abajo.
        // error(EXIT_FAILURE, errno, "Memory mapping failed");
    }
    uint16_t total_units_to_mmap = is_large_allocation ? units_needed + STRUCT_UNITS : UNITS_PER_CHUNK; 
    uint16_t used_units = is_large_allocation? STRUCT_UNITS : STRUCT_UNITS + BITMAP_UNITS;
    MemoryChunkHeader *new_chunk;

    new_chunk = (MemoryChunkHeader *)mem;
    new_chunk->addr = mem;
    new_chunk->id = 0; //TODO hacer que funcione con chunk_current_id++;
    new_chunk->is_large_allocation = is_large_allocation;
    new_chunk->next = next;
    new_chunk->chunk_total_units = total_units_to_mmap;
    new_chunk->bitmap = is_large_allocation ? NULL: (unsigned char *)mem + STRUCT_UNITS * UNIT_SIZE; // no bitmap needed in large allocations
    new_chunk->bitmap_size = is_large_allocation ? 8 : BITMAP_SIZE;
    new_chunk->chunk_available_units = total_units_to_mmap - used_units;

    if (!is_large_allocation){
        for (u_int16_t i = 0; i < used_units; i++){
            u_int16_t byte_index = i/8;
            u_int16_t bit_index = i%8;
            new_chunk->bitmap[byte_index] |= (1 << (7-bit_index));
        }
    }
    return new_chunk;
}