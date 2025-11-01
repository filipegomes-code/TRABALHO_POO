//
// Created by Filipe Gomes on 29/10/2025.
//

#ifndef TRABALHO_ROSEIRA_H
#define TRABALHO_ROSEIRA_H

#include "Plantas/Planta.h"

class Roseira : public Planta{
public:
    Roseira();
    ~Roseira() override; // tem se que dar override para destruir o objeto da class roseira, senao apenas destroi da classe base

    char Simbolo() const override;
    void Absorve() override;
    void CheckMorte() override;

};



#endif //TRABALHO_ROSEIRA_H
