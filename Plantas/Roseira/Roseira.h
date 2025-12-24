#ifndef TRABALHO_ROSEIRA_H
#define TRABALHO_ROSEIRA_H

#include "Plantas/Planta.h"

class Roseira : public Planta {
public:
    Roseira();

    ~Roseira() override = default;

    // tem se que dar override para destruir o objeto da class roseira, senao apenas destroi da classe base

    [[nodiscard]] Planta *duplicar() const override;

    [[nodiscard]] char Simbolo() const override { return 'r'; }

    bool passo(Jardim &j, int l, int c, Bloco &b) override;

protected:
    void Absorve(Bloco &b) override;

    bool CheckMorte() override;

private:
    int aguaAbsVida = 0;
    int nutrAbsVida = 0;
    bool All_PosVizOcupadas = false;

    [[nodiscard]] static bool vizinhosTodosComPlanta(const Jardim &j, int l, int c);

    void tentaMultiplicar(Jardim &j, int l, int c);
};

#endif //TRABALHO_ROSEIRA_H
