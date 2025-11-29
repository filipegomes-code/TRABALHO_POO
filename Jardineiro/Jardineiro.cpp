//
// Created by jpmre on 01/11/2025.
//

#include "Jardineiro.h"

Jardineiro::Jardineiro() {
}

Jardineiro::~Jardineiro() {
}

void Jardineiro::limparInventario() {
}

void Jardineiro::sair() {
    posLin = -1;
    posCol = -1;
    estaNoJardim = false;
}

void Jardineiro::entrar(int l, int c) {
    posLin = l;
    posCol = c;
    estaNoJardim = true;
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
}

void Jardineiro::listarFerramentas() const {
}
