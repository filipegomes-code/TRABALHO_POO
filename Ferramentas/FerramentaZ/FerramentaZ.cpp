//
// Created by jpmre on 01/11/2025.
//

#include "FerramentaZ.h"
#include "Settings.h"
#include "Jardim/Jardim.h"

Ferramenta * FerramentaZ::duplicar() const {
    return new FerramentaZ(*this);
}

bool FerramentaZ::aplicaEfeito(Bloco& b) {
    // Se já não tiver cargas suficientes para um uso completo, está “morta”
    if (cargasRestantes < Settings::FerramentaZ::custo_por_uso)
        return false;

    int nutrSolo = b.getNutri();
    int nutrNecessarios = Settings::FerramentaZ::nutrientes_para_converter;

    // nutrientes insuficientes → tem de ter pelo menos 15 nutri no solo
    if (nutrSolo < nutrNecessarios) {
        return true; // continua disponível para tentativas futuras
    }

    // 1) consome nutrientes
    b.setNutri(nutrSolo - nutrNecessarios);

    // 2) adiciona água ao solo
    b.setAgua(b.getAgua() + Settings::FerramentaZ::agua_fornecida);

    // 3) gasta 5 cargas
    cargasRestantes -= Settings::FerramentaZ::custo_por_uso;

    // 4) se as cargas chegarem a 0, a ferramenta fica inutilizável
    return cargasRestantes;
}

std::string FerramentaZ::getDescricao() const {
    return "Conversor Hidrico (cargas=" + std::to_string(cargasRestantes) + ")";
}
