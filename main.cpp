#include <iostream>
#include <cmath>
#include <complex>
#include <fstream>

using namespace std;

void psi_init(complex<double> **psi, int N, double A, double sigma, double *x, double xc){
    for (int i=1;i<N;i++){
        psi[i][0]=A*exp(-sigma*pow(x[i]-xc,2));
    }
    psi[0][0]=0.0;
    psi[N][0]=0.0;
}

int main(){
    // parametry
    const double m=1.0;
    const double hbar=1.0;
    const int N=75;
    const int Nt=200;
    const double xmin = -1.0;
    const double xmax = 1.0;
    const double tmax = 1.0;
    const double A=0.457646;
    const double sigma=15.0;
    const double xc=0.0;
    const double dx = (xmax-xmin)/N;
    const double dt = 0.0001;
    const complex<double> iu(0,1);
    const complex<double> a=iu/(2*dx*dx);
    // alokacja
    double *x = new double[N+1];
    complex<double> **psi = new complex<double>*[N+1];
    for (int i=0;i<=N;i++){
        psi[i] = new complex<double>[Nt+1];
    }
    double *V = new double[N+1];
    double *t = new double[Nt+1];
    // inicjalizacja
    for (int i=0;i<=N;i++){
        x[i] = xmin + dx*i;
        V[i]=0.0;
    }
    for (int n=0;n<=Nt;n++){
        t[n] = n*dt;
    }
    for (int i=0;i<=N;i++){
        for (int n=0;n<=Nt;n++){
            psi[i][n]=0.0;
        }
    }
    psi_init(psi,N,A,sigma,x,xc);
    // pętla po czasie
    for (int n=1;n<=Nt;n++){
        // pętla po przestrzeni
        for (int i=1;i<N;i++){
            psi[i][n]=psi[i][n-1]+dt*(a*psi[i+1][n-1]+(-2.0*a-iu*V[i])*psi[i][n-1]+a*psi[i-1][n-1]);
        }
    }
    // zapis do pliku
    ofstream file("psi.dat");
    for (int n=0;n<=Nt;n++){
        for (int i=0;i<=N;i++){
            file<<t[n]<<'\t'<<x[i]<<'\t'<<norm(psi[i][n])<<'\n';
        }
    }
    // czystki
    delete [] x;
    for (int i=0;i<=N;i++){
        delete [] i[psi];
    }
    delete [] psi;
    delete [] V;
    delete [] t;
    file.close();
    // return zero
    return 0;
}