cmake_minimum_required(VERSION 3.29)
project(AnalisisAlgoritmos)

set(CMAKE_CXX_STANDARD 20)

# Activar AUTOMOC, AUTOUIC y AUTORCC para Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Incluir directorios de cabeceras
include_directories(include)

# Encontrar paquetes de Qt5
find_package(Qt5 COMPONENTS Widgets Charts REQUIRED)

# Definir el ejecutable con los archivos fuente
add_executable(AnalisisAlgoritmos
        main.cpp
        "Algoritmos y Estructuras/BubbleSort.cpp"
        "Algoritmos y Estructuras/SelectionSort.cpp"
        "Algoritmos y Estructuras/MergeSort.cpp"
        "Algoritmos y Estructuras/ArbolBinario.cpp"
        "Algoritmos y Estructuras/LinkedList.cpp"
        "Pruebas/pruebas.cpp"
)

target_link_libraries(AnalisisAlgoritmos Qt5::Widgets Qt5::Charts)
