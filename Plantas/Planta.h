//
// Created by Filipe Gomes on 29/10/2025.
//

#ifndef TRABALHO_PLANTA_H
#define TRABALHO_PLANTA_H

#include "Jardim/Jardim.h"
#include <string>

class Planta{
protected:
    static int qtd_plantas;
    int nutrientes;
    int agua;
    std::string beleza;

    virtual void Absorve(Bloco& b) = 0;
    virtual bool CheckMorte() = 0;

public:
    Planta(int n, int a, std::string b);
    virtual ~Planta();

    // getters básicos – úteis para lplantas / lplanta / larea
    int getAgua() const        { return agua; }
    int getNutrientes() const  { return nutrientes; }
    const std::string& getBeleza() const { return beleza; }

    //virtual puras -> fazem coisas especificas para cada classe
    virtual char Simbolo()const=0;

    // Um único passo por instante
    virtual bool passo(Jardim& j, int l, int c, Bloco& b);

    virtual std::string getInfo() const;
};


#endif //TRABALHO_PLANTA_H
