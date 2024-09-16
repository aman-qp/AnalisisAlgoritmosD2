#include "pruebas.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QApplication>
#include <QMainWindow>
#include <iostream>
#include <vector>
#include <string>

// Función para mostrar una gráfica con múltiples series
void showGraph(const std::vector<int>& sizes,
                const std::vector<double>& bestTimes,
                const std::vector<double>& worstTimes,
                const std::vector<double>& avgTimes,
                const std::string& title) {
    QtCharts::QLineSeries *bestSeries = new QtCharts::QLineSeries();
    QtCharts::QLineSeries *worstSeries = new QtCharts::QLineSeries();
    QtCharts::QLineSeries *avgSeries = new QtCharts::QLineSeries();

    for (size_t i = 0; i < sizes.size(); ++i) {
        bestSeries->append(sizes[i], bestTimes[i]);
        worstSeries->append(sizes[i], worstTimes[i]);
        avgSeries->append(sizes[i], avgTimes[i]);
    }

    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(bestSeries);
    chart->addSeries(worstSeries);
    chart->addSeries(avgSeries);

    // Configuración de ejes y leyenda
    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).first()->setTitleText("Tamaño del problema");
    chart->axes(Qt::Vertical).first()->setTitleText("Tiempo de ejecución");
    chart->setTitle(QString::fromStdString(title));

    // Configuración de la leyenda
    bestSeries->setName("Mejor Caso");
    worstSeries->setName("Peor Caso");
    avgSeries->setName("Caso Promedio");

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

    std::vector<int> sizes = {100, 500, 1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500, 5000, 5500, 6000, 6500, 7000, 7500, 8000};


    int choice;
    do {
        choice = showMenuAndGetSelection();

        // Variables para almacenar los tiempos de ejecución
        std::vector<double> bestTimes, worstTimes, avgTimes;

        switch (choice) {
            case 1:
                runBubbleSortTests(sizes, bestTimes, worstTimes, avgTimes);
                showGraph(sizes, bestTimes, worstTimes, avgTimes, "BubbleSort");
                break;
            case 2:
                runSelectionSortTests(sizes, bestTimes, worstTimes, avgTimes);
                showGraph(sizes, bestTimes, worstTimes, avgTimes, "SelectionSort");
                break;
            case 3:
                runMergeSortTests(sizes, bestTimes, worstTimes, avgTimes);
                showGraph(sizes, bestTimes, worstTimes, avgTimes, "MergeSort");
                break;
            case 4:
                runLinkedListTests(sizes, bestTimes, worstTimes, avgTimes);
                showGraph(sizes, bestTimes, worstTimes, avgTimes, "LinkedList");
                break;
            case 5:
                runArbolBinarioTests(sizes, bestTimes, worstTimes, avgTimes);
                showGraph(sizes, bestTimes, worstTimes, avgTimes, "ArbolBinario");
                break;
            case 0:
                std::cout << "Saliendo..." << std::endl;
                return 0;
            default:
                std::cout << "Opción inválida. Por favor, selecciona una opción válida." << std::endl;
                break;
        }
    } while (choice != 0);

    return a.exec();
}
