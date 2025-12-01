//
// Created by jpmre on 01/11/2025.
//

#include "Tesoura.h"
#include "Jardim/Jardim.h"

Tesoura::Tesoura() : Ferramenta() {}

bool Tesoura::aplicaEfeito(Jardim *j, int l, int c) {
    // Ainda não implementamos lógica real
    return false;
}

std::string Tesoura::getDescricao() const {
    return "Tesoura";
}

