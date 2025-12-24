#include "Settings.h"
#include "Exotica.h"

using namespace std;

Exotica::Exotica() : Planta(Settings::Exotica::inicial_agua, Settings::Exotica::inicial_nutrientes, "Bonita") {
}

Planta *Exotica::duplicar() const {
    return new Exotica(*this);
}

void Exotica::tentaMultiplicar(Jardim &j, int l, int c) {
    // Condição interna: água > 40 e nutrientes > 30
    if (agua <= Settings::Exotica::multiplica_agua_maior ||
        nutrientes <= Settings::Exotica::multiplica_nutrientes_maior)
        return;

    // cria aleatoriedade na escolha do vizinho, o cato não tem isso.
    int start = rand() % 8; // NOLINT(cert-msc50-cpp)

    // vê vizinhos nas diagonais
    for (int k = 0; k < 8; ++k) {
        int dc[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
        int dl[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
        int idx = (start + k) % 8; // faz wrap

        int nl = l + dl[idx];
        int nc = c + dc[idx];

        if (nl < 0 || nl >= j.getDimLin() || nc < 0 || nc >= j.getDimCol())
            continue;

        Bloco &viz = j.getBloco(nl, nc);

        if (viz.getPlanta() == nullptr) {
            auto *clone = new Exotica();
            clone->nutrientes = Settings::Exotica::nova_nutrientes;
            clone->agua = Settings::Exotica::nova_agua;

            viz.setPlanta(clone);

            nutrientes -= Settings::Exotica::original_perde_nutrientes;
            agua -= Settings::Exotica::original_perde_agua;

            return;
        }
    }
}

void Exotica::Absorve(Bloco &b) {
    int aguaSolo = b.getAgua();
    int nutrSolo = b.getNutri();

    // absorve até 8 unidades de água do solo
    int absorveAgua = Settings::Exotica::absorcao_agua;
    // se não tiver mais que o que absorve, fica a 0
    if (aguaSolo < absorveAgua) {
        absorveAgua = aguaSolo;
        b.setAgua(aguaSolo - absorveAgua);
        agua += absorveAgua;
    } else {
        b.setAgua(aguaSolo - absorveAgua);
        agua += absorveAgua;
    }

    // absorve até 2 nutrientes do solo
    int maxNutr = Settings::Exotica::absorcao_nutrientes;
    int absorveNutr = min(maxNutr, nutrSolo);
    if (absorveNutr > 0) {
        b.setNutri(nutrSolo - absorveNutr);
        nutrientes += absorveNutr;
    }

    // liberta 3 nutrientes no solo (pólen fértil)
    b.setNutri(b.getNutri() + Settings::Exotica::enriquece_solo_nutri);

    // solo seco
    if (b.getAgua() < Settings::Exotica::morre_agua_solo_menor)
        ++instantesSoloSeco;
    else
        instantesSoloSeco = 0;
}

bool Exotica::CheckMorte() {
    if (agua < Settings::Exotica::morre_agua_menor)
        return true;

    // 2) solo sem água durante 3 instantes consecutivos
    if (instantesSoloSeco >= Settings::Exotica::morre_agua_solo_instantes)
        return true;

    return false;
}

bool Exotica::passo(Jardim &j, int l, int c, Bloco &b) {
    // 1) absorve e atualiza contadores
    Absorve(b);

    if (CheckMorte()) {
        int nutrDeposita = min(Settings::Exotica::morre_nutri_solo, nutrientes);
        b.setNutri(b.getNutri() + nutrDeposita);
        agua = 0;
        return false; // morreu → Jardim vai fazer delete
    }

    // 3) se está viva, pode tentar multiplicar
    tentaMultiplicar(j, l, c);

    return true;
}
