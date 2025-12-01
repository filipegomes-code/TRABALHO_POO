//
// Created by jpmre on 01/11/2025.
//

#include "Adubo.h"
#include "Jardim/Jardim.h"

Adubo::Adubo()
        : Ferramenta(), capacidadeAdubo(0) {}

bool Adubo::aplicaEfeito(Jardim *j, int l, int c) {
    // lógica real fica para depois
    return false;
}

std::string Adubo::getDescricao() const {
    return "Adubo";
}
