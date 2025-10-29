//
// Created by Filipe Gomes on 29/10/2025.
//
#include "Cacto.h"
#include "iostream"

// CACTO
Cacto::Cacto() : Planta(0,0, "neutra"){}

Cacto::~Cacto(){}

void Cacto::Absorve() {
    // logica para absorver agua e solo da determinada posição
    // 25% unidade agua
    // 5 unidades nutri
}

void Cacto::Morre(){
    // agua solo > 100 por 3 instantes seguidos
    // qtd nutri == 0 por 3 instantes seguidos
    // etc..
}

// fazer funcao para retornar char 'c' -> representa cacto
