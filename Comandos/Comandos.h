//
// Created by Filipe Gomes on 20/10/2025.
//
#ifndef TRABALHO_COMANDOS_H
#define TRABALHO_COMANDOS_H

#include "Jardim/jardim.h"

using namespace std;

namespace cmd{
    constexpr std::string_view FIM = "fim";
    constexpr std::string_view JARDIM = "jardim";
    constexpr std::string_view EXECUTA = "executa";
    constexpr std::string_view VAZIO = "  ";
    constexpr std::string_view PLANTA_TESTE = "c ";
    constexpr std::string_view AVANCA = "avanca";
    constexpr std::string_view LPLANTAS = "lplantas"; // tipo planta, pos , valor propriedades internas, propriedades solo
    constexpr std::string_view LPLANTA = "lplanta"; // propriedas da planta numa certa posicao
    constexpr std::string_view LAREA = "larea"; // ler do enunciado
    constexpr std::string_view LSOLO = "lsolo"; // ler do enunciado
    constexpr std::string_view LFERR = "lferr"; // ferr que jardineiro transporta + a da mão. (detalhes + identificação)

    // COMANDOS QUE ALTERAM O JARDIM -> fazendo com que seja preciso a impressao dele again.
    constexpr std::string_view COLHE = "colhe <l><c>";
    constexpr std::string_view PLANTA = "planta <l><c><tipo>";
    constexpr std::string_view LARGA = "larga"; // se tiver ferr na mao, larga e junta às outras
    constexpr std::string_view PEGA = "pega <n>"; // coloca na mao uma ferr com o numero de serie n, se existir
    constexpr std::string_view COMPRA = "compra <c>"; // compra ferr de tipo g,a,t,z

    // MOVIMENTO JARDINEIRO
    constexpr std::string_view ESQ = "e";
    constexpr std::string_view DIR = "d";
    constexpr std::string_view CIMA = "c";
    constexpr std::string_view BAIXO = "b";

    constexpr std::string_view ENTRA = "entra <l><c>"; // se já estiver no jardim, teletransportasse para essa pos
    constexpr std::string_view SAI = "sai"; // sai jardim
}

// PROTOTIPO
bool Executa_Comandos(istream& msg, Retangulo& x);


#endif //TRABALHO_COMANDOS_H
