//
// Created by jpmre on 01/11/2025.
//

#ifndef TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_FERRAMENTAZ_H
#define TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_FERRAMENTAZ_H

#include "Settings.h"
#include "Ferramentas/Ferramenta.h"


class FerramentaZ : public Ferramenta {
private:
    int cargasRestantes = Settings::FerramentaZ::capacidade_inicial;

public:
    FerramentaZ()=default;

    bool aplicaEfeito(Bloco& b) override;
    char getTipo() const override {return 'z';}
    std::string getDescricao() const override;
};


#endif //TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_FERRAMENTAZ_H