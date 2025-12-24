#ifndef TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_TESOURA_H
#define TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_TESOURA_H

#include "Ferramentas/Ferramenta.h"

using std::string;

class Tesoura : public Ferramenta {
public:
    Tesoura();

    [[nodiscard]] Ferramenta *duplicar() const override;

    bool aplicaEfeito(Bloco &b) override;

    [[nodiscard]] char getTipo() const override { return 't'; }

    [[nodiscard]] string getDescricao() const override;
};

#endif //TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_TESOURA_H
