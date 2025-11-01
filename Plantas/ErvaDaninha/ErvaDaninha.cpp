//
// Created by Filipe Gomes on 29/10/2025.
//
#include "ErvaDaninha.h"
#include "Settings.h"

// ERVA DANINHA
ErvaDaninha::ErvaDaninha() : Planta(Settings::ErvaDaninha::inicial_nutrientes, Settings::ErvaDaninha::inicial_agua, "Feia")
{}

ErvaDaninha::~ErvaDaninha()=default;

void ErvaDaninha::Absorve() {
    // logica para absorver agua e solo da determinada posição
    // 25% unidade agua
    // 5 unidades nutri
}

void ErvaDaninha::CheckMorte(){
    // agua solo > 100 por 3 instantes seguidos
    // qtd nutri == 0 por 3 instantes seguidos
    // etc..
}

char ErvaDaninha::Simbolo() const {
    return 'e';
}

// fazer funcao para retornar char 'e' -> representa ervaDaninha
