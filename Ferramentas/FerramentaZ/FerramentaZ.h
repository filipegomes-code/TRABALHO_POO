//
// Created by jpmre on 01/11/2025.
//

#ifndef TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_FERRAMENTAZ_H
#define TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_FERRAMENTAZ_H
#include "Ferramentas/Ferramenta.h"


class FerramentaZ : public Ferramenta {
public:
    FerramentaZ();

    bool aplicaEfeito(Jardim *j, int l, int c) override;
    char getTipo() const override {return 'z';}
    std::string getDescricao() const override;
private:
    int cargasRestantes;
};


#endif //TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_FERRAMENTAZ_H