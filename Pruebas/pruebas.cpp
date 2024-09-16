#include "pruebas.h"
#include "BubbleSort.h"
#include "SelectionSort.h"
#include "MergeSort.h"
#include "LinkedList.h"
#include "ArbolBinario.h"
#include <chrono>
#include <random>
#include <algorithm>
#include <cmath>

std::vector<int> generateRandomArray(int size) {
    std::vector<int> arr(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10000);
    for (int i = 0; i < size; ++i) {
        arr[i] = dis(gen);
    }
    return arr;
}

std::vector<int> generateWorstCase(int size) {
    std::vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = size - i;
    }
    return arr;
}

std::vector<int> generateBestCase(int size) {
    std::vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = i + 1;
    }
    return arr;
}

std::vector<double> calculateTheoreticalValues(const std::vector<int>& sizes, const std::string& algorithm) {
    std::vector<double> theoreticalValues;
    double scaleFactor = 0.0001;
    for (int n : sizes) {
        double value;
        if (algorithm == "BubbleSort" || algorithm == "SelectionSort") {
            value = n * n;  // O(n^2)
        } else if (algorithm == "MergeSort") {
            value = n * log2(n);  // O(n log n)
        } else if (algorithm == "LinkedList") {
            value = n;  // O(n)
        } else if (algorithm == "ArbolBinario") {
            value = log2(n);  // O(log n)
        } else {
            value = 0;  // Valor por defecto si el algoritmo no está reconocido
        }
        // Aplica el factor de ajuste para que sea comparable con los resultados empíricos
        value *= scaleFactor;

        theoreticalValues.push_back(value);
    }
    return theoreticalValues;
}

template<typename Func>
double measureTime(Func func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    return duration.count();
}

// Pruebas para BubbleSort
void runBubbleSortTests(std::vector<int> sizes, std::vector<double> &bestTimes, std::vector<double> &worstTimes, std::vector<double> &avgTimes) {
    for (int N : sizes) {
        auto bestCase = generateBestCase(N);
        auto worstCase = generateWorstCase(N);
        auto avgCase = generateRandomArray(N);

        double bestTime = measureTime([&]() { BubbleSort(bestCase.data(), N); });
        double worstTime = measureTime([&]() { BubbleSort(worstCase.data(), N); });
        double avgTime = measureTime([&]() { BubbleSort(avgCase.data(), N); });

        bestTimes.push_back(bestTime);
        worstTimes.push_back(worstTime);
        avgTimes.push_back(avgTime);
    }
}

// Pruebas para SelectionSort
void runSelectionSortTests(std::vector<int> sizes, std::vector<double> &bestTimes, std::vector<double> &worstTimes, std::vector<double> &avgTimes) {
    for (int N : sizes) {
        auto bestCase = generateBestCase(N);
        auto worstCase = generateWorstCase(N);
        auto avgCase = generateRandomArray(N);

        double bestTime = measureTime([&]() { SelectionSort(bestCase.data(), N); });
        double worstTime = measureTime([&]() { SelectionSort(worstCase.data(), N); });
        double avgTime = measureTime([&]() { SelectionSort(avgCase.data(), N); });

        bestTimes.push_back(bestTime);
        worstTimes.push_back(worstTime);
        avgTimes.push_back(avgTime);
    }
}
//Pruebas para MergeSort
void runMergeSortTests(std::vector<int> sizes, std::vector<double> &bestTimes, std::vector<double> &worstTimes, std::vector<double> &avgTimes) {
    for (int N : sizes) {
        auto bestCase = generateBestCase(N);
        auto worstCase = generateWorstCase(N);
        auto avgCase = generateRandomArray(N);

        double bestTime = measureTime([&]() { MergeSort(bestCase.data(), 0, N - 1); });
        double worstTime = measureTime([&]() { MergeSort(worstCase.data(), 0, N - 1); });
        double avgTime = measureTime([&]() { MergeSort(avgCase.data(), 0, N - 1); });

        bestTimes.push_back(bestTime);
        worstTimes.push_back(worstTime);
        avgTimes.push_back(avgTime);
    }
}
//Pruebas para LinketList
void runLinkedListTests(std::vector<int> sizes, std::vector<double> &bestTimes, std::vector<double> &worstTimes, std::vector<double> &avgTimes) {
    for (int N : sizes) {
        LinkedList bestList, worstList, avgList;
        auto data = generateRandomArray(N);

        // Mejor caso: búsqueda al principio
        for (int i = N - 1; i >= 0; i--) {
            bestList.insert(data[i]);
        }
        double bestTime = measureTime([&]() { bestList.search(data[N-1]); });

        // Peor caso: búsqueda al final
        for (int val : data) {
            worstList.insert(val);
        }
        double worstTime = measureTime([&]() { worstList.search(data[N-1]); });

        // Caso promedio: búsqueda en posición aleatoria
        for (int val : data) {
            avgList.insert(val);
        }
        int randomIndex = rand() % N;
        double avgTime = measureTime([&]() { avgList.search(data[randomIndex]); });

        bestTimes.push_back(bestTime);
        worstTimes.push_back(worstTime);
        avgTimes.push_back(avgTime);
    }
}

// Pruebas para ArbolBinario
void runArbolBinarioTests(std::vector<int> sizes, std::vector<double> &bestTimes, std::vector<double> &worstTimes, std::vector<double> &avgTimes) {
    for (int N : sizes) {
        ArbolBinario bestTree, worstTree, avgTree;
        auto data = generateRandomArray(N);
        std::sort(data.begin(), data.end());

        // Función para insertar balanceado
        std::function<void(ArbolBinario&, const std::vector<int>&, int, int)> insertBalanced =
        [&insertBalanced](ArbolBinario &tree, const std::vector<int> &arr, int start, int end) {
            if (start > end) return;
            int mid = (start + end) / 2;
            tree.insert(arr[mid]);
            insertBalanced(tree, arr, start, mid - 1);
            insertBalanced(tree, arr, mid + 1, end);
        };

        // Mejor caso: árbol balanceado
        double bestTime = measureTime([&]() {
            insertBalanced(bestTree, data, 0, N - 1);
        });

        // Peor caso: árbol degenerado (como lista enlazada)
        double worstTime = measureTime([&]() {
            for (int val : data) {
                worstTree.insert(val);
            }
        });

        // Caso promedio: inserciones aleatorias
        std::random_shuffle(data.begin(), data.end());
        double avgTime = measureTime([&]() {
            for (int val : data) {
                avgTree.insert(val);
            }
        });

        bestTimes.push_back(bestTime);
        worstTimes.push_back(worstTime);
        avgTimes.push_back(avgTime);
    }
}