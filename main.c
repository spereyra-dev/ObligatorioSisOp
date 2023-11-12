#include "my_malloc_manager.h"

// Funcion para obtener la entrada del usuario
int get_user_input(char *prompt, int *input) {
    printf("%s", prompt);
    if(scanf("%d", input) != 1) {
        printf("Invalid input.\n");
        return 0;
    }
    return 1;
}

uint16_t chunk_current_id = 0;
MemoryChunkHeader *first_chunk = NULL;

int main() {
    char *ptr;
    MemoryChunkHeader *chunk;
    AllocationHeader *header;
    while (1) {
        int choice;
        if (!get_user_input("Enter your choice (1 to set, 2 to clear or 0 to exit) ", &choice)) {
            continue;
        }
        if (choice == EXIT_CHOICE) {
            break;
        }
        int qty;
        if (choice == SET_CHOICE){
            if (!get_user_input("Enter the number of bits to occupy: ", &qty)) {
                continue;
            }
            ptr = my_malloc(qty);
            printf("Allocated memory at address: %p\n", ptr);
            header = (AllocationHeader *)(((char *)ptr) - sizeof(AllocationHeader));
            chunk = (MemoryChunkHeader *)(((char *)header) - header->bit_index * UNIT_SIZE);
            printf("MemoryChunkHeader details:\n");
            printf("  addr: %p\n", chunk->addr);
            printf("  id: %d\n", chunk->id);
            printf("  is_large_allocation: %s\n", chunk->is_large_allocation ? "Yes" : "No");
            printf("  next: %p\n", chunk->next);
            printf("  chunk_total_units: %d\n", chunk->chunk_total_units);
            printf("  bitmap: %p\n", chunk->bitmap);
            printf("  bitmap_size: %hu\n", chunk->bitmap_size);
            printf("  chunk_available_units: %d\n", chunk->chunk_available_units);
            printf("\n");
            if (!chunk->is_large_allocation) {
                print_bitmap(chunk->bitmap, BITMAP_SIZE);
            }
        } else if (choice == CLEAR_CHOICE){
            printf("Enter the pointer to free: ");
            void *ptrFree;
            if (scanf("%p", &ptrFree) != 1) {
                printf("Invalid input.\n");
                continue;
            }
            my_free(ptrFree);
            printf("Memory freed.\n");
        } else {
            fprintf(stderr, "Invalid choice. Please choose 1 to set, 2 to clear or 0 to exit.\n");
        }
    }
    return 0;
}