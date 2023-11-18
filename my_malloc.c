#include "my_malloc_manager.h"

void my_malloc_init(){
    // initialize the memory manager
    // create the first chunk
    first_chunk = create_new_chunk(UNITS_PER_CHUNK, 0, NULL);
    if (first_chunk == NULL || first_chunk->bitmap == NULL) {
        printf("Initialization failed");
    }
    
}

void *my_malloc(size_t nbytes){
    uint16_t units_needed = (nbytes + sizeof(AllocationHeader) + UNIT_SIZE - 1) / UNIT_SIZE;
    printf("Units needed: %hd\n", units_needed);
    MemoryChunkHeader *chunk = NULL;
    int bit_index;
    int is_large_allocation = IS_LARGE_ALLOCATION(units_needed);
    if (first_chunk == NULL) {
        my_malloc_init(); 
    }
    if (is_large_allocation) {
        printf("\n New chunk for large allocation will be created. We need %hd units.\n", units_needed);
        chunk = first_chunk->next = create_new_chunk(units_needed, 1, first_chunk->next); 
        bit_index = STRUCT_UNITS;
    } else {
        for (chunk = first_chunk; chunk != NULL; chunk = chunk->next) {
            if (units_needed > chunk->chunk_available_units) {
                printf("Not enough space in chunk id %hd that has %hd available units\n", chunk->id, chunk->chunk_available_units);
                continue; 
            }
            bit_index = first_fit(chunk->bitmap, chunk->bitmap_size, units_needed);
            if (bit_index != -1) {
                printf("\nFound a hole in chunk id %hd at bit index %d\n", chunk->id, bit_index);
                break;
            }
        }
        if (chunk == NULL) {
            chunk = first_chunk->next = create_new_chunk (units_needed, 0, first_chunk->next); 
            bit_index = first_fit(chunk->bitmap, chunk->bitmap_size, units_needed);
            if (bit_index == -1) { 
                fprintf(stderr, "bit index return -1 on new chunk, programming error. Exiting.\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    chunk->chunk_available_units -= units_needed;
    size_t offset = bit_index * UNIT_SIZE;
    AllocationHeader *allocation_header = (AllocationHeader *) ((char *) chunk->addr + offset);
    allocation_header->nunits = is_large_allocation ? 0 : units_needed;
    allocation_header->bit_index = bit_index;
    return (char *) allocation_header + sizeof (AllocationHeader);
}