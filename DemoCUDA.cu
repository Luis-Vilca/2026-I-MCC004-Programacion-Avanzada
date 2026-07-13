#include <iostream>
#include <cstdio>
#include <cuda_runtime.h>
#include "DemoCUDA.h"

using namespace std;
using TI = int;

#define CUDA_CHECK(x)                                             \
{                                                                 \
    cudaError_t err = (x);                                        \
    if (err != cudaSuccess)                                       \
    {                                                             \
        cout << "CUDA Error: " << cudaGetErrorString(err)         \
             << " (Linea " << __LINE__ << ")" << endl;            \
        exit(EXIT_FAILURE);                                       \
    }                                                             \
}

__global__ //Será ejecutada por la GPU
void sumaKernel(TI* A, TI* B, TI* C)
{
    TI i = threadIdx.x;
    printf("Hilo %d\n", i);
    C[i] = A[i] + B[i];
}

void ejecutarDemoCUDA()
{
    const TI N = 5;

    //Esto esta en la RAM del computador (host)
    TI h_A[N] = {1,2,3,4,5};
    TI h_B[N] = {10,20,30,40,50};
    TI h_C[N] = {0};

    //Punteros de la GPU (device)
    TI *d_A, *d_B, *d_C;

    TI numDevices = 0;
    CUDA_CHECK(cudaGetDeviceCount(&numDevices));

    cout << "Numero de GPUs: " << numDevices << endl;

    //Malloc para reservar memoria en la VRAM: equivalente a new
    CUDA_CHECK(cudaMalloc(&d_A, N * sizeof(TI)));
    CUDA_CHECK(cudaMalloc(&d_B, N * sizeof(TI)));
    CUDA_CHECK(cudaMalloc(&d_C, N * sizeof(TI)));

    CUDA_CHECK(cudaMemcpy(d_A, h_A, N * sizeof(TI), cudaMemcpyHostToDevice));
    CUDA_CHECK(cudaMemcpy(d_B, h_B, N * sizeof(TI), cudaMemcpyHostToDevice));

    //1 bloque de 5 hilos y ejecuta sumaKernel
    sumaKernel<<<1, N>>>(d_A, d_B, d_C);

    CUDA_CHECK(cudaGetLastError());
    //CPU espera a que la GPU termine
    CUDA_CHECK(cudaDeviceSynchronize());
    //De la GPU a la memoria RAM
    CUDA_CHECK(cudaMemcpy(h_C, d_C, N * sizeof(TI), cudaMemcpyDeviceToHost));

    cout << "\nResultado:\n";

    for (TI i = 0; i < N; i++)
        cout << h_C[i] << " ";

    cout << endl;

    CUDA_CHECK(cudaFree(d_A));
    CUDA_CHECK(cudaFree(d_B));
    CUDA_CHECK(cudaFree(d_C));
}