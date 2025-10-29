
#ifndef TRABALHO_JARDIM_H
#define TRABALHO_JARDIM_H

#include <string>

class Planta;

// cada pos(bloco) do jardim.
struct bloco{
    Planta* p = nullptr; // mudar p para planta, dps de eliminar a string planta
    std::string planta; // trocar isto por Planta* , ele quer relaçao jardim->planta para meta 1
    int agua;
    int nutri;
    bool temJard;
};

// estrutura para o jardim como um todo.
struct Retangulo {
    int dimLin;
    int dimCol;
    int tam_jardim;
    bloco* solo; // por aqui dentro [] o tamanho dinamica
};


// PROTOTIPOS
void inicializa(Retangulo& x);
void MostraJardim(Retangulo& x);
void Planta_posRandom(Retangulo& jardim_plantas);
void CriaJardim(int L, int C ,Retangulo& x);


#endif //TRABALHO_JARDIM_H
