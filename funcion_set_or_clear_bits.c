#include "my_malloc_manager.h"

void set_or_clear_bits(int set, Bitmap bitmap, uint16_t start_byte_index, uint16_t start_bit_index, uint16_t qty) {
    for (uint16_t i = 0; i < qty; i++) {
        unsigned char *current_byte = &bitmap[(start_byte_index + (start_bit_index + i) / 8) % BITMAP_SIZE];
        unsigned char current_bit = 1 << (7 - ((start_bit_index + i) % 8));
        
        if (set) {
            *current_byte |= current_bit; // Si set es 1, escribimos un 1
        } else {
            *current_byte &= ~current_bit; // Si set es 0, escribimos un 0
        }
    }
}