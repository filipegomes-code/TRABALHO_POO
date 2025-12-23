#ifndef TRABALHO_JARDIM_H
#define TRABALHO_JARDIM_H

#include "Jardineiro/Jardineiro.h"
#include <string>
#include <map>

class Planta;
class Ferramenta;

// cada pos(bloco) do jardim.
class Bloco{
public:
    Bloco();

    Planta* getPlanta() const;
    void setPlanta(Planta* p);

    Ferramenta* getFerramenta() const;
    void setFerramenta(Ferramenta* f);

    int getAgua() const;
    void setAgua(int n);

    int getNutri() const;
    void setNutri(int n);

private:
    Planta* planta;
    Ferramenta* ferr;
    int agua;
    int nutri;
};

// estrutura para o jardim como um todo.
class Jardim {
public:
    Jardim();
    Jardim(int linhas, int colunas);

    Jardim(const Jardim& outro);
    Jardim& operator=(const Jardim& outro);

    ~Jardim();

    static bool salvarJogo(const std::string& nome, const Jardim& atual);
    static bool recuperarJogo(const std::string& nome, Jardim& atual);
    static bool apagarJogo(const std::string& nome);

    bool existe() const;             // há jardim criado? (solo != nullptr)
    void cria(int linhas, int colunas);
    void destroi();

    int getDimLin() const;
    int getDimCol() const;

    Bloco& getBloco(int l, int c);
    const Bloco& getBloco(int l, int c) const;

    // operaçoes de listar informação
    std::string listaAllPlantas()const;
    std::string lista1Planta(int l, int c) const;
    std::string listaArea() const;
    std::string listaAreaIndicada(int l, int c) const;
    std::string listaAreaRaio(int l, int c, int n)const;

    // operaçoes do jardineiro que o jardim controla
    bool JardineiroDentro() const { return jard.getEstaNoJardim(); }
    const Jardineiro& getJardineiro() const { return jard; }

    void listFerrJardineiro() const;
    bool comprarFerrJardineiro(char tipoFerr);
    bool pegarFerrJardineiro(int numSerie);
    bool largarFerrJardineiro();

    bool plantar(int l , int c, char tipo);
    bool colher(int l, int c);

    bool entraJardineiro(int l, int c);
    bool saiJardineiro();
    bool moveJardineiro(std::string dir);   // 'e','d','c','b'

    bool avancar(int n);

    void mostra() const;

private:
    static int instantes;
    int dimLin;
    int dimCol;
    int tamJardim;
    Bloco* solo;
    Jardineiro jard;

    static std::map<std::string, Jardim> salvaguardas;

    int index(int l, int c) const; // converter l c para indice no array
    void inicializa();
    void plantaPosRandom();
    void ferramentaPosRandom();

    void apanhaFerrAutomatico(int l, int c);
    void novaFerramentaPosRandom();
};

#endif //TRABALHO_JARDIM_H
