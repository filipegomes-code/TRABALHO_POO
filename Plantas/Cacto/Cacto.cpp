#include "Cacto.h"
#include "../../Settings.h"

Cacto::Cacto() : Planta(0, 0, "neutra") {
}

Cacto::~Cacto() = default;

Planta *Cacto::duplicar() const {
    return new Cacto(*this);
}

// Multiplicação: tenta encontrar vizinho vazio e criar cato metade/metade
void Cacto::tentaMultiplicar(Jardim &j, int l, int c) {
    if (nutrientes <= Settings::Cacto::multiplica_nutrientes_maior || agua <= Settings::Cacto::multiplica_agua_maior)
        return;

    // Vamos considerar vizinhos 8-direções (dl, dc em {-1,0,1} exceto 0,0)
    // Podes adaptar para só 4 se a stor tiver dito isso.
    int linMax = j.getDimLin();
    int colMax = j.getDimCol();

    // vê vizinhos nas diagonais
    for (int dl = -1; dl <= 1; ++dl) {
        for (int dc = -1; dc <= 1; ++dc) {
            if (dl == 0 && dc == 0) continue; // pula 0, porque é a posicao atual a soma das linhas e colunas +0

            int nl = l + dl;
            int nc = c + dc;

            if (nl < 0 || nl >= linMax || nc < 0 || nc >= colMax)
                continue;

            Bloco &viz = j.getBloco(nl, nc);
            if (viz.getPlanta() == nullptr) {
                // faz split de água/nutrientes
                int aguaNovo = agua / 2;
                int nutrNovo = nutrientes / 2;

                agua -= aguaNovo;
                nutrientes -= nutrNovo;

                auto *novo = new Cacto();
                // como estamos dentro de Cato, podemos mexer nos protected do novo
                novo->agua = aguaNovo;
                novo->nutrientes = nutrNovo;

                viz.setPlanta(novo);
                return; // só cria um por instante
            }
        }
    }
}

void Cacto::Absorve(Bloco &b) {
    // 25% da água do solo
    int aguaSolo = b.getAgua();
    int absorveAgua = (Settings::Cacto::absorcao_agua_percentagem * aguaSolo) / 100; // 25%
    if (absorveAgua > 0) {
        b.setAgua(aguaSolo - absorveAgua);
        agua += absorveAgua;
        aguaAbsVida += absorveAgua;
    }

    // até 5 nutrientes do solo
    int nutrSolo = b.getNutri();
    int nutrMaxAbsorve = Settings::Cacto::absorcao_nutrientes;
    int absorveNutr = (nutrMaxAbsorve >= nutrSolo) ? nutrSolo : nutrMaxAbsorve;

    if (absorveNutr > 0) {
        b.setNutri(nutrSolo - absorveNutr);
        nutrientes += absorveNutr;
        nutrAbsVida += absorveNutr;
    }

    // atualizar contadores para morte (com base no SOLO)
    if (b.getAgua() > Settings::Cacto::morre_agua_solo_maior)
        ++contaAguaAlta;
    else
        contaAguaAlta = 0;

    if (b.getNutri() < Settings::Cacto::morre_nutrientes_solo_menor)
        ++contaSemNutrientes;
    else
        contaSemNutrientes = 0;
}

bool Cacto::CheckMorte() {
    // se em 3 instantes seguidos tiver os valores que a matam, é destruida.
    if (contaAguaAlta >= Settings::Cacto::morre_agua_solo_instantes || contaSemNutrientes >
        Settings::Cacto::morre_nutrientes_solo_instantes)
        return true;
    return false;
}

bool Cacto::passo(Jardim &j, int l, int c, Bloco &b) {
    // 1) absorve e atualiza contadores
    Absorve(b);

    if (CheckMorte()) {
        // ao morrer, deixa no solo todos os nutrientes que absorveu durante a vida
        b.setNutri(b.getNutri() + nutrAbsVida);
        return false; // morreu → Jardim vai fazer delete
    }

    // 3) se está viva, pode tentar multiplicar
    tentaMultiplicar(j, l, c);

    return true;
}
