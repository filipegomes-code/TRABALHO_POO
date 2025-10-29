//
// Created by Filipe Gomes on 29/10/2025.
//

#include "Roseira.h"
#include "Settings.h"

// ROSEIRA
Roseira::Roseira() : Planta(Settings::Roseira::inicial_agua, Settings::Roseira::inicial_nutrientes, "Bonita")
{}

Roseira::~Roseira()=default;

void Roseira::Absorve() {
    // 25 nutri acumulados e 25 agua
    // cada instante perde 4 agua, 4 nutri.
    // absorve 5 agua e 8 nutri do solo se existir
}

void Roseira::Morre(){
    // agua == 0 || nutri == 0 || nutri == 200 || todas pos vizinhas tiver planta
    // etc..
}

// fazer funcao para retornar char 'r' -> representa Roseira



