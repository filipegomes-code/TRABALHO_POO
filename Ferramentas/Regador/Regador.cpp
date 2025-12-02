//
// Created by jpmre on 01/11/2025.
//

#include "Regador.h"
#include "Settings.h"
#include "Jardim/Jardim.h"

Regador::Regador()
        : Ferramenta(), capacidadeAgua(Settings::Regador::capacidade) {}

bool Regador::aplicaEfeito(Bloco& b) {
    if (capacidadeAgua <= 0)
        return false;

    int dose = Settings::Regador::dose;
    if (capacidadeAgua < dose)
         dose = capacidadeAgua;

    b.setAgua(b.getAgua() + dose);
    capacidadeAgua -= dose;

    return capacidadeAgua > 0;
}

std::string Regador::getDescricao() const {
    return "Regador (agua=" + std::to_string(capacidadeAgua) + ")";
}


