#include <iostream>
#include <cmath>
#include <complex>
#include <fstream>

using namespace std;

typedef complex<double> cmp;

void psi_init(cmp **psi, int N, double A, double sigma, double *x, double xc, double p0){
    const cmp iu(0,1);
    for (int i=1;i<N;i++){
        psi[0][i]=A*exp(-sigma*pow(x[i]-xc,2))*exp(iu*p0);
    }
    psi[0][0]=0.0;
    psi[0][N]=0.0;
}

void thomas(cmp *nw, cmp *prawa, int n, cmp a, cmp b){
    cmp *cprim = new cmp[n-1];
    cmp *dprim = new cmp[n];

    cprim[0]=a/b;
    for (int i=1;i<n-1;i++){
        cprim[i] = a/(b-a*cprim[i-1]);
    }
    dprim[0]=prawa[0]/b;
    for (int i=1;i<n;i++){
        dprim[i]=(prawa[i]-a*dprim[i-1])/(b-a*cprim[i-1]);
    }
    nw[n-1]=dprim[n-1];
    for (int i=n-2;i>=0;i--){
        nw[i]=dprim[i]-cprim[i]*nw[i+1];
    }

    delete [] cprim;
    delete [] dprim;
}

void fillPrawa(cmp *prawa, cmp **psi, cmp a, cmp b, int Nx, int n){
    for (int i=0;i<Nx-1;i++){
        prawa[i] = a*psi[n][i]+conj(b)*psi[n][i+1]+a*psi[n][i+2];
    }
}

int main(){
    // parametry
    //const double m=1.0;
    //const double hbar=1.0;
    const int N=100;
    const int Nt=200;
    const double xmin = -1.89;
    const double xmax = 1.89;
    const double tmax = 0.64;
    const double A=1.758;
    const double sigma=15.0;
    const double p0=30.0;
    const double xc=-1.0;
    const double dx = (xmax-xmin)/N;
    const double dt = tmax/Nt;
    const cmp iu(0,1);
    const int fps = 30;
    // alokacja
    double *x = new double[N+1];
    cmp **psi = new cmp*[Nt+1];
    for (int i=0;i<=Nt;i++){
        psi[i] = new cmp[N+1];
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
            psi[n][i]=0.0;
        }
    }
    psi_init(psi,N,A,sigma,x,xc,p0);
    // zmienne do rozwiązania
    cmp *nw = new cmp[N-1];
    const cmp a=iu*dt;
    const cmp b=4*dx*dx+2.0*a;
    cmp *prawa = new cmp[N-1];
    fillPrawa(prawa,psi,a,b,N,0);
    // pętla po czasie
    for (int n=1;n<=Nt;n++){
        thomas(nw,prawa,N-1,-a,b);
        for (int i=1;i<N;i++){
            psi[n][i]=nw[i-1];
        }
        fillPrawa(prawa,psi,a,b,N,n);
    }
    // zapis do pliku
    ofstream file("psi.dat");
    for (int n=0;n<=Nt;n++){
        for (int i=0;i<=N;i++){
            file<<t[n]<<'\t'<<x[i]<<'\t'<<norm(psi[n][i])<<'\n';
        }
    }
    // zapis fps
    ofstream fpsfile("fps.dat");
    fpsfile<<fps;
    fpsfile.close();
    // czystki
    delete [] x;
    for (int i=0;i<=Nt;i++){
        delete [] psi[i];
    }
    delete [] psi;
    delete [] V;
    delete [] t;
    delete [] nw;
    delete [] prawa;
    file.close();
    // return zero
    return 0;
}