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
#define SWAP(x, y) \
    do { \
        unsigned int temp = *(x); \
        *(x) = *(y); \
        *(y) = temp; \
    } while (0)

// Swap two elements in an array if the first is greater than the second
#define SWAP_IF_GREATER(array, a, b) do { \
    if ((array)[a] > (array)[b]) { \
        SWAP(&(array)[a], &(array)[b]); \
    } \
} while (0)

// Find the median of three elements in an array (low, mid, high)
#define MEDIAN_OF_THREE(array, low, high) ({ \
    int mid = low + ((high - low) / 2); \
    SWAP_IF_GREATER(array, low, mid); \
    SWAP_IF_GREATER(array, low, high); \
    SWAP_IF_GREATER(array, mid, high); \
    (array)[mid]; \
})

#endif // UTILS_H
