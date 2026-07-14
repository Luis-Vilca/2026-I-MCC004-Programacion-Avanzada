#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>

#include "demoThreads.h"
#include "types.h"

using namespace std;

constexpr TI NUM_ELEMENTS = 1000000;
constexpr TI NUM_THREADS  = 4;


static void processRange(vector<TI>& data, TI begin, TI end)
{
    for (TI i = begin; i < end; ++i)
        data[i] = data[i] * data[i] + 5; // Trabajo artificial para que exista carga computacional

}

void demoThreads()
{
    vector<TI> data(NUM_ELEMENTS);

    for (TI i = 0; i < NUM_ELEMENTS; ++i)
        data[i] = i;

    //----------------------------
    // Un solo hilo
    //----------------------------
    auto startSingle = chrono::high_resolution_clock::now();
    processRange(data, 0, NUM_ELEMENTS);
    auto endSingle = chrono::high_resolution_clock::now();

    auto singleTime = chrono::duration_cast<chrono::milliseconds>(endSingle - startSingle);

    //----------------------------
    // Reiniciar datos
    //----------------------------
    for (TI i = 0; i < NUM_ELEMENTS; ++i)
        data[i] = i;

    //----------------------------
    // Cuatro hilos
    //----------------------------
    auto startMulti = chrono::high_resolution_clock::now();
    vector<thread> threads;
    TI block = NUM_ELEMENTS / NUM_THREADS;

    for (TI i = 0; i < NUM_THREADS; ++i)
    {
        TI begin = i * block;
        TI end = (i == NUM_THREADS - 1) ? NUM_ELEMENTS : begin + block;

        threads.emplace_back(processRange, ref(data), begin, end);
    }

    for (auto &t : threads)
        t.join();

    auto endMulti = chrono::high_resolution_clock::now();
    auto multiTime =chrono::duration_cast<chrono::milliseconds>(endMulti - startMulti);

    //----------------------------
    // Mostrar resultados
    //----------------------------
    {
        cout << "======================================" << endl;
        cout << "Numero de elementos : " << NUM_ELEMENTS << endl;
        cout << "Numero de hilos     : " << NUM_THREADS << endl;
        cout << endl;
        cout << "Tiempo (1 hilo)     : "
             << singleTime.count() << " ms" << endl;

        cout << "Tiempo (4 hilos)    : "
             << multiTime.count() << " ms" << endl;

        cout << "Speedup             : "
             << (TD)singleTime.count() / (TD)multiTime.count()
             << "x" << endl;
        cout << "======================================" << endl;
    }
}