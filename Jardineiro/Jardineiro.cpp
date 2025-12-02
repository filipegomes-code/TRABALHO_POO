//
// Created by jpmre on 01/11/2025.
//

#include "Jardineiro.h"

#include "Ferramentas/Ferramenta.h"
#include "Ferramentas/Adubo/Adubo.h"
#include "Ferramentas/Regador/Regador.h"
#include "Ferramentas/Tesoura/Tesoura.h"

#include <iostream>

int Jardineiro::compararInstante = 0;

Jardineiro::Jardineiro() {
}

Jardineiro::~Jardineiro() {
}

void Jardineiro::limparInventario() {
    for(Ferramenta* f : inventario)
        delete f;
    inventario.clear();
    ferramentaAtiva = nullptr;
}

bool Jardineiro::sair() {
    if(entradasSaidasRestantes > 0) {
        posLin = -1;
        posCol = -1;
        estaNoJardim = false;
        entradasSaidasRestantes--;
        return true;
    }
    return false;
}

bool Jardineiro::entrar(int l, int c) {
    if(entradasSaidasRestantes > 0) {
        posLin = l;
        posCol = c;
        estaNoJardim = true;
        entradasSaidasRestantes--;
        return true;
    }
    return false;
}

// se esgotar o numero de movimentos possiveis retorna false, senao true
bool Jardineiro::atualizaPos(int l, int c) {
    if(movimentosRestantes > 0) {
        posLin = l;
        posCol = c;
        movimentosRestantes--;
        return true;
    }
    return false;
}

bool Jardineiro::pegarFerramenta(int numSerie) {
    for (Ferramenta* f : inventario) {
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
    Ferramenta* nova = nullptr;

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
            // nova = new FerramentaZ();
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
    if(!f)
        return;

    inventario.push_back(f);

    if(!ferramentaAtiva){
        ferramentaAtiva = f;
    }
}

void Jardineiro::FerrDestruida() {
    if(ferramentaAtiva == nullptr)
        return;

    auto it = std::find(inventario.begin(), inventario.end(), ferramentaAtiva);

    if(it != inventario.end()){
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

std::vector<std::string> Jardineiro::listarFerramentas() const {
    std::vector<std::string> out;

    for (auto* f : inventario) {
        std::string linha =
                "[" + std::to_string(f->getNumSerie()) + "] " +
                f->getTipo() + std::string(" - ") +
                f->getDescricao();

        if (f == ferramentaAtiva)
            linha += " (ativa)";

        out.push_back(linha);
    }

    return out;
}
