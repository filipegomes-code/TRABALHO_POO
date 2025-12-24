#ifndef TRABALHO_JARDIM_H
#define TRABALHO_JARDIM_H

#include "Jardineiro/Jardineiro.h"
#include <string>
#include <map>

using std::string;
using std::map;

class Planta;
class Ferramenta;

// cada pos(bloco) do jardim.
class Bloco {
public:
    Bloco();

    [[nodiscard]] Planta *getPlanta() const;

    void setPlanta(Planta *p);

    [[nodiscard]] Ferramenta *getFerramenta() const;

    void setFerramenta(Ferramenta *f);

    [[nodiscard]] int getAgua() const;

    void setAgua(int n);

    [[nodiscard]] int getNutri() const;

    void setNutri(int n);

private:
    Planta *planta;
    Ferramenta *ferr;
    int agua;
    int nutri;
};

// estrutura para o jardim como um todo.
class Jardim {
public:
    Jardim();

    Jardim(int linhas, int colunas);

    Jardim(const Jardim &outro);

    Jardim &operator=(const Jardim &outro);

    ~Jardim();

    static bool salvarJogo(const string &nome, const Jardim &atual);

    static bool recuperarJogo(const string &nome, Jardim &atual);

    static bool apagarJogo(const string &nome);

    [[nodiscard]] bool existe() const; // há jardim criado? (solo != nullptr)
    void cria(int linhas, int colunas);

    void destroi();

    [[nodiscard]] int getDimLin() const;

    [[nodiscard]] int getDimCol() const;

    Bloco &getBloco(int l, int c);

    [[nodiscard]] const Bloco &getBloco(int l, int c) const;

    // operaçoes de listar informação
    [[nodiscard]] string listaAllPlantas() const;

    [[nodiscard]] string lista1Planta(int l, int c) const;

    [[nodiscard]] string listaArea() const;

    [[nodiscard]] string listaAreaIndicada(int l, int c) const;

    [[nodiscard]] string listaAreaRaio(int l, int c, int n) const;

    // operaçoes do jardineiro que o jardim controla
    [[nodiscard]] bool JardineiroDentro() const { return jard.getEstaNoJardim(); }
    [[nodiscard]] const Jardineiro &getJardineiro() const { return jard; }

    void listFerrJardineiro() const;

    bool comprarFerrJardineiro(char tipoFerr);

    bool pegarFerrJardineiro(int numSerie);

    bool largarFerrJardineiro();

    bool plantar(int l, int c, char tipo);

    bool colher(int l, int c);

    bool entraJardineiro(int l, int c);

    bool saiJardineiro();

    bool moveJardineiro(const string &dir); // 'e','d','c','b'

    bool avancar(int n);

    void mostra() const;

private:
    static int instantes;
    int dimLin;
    int dimCol;
    int tamJardim;
    Bloco *solo;
    Jardineiro jard;

    static map<string, Jardim> salvaguardas;

    [[nodiscard]] int index(int l, int c) const; // converter l c para indice no array
    void inicializa() const;

    void plantaPosRandom() const;

    void ferramentaPosRandom() const;

    void apanhaFerrAutomatico(int l, int c);

    void novaFerramentaPosRandom() const;
};

#endif //TRABALHO_JARDIM_H
