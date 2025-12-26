#ifndef TRABALHO_PLANTA_H
#define TRABALHO_PLANTA_H

#include "Jardim/Jardim.h"
#include <string>

using std::string;

class Planta {
public:
    Planta(int n, int a, string b);

    virtual ~Planta();

    [[nodiscard]] virtual Planta *duplicar() const = 0;

    // getters básicos – úteis para lplantas / lplanta / larea
    [[nodiscard]] int getAgua() const { return agua; }
    [[nodiscard]] int getNutrientes() const { return nutrientes; }
    [[nodiscard]] const string &getBeleza() const { return beleza; }

    //virtual puras → fazem coisas específicas para cada classe
    [[nodiscard]] virtual char Simbolo() const =0;

    // Um único passo por instante
    virtual bool passo(Jardim &j, int l, int c, Bloco &b) = 0;

protected:
    int nutrientes;
    int agua;
    string beleza;

    virtual void Absorve(Bloco &b) = 0;

    virtual bool CheckMorte() = 0;
};

#endif //TRABALHO_PLANTA_H
