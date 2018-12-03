/* Trabalho-prova final modularidade
   Especificação 7-8 - Líder: Letícia
   Nomes: Letícia - Otávio - Anne Carolina - Antônio H.
   
   Arquivo: prova2TP2.h
*/
#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

//--------------------------------------------------
// Declaração de classe Sistema 1.
//--------------------------------------------------

class Sistema1{
private:
    
	//valores iniciais 
    double X0 = 0.1;
    double Y0 = 0.1;
    double Z0 = 0.1;
	double T0 = 0;

	double FunctionZ(double Yn , double Zn , double g , double RL);
	double FunctionX(double Xn , double Yn , double a , double B1);

public: // tudo aqui a classe filha herda
	vector<double> x , y , z;
	int n = 10000;
	 
	const double a = 0.9259;
    const double B1 = 0.15;
    const double B2 = 1.5;
    const double g = 0.1;
    const double RL = 0.002;
    
    double h = 0.02; //tamanho que se avança no tempo, deve ser pequeno, muito menor que 1

    double FunctionF(double Xn);
    double FunctionY(double Xn , double Yn , double Zn , double  a , double B2);
    
    vector<double> getX();
    vector<double> getY();
	vector<double> getZ();
		
	void InitFuncs();

};

//--------------------------------------------------
// Definição de classe Sistema 1.
//--------------------------------------------------
vector<double> Sistema1::getX(){
	return x;
}

vector<double> Sistema1::getY(){
	return y;
}

vector<double> Sistema1::getZ(){
	return z;
}
		
double Sistema1::FunctionF(double Xn){

    double M0 = -0.7879;
    double M1 = -1.4357;
    double Bp = 1;
    double F;

    F = M0 * Xn + 0.5 * (M1 - M0) * (abs(Xn + Bp) - abs(Xn - Bp));

    return F;
}

double Sistema1::FunctionX(double Xn , double Yn , double a , double B1){

    double X;

    X = (a * (Yn - Xn))/B1 - FunctionF(Xn)/B1;

    return X;

}

double Sistema1::FunctionY(double Xn , double Yn , double Zn , double a , double B2){

    double Y;

    Y = (a * (-Yn + Xn))/B2 + (Zn)/B2; 

    return Y;

}

double Sistema1::FunctionZ(double Yn , double Zn , double g , double RL){

    double Z;

    Z = (-Yn/g)-(RL * Zn)/g;

    return Z;

}

void Sistema1::InitFuncs(){    

    double xn ,yn ,zn;
	//x1(posicão no vetor: "x[0]")=x0;
	xn = X0;
    yn = Y0;
    zn = Z0;
    x.push_back(xn); y.push_back(yn); z.push_back(zn);
    //x2(posicão no vetor: "x[1]")=x1
    xn = X0 + h * FunctionX(X0 , Y0 , a , B1); //x1 = x0 + h * X(x0 , y0 , a , B1)
    yn = Y0 + h * FunctionY(X0 , Y0 , Z0 , a , B2); //y1 = y0 + h * Y(x0 , y0 , z0 , a , B2) 
    zn = Z0 + h * FunctionZ(Y0 , Z0 , g , RL); //z1 = z0 + h * Z(y0 , z0 , g , RL)
    x.push_back(xn); y.push_back(yn); z.push_back(zn);

    for(int i = 2 ; i <= n - 1 ; i++){

        xn = xn + h * FunctionX(xn , yn , a , B1); //xn = x(n-1) + h * X(x(n-1) , y(n-1) , a , B1)
        yn = yn + h * FunctionY(xn , yn , zn , a , B2); //y(n-1) = y1 + h * Y(x(n-1) , z(n-1) , z(n-1) , a , B2)
        zn = zn + h * FunctionZ(yn , zn , g , RL); //zn = z(n-1) + h * Z(y(n-1) , z(n-1) , g , RL) 
        x.push_back(xn); y.push_back(yn); z.push_back(zn);

    }    
}

//--------------------------------------------------
// Declaração de classe Sistema 2.
//--------------------------------------------------

class Sistema2 : public Sistema1{ //herança
private:
    
	//valores iniciais 
    double Xs0 = 0;
    double Ys0 = 0.03;
    double Zs0 = 0;
	double T0 = 0;
public:
	//Polimorfismo: Reescrevendo função do Sistema1: com mesmo nome que deve ser diferente no sistema 2
	void InitFuncs(vector<double> Xn,vector<double> Zn);
	// o resto herdo tudo da outra classe
};

//--------------------------------------------------
// Definição de classe Sistema 2.
//--------------------------------------------------

void Sistema2::InitFuncs(vector<double> Xn,vector<double> Zn){// recebe x e z do sistema 1
	double Xsn ,Ysn ,Zsn;
    //Inicializando com valores iniciais diferentes do sistema1
	Xsn = Xs0;
    Ysn = Ys0;
    Zsn = Zs0;
    x.push_back(Xsn); y.push_back(Ysn); z.push_back(Zsn);
    
    // Xs e Zs recebem, respectivamente, Xn e Zn do Sistema1
    Xsn =  Xn[1];// Xs1 = Xn1
    Ysn = Ys0 + h * FunctionY(Xs0 , Ys0 , Zs0 , a , B2); //Ys1 = Ys0 + h * Y(Xs0 , Ys0 , Zs0 , a , B2) 
    Zsn = Zn[1]; //Zs1 = Zn1
    x.push_back(Xsn); y.push_back(Ysn); z.push_back(Zsn);

    for(int i = 2 ; i <= n - 1 ; i++){

        Xsn = Xn[i];
        Ysn = Ysn + h * FunctionY(Xsn , Ysn , Zsn , a , B2); //Y(sn-1) = Ys1 + h * Y(Xs(n-1) , Ys(n-1) , Zs(n-1) , a , B2)
        Zsn = Zn[i];
        x.push_back(Xsn); y.push_back(Ysn); z.push_back(Zsn);

    }
}

//--------------------------------------------------
// Declaração de classe Acoplar.
//--------------------------------------------------

class Acoplar{
public:
	vector<double> Xn , Yn , Zn, Xsn, Ysn, Zsn;
	void Solve();
	void Print();
	
};

//--------------------------------------------------
// Definição de classe Acoplar.
//--------------------------------------------------

void Acoplar::Solve(){
//primeiro sistema
    Sistema1 s1;
    s1.InitFuncs();
    Xn = s1.getX();
    Yn = s1.getY();
    Zn = s1.getZ();
    
//segundo sistema
	Sistema2 s2;
    s2.InitFuncs(Xn,Zn);
    Xsn = s2.getX();
    Ysn = s2.getY();
    Zsn = s2.getZ();

}
void Acoplar::Print(){

    int tam = Xn.size();
    	cout << "N Iteracao  |   [Sistema 1]   >   [Sistema 2] \n";
    for(int i = 0 ; i < tam ; i++){
    
        cout << i << " = [" << Xn[i] << ", " << Yn[i] << ", " << Zn[i] << "]" << " > [" << Xsn[i] << ", " << Ysn[i] << ", " << Zsn[i] << "]\n";
    }

}




