//
// Created by jpmre on 01/11/2025.
//

#ifndef TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_EXOTICA_H
#define TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_EXOTICA_H
#include "Plantas/Planta.h"


class Exotica : public Planta {
public:
    Exotica();
    ~Exotica() override = default;

    Planta* duplicar() const override;

    char Simbolo() const override { return 'x'; }
    bool passo(Jardim& j, int l, int c, Bloco& b) override;

protected:
    void Absorve(Bloco& b) override;
    bool CheckMorte() override;

private:
    int instantesSoloSeco = 0;

    void tentaMultiplicar(Jardim& j, int l, int c);
};


#endif //TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_EXOTICA_H