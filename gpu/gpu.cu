#include "gpu.h"

__global__ void vecadd_kernel(uint64_t *A, uint64_t *B, uint64_t *C, int n) {
    int i = threadIdx.x;
    if (i < n) C[i] = A[i] + B[i];
}

void gpu_vector_add(uint64_t *A, uint64_t *B, uint64_t *C, int n) {
    uint64_t *dA, *dB, *dC;
    cudaMalloc(&dA, n * sizeof(uint64_t));
    cudaMalloc(&dB, n * sizeof(uint64_t));
    cudaMalloc(&dC, n * sizeof(uint64_t));
    cudaMemcpy(dA, A, n * sizeof(uint64_t), cudaMemcpyHostToDevice);
    cudaMemcpy(dB, B, n * sizeof(uint64_t), cudaMemcpyHostToDevice);

    vecadd_kernel<<<1, n>>>(dA, dB, dC, n);

    cudaMemcpy(C, dC, n * sizeof(uint64_t), cudaMemcpyDeviceToHost);
    cudaFree(dA); cudaFree(dB); cudaFree(dC);
}