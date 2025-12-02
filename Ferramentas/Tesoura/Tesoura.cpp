//
// Created by jpmre on 01/11/2025.
//

#include "Tesoura.h"
#include "Jardim/Jardim.h"

Tesoura::Tesoura() : Ferramenta() {}

bool Tesoura::aplicaEfeito(Bloco& b) {
    // por agora: se houver planta, corta-a (depois afinamos para “feia”)
    if (b.getPlanta() != nullptr) {
        delete b.getPlanta();
        b.setPlanta(nullptr);
    }
    return true; // tesoura não se gasta
}

std::string Tesoura::getDescricao() const {
    return "Tesoura";
}

