#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<sys/time.h>
#include <omp.h>

#define E 0.00001
#define T 0.01

double Spr, Spr1, Spz;

int main(int argc, char**argv)
 { int i, j, v, M;
 M=atoi(*++argv); // Enter the size LSAE
 printf(" Dimension of LSAE = %d\n",M);
 double itime, ftime, exec_time;
 
 double ( *A )[M] = malloc( sizeof( double[M][M] ) );
 double F[M], Xk[M], Zk[M];
 double Rk[M], Sz[M], alf, bet, mf;
 
 for(mf=0,i = 0; i < M; i++)
 { for(j = 0; j < M; j++)
 { if(i == j)
 A[i][j] = 2.0;
 else
 A[i][j] = 1.0;
 }
 F[i] = M + 1;

mf += F[i] * F[i];
 }

 for(i = 0; i < M; i++)
 Xk[i] = 0.2;

 for(i = 0; i < M; i++)
 { for(Sz[i]=0,j = 0; j < M; j++)
 Sz[i] += A[i][j] * Xk[j];
Rk[i] = F[i] - Sz[i];
Zk[i] = Rk[i];
 }

 itime = omp_get_wtime();
 do
 {

 Spz = 0;
 Spr = 0;
 for(i = 0; i < M; i++)
 { for(Sz[i]=0, j = 0; j < M; j++)
 Sz[i] += A[i][j] * Zk[j];
 Spz += Sz[i] * Zk[i];
 Spr += Rk[i] * Rk[i];
 }
 alf = Spr/Spz; 
 
 Spr1 = 0;
 for(i = 0; i < M; i++)
 { Xk[i] += alf*Zk[i];
 Rk[i] -= alf*Sz[i];
 Spr1 += Rk[i]*Rk[i];
 }
 bet = Spr1/Spr;
 
 for(i = 0; i < M; i++)
 Zk[i] = Rk[i] + bet*Zk[i];
 }
 while(Spr1/mf > E*E);
 ftime = omp_get_wtime();
 exec_time = ftime - itime;
 printf("\n\nTime taken is %f", exec_time);
/* Для контролю результатів виводяться 8 перших коренів */
printf(" %f %f %f %f %f %f %f %f\n",Xk[0],Xk[1],Xk[2],Xk[3],Xk[4],Xk[5],
Xk[6], Xk[7]);
 return(0);
 }