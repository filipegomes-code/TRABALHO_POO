//
// Created by Filipe Gomes on 29/10/2025.
//

#include "Roseira.h"
#include "../../Settings.h"

// ROSEIRA
Roseira::Roseira() : Planta(Settings::Roseira::inicial_agua, Settings::Roseira::inicial_nutrientes, "Bonita") {}

Planta * Roseira::duplicar() const {
    return new Roseira(*this);
}

// 3) Multiplicação: tenta encontrar vizinho vazio e criar novo cacto metade/metade
void Roseira::tentaMultiplicar(Jardim& j, int l, int c) {
    if (nutrAbsVida <= Settings::Roseira::multiplica_nutrientes_maior)
        return;

    // 8 posicoes possiveis
    int dl[8] = {-1,-1,-1,0,0,1,1,1};
    int dc[8] = {-1,0,1,-1,1,-1,0,1};

    // cria aleatoriedade na escolha do vizinho, o cacto n tem isso.
    int start = rand() % 8;

    // vê vizinhos nas diagonais
    for (int k = 0; k < 8; ++k) {
        int idx = (start + k) % 8; // faz wrap

        int nl = l + dl[idx];
        int nc = c + dc[idx];

        if (nl < 0 || nl >= j.getDimLin() || nc < 0 || nc >= j.getDimCol())
            continue;

        Bloco& viz = j.getBloco(nl, nc);

        if (viz.getPlanta() == nullptr) {
            auto* nova = new Roseira();
            nova->nutrientes = Settings::Roseira::nova_nutrientes;
            nova->agua = (Settings::Roseira::nova_agua_percentagem * agua) / 100;

            nutrientes = Settings::Roseira::original_nutrientes;
            agua = (Settings::Roseira::original_agua_percentagem * agua) / 100;

            return;
        }
    }
}

// verifica se TODAS as posições vizinhas imediatas têm planta
bool Roseira::vizinhosTodosComPlanta(const Jardim& j, int l, int c) const {
    int dl[8] = {-1,-1,-1,0,0,1,1,1};
    int dc[8] = {-1,0,1,-1,1,-1,0,1};

    bool encontrouAlgumaPosValida = false;
    bool todasOcupadas = true;

    for (int k = 0; k < 8; ++k) {
        int nl = l + dl[k];
        int nc = c + dc[k];

        if (nl < 0 || nl >= j.getDimLin() || nc < 0 || nc >= j.getDimCol())
            continue; // fora do jardim

        encontrouAlgumaPosValida = true;

        const Bloco& viz = j.getBloco(nl, nc);
        if (viz.getPlanta() == nullptr) {
            todasOcupadas = false;
            break;
        }
    }

    if (!encontrouAlgumaPosValida)
        return false;

    return todasOcupadas;
}

void Roseira::Absorve(Bloco& b) {
    //  + 5 água do solo (SE EXISTIR) e -4 de agua dela propria
    int aguaSolo = b.getAgua();
    agua -= Settings::Roseira::perda_agua;

    if(agua < 0) agua = 0;

    if(aguaSolo >= Settings::Roseira::absorcao_agua) {
        int absorveAgua = Settings::Roseira::absorcao_agua;

        aguaAbsVida += absorveAgua; // agua absorvida acumulada

        b.setAgua(aguaSolo - absorveAgua);
        agua += absorveAgua;
    }

    // + 8 nutri do solo (SE EXISTIR) e - 4 nutri dela propria
    int nutrSolo = b.getNutri();
    nutrientes -= Settings::Roseira::perda_nutrientes;

    if(nutrientes < 0) nutrientes = 0;

    if(nutrSolo >= Settings::Roseira::absorcao_nutrientes) {
        int absorveNutr = Settings::Roseira::absorcao_nutrientes;

        nutrAbsVida += absorveNutr;

        b.setNutri(nutrSolo - absorveNutr);
        nutrientes += absorveNutr;
    }
}

bool Roseira::CheckMorte(){
    if (agua < Settings::Roseira::morre_agua_menor)  // morre_agua_menor = 1 → água < 1 → água == 0
        return true;

    // 2) nutrientes acumulados chegam a 0
    if (nutrientes < Settings::Roseira::morre_nutrientes_menor) // idem
        return true;

    // 3) nutrientes acumulados atingem 200
    if (nutrientes >= Settings::Roseira::morre_nutrientes_maior)
        return true;

    return false;
}

bool Roseira::passo(Jardim& j, int l, int c, Bloco& b) {
    // 1) absorve e atualiza contadores
    Absorve(b);

    // 2) morte pela condição "todas as vizinhas com planta"
    if (vizinhosTodosComPlanta(j, l, c)) {
        b.setAgua( b.getAgua() + aguaAbsVida / 2 );
        b.setNutri( b.getNutri() + nutrAbsVida / 2 );
        return false;
    }

    if (CheckMorte()) {
        // ao morrer deixa metade da agua e nutri , absorvido na sua vida
        b.setAgua( aguaAbsVida / 2);
        b.setNutri( nutrAbsVida / 2);
        return false; // morreu → Jardim vai fazer delete
    }

    // 3) se ainda está viva, pode tentar multiplicar
    tentaMultiplicar(j, l, c);

    return true;
}



