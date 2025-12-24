#ifndef TRABALHO_COMANDOS_H
#define TRABALHO_COMANDOS_H

#include <memory>

#include "Jardim/Jardim.h"

using std::string_view;
using std::vector;
using std::string;
using std::unique_ptr;
using std::istream;

namespace cmd_keys {
    constexpr string_view FIM = "fim";
    constexpr string_view JARDIM = "jardim";
    constexpr string_view EXECUTA = "executa";
    constexpr string_view AVANCA = "avanca";

    // Listagens
    constexpr string_view LPLANTAS = "lplantas";
    constexpr string_view LPLANTA = "lplanta";
    constexpr string_view LAREA = "larea";
    constexpr string_view LSOLO = "lsolo";
    constexpr string_view LFERR = "lferr";

    // Ações
    constexpr string_view COLHE = "colhe";
    constexpr string_view PLANTA = "planta";
    constexpr string_view LARGA = "larga";
    constexpr string_view PEGA = "pega";
    constexpr string_view COMPRA = "compra";

    // Movimento do Jardineiro
    constexpr string_view ENTRA = "entra";
    constexpr string_view SAI = "sai";
    constexpr string_view ESQ = "e";
    constexpr string_view DIR = "d";
    constexpr string_view CIMA = "c";
    constexpr string_view BAIXO = "b";

    // Persistência
    constexpr string_view GRAVA = "grava";
    constexpr string_view RECUPERA = "recupera";
    constexpr string_view APAGA = "apaga";
}

// --- Interface Comando ---
class Comando {
public:
    virtual ~Comando() = default;

    virtual bool executar(Jardim &jardim, const vector<string> &args) = 0;
};

// --- Fábrica de Comandos ---
class ComandoFactory {
public:
    static unique_ptr<Comando> criar(const string &nome);
};

// --- Processamento dos Comandos ---
bool ProcessarComandos(istream &in, Jardim &jardim);

#endif //TRABALHO_COMANDOS_H
