#ifndef TRABALHO_ERVADANINHA_H
#define TRABALHO_ERVADANINHA_H

#include "Plantas/Planta.h"

class ErvaDaninha : public Planta {
public:
    ErvaDaninha();

    ~ErvaDaninha() override;

    [[nodiscard]] Planta *duplicar() const override;

    [[nodiscard]] char Simbolo() const override { return 'e'; }

    bool passo(Jardim &j, int l, int c, Bloco &b) override;

protected:
    void Absorve(Bloco &b) override;

    bool CheckMorte() override;

private:
    int idade = 0; // instantes de vida (morre aos 60)
    int instantesDesdeMult = 0; // instantes desde a última multiplicação
    int instantesTotal = 0;

    // helpers privados
    void tentaMultiplicar(Jardim &j, int l, int c);
};

#endif //TRABALHO_ERVADANINHA_H
