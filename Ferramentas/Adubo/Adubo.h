#ifndef TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_ADUBO_H
#define TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_ADUBO_H

#include "Ferramentas/Ferramenta.h"

class Adubo : public Ferramenta {
public:
    Adubo();

    Ferramenta* duplicar() const override;

    bool aplicaEfeito(Bloco& b) override;

    char getTipo() const override { return 'a'; }
    std::string getDescricao() const override;
private:
    int capacidadeAdubo;
};


#endif //TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_ADUBO_H