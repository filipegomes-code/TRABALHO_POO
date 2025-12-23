//
// Created by jpmre on 01/11/2025.
//

#include "Tesoura.h"
#include "Jardim/Jardim.h"
#include "Plantas/Planta.h"

Tesoura::Tesoura() : Ferramenta() {}

Ferramenta * Tesoura::duplicar() const {
    return new Tesoura(*this);
}

bool Tesoura::aplicaEfeito(Bloco& b) {
    Planta* p = b.getPlanta();
    if (!p)
        return true; // nada acontece

    // só elimina plantas "Feias"
    if (p->getBeleza() == "Feia") {
        delete p;
        b.setPlanta(nullptr);
    }

    return true; // tesoura nunca se gasta
}

std::string Tesoura::getDescricao() const {
    return "Tesoura";
}

