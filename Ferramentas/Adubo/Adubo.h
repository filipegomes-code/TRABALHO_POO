#ifndef TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_ADUBO_H
#define TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_ADUBO_H

#include "Ferramentas/Ferramenta.h"

using std::string;

class Adubo : public Ferramenta {
public:
    Adubo();

    [[nodiscard]] Ferramenta *duplicar() const override;

    bool aplicaEfeito(Bloco &b) override;

    [[nodiscard]] char getTipo() const override { return 'a'; }

    [[nodiscard]] string getDescricao() const override;

private:
    int capacidadeAdubo;
};

#endif //TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_ADUBO_H
