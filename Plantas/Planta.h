//
// Created by Filipe Gomes on 29/10/2025.
//

#ifndef TRABALHO_PLANTA_H
#define TRABALHO_PLANTA_H

#include "Jardim/jardim.h"
#include <string>

class Planta{
protected:
    static int qtd_plantas;
    int nutrientes;
    int agua;
    std::string beleza;

public:
    Planta(int n, int a, std::string b);
    virtual ~Planta();

    // virtual não puras
    virtual void get_valores();

    //virtual puras -> fazem coisas especificas para cada classe
    virtual void Absorve() = 0;
    virtual void Morre() = 0;

};


#endif //TRABALHO_PLANTA_H
