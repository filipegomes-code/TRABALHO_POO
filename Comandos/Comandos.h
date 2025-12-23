#ifndef TRABALHO_COMANDOS_H
#define TRABALHO_COMANDOS_H

#include <memory>

#include "Jardim/Jardim.h"

namespace cmd_keys {
    constexpr std::string_view FIM = "fim";
    constexpr std::string_view JARDIM = "jardim";
    constexpr std::string_view EXECUTA = "executa";
    constexpr std::string_view AVANCA = "avanca";

    // Listagens
    constexpr std::string_view LPLANTAS = "lplantas"; // tipo planta, pos , valor propriedades internas, propriedades solo
    constexpr std::string_view LPLANTA = "lplanta"; // propriedas da planta numa certa posicao
    constexpr std::string_view LAREA = "larea"; // ler do enunciado
    constexpr std::string_view LSOLO = "lsolo"; // ler do enunciado
    constexpr std::string_view LFERR = "lferr"; // ferr que jardineiro transporta + a da mão. (detalhes + identificação)

    // Ações
    constexpr std::string_view COLHE = "colhe";
    constexpr std::string_view PLANTA = "planta";
    constexpr std::string_view LARGA = "larga"; // se tiver ferr na mao, larga e junta às outras
    constexpr std::string_view PEGA = "pega"; // coloca na mao uma ferr com o numero de serie n, se existir
    constexpr std::string_view COMPRA = "compra"; // compra ferr de tipo g,a,t,z

    // Movimento do Jardineiro
    constexpr std::string_view ENTRA = "entra"; // se já estiver no jardim, teletransportasse para essa pos
    constexpr std::string_view SAI = "sai"; // sai jardim
    constexpr std::string_view ESQ = "e";
    constexpr std::string_view DIR = "d";
    constexpr std::string_view CIMA = "c";
    constexpr std::string_view BAIXO = "b";

    // Persistência
    constexpr std::string_view GRAVA = "grava";
    constexpr std::string_view RECUPERA = "recupera";
    constexpr std::string_view APAGA = "apaga";
}

// --- Interface Comando ---
class Comando {
public:
    virtual ~Comando() = default;
    virtual bool executar(Jardim& jardim, const std::vector<std::string>& args) = 0; // Retorna false se for para terminar o programa (comando 'fim'), true caso contrário
};

// --- Fábrica de Comandos ---
class ComandoFactory {
public:
    static std::unique_ptr<Comando> criar(const std::string& nome); // Cria o comando apropriado com base na string 'nome'
};

// --- Processamento dos Comandos ---
bool ProcessarComandos(std::istream& in, Jardim& jardim);

#endif //TRABALHO_COMANDOS_H
