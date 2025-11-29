#include "Jardim.h"
#include "../Settings.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Ferramentas/Adubo/Adubo.h"
#include "Ferramentas/Regador/Regador.h"
#include "Ferramentas/Tesoura/Tesoura.h"
#include "Plantas/Roseira/Roseira.h"
#include "Plantas/Cacto/Cacto.h"
#include "Plantas/ErvaDaninha/ErvaDaninha.h"

using namespace std;

Bloco::Bloco()
        : planta(nullptr), ferr(nullptr), agua(0), nutri(0) {}

Planta* Bloco::getPlanta() const {
    return planta;
}

void Bloco::setPlanta(Planta* p) {
    planta = p;
}

Ferramenta* Bloco::getFerramenta() const {
    return ferr;
}

void Bloco::setFerramenta(Ferramenta* f) {
    ferr = f;
}

int Bloco::getAgua() const {
    return agua;
}

void Bloco::setAgua(int a) {
    agua = a;
}

int Bloco::getNutri() const {
    return nutri;
}

void Bloco::setNutri(int n) {
    nutri = n;
}


///////////////            ///////////////
                //JARDIM//
///////////////            ///////////////

Jardim::Jardim()
        : dimLin(0), dimCol(0), tamJardim(0), solo(nullptr) {}

Jardim::Jardim(int linhas, int colunas)
        : dimLin(0), dimCol(0), tamJardim(0), solo(nullptr) {
    cria(linhas, colunas);
}

Jardim::~Jardim() {
    destroi();
}

bool Jardim::existe() const {
    return solo;
}

void Jardim::cria(int linhas, int colunas) {
    // se já existir, limpar primeiro
    destroi();

    if (linhas < 1 || linhas > 26 || colunas < 1 || colunas > 26) {
        // dimensões inválidas, não cria nada
        return;
    }

    dimLin = linhas;
    dimCol = colunas;
    tamJardim = linhas * colunas;

    solo = new Bloco[tamJardim];

    inicializa();
    mostra();
}

void Jardim::destroi() {
    if (!solo) {
        dimLin = dimCol = tamJardim = 0;
        return;
    }

    // libertar plantas e ferramentas
    for (int i = 0; i < tamJardim; ++i) {
        if (solo[i].getPlanta() != nullptr) {
            delete solo[i].getPlanta();
            solo[i].setPlanta(nullptr);
        }
        if (solo[i].getFerramenta() != nullptr) {
            delete solo[i].getFerramenta();
            solo[i].setFerramenta(nullptr);
        }
    }

    delete[] solo;
    solo = nullptr;
    dimLin = dimCol = tamJardim = 0;
}

int Jardim::getDimLin() const {
    return dimLin;
}

int Jardim::getDimCol() const {
    return dimCol;
}

// encontra a posicao no array 1D
int Jardim::index(int l, int c) const {
    return l * dimCol + c;
}

// extrai o bloco dessa posicao
Bloco& Jardim::getBloco(int l, int c) {
    return solo[index(l, c)];
}

const Bloco& Jardim::getBloco(int l, int c) const {
    return solo[index(l, c)];
}

// apenas atribui a cada bloco(pos. jardim) as caracteristicas
void Jardim::inicializa() {
    for (int i = 0; i < tamJardim; ++i) {
        int agua = rand() % (Settings::Jardim::agua_max - Settings::Jardim::agua_min + 1)
                   + Settings::Jardim::agua_min;

        int nutri = rand() % (Settings::Jardim::nutrientes_max - Settings::Jardim::nutrientes_min + 1)
                    + Settings::Jardim::nutrientes_min;

        solo[i].setAgua(agua);
        solo[i].setNutri(nutri);
        solo[i].setPlanta(nullptr);
        solo[i].setFerramenta(nullptr);
    }

    plantaPosRandom();
}

void Jardim::plantaPosRandom() {
    // 3 plantas aleatórias (por agora, sempre roseiras)
    for (int i = 0; i < 3; ) {
        int pos = rand() % tamJardim;

        if (solo[pos].getPlanta() == nullptr) {
            int numRand = rand() % 3 + 1;
            // no futuro podes randomizar entre Roseira/Cacto/ErvaDaninha/etc.
            switch (numRand) {
                case 1: solo[pos].setPlanta(new Roseira()); break;
                case 2: solo[pos].setPlanta(new Cacto()); break;
                case 3: solo[pos].setPlanta(new ErvaDaninha()); break;
                default: solo[pos].setPlanta(new Roseira()); break; // se de qql maneira n calhar um daqueles numeros, cria na msm.
            }
            ++i;
        }
    }
}

void Jardim::mostra()const{

    cout << ' ' << ' ';
    for (int regua_col = 0; regua_col < dimCol ; regua_col++)
        cout << char('A' + regua_col) << ' ';
    cout << endl;

    // imprime a regua em cada linha e imprime o jardim. Usa offset para não mostrar o mesmo elemento repetido.
    for (int regua_lin = 0; regua_lin < dimLin; regua_lin++) {
        cout << char('A'+ regua_lin) << ' ';
        for (int j = 0; j < dimCol ; j++) {
            // Ordem das ferramentas
            if(jard.getEstaNoJardim() &&  jard.getPosLin() == regua_lin && jard.getPosCol() == j){
                cout << jard.getSimbolo() << ' ';
            }
            else if(solo[regua_lin * dimCol + j].getPlanta() != nullptr ) {
                cout << solo[regua_lin * dimCol + j].getPlanta()->Simbolo() << ' ';
            }else if(solo[regua_lin * dimCol + j].getFerramenta() != nullptr) {
                cout << solo[regua_lin * dimCol + j].getFerramenta()->getTipo() << ' ';
            }
            else
                cout << "  ";
        }
        cout << endl;
    }
}

bool Jardim::entraJardineiro(int l, int c) {
    jard.entrar(l,c);
    return true;
}

bool Jardim::saiJardineiro() {
    if(jard.getEstaNoJardim()){
        jard.sair();
    }
    return true;
}

