#include <stdio.h>
#include <omp.h>
#include <time.h>

#define N 550

int main() {

    double C[N][N], A[N][N], B[N][N];
    size_t i, j, k;
    long t_ref, t_end;

    #pragma omp parallel private(i,j,k) shared(C,B,A)
    {
        #pragma omp for schedule(static)
        for (i = 0; i < N; i++ ) {
            for ( j = 0; j < N; j++ ) {
                C[i][j] = 0.;
                for ( k = 0; k < N; k++ ) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }
    }
    return 0;
}

// Normal : 0.845s
// 4 threads: static - 0.534s,  dynamic - 0.520s;
// 3 threads: static - 0.613s,  dynamic - 0.530s;
// 2 threads: static - 0.647s,  dynamic - 0.639s;
// 1 thread:  static - 1.169s,  dynamic - 1.100s;