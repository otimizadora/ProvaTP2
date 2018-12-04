#ifndef SISTEMA2_H
#define SISTEMA2_H

//Trabalho-prova final modularidade
//   Especificação 7-8 - Líder: Letícia
//   Nomes: Letícia - 15/0015178
//          Otávio - 15/0143401
//          Anne Carolina - 14/0016546
//          Antonio H - 15/0118236
#include "Sistema1.h"
//--------------------------------------------------
// Declara��o de classe Sistema 2.
//--------------------------------------------------

class Sistema2 : public Sistema1{ //heran�a
private:
    
	//valores iniciais 
    long double Xs0 = 0;
    long double Ys0 = 0.03;
    long double Zs0 = 0;
	long double T0 = 0;
public:
	//Polimorfismo: Reescrevendo função do Sistema1 que tem mesmo nome, mas definições diferentes em cada sistema
	void InitFuncs(vector<long double> Xn,vector<long double> Zn);
	// o resto herdo tudo da outra classe
};

//--------------------------------------------------
// Definição de classe Sistema 2.
//--------------------------------------------------

void Sistema2::InitFuncs(vector<long double> Xn,vector<long double> Zn){// recebe x e z do sistema 1
	long double Xsn ,Ysn ,Zsn;
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
#endif
