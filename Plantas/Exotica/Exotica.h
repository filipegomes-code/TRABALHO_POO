//
// Created by jpmre on 01/11/2025.
//

#ifndef TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_EXOTICA_H
#define TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_EXOTICA_H
#include "Plantas/Planta.h"


class Exotica : public Planta {
public:
    Exotica();
    ~Exotica() override;

    char Simbolo() const override;
    void Absorve() override;
    void CheckMorte() override;
    std::string getTipo() const;
private:
    int instantesSoloSeco; // contador para a condição de morte
};


#endif //TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_EXOTICA_H