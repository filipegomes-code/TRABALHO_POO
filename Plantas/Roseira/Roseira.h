//
// Created by Filipe Gomes on 29/10/2025.
//

#ifndef TRABALHO_ROSEIRA_H
#define TRABALHO_ROSEIRA_H

#include "Plantas/Planta.h"

class Roseira : public Planta{

public:
    Roseira();
    ~Roseira() override = default; // tem se que dar override para destruir o objeto da class roseira, senao apenas destroi da classe base

    Planta* duplicar() const override;

    char Simbolo() const override { return 'r';}
    bool passo(Jardim& j, int l, int c, Bloco& b) override;

protected:
    void Absorve(Bloco& b) override;
    bool CheckMorte() override;

private:
    int aguaAbsVida = 0;
    int nutrAbsVida = 0;
    bool All_PosVizOcupadas = false;

    bool vizinhosTodosComPlanta(const Jardim& j, int l, int c) const;
    void tentaMultiplicar(Jardim& j, int l, int c);
};



#endif //TRABALHO_ROSEIRA_H
