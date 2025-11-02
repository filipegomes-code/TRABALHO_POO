
#ifndef TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_ADUBO_H
#define TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_ADUBO_H
#include "Ferramentas/Ferramenta.h"


class Adubo : public Ferramenta {
public:
    Adubo();
    bool aplicaEfeito(Jardim* j, int l, int c) override;
    std::string getTipo() const override;
    std::string getDescricao() const override;
private:
    int capacidadeAdubo;
};


#endif //TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_ADUBO_H