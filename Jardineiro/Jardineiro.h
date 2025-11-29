//
// Created by jpmre on 01/11/2025.
//

#ifndef TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_JARDINEIRO_H
#define TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_JARDINEIRO_H

#include <vector>

class Ferramenta;

class Jardineiro {
private:
    int posLin = -1, posCol=-1;
    bool estaNoJardim = false;
    std::vector<Ferramenta*> inventario; // inventario de ferramentas do jardineiro
    Ferramenta* ferramentaAtiva = nullptr; // ferramenta na mão do jardineiro

    // Contadores de ações por instante
    int movimentosRestantes = 0;
    int plantacoesRestantes = 0;
    int colheitasRestantes = 0;
    int entradasSaidasRestantes = 0;

public:
    Jardineiro();
    ~Jardineiro();

    void limparInventario();

    static char getSimbolo() {return '*';}
    void move(char dir);
    void sair();
    void entrar(int l, int c);

    void pegarFerramenta(int numSerie);
    void largarFerramenta();
    void comprarFerramenta(char tipo);

    // apanha a ferramenta de uma posição e adiciona ao inventário
    void apanharFerramenta(Ferramenta* f);

    // aquando da mudança de instante, reinicia os contadores de ações
    void reiniciaContadores();
    bool podeMover() const;

    // devolve se o jardineiro está ou não no jardim
    bool getEstaNoJardim() const { return estaNoJardim; }
    int getPosLin() const { return posLin; }
    int getPosCol() const { return posCol; }
    // devolve a ferramenta ativa (na mão) do jardineiro
    Ferramenta* getFerramentaAtiva() const { return ferramentaAtiva; }

    // lista as ferramentas no inventario (vetor) do jardineiro
    void listarFerramentas() const;
};


#endif //TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_JARDINEIRO_H