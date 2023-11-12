#include "my_malloc_manager.h"

MemoryChunkHeader* create_new_chunk(uint16_t units_needed, int is_large_allocation, MemoryChunkHeader *next) {
    uint16_t total_units_to_mmap = is_large_allocation ? units_needed + STRUCT_UNITS : UNITS_PER_CHUNK; 
    void *mem = mmap(NULL, total_units_to_mmap * UNIT_SIZE, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (mem == MAP_FAILED) {
        fprintf(stderr, "Memory mapping failed\n");
        exit(EXIT_FAILURE);
    }
    uint16_t used_units = is_large_allocation ? STRUCT_UNITS : STRUCT_UNITS + BITMAP_UNITS;
    MemoryChunkHeader *new_chunk;

    new_chunk = (MemoryChunkHeader *)mem;
    new_chunk->addr = mem;
    new_chunk->id = chunk_current_id++;
    new_chunk->is_large_allocation = is_large_allocation;
    new_chunk->next = next;
    new_chunk->chunk_total_units = total_units_to_mmap;
    new_chunk->chunk_available_units = total_units_to_mmap - used_units;
    new_chunk->bitmap = is_large_allocation ? NULL : (unsigned char *)mem + STRUCT_UNITS * UNIT_SIZE; 
    new_chunk->bitmap_size = is_large_allocation ? 0 : BITMAP_SIZE;

    if (!is_large_allocation){
        //Marcar con 1 los used_units del bitmap.
        set_or_clear_bits(1, new_chunk->bitmap, 0, 0, used_units);
    }
    return new_chunk;
}