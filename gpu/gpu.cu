#include <cuda_runtime.h>
#include <stdint.h>
#include <stdio.h>
#include "../utils/utils.h"  // make sure the relative path is correct

extern "C" {

// GPU vector add
void gpu_vector_add(uint64_t *A, uint64_t *B, uint64_t *C, int n){
    for(int i=0;i<n;i++) C[i] = A[i] + B[i];
    log_info("GPU vector add completed\n");
}

// GPU matrix multiply
void gpu_matrix_mul(uint64_t *A, uint64_t *B, uint64_t *C, int N){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            uint64_t sum = 0;
            for(int k=0;k<N;k++) sum += A[i*N+k]*B[k*N+j];
            C[i*N+j] = sum;
        }
    }
    log_info("GPU matrix multiply completed\n");
}

} // extern "C"