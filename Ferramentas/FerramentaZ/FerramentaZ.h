#ifndef TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_FERRAMENTAZ_H
#define TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_FERRAMENTAZ_H

#include "Settings.h"
#include "Ferramentas/Ferramenta.h"

using std::string;

class FerramentaZ : public Ferramenta {
public:
    FerramentaZ() = default;

    [[nodiscard]] Ferramenta *duplicar() const override;

    bool aplicaEfeito(Bloco &b) override;

    [[nodiscard]] char getTipo() const override { return 'z'; }

    [[nodiscard]] string getDescricao() const override;

private:
    int cargasRestantes = Settings::FerramentaZ::capacidade_inicial;
};

#endif //TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_FERRAMENTAZ_H
