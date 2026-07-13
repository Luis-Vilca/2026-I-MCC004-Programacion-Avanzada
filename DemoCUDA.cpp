#include <iostream>
#include <cuda_runtime.h>
#include "types.h"

//nvcc DemoCUDA.cpp DemoCUDA.cu -o democuda.exe (en x64 native tools)
#include "DemoCUDA.h"

int main()
{
    ejecutarDemoCUDA();
    return 0;
}