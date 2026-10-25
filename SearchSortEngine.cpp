#include "SearchSortEngine.h"

int SearchSortEngine::linearSearch(StudentRecord arr[], int size, int targetId, long long& comparisons) {
    comparisons = 0;
    for (int i = 0; i < size; i++) {
        comparisons++;
        if (arr[i].studentId == targetId) {
            return i;
        }
    }
    return -1;
}

int SearchSortEngine::binarySearch(StudentRecord arr[], int size, int targetId, long long& comparisons) {
    comparisons = 0;
    int left = 0;
    int right = size - 1;
    while (left <= right) {
        comparisons++;
        int mid = left + (right - left) / 2;
        if (arr[mid].studentId == targetId) {
            return mid;
        }
        if (arr[mid].studentId < targetId) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

void SearchSortEngine::bubbleSort(StudentRecord arr[], int size, long long& comparisons, long long& swaps) {
    comparisons = 0;
    swaps = 0;
    for (int i = 0; i < size - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < size - i - 1; j++) {
            comparisons++;
            if (arr[j].studentId > arr[j + 1].studentId) {
                StudentRecord temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swaps++;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void SearchSortEngine::selectionSort(StudentRecord arr[], int size, long long& comparisons, long long& swaps) {
    comparisons = 0;
    swaps = 0;
    for (int i = 0; i < size - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < size; j++) {
            comparisons++;
            if (arr[j].studentId < arr[minIdx].studentId) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            StudentRecord temp = arr[i];
            arr[i] = arr[minIdx];
            arr[minIdx] = temp;
            swaps++;
        }
    }
}

void SearchSortEngine::insertionSort(StudentRecord arr[], int size, long long& comparisons, long long& swaps) {
    comparisons = 0;
    swaps = 0;
    for (int i = 1; i < size; i++) {
        StudentRecord key = arr[i];
        int j = i - 1;
        while (j >= 0) {
            comparisons++;
            if (arr[j].studentId > key.studentId) {
                arr[j + 1] = arr[j];
                swaps++;
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = key;
    }
}
