
#ifndef TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_JARDINEIRO_H
#define TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_JARDINEIRO_H
#include <vector>

#include "Ferramentas/Ferramenta.h"


class Jardineiro {
public:
    Jardineiro();
    ~Jardineiro();

    void limparInventario();

    void move(Jardim* j, char dir);
    void sair();
    void entrar(Jardim* j, int l, int c);

    void colherPlanta(Jardim* j, int l, int c);
    void plantarPlanta(Jardim* j, int l, int c);

    void pegarFerramenta(int numSerie);
    void largarFerramenta();
    void comprarFerramenta(char tipo);

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
    void listarFerramentas() const;
private:
    int posLin, posCol;
    bool estaNoJardim;
    std::vector<Ferramenta*> inventario; // inventario de ferramentas do jardineiro
    Ferramenta* ferramentaAtiva; // ferramenta na mão do jardineiro

    // Contadores de ações por instante
    int movimentosRestantes;
    int plantacoesRestantes;
    int colheitasRestantes;
    int entradasSaidasRestantes;
};


#endif //TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_JARDINEIRO_H