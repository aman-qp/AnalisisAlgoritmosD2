#include "pruebas.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QApplication>
#include <QMainWindow>
#include <iostream>
#include <vector>
#include <string>
#include <QValueAxis>

// Función para obtener tamaños específicos para cada algoritmo
std::vector<int> getSizes(const std::string& algorithm) {
    if (algorithm == "BubbleSort" || algorithm == "SelectionSort") {
        return {100, 500, 1000, 1500, 2000, 2500, 3000};
    } else if (algorithm == "MergeSort") {
        return {1000, 5000, 10000, 50000, 100000, 500000, 1000000};
    } else if (algorithm == "LinkedList" || algorithm == "ArbolBinario") {
        return {100, 1000, 10000, 100000, 1000000};
    }
    return {100, 500, 1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500, 5000};
}

// Función para mostrar una gráfica con múltiples series
void showGraph(const std::vector<int>& sizes,
               const std::vector<double>& bestTimes,
               const std::vector<double>& worstTimes,
               const std::vector<double>& avgTimes,
               const std::vector<double>& theoreticalTimes,
               const std::string& title) {
    QtCharts::QLineSeries *bestSeries = new QtCharts::QLineSeries();
    QtCharts::QLineSeries *worstSeries = new QtCharts::QLineSeries();
    QtCharts::QLineSeries *avgSeries = new QtCharts::QLineSeries();
    QtCharts::QLineSeries *theoreticalSeries = new QtCharts::QLineSeries();

    // Encontrar el valor máximo para normalizar
    double maxTime = 0;
    for (size_t i = 0; i < sizes.size(); ++i) {
        maxTime = std::max({maxTime, bestTimes[i], worstTimes[i], avgTimes[i], theoreticalTimes[i]});
    }

    // Factor de multiplicación para ajustar la escala
    double scaleFactor = 1.0 / maxTime;

    for (size_t i = 0; i < sizes.size(); ++i) {
        bestSeries->append(sizes[i], bestTimes[i] * scaleFactor);
        worstSeries->append(sizes[i], worstTimes[i] * scaleFactor);
        avgSeries->append(sizes[i], avgTimes[i] * scaleFactor);
        theoreticalSeries->append(sizes[i], theoreticalTimes[i] * scaleFactor);
    }

    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(bestSeries);
    chart->addSeries(worstSeries);
    chart->addSeries(avgSeries);
    chart->addSeries(theoreticalSeries);

    // Configuración de ejes y titulo
    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).first()->setTitleText("Tamaño del problema");
    chart->axes(Qt::Vertical).first()->setTitleText("Tiempo de ejecución");
    chart->setTitle(QString::fromStdString(title));

    // Configuración de los titulos
    bestSeries->setName("Mejor Caso");
    worstSeries->setName("Peor Caso");
    avgSeries->setName("Caso Promedio");
    theoreticalSeries->setName("Valor Teórico");

    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QMainWindow *window = new QMainWindow();
    window->setCentralWidget(chartView);
    window->resize(800, 600);
    window->show();

    // Esperar a que la ventana se cierre antes de volver a mostrar el menú
    while (window->isVisible()) {
        QApplication::processEvents();
    }

    delete window; // Limpiar la ventana después de que se cierra
}

// Función para mostrar un menú y leer la opción seleccionada
int showMenuAndGetSelection() {
    std::cout << "Selecciona qué gráfica deseas ver:" << std::endl;
    std::cout << "1. BubbleSort" << std::endl;
    std::cout << "2. SelectionSort" << std::endl;
    std::cout << "3. MergeSort" << std::endl;
    std::cout << "4. LinkedList" << std::endl;
    std::cout << "5. ArbolBinario" << std::endl;
    std::cout << "0. Salir" << std::endl;

    int choice;
    std::cin >> choice;
    return choice;
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    int choice;
    do {
        choice = showMenuAndGetSelection();

        // Variables para almacenar los tiempos de ejecución
        std::vector<double> bestTimes, worstTimes, avgTimes, theoreticalTimes;
        std::string algorithmName;

        switch (choice) {
            case 1:
                algorithmName = "BubbleSort";
            break;
            case 2:
                algorithmName = "SelectionSort";
            break;
            case 3:
                algorithmName = "MergeSort";
            break;
            case 4:
                algorithmName = "LinkedList";
            break;
            case 5:
                algorithmName = "ArbolBinario";
            break;
            case 0:
                std::cout << "Saliendo..." << std::endl;
            return 0;
            default:
                std::cout << "Opción inválida. Por favor, selecciona una opción válida." << std::endl;
            continue;
        }

        std::vector<int> sizes = getSizes(algorithmName);

        if (algorithmName == "BubbleSort") {
            runBubbleSortTests(sizes, bestTimes, worstTimes, avgTimes);
        } else if (algorithmName == "SelectionSort") {
            runSelectionSortTests(sizes, bestTimes, worstTimes, avgTimes);
        } else if (algorithmName == "MergeSort") {
            runMergeSortTests(sizes, bestTimes, worstTimes, avgTimes);
        } else if (algorithmName == "LinkedList") {
            runLinkedListTests(sizes, bestTimes, worstTimes, avgTimes);
        } else if (algorithmName == "ArbolBinario") {
            runArbolBinarioTests(sizes, bestTimes, worstTimes, avgTimes);
        }

        theoreticalTimes = calculateTheoreticalValues(sizes, algorithmName);
        showGraph(sizes, bestTimes, worstTimes, avgTimes, theoreticalTimes, algorithmName);

    } while (choice != 0);

    return a.exec();
}

