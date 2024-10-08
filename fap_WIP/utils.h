#ifndef UTILS_H
#define UTILS_H

// Made by Comrade Orion!

#define LF_POLY_ODD (0x29CE5C)
#define LF_POLY_EVEN (0x870804)
#define BIT(x, n) ((x) >> (n) & 1)
#define BEBIT(x, n) BIT(x, (n) ^ 24)
#define SWAPENDIAN(x) \
    ((x) = ((x) >> 8 & 0xff00ff) | ((x) & 0xff00ff) << 8, (x) = (x) >> 16 | (x) << 16)

#define SWAP(x, y) do { \
    int temp = *(x); \
    *(x) = *(y); \
    *(y) = temp; \
} while (0)

#define MEDIAN_OF_THREE(array, low, high) ({ \
    int mid = low + (high - low) / 2; \
    if ((array)[low] > (array)[mid]) \
        SWAP(&array[low], &array[mid]); \
    if ((array)[low] > (array)[high]) \
        SWAP(&array[low], &array[high]); \
    if ((array)[mid] > (array)[high]) \
        SWAP(&array[mid], &array[high]); \
    (array)[mid]; /* Return the median value */ \
})


#endif // UTILS_H
