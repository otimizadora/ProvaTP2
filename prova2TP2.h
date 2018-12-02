//Equacoes = Sistema 1
//Equacoes2 = Sistema 2

#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

class Equacoes{
// n = 0 ; ys1 = y0 + h * Y(x0 , y0 , z0 , a , B2)
    vector<double> x , y , z;

public:

    double FunctionF(double Xn);
    double FunctionX(double Xn , double Yn , double a , double B1);
    double FunctionY(double Xn , double Yn , double Zn , double  a , double B2);
    double FunctionZ(double Yn , double Zn , double g , double RL);
    void InitFuncs();
    void Imprimi();

};

double Equacoes::FunctionF(double Xn){

    double M0 = -0.7879;
    double M1 = -1.4357;
    double Bp = 1;
    double F;

    F = M0 * Xn + 0.5 * (M1 - M0) * (abs(Xn + Bp) - abs(Xn - Bp));

    return F;
}

double Equacoes::FunctionX(double Xn , double Yn , double a , double B1){

    double X;

    X = (a * (-Yn + Xn))/B1 - FunctionF(Xn)/B1;

    return X;

}

double Equacoes::FunctionY(double Xn , double Yn , double Zn , double a , double B2){

    double Y;

    Y = (a * (-Yn + Xn))/B2 + (Zn)/B2; 

    return Y;

}

double Equacoes::FunctionZ(double Yn , double Zn , double g , double RL){

    double Z;

    Z = (-Yn/g)-(RL * Zn)/g;

    return Z;

}

void Equacoes::InitFuncs(){

    double a = 0.9259;
    double B1 = 0.15;
    double B2 = 1.5;
    double g = 0.1;
    double RL = 0.002;
    double X0 = 0.1;
    double Y0 = 0.1;
    double Z0 = 0.1;
    double T0 = 0;
    double h = 0.02;
    int n = 10000;
    double xn ,yn ,zn;

    xn = X0 + h * FunctionX(X0 , Y0 , a , B1); //x1 = x0 + h * X(x0 , y0 , a , B1)
    yn = Y0 + h * FunctionY(X0 , Y0 , Z0 , a , B2); //y1 = y0 + h * Y(x0 , y0 , z0 , a , B2) 
    zn = Z0 + h * FunctionZ(Y0 , Z0 , g , RL); //z1 = z0 + h * Z(y0 , z0 , g , RL)
    x.push_back(xn); y.push_back(xn); z.push_back(xn);

    xn = xn + h * FunctionX(xn , yn , a , B1); //x2 = x1 + h * X(x1 , y1 , a , B1)
    yn = yn + h * FunctionY(xn , yn , zn , a , B2); //y2 = y1 + h * Y(x1 , z1 , z1 , a , B2)
    zn = zn + h * FunctionZ(yn , zn , g , RL); //z2 = z1 + h * Z(y1 , z1 , g , RL) 
    x.push_back(xn); y.push_back(xn); z.push_back(xn);

    for(int i = 2 ; i <= n - 1 ; i++){

        xn = xn + h * FunctionX(xn , yn , a , B1); //xn = x(n-1) + h * X(x(n-1) , y(n-1) , a , B1)
        yn = yn + h * FunctionY(xn , yn , zn , a , B2); //y(n-1) = y1 + h * Y(x(n-1) , z(n-1) , z(n-1) , a , B2)
        zn = zn + h * FunctionZ(yn , zn , g , RL); //zn = z(n-1) + h * Z(y(n-1) , z(n-1) , g , RL) 
        x.push_back(xn); y.push_back(xn); z.push_back(xn);

    }    
}

void Equacoes::Imprimi(){

    int tam = x.size();
    for(int i = 0 ; i < tam ; i++){
        cout << x[i] <<" "<< y[i] <<" "<< z[i]; 
    }

}

class Equacoes2{

    vector<double> xs , ys , zs;

public:

    void StartFunc();
    void Print();

};

void Equacoes2::StartFunc(){

    double a = 0.9259;
    double B1 = 0.15;
    double B2 = 1.5;
    double g = 0.1;
    double RL = 0.002;
    double Xs0 = 0.1;
    double Ys0 = 0.1;
    double Zs0 = 0.1;
    double T0 = 0;
    double h = 0.02;
    int n = 10000;
    double xsn ,ysn ,zsn;
    Equacoes eq; // Declaro um objeto da outra classe para ultilizar as funções da mesma.

    xsn = Xs0; //para n = 0 ; xs(n + 1) = x(n + 1) ; xs1 = x1
    ysn = Ys0 + h * eq.FunctionY(Xs0 , Ys0 , Zs0 , a , B2); // n = 0 ; ys1 = y0 + h * Y(x0 , y0 , z0 , a , B2)
    zsn = Zs0; //para n = 0 ; zs(n + 1) = z(n + 1) ; z1 = z1
    xs.push_back(xsn); ys.push_back(ysn); zs.push_back(zsn);

    xsn = xsn; //para n = 1 ; xs(n + 1) = x(n + 1) ; xs2 = x2
    ysn = ysn + h * eq.FunctionY(xsn , ysn , zsn , a , B2); // n = 1 ; ys2 = y1 + h * Y(x1 , y1 , z1 , a , B2)
    zsn = zsn; //para n = 1 ; zs(n + 1) = z(n + 1) ; zs2 = z2
    xs.push_back(xsn); ys.push_back(ysn); zs.push_back(zsn);

    for(int i = 2 ; i <= n - 1 ; i++){

        xsn = xsn;
        ysn = ysn + h * eq.FunctionY(xsn , ysn , zsn , a , B2);
        zsn = zsn;
        xs.push_back(xsn); ys.push_back(ysn); zs.push_back(zsn);

    } 

}

void Equacoes2::Print(){

    int tam = xs.size();

    for(int i = 0 ; i < tam ; i++){
        cout << xs[i] << " " << ys[i] << " " << zs[i] << " ";
    }

}