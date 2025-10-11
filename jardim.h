
#ifndef TRABALHO_JARDIM_H
#define TRABALHO_JARDIM_H

#include <iostream>
#include <cstdlib> // biblioteca para o rand, srand
#include <ctime> // biblioteca para o time
using namespace std;

const int dimLin = 10;
const int dimCol = 15;


struct Retangulo {
    string soloJardim[dimLin][dimCol];
};



// PROTOTIPOS
void inicializa(Retangulo& x);
void MostraJardim(const Retangulo& x);


#endif //TRABALHO_JARDIM_H
