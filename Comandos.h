//
// Created by Filipe Gomes on 20/10/2025.
//
#ifndef TRABALHO_COMANDOS_H
#define TRABALHO_COMANDOS_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <string>
#include "jardim.h"

using namespace std;

namespace cmd{
    constexpr std::string_view FIM = "fim";
    constexpr std::string_view JARDIM = "jardim";
    constexpr std::string_view EXECUTA = "executa";
    constexpr std::string_view VAZIO = "  ";
    constexpr std::string_view PLANTA = "c ";
    constexpr std::string_view AVANCA = "avanca";
}

// PROTOTIPO
bool Executa_Comandos(istream& msg, Retangulo& x);


#endif //TRABALHO_COMANDOS_H
