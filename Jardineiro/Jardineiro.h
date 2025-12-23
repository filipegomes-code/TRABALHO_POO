//
// Created by jpmre on 01/11/2025.
//

#ifndef TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_JARDINEIRO_H
#define TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_JARDINEIRO_H

#include <string>
#include <vector>
#include "Settings.h"

class Ferramenta;

class Jardineiro {
public:
    Jardineiro() = default;
    ~Jardineiro();

    Jardineiro(const Jardineiro& outro);
    Jardineiro& operator=(const Jardineiro& outro);

    static char getSimbolo() { return '*'; }
    bool sair();
    bool entrar(int l, int c);
    bool podeMover() const { return movimentosRestantes; }
    bool atualizaPos(int l, int c);

    bool pegarFerramenta(int numSerie);
    bool largarFerramenta();
    bool comprarFerramenta(char tipo);
    void FerrDestruida();
    bool podePlantar() const;
    void registaPlantacao();
    bool podeColher() const;
    void registaColheita();

    // apanha a ferramenta de uma posição e adiciona ao inventário
    void apanharFerramenta(Ferramenta* f);

    // aquando da mudança de instante, reinicia os contadores de ações
    void reiniciaContadores();

    // devolve se o jardineiro está ou não no jardim
    bool getEstaNoJardim() const { return estaNoJardim; }

    int getPosLin() const { return posLin; }
    int getPosCol() const { return posCol; }

    // devolve a ferramenta ativa (na mão) do jardineiro
    Ferramenta* getFerramentaAtiva() const { return ferramentaAtiva; }

    // lista as ferramentas no inventario (vetor) do jardineiro
    std::vector<std::string> listarFerramentas() const;

private:
    int posLin = -1, posCol=-1;
    bool estaNoJardim = false;
    std::vector<Ferramenta*> inventario; // inventario de ferramentas do jardineiro
    Ferramenta* ferramentaAtiva = nullptr; // ferramenta na mão do jardineiro

    // Contadores de ações por instante
    int movimentosRestantes = Settings::Jardineiro::max_movimentos;
    int plantacoesRestantes = Settings::Jardineiro::max_plantacoes;
    int colheitasRestantes = Settings::Jardineiro::max_colheitas;
    int entradasSaidasRestantes = Settings::Jardineiro::max_entradas_saidas;

    void limparInventario();
};


#endif //TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_JARDINEIRO_H