// my_malloc_manager.h

// malloc es una función en el lenguaje de programación C que se utiliza para
//  asignar memoria dinámica durante la ejecución de un
// programa. Pertenece a la biblioteca estándar de C stdlib.h

#ifndef MY_ALLOC_MANAGER_H // prevent multiple includes
#define MY_ALLOC_MANAGER_H 1
// Standard includes
#include <errno.h>  // for errno
// #include <error.h>  // for error handling of system calls: man 3 error
#include <stddef.h> // for size_t
#include <stdio.h>  // for I/O functions
#include <stdlib.h> // for EXIT_FAILURE
#include <string.h> // for string manipulation functions
#include <stdint.h>
#include <sys/mman.h>


#define BITMAP_SIZE 16 // in bytes
#define UNITS_PER_CHUNK (BITMAP_SIZE * 8)
#define UNIT_SIZE (uint16_t) 16
#define SET_CHOICE 1
#define CLEAR_CHOICE 2
#define EXIT_CHOICE 0
//
#define STRUCT_UNITS (uint16_t)((sizeof (MemoryChunkHeader) + UNIT_SIZE - 1) / UNIT_SIZE) // will work even if it is exactly divisible by UNIT_SIZE
#define BITMAP_UNITS (uint16_t)((BITMAP_SIZE + UNIT_SIZE - 1) / UNIT_SIZE)
#define MAX_MALLOC_SIZE = (size_t)16 * 1024 * 1024 // 16 MB is the maximum malloc size
#define IS_LARGE_ALLOCATION(units_needed) (units_needed >= (UNITS_PER_CHUNK - STRUCT_UNITS - BITMAP_UNITS))
//
typedef unsigned char *Bitmap;
extern uint16_t chunk_current_id;
extern void *my_malloc(size_t nbytes);
extern void my_free(void *ptr); // TODO implementar

typedef struct MemoryChunkHeader {
    void *addr;
    uint16_t id;
    uint16_t is_large_allocation;
    uint16_t chunk_total_units;
    uint16_t chunk_available_units;
    Bitmap bitmap;
    uint16_t bitmap_size;
    struct MemoryChunkHeader *next;
} MemoryChunkHeader;

typedef struct AllocationHeader {
    uint16_t nunits;
    uint16_t bit_index;
} AllocationHeader;

extern MemoryChunkHeader *first_chunk; //TODO MemoryChunkHeader* o void*?
int first_fit(unsigned char *bitmap, size_t bitmap_size, size_t units_needed);
void print_bitmap(unsigned char *bitmap, size_t bitmap_size);
void set_or_clear_bits(int set, Bitmap bitmap, uint16_t start_byte_index, uint16_t start_bit_index, uint16_t qty);
MemoryChunkHeader* create_new_chunk(uint16_t units_needed, int is_large_allocation, MemoryChunkHeader *next);
void my_malloc_init();


#endif // MY_ALLOC_MANAGER_H