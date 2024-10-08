#ifndef UTILS_H
#define UTILS_H

// Made by Comrade Orion!
// Utility macros for various bit manipulations and sorting

// LFSR polynomials
#define LF_POLY_ODD  (0x29CE5C)
#define LF_POLY_EVEN (0x870804)

// Get the nth bit of x
#define BIT(x, n) (((x) >> (n)) & 1)

// Get the nth bit of x, but flipped based on big-endian order
#define BEBIT(x, n) BIT(x, (n) ^ 24)

// Swap the endianness of a 32-bit integer
#define SWAPENDIAN(x)  \
    ((x) = (((x) >> 8 & 0xff00ff) | ((x) & 0xff00ff) << 8), \
     (x) = ((x) >> 16) | ((x) << 16))

// Swap two variables of the same type
#define SWAP(x, y) do { unsigned int temp = (x); (x) = (y); (y) = temp; } while (0)

    
// Swap two elements in an array if the first is greater than the second
#define SWAP_IF_GREATER(array, a, b) do { \
    unsigned int temp_a = (array)[a]; \
    unsigned int temp_b = (array)[b]; \
    asm volatile ( \
        "cmp %[temp_a], %[temp_b] \n"      /* Compare temp_a and temp_b */ \
        "it lt \n"                         /* If less than, execute the following instructions */ \
        "movlt %[temp_a], %[temp_b] \n"    /* Move temp_b to temp_a if temp_a < temp_b */ \
        "it lt \n"                         /* If less than, execute the following instructions */ \
        "movlt %[temp_b], %[temp_a] \n"    /* Move temp_a to temp_b if temp_a < temp_b */ \
        : [temp_a] "+r" (temp_a), [temp_b] "+r" (temp_b) \
        : \
        : "cc" \
    ); \
    (array)[a] = temp_a; \
    (array)[b] = temp_b; \
} while (0)

// Find the median of three elements in an array (low, mid, high)
#define MEDIAN_OF_THREE(array, low, high) ({ \
    int mid = low + ((high - low) / 2); \
    SWAP_IF_GREATER(array, low, mid); \
    SWAP_IF_GREATER(array, low, high); \
    SWAP_IF_GREATER(array, mid, high); \
    (array)[mid]; \
})

// Pretty sure the difference between 12 and 8 is negligable in RAM, but 16 works *really* well
// Like I don't believe that a whole ass KB is within error most of the time

// #define INSERTION_SORT_THRESHOLD 12 // 8.2 KB (??) Free

//#define INSERTION_SORT_THRESHOLD 8 // 8.6 KB Free

#define INSERTION_SORT_THRESHOLD 16 //9.664 KB (!!) Free 

#endif // UTILS_H
