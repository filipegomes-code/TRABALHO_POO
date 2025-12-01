//
// Created by jpmre on 01/11/2025.
//

#include "Regador.h"
#include "Settings.h"

Regador::Regador()
        : Ferramenta(), capacidadeAgua(Settings::Regador::capacidade) {}

bool Regador::aplicaEfeito(Jardim *j, int l, int c) {
    // lógica real fica para depois
    return false;
}

std::string Regador::getDescricao() const {
    return "Regador";
}


