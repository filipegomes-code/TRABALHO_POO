
#ifndef TRABALHO_JARDIM_H
#define TRABALHO_JARDIM_H

#include <string>

class Planta;

// cada pos(bloco) do jardim.
struct bloco{
    Planta* planta = nullptr;
    int agua;
    int nutri;
    bool temJard;
};

// estrutura para o jardim como um todo.
struct Retangulo {
    int dimLin;
    int dimCol;
    int tam_jardim;
    bloco* solo;
};

// PROTOTIPOS
void inicializa(Retangulo& x);
void MostraJardim(Retangulo& x);
void Planta_posRandom(Retangulo& jardim_plantas);
void CriaJardim(int L, int C ,Retangulo& x);


#endif //TRABALHO_JARDIM_H
