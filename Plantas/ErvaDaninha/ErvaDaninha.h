//
// Created by Filipe Gomes on 29/10/2025.
//

#ifndef TRABALHO_ERVADANINHA_H
#define TRABALHO_ERVADANINHA_H

#include "Plantas/Planta.h"

class ErvaDaninha : public Planta{
private:
    int idade = 0;              // instantes de vida (morre aos 60)
    int instantesDesdeMult = 0; // instantes desde a última multiplicação
    int instantesTotal = 0;

    // helpers privados
    void tentaMultiplicar(Jardim& j, int l, int c);

protected:
    void Absorve(Bloco& b) override;
    bool CheckMorte() override;

public:
    ErvaDaninha();
    ~ErvaDaninha() override;

    char Simbolo()const override {return 'e';}
    bool passo(Jardim& j, int l, int c, Bloco& b) override;

};



#endif //TRABALHO_ERVADANINHA_H
