#include "ErvaDaninha.h"
#include "../../Settings.h"

ErvaDaninha::ErvaDaninha() : Planta(Settings::ErvaDaninha::inicial_nutrientes, Settings::ErvaDaninha::inicial_agua,
                                    "Feia") {
}

ErvaDaninha::~ErvaDaninha() = default;

Planta *ErvaDaninha::duplicar() const {
    return new ErvaDaninha(*this);
}

void ErvaDaninha::tentaMultiplicar(Jardim &j, int l, int c) {
    if (nutrientes <= Settings::ErvaDaninha::multiplica_nutrientes_maior || instantesDesdeMult <
        Settings::ErvaDaninha::multiplica_instantes)
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

        // erva daninha ocupa MESMO se houver planta
        if (viz.getPlanta() != nullptr) {
            delete viz.getPlanta();
            viz.setPlanta(nullptr);
        }

        // cria erva no vizinho
        auto *novo = new ErvaDaninha();
        novo->agua = Settings::ErvaDaninha::inicial_agua;
        novo->nutrientes = Settings::ErvaDaninha::nova_nutrientes;
        viz.setPlanta(novo);

        instantesDesdeMult = 0; // reset instantes
        return;
    }
}

void ErvaDaninha::Absorve(Bloco &b) {
    // 1 unidade água do solo
    int aguaSolo = b.getAgua();
    if (aguaSolo > 0) {
        int absorveAgua = Settings::ErvaDaninha::absorcao_agua;

        b.setAgua(aguaSolo - absorveAgua);
        agua += absorveAgua;
    }

    // até 5 nutrientes do solo
    int nutrSolo = b.getNutri();
    if (nutrSolo > 0) {
        int absorveNutr = Settings::ErvaDaninha::absorcao_nutrientes;

        b.setNutri(nutrSolo - absorveNutr);
        nutrientes += absorveNutr;
    }

    // atualizar contadores para morte (com base nos instantes) → erva daninha morre de acordo com instantes e não valores do solo
    ++instantesDesdeMult;
    ++instantesTotal;
}

bool ErvaDaninha::CheckMorte() {
    // se em 3 instantes seguidos tiver os valores que a matam, é destruida.
    if (instantesTotal == Settings::ErvaDaninha::morre_instantes)
        return true;
    return false;
}

bool ErvaDaninha::passo(Jardim &j, int l, int c, Bloco &b) {
    // 1) absorve e atualiza contadores
    Absorve(b);

    if (CheckMorte()) {
        // ao morrer, n deixa nada no solo
        b.setNutri(b.getNutri());
        return false; // morreu → Jardim vai fazer delete
    }

    // 3) se está viva, pode tentar multiplicar
    tentaMultiplicar(j, l, c);

    return true;
}
