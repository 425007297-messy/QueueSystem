#ifndef SEARCH_SORT_ENGINE_H
#define SEARCH_SORT_ENGINE_H

#include "EntityModel.h"

class SearchSortEngine {
public:
    static int linearSearch(StudentRecord arr[], int size, int targetId, long long& comparisons);
    static int binarySearch(StudentRecord arr[], int size, int targetId, long long& comparisons);

    static void bubbleSort(StudentRecord arr[], int size, long long& comparisons, long long& swaps);
    static void selectionSort(StudentRecord arr[], int size, long long& comparisons, long long& swaps);
    static void insertionSort(StudentRecord arr[], int size, long long& comparisons, long long& swaps);
};

#endif
