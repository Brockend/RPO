#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <math.h>
using namespace std;
int main(int argc, char**argv)
{
int i,j,k,num;
double tmp;
num=0;
if (argc!=2)
 cout<<"\n !!!ERROR!!! Example of command: ./gauss <dimension of LSAE> !!!ERROR!!!\n"<<endl, exit(1);

cout<<"************************************************************************"<<endl;
 num=atoi(*++argv); // Enter the size LSAE
 cout<<"\tDimension of LSAE = "<<num<<endl;
double **massiv = new double * [num];
 for (i=0; i<num; i++)
 massiv[i] = new double [num+1];
double *xi = new double [num];
double *x = new double [num];
 for (i=0;i<num;i++)
 for(j=0;j<num;j++)
 while ((massiv[i][j]=5.-floor(rand()/3276.7+.5))==0);
 for (j=0;j<num;j++)
 while ((xi[j]=5.-floor(rand()/3276.7+.5))==0);

 for (i=0;i<num;i++)
 for(j=0;j<num;j++)
 massiv[i][num]+=massiv[i][j]*xi[j];
 for (k=0; k<num; k++)
 {
 tmp=abs(massiv[k][k]), i=k;
 for (j=k+1; j<num; j++)
 if(abs(massiv[j][k])>tmp)
 i=j, tmp=abs(massiv[j][k]);
 if (i!=k)
 {
 for (j=k; j<=num; j++)
 {
 tmp=massiv[k][j];
 massiv[k][j]=massiv[i][j];
 massiv[i][j]=tmp;
 }
 }
 for (j=num; j>=k+1; j--)
 massiv[k][j]/=massiv[k][k];
 for (i=k+1; i<num; i++)
 {
 tmp=massiv[i][k];
 massiv[i][k]=0;
 if (tmp!=0)
 for (j=k+1; j<num+1; j++)
 massiv[i][j]-=tmp*massiv[k][j];
 }
 }
for(j=num-1; j>=0; j--)
 {
 *(x+j)=massiv[j][num];
 for (i=j; i>=0; i--)
 massiv[i][num]-=massiv[i][j]**(x+j);
 }
 cout<<"\nCorrect answer:"<<endl;
 for (i=0; i<10; i++)
 cout<<" xi"<<i+1<<"="<<setw(2)<<*(xi+i);
 cout<<endl;
 cout<<"Solution:"<<endl;
 for (i=0; i<10; i++)
 cout<<" x"<<i+1<<"="<<setw(2)<<*(x+i);
 cout<<endl;

cout<<"************************************************************************"<<endl;
 for (i=0; i<num+1; i++)
 delete [ ] massiv[i];
 delete [ ] massiv;
 delete [ ] xi;
 delete [ ] x;
return 0;
}
