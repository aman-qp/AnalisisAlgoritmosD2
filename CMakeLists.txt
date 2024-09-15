cmake_minimum_required(VERSION 3.29)
project(AnalisisAlgoritmos)

set(CMAKE_CXX_STANDARD 20)

# Incluir directorios de cabeceras
include_directories(include)

# Definir el ejecutable con los archivos fuente
add_executable(AnalisisAlgoritmos
        main.cpp
        "Algoritmos y Estructuras/BubbleSort.cpp"
        "Algoritmos y Estructuras/SelectionSort.cpp"
        "Algoritmos y Estructuras/MergeSort.cpp"
        "Algoritmos y Estructuras/ArbolBinario.cpp"
        "Algoritmos y Estructuras/LinkedList.cpp"
        test.cpp
)
