//
// Created by jpmre on 01/11/2025.
//

#ifndef TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_TESOURA_H
#define TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_TESOURA_H
#include "Ferramentas/Ferramenta.h"


class Tesoura : public Ferramenta {
public:
    Tesoura();
    bool aplicaEfeito(Jardim *j, int l, int c) override;
    std::string getTipo() const override;
    std::string getDescricao() const override;
};


#endif //TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_TESOURA_H