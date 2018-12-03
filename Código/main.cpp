/* Trabalho-prova final modularidade
   Especificação 7-8 - Líder: Letícia
   Nomes: Letícia - Otávio - Anne Carolina - Antônio H.
   
   Arquivo: main.cpp
*/
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <assert.h>
#include <ctype.h>
#include <stddef.h>

using namespace std;

#include "Sistema1.h"
#include "Sistema2.h"
#include "Acoplar.h"


int main(){

    Acoplar coupling;

    coupling.Solve();
 	coupling.Print();

    return 0;
}
