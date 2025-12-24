#include "Jardineiro.h"

#include <algorithm>

#include "Ferramentas/Ferramenta.h"
#include "Ferramentas/Adubo/Adubo.h"
#include "Ferramentas/Regador/Regador.h"
#include "Ferramentas/Tesoura/Tesoura.h"
#include "Ferramentas/FerramentaZ/FerramentaZ.h"

using namespace std;

Jardineiro::~Jardineiro() {
    limparInventario();
}

Jardineiro::Jardineiro(const Jardineiro &outro) {
    *this = outro;
}

Jardineiro &Jardineiro::operator=(const Jardineiro &outro) {
    if (this == &outro) return *this;

    limparInventario();

    posLin = outro.posLin;
    posCol = outro.posCol;
    estaNoJardim = outro.estaNoJardim;
    movimentosRestantes = outro.movimentosRestantes;
    plantacoesRestantes = outro.plantacoesRestantes;
    colheitasRestantes = outro.colheitasRestantes;
    entradasSaidasRestantes = outro.entradasSaidasRestantes;

    int indiceAtiva = -1;

    for (int i = 0; i < outro.inventario.size(); ++i) {
        if (outro.inventario[i] == outro.ferramentaAtiva) {
            indiceAtiva = i;
        }

        if (outro.inventario[i] != nullptr) {
            inventario.push_back(outro.inventario[i]->duplicar());
        }
    }

    if (indiceAtiva != -1 && indiceAtiva < inventario.size()) {
        ferramentaAtiva = inventario[indiceAtiva];
    } else {
        ferramentaAtiva = nullptr;
    }

    return *this;
}

void Jardineiro::limparInventario() {
    for (Ferramenta *f: inventario)
        delete f;
    inventario.clear();
    ferramentaAtiva = nullptr;
}

bool Jardineiro::sair() {
    if (entradasSaidasRestantes > 0) {
        posLin = -1;
        posCol = -1;
        estaNoJardim = false;
        entradasSaidasRestantes--;
        return true;
    }
    return false;
}

bool Jardineiro::entrar(int l, int c) {
    if (entradasSaidasRestantes > 0) {
        posLin = l;
        posCol = c;
        estaNoJardim = true;
        entradasSaidasRestantes--;
        return true;
    }
    return false;
}

// se esgotar o número de movimentos possiveis retorna false, senao true
bool Jardineiro::atualizaPos(int l, int c) {
    if (podeMover()) {
        posLin = l;
        posCol = c;
        movimentosRestantes--;
        return true;
    }
    return false;
}

bool Jardineiro::pegarFerramenta(int numSerie) {
    for (Ferramenta *f: inventario) { // NOLINT(*-use-anyofallof)
        if (f->getNumSerie() == numSerie) {
            ferramentaAtiva = f;
            return true;
        }
    }
    return false;
}

bool Jardineiro::largarFerramenta() {
    if (!ferramentaAtiva)
        return false;

    ferramentaAtiva = nullptr;
    return true;
}

bool Jardineiro::comprarFerramenta(char tipo) {
    Ferramenta *nova = nullptr;

    switch (tipo) {
        case 'g': // regador
            nova = new Regador();
            break;
        case 'a': // adubo
            nova = new Adubo();
            break;
        case 't': // tesoura
            nova = new Tesoura();
            break;
        case 'z':
            nova = new FerramentaZ();
            break;
        default:
            return false;
    }

    inventario.push_back(nova);

    if (!ferramentaAtiva)
        ferramentaAtiva = nova;

    return true;
}

void Jardineiro::apanharFerramenta(Ferramenta *f) {
    if (!f)
        return;

    inventario.push_back(f);

    if (!ferramentaAtiva) {
        ferramentaAtiva = f;
    }
}

void Jardineiro::FerrDestruida() {
    if (ferramentaAtiva == nullptr)
        return;

    auto it = find(inventario.begin(), inventario.end(), ferramentaAtiva);

    if (it != inventario.end()) {
        delete ferramentaAtiva;
        inventario.erase(it);
    }
    ferramentaAtiva = nullptr;
}

void Jardineiro::reiniciaContadores() {
    movimentosRestantes = Settings::Jardineiro::max_movimentos;
    plantacoesRestantes = Settings::Jardineiro::max_plantacoes;
    colheitasRestantes = Settings::Jardineiro::max_colheitas;
    entradasSaidasRestantes = Settings::Jardineiro::max_entradas_saidas;
}

vector<string> Jardineiro::listarFerramentas() const {
    vector<string> out;
    for (auto *f: inventario) {
        string linha =
                "[" + to_string(f->getNumSerie()) + "] " +
                f->getTipo() + string(" - ") +
                f->getDescricao();
        if (f == ferramentaAtiva)
            linha += " (na mão)";

        out.push_back(linha);
    }
    return out;
}

bool Jardineiro::podePlantar() const {
    return plantacoesRestantes;
}

void Jardineiro::registaPlantacao() {
    --plantacoesRestantes;
}

bool Jardineiro::podeColher() const {
    return colheitasRestantes;
}

void Jardineiro::registaColheita() {
    --colheitasRestantes;
}
