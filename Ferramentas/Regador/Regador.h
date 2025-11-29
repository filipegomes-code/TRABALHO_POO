//
// Created by jpmre on 01/11/2025.
//

#ifndef TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_REGADOR_H
#define TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_REGADOR_H
#include "Ferramentas/Ferramenta.h"


class Regador : public Ferramenta {
public:
    Regador();
    bool aplicaEfeito(Jardim *j, int l, int c) override;
    char getTipo() const override {return 'g';}
    std::string getDescricao() const override;
private:
    int capacidadeAgua;
};


#endif //TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_REGADOR_H