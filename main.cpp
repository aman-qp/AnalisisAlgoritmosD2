#include <iostream>
#include <chrono>
#include "BubbleSort.h"
#include "SelectionSort.h"
#include "MergeSort.h"
#include "LinkedList.h"
#include "ArbolBinario.h"

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
}

int main() {
    const int N = 1000;  // Ajusta N según el tamaño que desees probar
    int arr[N];

    // Rellenar el arreglo con valores aleatorios
    for (int i = 0; i < N; i++)
        arr[i] = rand() % 10000;

    // Prueba de BubbleSort
    int bubbleArr[N];
    std::copy(arr, arr + N, bubbleArr);
    auto start = std::chrono::high_resolution_clock::now();
    BubbleSort(bubbleArr, N);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "BubbleSort tomó " << duration.count() << " segundos." << std::endl;

    // Prueba de SelectionSort
    int selectionArr[N];
    std::copy(arr, arr + N, selectionArr);
    start = std::chrono::high_resolution_clock::now();
    SelectionSort(selectionArr, N);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "SelectionSort tomó " << duration.count() << " segundos." << std::endl;

    // Prueba de MergeSort
    int mergeArr[N];
    std::copy(arr, arr + N, mergeArr);
    start = std::chrono::high_resolution_clock::now();
    MergeSort(mergeArr, 0, N - 1);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "MergeSort tomó " << duration.count() << " segundos." << std::endl;

    // Prueba de búsqueda en la Lista Enlazada (creamos la lista manualmente)
    LinkedList lista;
    // Creación manual de la lista con N nodos
    for (int i = 0; i < N; i++) {
        Node* newNode = new Node(rand() % 10000);
        newNode->next = lista.head;  // Insertamos al principio
        lista.head = newNode;
    }

    start = std::chrono::high_resolution_clock::now();
    lista.search(rand() % 10000);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "Búsqueda en Lista Enlazada tomó " << duration.count() << " segundos." << std::endl;

    // Prueba de inserción en el Árbol Binario
    ArbolBinario arbol;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        arbol.insert(rand() % 10000);
    }
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << "Inserción en Árbol Binario tomó " << duration.count() << " segundos." << std::endl;

    return 0;
}
