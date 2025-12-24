#ifndef TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_REGADOR_H
#define TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_REGADOR_H

#include "Ferramentas/Ferramenta.h"

using std::string;

class Regador : public Ferramenta {
public:
    Regador();

    [[nodiscard]] Ferramenta *duplicar() const override;

    bool aplicaEfeito(Bloco &b) override;

    [[nodiscard]] char getTipo() const override { return 'g'; }

    [[nodiscard]] string getDescricao() const override;

private:
    int capacidadeAgua;
};

#endif //TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_REGADOR_H
