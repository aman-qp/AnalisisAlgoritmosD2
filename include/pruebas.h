#ifndef PRUEBAS_H
#define PRUEBAS_H

#include <vector>
#include <iostream>

// Declaración de funciones para generar arreglos y medir tiempo
std::vector<int> generateRandomArray(int size);
std::vector<int> generateWorstCase(int size);
std::vector<int> generateBestCase(int size);
std::vector<double> calculateTheoreticalValues(const std::vector<int>& sizes, const std::string& algorithm);

template<typename Func>
double measureTime(Func func);

// Declaración de funciones para ejecutar las pruebas
void runBubbleSortTests(std::vector<int> sizes, std::vector<double> &bestTimes, std::vector<double> &worstTimes, std::vector<double> &avgTimes);
void runSelectionSortTests(std::vector<int> sizes, std::vector<double> &bestTimes, std::vector<double> &worstTimes, std::vector<double> &avgTimes);
void runMergeSortTests(std::vector<int> sizes, std::vector<double> &bestTimes, std::vector<double> &worstTimes, std::vector<double> &avgTimes);
void runLinkedListTests(std::vector<int> sizes, std::vector<double> &bestTimes, std::vector<double> &worstTimes, std::vector<double> &avgTimes);
void runArbolBinarioTests(std::vector<int> sizes, std::vector<double> &bestTimes, std::vector<double> &worstTimes, std::vector<double> &avgTimes);

#endif // PRUEBAS_H
