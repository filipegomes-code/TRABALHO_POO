//
// Created by jpmre on 01/11/2025.
//

#include "Adubo.h"
#include "Settings.h"
#include "Jardim/Jardim.h"

Adubo::Adubo()
        : Ferramenta(), capacidadeAdubo(Settings::Adubo::capacidade) {}

Ferramenta * Adubo::duplicar() const {
    return new Adubo(*this);
}

bool Adubo::aplicaEfeito(Bloco& b) {
    if (capacidadeAdubo <= 0)
        return false;

    int dose = Settings::Adubo::dose;
    if (capacidadeAdubo < dose)
        dose = capacidadeAdubo;

    b.setNutri(b.getNutri() + dose);
    capacidadeAdubo -= dose;

    return capacidadeAdubo > 0;
}

std::string Adubo::getDescricao() const {
    return "Adubo (qtd=" + std::to_string(capacidadeAdubo) + ")";
}
