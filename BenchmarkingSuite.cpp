#include "BenchmarkingSuite.h"
#include "SearchSortEngine.h"
#include "EntityModel.h"
#include <iostream>
#include <chrono>
#include <cstdlib>

void BenchmarkingSuite::runBenchmarkSuite() {
    int testSizes[] = {100, 1000, 10000, 50000};
    int numSizes = 4;

    std::cout << "\n=================================== BENCHMARKING SUITE PERFORMANCE REPORT ===================================\n";
    std::cout << "Algorithm\t\tDataset Size (N)\tComparisons\t\tSwaps\t\tTime Elapsed (ms)\tBig-O\n";
    std::cout << "-------------------------------------------------------------------------------------------------------------\n";

    for (int s = 0; s < numSizes; s++) {
        int N = testSizes[s];
        StudentRecord* rawData = new StudentRecord[N];
        for (int i = 0; i < N; i++) {
            rawData[i] = {rand() % 900000 + 100000, "Student_" + std::to_string(i), "Inquiry", PriorityTier::REGULAR, 1.0 + (rand() % 200) / 100.0, "10:00 AM"};
        }

        // 1. Linear Search Benchmark
        StudentRecord* copyLS = new StudentRecord[N];
        for(int i=0; i<N; i++) copyLS[i] = rawData[i];
        long long compLS = 0;
        auto start = std::chrono::high_resolution_clock::now();
        SearchSortEngine::linearSearch(copyLS, N, copyLS[N/2].studentId, compLS);
        auto end = std::chrono::high_resolution_clock::now();
        double elapsedLS = std::chrono::duration<double, std::milli>(end - start).count();

        std::cout << "Linear Search\t\t" << N << "\t\t\t" << compLS << "\t\t\tN/A\t\t" << elapsedLS << " ms\t\tO(n)\n";
        delete[] copyLS;

        // 2. Bubble Sort Benchmark (Up to N=10,000)
        if (N <= 10000) {
            StudentRecord* copyBubble = new StudentRecord[N];
            for(int i=0; i<N; i++) copyBubble[i] = rawData[i];
            long long compBS = 0, swapBS = 0;
            start = std::chrono::high_resolution_clock::now();
            SearchSortEngine::bubbleSort(copyBubble, N, compBS, swapBS);
            end = std::chrono::high_resolution_clock::now();
            double elapsedBS = std::chrono::duration<double, std::milli>(end - start).count();

            std::cout << "Bubble Sort\t\t" << N << "\t\t\t" << compBS << "\t\t" << swapBS << "\t\t" << elapsedBS << " ms\t\tO(n^2)\n";
            delete[] copyBubble;
        }

        // 3. Selection Sort Benchmark
        if (N <= 10000) {
            StudentRecord* copySel = new StudentRecord[N];
            for(int i=0; i<N; i++) copySel[i] = rawData[i];
            long long compSS = 0, swapSS = 0;
            start = std::chrono::high_resolution_clock::now();
            SearchSortEngine::selectionSort(copySel, N, compSS, swapSS);
            end = std::chrono::high_resolution_clock::now();
            double elapsedSS = std::chrono::duration<double, std::milli>(end - start).count();

            std::cout << "Selection Sort\t\t" << N << "\t\t\t" << compSS << "\t\t" << swapSS << "\t\t" << elapsedSS << " ms\t\tO(n^2)\n";
            delete[] copySel;
        }

        delete[] rawData;
    }
    std::cout << "=============================================================================================================\n";
}
