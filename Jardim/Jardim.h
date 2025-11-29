
#ifndef TRABALHO_JARDIM_H
#define TRABALHO_JARDIM_H

#include "Jardineiro/Jardineiro.h"
#include <string>

class Planta;
class Ferramenta;

// cada pos(bloco) do jardim.
class Bloco{
private:
    Planta* planta;
    Ferramenta* ferr;
    int agua;
    int nutri;
    // bool temJard;

public:
    Bloco();

    Planta* getPlanta() const;
    void setPlanta(Planta* p);
    Ferramenta* getFerramenta() const;
    void setFerramenta(Ferramenta* f);
    int getAgua()const;
    void setAgua(int n);
    int getNutri()const;
    void setNutri(int n);

};

// estrutura para o jardim como um todo.
class Jardim {
private:
    int dimLin;
    int dimCol;
    int tamJardim;
    Bloco* solo;
    Jardineiro jard;

    int index(int l, int c)const; // converter l c para indice no array
    void inicializa();
    void plantaPosRandom();
public:
    Jardim();
    Jardim(int linhas, int colunas);
    Jardim(const Jardim&) = delete;
    Jardim& operator=(const Jardim&) = delete;
    ~Jardim();

    bool existe() const;             // há jardim criado? (solo != nullptr)
    void cria(int linhas, int colunas);
    void destroi();

    int getDimLin() const;
    int getDimCol() const;

    Bloco& getBloco(int l, int c);
    const Bloco& getBloco(int l, int c) const;

    // operaçoes do jardineiro que o jardim controla
    bool JardineiroDentro() const { return jard.getEstaNoJardim(); }
    const Jardineiro& getJardineiro() const { return jard; }

    bool entraJardineiro(int l, int c);
    bool saiJardineiro();
    bool moveJardineiro(char dir);   // 'e','d','c','b'

    //  Operações futuras sobre plantas
    bool plantar(int l, int c, char tipo); // ainda por implementar
    bool colher(int l, int c);             // ainda por implementar

    void mostra() const;

};

#endif //TRABALHO_JARDIM_H
