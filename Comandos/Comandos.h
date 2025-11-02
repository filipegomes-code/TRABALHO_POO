
#ifndef TRABALHO_COMANDOS_H
#define TRABALHO_COMANDOS_H

#include "Jardim/Jardim.h"

namespace cmd{
    constexpr std::string_view FIM = "fim";
    constexpr std::string_view JARDIM = "jardim";
    constexpr std::string_view EXECUTA = "executa";
    constexpr std::string_view AVANCA = "avanca";
    constexpr std::string_view LPLANTAS = "lplantas"; // tipo planta, pos , valor propriedades internas, propriedades solo
    constexpr std::string_view LPLANTA = "lplanta"; // propriedas da planta numa certa posicao
    constexpr std::string_view LAREA = "larea"; // ler do enunciado
    constexpr std::string_view LSOLO = "lsolo"; // ler do enunciado
    constexpr std::string_view LFERR = "lferr"; // ferr que jardineiro transporta + a da mão. (detalhes + identificação)

    // COMANDOS QUE ALTERAM O JARDIM -> fazendo com que seja preciso a impressao dele again.
    constexpr std::string_view COLHE = "colhe";
    constexpr std::string_view PLANTA = "planta";
    constexpr std::string_view LARGA = "larga"; // se tiver ferr na mao, larga e junta às outras
    constexpr std::string_view PEGA = "pega"; // coloca na mao uma ferr com o numero de serie n, se existir
    constexpr std::string_view COMPRA = "compra"; // compra ferr de tipo g,a,t,z

    // MOVIMENTO JARDINEIRO
    namespace mov {
        constexpr std::string_view ESQ = "e";
        constexpr std::string_view DIR = "d";
        constexpr std::string_view CIMA = "c";
        constexpr std::string_view BAIXO = "b";
    }

    constexpr std::string_view ENTRA = "entra"; // se já estiver no jardim, teletransportasse para essa pos
    constexpr std::string_view SAI = "sai"; // sai jardim
}

// PROTOTIPO
bool Executa_Comandos(std::istream& msg, Retangulo& x);


#endif //TRABALHO_COMANDOS_H
