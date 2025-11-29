
#ifndef TRABALHO_JARDIM_H
#define TRABALHO_JARDIM_H

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

    void mostra() const;

};

#endif //TRABALHO_JARDIM_H
