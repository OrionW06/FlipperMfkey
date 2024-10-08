#ifndef UTILS_H
#define UTILS_H

#pragma GCC optimize("O3")
#pragma GCC optimize("-funroll-all-loops")

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
#define SWAP(a, b) \
    __asm__ __volatile__ ( \
        "eor r2, %0, %1\n\t" \
        "eor %0, %0, r2\n\t" \
        "eor %1, %1, r2" \
        : "+r" (*a), "+r" (*b) \
        : \
        : "r2" \
    )


// Find the median of three elements in an array (low, mid, high)
//static inline unsigned int MEDIAN_OF_THREE(unsigned int *arr, int low, int high) {
//    int mid = low + ((high - low) >> 1);
//    if (arr[mid] < arr[low])
//        SWAP(&arr[mid], &arr[low]);
//    if (arr[high] < arr[low])
//        SWAP(&arr[high], &arr[low]);
//    if (arr[mid] < arr[high])
//        SWAP(&arr[mid], &arr[high]);
//    return arr[high];
//}

static inline unsigned int MEDIAN_OF_THREE(unsigned int *arr, int low, int high) {
    int mid = low + ((high - low) >> 1);

    // Load arr[low], arr[mid], arr[high] into temporary variables
    unsigned int low_val = arr[low];
    unsigned int mid_val = arr[mid];
    unsigned int high_val = arr[high];

    __asm__ __volatile__ (
        // Compare and swap elements to find the median
        "cmp %[mid], %[low]\n\t"
        "blt 1f\n\t"
        "mov %[temp], %[mid]\n\t"
        "mov %[mid], %[low]\n\t"
        "mov %[low], %[temp]\n\t"
        "1:\n\t"
        "cmp %[high], %[low]\n\t"
        "blt 2f\n\t"
        "mov %[temp], %[high]\n\t"
        "mov %[high], %[low]\n\t"
        "mov %[low], %[temp]\n\t"
        "2:\n\t"
        "cmp %[mid], %[high]\n\t"
        "blt 3f\n\t"
        "mov %[temp], %[mid]\n\t"
        "mov %[mid], %[high]\n\t"
        "mov %[high], %[temp]\n\t"
        "3:\n\t"
        : [low] "+r" (low_val), [mid] "+r" (mid_val), [high] "+r" (high_val), [temp] "=&r" (high_val)
        : // No inputs
        : "cc" // Clobber condition flags
    );

    // Store the sorted results back into the array
    arr[low] = low_val;
    arr[mid] = mid_val;
    arr[high] = high_val;

    return arr[high];
}

#endif // UTILS_H
