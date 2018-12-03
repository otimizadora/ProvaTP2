#ifndef SISTEMA1_H
#define SISTEMA1_H
/* Trabalho-prova final modularidade
   Especificação 7-8 - Líder: Letícia
   Nomes: Letícia - Otávio - Anne Carolina - Antônio H.
   
   Arquivo: Sistema1.h
*///--------------------------------------------------
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
#endif
