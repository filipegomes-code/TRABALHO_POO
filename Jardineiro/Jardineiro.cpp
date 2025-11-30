//
// Created by jpmre on 01/11/2025.
//

#include "Jardineiro.h"

int Jardineiro::compararInstante = 0;

Jardineiro::Jardineiro() {
}

Jardineiro::~Jardineiro() {
}

void Jardineiro::limparInventario() {
}

bool Jardineiro::sair() {
    if(entradasSaidasRestantes > 0) {
        posLin = -1;
        posCol = -1;
        estaNoJardim = false;
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

void Jardineiro::pegarFerramenta(int numSerie) {
}

void Jardineiro::largarFerramenta() {
}

void Jardineiro::comprarFerramenta(char tipo) {
}

void Jardineiro::apanharFerramenta(Ferramenta *f) {
}

void Jardineiro::reiniciaContadores() {
    movimentosRestantes = Settings::Jardineiro::max_movimentos;
    plantacoesRestantes = Settings::Jardineiro::max_plantacoes;
    colheitasRestantes = Settings::Jardineiro::max_colheitas;
    entradasSaidasRestantes = Settings::Jardineiro::max_entradas_saidas;
}

void Jardineiro::listarFerramentas() const {
}
