#include <cuda_runtime.h>
#include <iostream>

__global__ void vecadd(float *a, float *b, float *c, int n) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < n) c[idx] = a[idx] + b[idx] * 2;
}

int main() {
    int N = 1024;
    float *a, *b, *c;
    cudaMallocManaged(&a, N*sizeof(float));
    cudaMallocManaged(&b, N*sizeof(float));
    cudaMallocManaged(&c, N*sizeof(float));

    for(int i=0;i<N;i++){ a[i]=i; b[i]=i*2; }

    vecadd<<<(N+255)/256, 256>>>(a,b,c,N);
    cudaDeviceSynchronize();

    for(int i=0;i<5;i++)
        std::cout<<c[i]<<" ";
    std::cout<<"\n";

    cudaFree(a); cudaFree(b); cudaFree(c);
    return 0;
}