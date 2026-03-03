#include <iostream>
#include <cmath>
#include <complex>

using namespace std;

int main(){
    // parametry
    const int N=75;
    const int Nt=20;
    const double xmin = -1.0;
    const double xmax = 1.0;
    const double dx = (xmax-xmin)/N;
    // alokacja
    double *x = new double[N+1];
    complex<double> **psi = new complex<double>*[N+1];
    for (int i=0;i<=N;i++){
        psi[i] = new complex<double>[Nt+1];
    }
    // czystki
    delete [] x;
    for (int i=0;i<=N;i++){
        delete [] i[psi];
    }
    delete [] psi;
    return 0;
}