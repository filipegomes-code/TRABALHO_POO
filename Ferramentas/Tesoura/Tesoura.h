#ifndef TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_TESOURA_H
#define TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_TESOURA_H

#include "Ferramentas/Ferramenta.h"

class Tesoura : public Ferramenta {
public:
    Tesoura();

    Ferramenta* duplicar() const override;

    bool aplicaEfeito(Bloco& b) override;

    char getTipo() const override { return 't'; }
    std::string getDescricao() const override;
};

#endif //TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_TESOURA_H