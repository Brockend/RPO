#include<stdio.h>
#include<sys/time.h>
#include <omp.h>
#include<stdlib.h>

int main(int argc, char**argv) {
    int i, j;
    int N = atoi(*++argv);
    long int dt;
    double( * A)[N] = malloc(sizeof(double[N][N]));
    double t, e;
    double F[N], mf, X[N], X1[N], S[N], msf;
    double itime, ftime, exec_time;
    
    mf = 0;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++)
            (i == j) ? (A[i][j] = 2) : (A[i][j] = 1);
        F[i] = N + 1;
        mf += F[i] * F[i];
    }
    t = 0.01;
    e = 0.00001;

    for (i = 0; i < N; i++)
        X1[i] = 0.6;

    itime = omp_get_wtime();
    do {
        for (i = 0; i < N; i++)
            X[i] = X1[i];
        for (msf = 0, i = 0; i < N; i++) {
            for (S[i] = 0, j = 0; j < N; j++)
                S[i] += A[i][j] * X[j];
            X1[i] = X[i] - t * (S[i] - F[i]);
            msf += (S[i] - F[i]) * (S[i] - F[i]);
        }
    }
    while (msf / mf > e * e); 

    ftime = omp_get_wtime();
    exec_time = ftime - itime;
    
    printf(" Time= %f\n", exec_time);
    
   
    for (i = 0; i < 4; i++) {
        printf(" %f\n", X[i]);
    }

    return (0);
}