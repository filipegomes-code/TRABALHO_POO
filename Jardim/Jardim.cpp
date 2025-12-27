#include <iostream>
#include "Jardim.h"
#include <sstream>
#include "Comandos/Comandos.h"
#include "Ferramentas/Adubo/Adubo.h"
#include "Ferramentas/Regador/Regador.h"
#include "Ferramentas/Tesoura/Tesoura.h"
#include "Ferramentas/FerramentaZ/FerramentaZ.h"
#include "Plantas/Roseira/Roseira.h"
#include "Plantas/Cacto/Cacto.h"
#include "Plantas/ErvaDaninha/ErvaDaninha.h"
#include "Plantas/Exotica/Exotica.h"

using namespace std;

map<string, Jardim> Jardim::salvaguardas;

Bloco::Bloco()
    : planta(nullptr), ferr(nullptr), agua(0), nutri(0) {
}

Planta *Bloco::getPlanta() const {
    return planta;
}

void Bloco::setPlanta(Planta *p) {
    planta = p;
}

Ferramenta *Bloco::getFerramenta() const {
    return ferr;
}

void Bloco::setFerramenta(Ferramenta *f) {
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

int Jardim::instantes = 0;

Jardim::Jardim()
    : dimLin(0), dimCol(0), tamJardim(0), solo(nullptr) {
}

Jardim::Jardim(int linhas, int colunas)
    : dimLin(0), dimCol(0), tamJardim(0), solo(nullptr) {
    cria(linhas, colunas);
}

Jardim::Jardim(const Jardim &outro) : dimLin(0), dimCol(0), tamJardim(0), solo(nullptr) {
    *this = outro;
}

Jardim &Jardim::operator=(const Jardim &outro) {
    if (this == &outro) return *this;

    destroi();

    if (!outro.existe()) return *this;

    dimLin = outro.dimLin;
    dimCol = outro.dimCol;
    tamJardim = outro.tamJardim;

    solo = new Bloco[tamJardim];

    for (int i = 0; i < tamJardim; ++i) {
        solo[i].setAgua(outro.solo[i].getAgua());
        solo[i].setNutri(outro.solo[i].getNutri());

        if (outro.solo[i].getPlanta() != nullptr) {
            solo[i].setPlanta(outro.solo[i].getPlanta()->duplicar());
        } else {
            solo[i].setPlanta(nullptr);
        }

        if (outro.solo[i].getFerramenta() != nullptr) {
            solo[i].setFerramenta(outro.solo[i].getFerramenta()->duplicar());
        } else {
            solo[i].setFerramenta(nullptr);
        }
    }

    jard = outro.jard;

    return *this;
}

Jardim::~Jardim() {
    destroi();
}

bool Jardim::salvarJogo(const string &nome, const Jardim &atual) {
    if (!atual.existe()) return false;

    salvaguardas[nome] = atual;
    return true;
}

bool Jardim::recuperarJogo(const string &nome, Jardim &atual) {
    auto it = salvaguardas.find(nome);
    if (it == salvaguardas.end())
        return false;

    atual = it->second;

    atual.mostra();

    return true;
}

bool Jardim::apagarJogo(const string &nome) {
    return salvaguardas.erase(nome) > 0;
}

bool Jardim::existe() const {
    return solo;
}

void Jardim::cria(int linhas, int colunas) {
    // se já existir, limpar primeiro
    destroi();

    if (linhas < 1 || linhas > 26 || colunas < 1 || colunas > 26)
        return;

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
Bloco &Jardim::getBloco(int l, int c) {
    return solo[index(l, c)];
}

const Bloco &Jardim::getBloco(int l, int c) const {
    return solo[index(l, c)];
}

std::string Jardim::listaAllPlantas() const {
    std::ostringstream oss;

    bool encontrou = false;

    for (int l = 0; l < dimLin; ++l) {
        for (int c = 0; c < dimCol; ++c) {
            const Bloco &b = getBloco(l, c);
            Planta *p = b.getPlanta();

            if (p != nullptr) {
                encontrou = true;

                char lc_lin = static_cast<char>('a' + l);
                char lc_col = static_cast<char>('a' + c);

                oss << "posição " << lc_lin << lc_col
                        << " - tipo = '" << p->Simbolo() << "'"
                        << " | planta: água=" << p->getAgua()
                        << ", nutrientes = " << p->getNutrientes()
                        << ", beleza = \"" << p->getBeleza() << "\""
                        << " | solo: água = " << b.getAgua()
                        << ", nutrientes = " << b.getNutri()
                        << "\n";
            }
        }
    }

    if (!encontrou)
        oss << "Não há plantas no jardim.\n";

    return oss.str();
}

string Jardim::lista1Planta(int l, int c) const {
    ostringstream oss;

    const Bloco &b = getBloco(l, c);
    Planta *p = b.getPlanta();

    if (!b.getPlanta()) {
        oss << "Não há planta na posição.\n";
        return oss.str();
    }

    char lc_lin = static_cast<char>('a' + l);
    char lc_col = static_cast<char>('a' + c);

    oss << "posição " << lc_lin << lc_col
            << " - tipo = '" << p->Simbolo() << "'"
            << " | planta: água = " << p->getAgua()
            << ", nutrientes = " << p->getNutrientes()
            << ", beleza = \"" << p->getBeleza() << "\""
            << " | solo: água = " << b.getAgua()
            << ", nutrientes = " << b.getNutri()
            << "\n";

    return oss.str();
}

string Jardim::listaArea() const {
    ostringstream oss;

    bool encontrou = false;

    for (int l = 0; l < dimLin; ++l) {
        for (int c = 0; c < dimCol; ++c) {
            const Bloco &b = getBloco(l, c);

            bool temPlanta = (b.getPlanta());
            bool temFerr = (b.getFerramenta());
            bool temJard = (jard.getEstaNoJardim() &&
                            jard.getPosLin() == l &&
                            jard.getPosCol() == c);

            // posição totalmente vazia = ignora
            if (!temPlanta && !temFerr && !temJard)
                continue;

            encontrou = true;

            char lc_lin = static_cast<char>('a' + l);
            char lc_col = static_cast<char>('a' + c);

            oss << "posição " << lc_lin << lc_col
                    << " | solo: água = " << b.getAgua()
                    << ", nutrientes = " << b.getNutri();

            // jardineiro
            if (temJard)
                oss << " | jardineiro: *";

            // planta
            if (temPlanta) {
                const Planta *p = b.getPlanta();
                oss << " | planta: tipo = '" << p->Simbolo() << "'"
                        << ", água = " << p->getAgua()
                        << ", nutrientes = " << p->getNutrientes()
                        << ", beleza = \"" << p->getBeleza() << "\"";
            }

            // ferramenta
            if (temFerr) {
                const Ferramenta *f = b.getFerramenta();
                oss << " | ferramenta: tipo = '" << f->getTipo() << "'";
            }

            oss << "\n";
        }
    }

    if (!encontrou)
        oss << "Não há nenhuma posição com conteúdo no jardim.\n";

    return oss.str();
}

// se a pessoa não definir raio [n], apenas mostra info do bloco nessa posicao
string Jardim::listaAreaIndicada(int l, int c) const {
    ostringstream oss;

    const Bloco &b = getBloco(l, c);
    char lc_lin = static_cast<char>('a' + l);
    char lc_col = static_cast<char>('a' + c);


    bool temPlanta = (b.getPlanta());
    bool temFerr = (b.getFerramenta());
    bool temJard = (jard.getEstaNoJardim() &&
                    jard.getPosLin() == l &&
                    jard.getPosCol() == c);

    oss << "posição " << lc_lin << lc_col
            << " | solo: água = " << b.getAgua()
            << ", nutrientes = " << b.getNutri() << "\n";

    if (!temPlanta && !temFerr && !temJard) {
        oss << " | vazia\n";
        return oss.str();
    }

    if (temPlanta || temFerr) {
        // jardineiro
        if (temJard)
            oss << " | jardineiro: *";

        // planta
        if (temPlanta) {
            const Planta *p = b.getPlanta();
            oss << " | planta: tipo = '" << p->Simbolo() << "'"
                    << ", água = " << p->getAgua()
                    << ", nutrientes = " << p->getNutrientes()
                    << ", beleza = \"" << p->getBeleza() << "\"";
        }

        // ferramenta
        if (temFerr) {
            const Ferramenta *f = b.getFerramenta();
            oss << " | ferramenta: tipo = '" << f->getTipo() << "'";
        }

        oss << "\n";
    }
    return oss.str();
}

// se a pessoa definir raio [n], mostra info dos blocos com raio [n] a partir do bloco atual (l, c)
string Jardim::listaAreaRaio(int l, int c, int n) const {
    ostringstream oss;

    // ja mostra a info na posicao atual (l, c) → centro
    oss << listaAreaIndicada(l, c);

    for (int i = -n; i <= n; ++i) {
        for (int j = -n; j <= n; ++j) {
            // não queremos que i e j sejam 0, senao isso é o centro que já foi tratado antes
            if (i == 0 && j == 0) continue;

            int linNovaVizRaio = l + i;
            int colNovaVizRaio = c + j;

            // segurança: não sair do jardim
            if (linNovaVizRaio < 0 || linNovaVizRaio >= dimLin ||
                colNovaVizRaio < 0 || colNovaVizRaio >= dimCol)
                continue;

            oss << listaAreaIndicada(linNovaVizRaio, colNovaVizRaio);
        }
    }

    return oss.str();
}

// apenas atribui a cada bloco(pos. jardim) as caracteristicas
void Jardim::inicializa() const {
    for (int i = 0; i < tamJardim; ++i) {
        int agua = rand() % (Settings::Jardim::agua_max - Settings::Jardim::agua_min + 1) // NOLINT(cert-msc50-cpp)
                   + Settings::Jardim::agua_min;

        int nutri = rand() % (Settings::Jardim::nutrientes_max - Settings::Jardim::nutrientes_min + 1) // NOLINT(cert-msc50-cpp)
                    + Settings::Jardim::nutrientes_min;

        solo[i].setAgua(agua);
        solo[i].setNutri(nutri);
        solo[i].setPlanta(nullptr);
        solo[i].setFerramenta(nullptr);
    }

    plantaPosRandom();
    ferramentaPosRandom();
}

void Jardim::ferramentaPosRandom() const {
    // 3 ferr aleatórias
    for (int i = 0; i < 3;) {
        int pos = rand() % tamJardim; // NOLINT(cert-msc50-cpp)

        if (solo[pos].getFerramenta() == nullptr) {
            // no futuro podes randomizar entre Roseira/Cacto/ErvaDaninha/etc.
            switch (rand() % 4 + 1) { // NOLINT(cert-msc50-cpp)
                case 1: solo[pos].setFerramenta(new Adubo());
                    break;
                case 2: solo[pos].setFerramenta(new Regador());
                    break;
                case 3: solo[pos].setFerramenta(new Tesoura());
                    break;
                case 4: solo[pos].setFerramenta(new FerramentaZ());
                    break;
                default: solo[pos].setFerramenta(new Adubo());
                    break; // se de qql maneira não calhar um daqueles numeros, cria na msm.
            }
            ++i;
        }
    }
}

void Jardim::plantaPosRandom() const {
    // 3 plantas aleatórias
    for (int i = 0; i < 3;) {
        int pos = rand() % tamJardim; // NOLINT(cert-msc50-cpp)

        if (solo[pos].getPlanta() == nullptr) {
            switch (rand() % 4 + 1) { // NOLINT(cert-msc50-cpp)
                case 1: solo[pos].setPlanta(new Roseira());
                    break;
                case 2: solo[pos].setPlanta(new Cacto());
                    break;
                case 3: solo[pos].setPlanta(new ErvaDaninha());
                    break;
                case 4: solo[pos].setPlanta(new Exotica());
                    break;
                default: solo[pos].setPlanta(new Roseira());
                    break; // se de qql maneira não calhar um daqueles numeros, cria na msm.
            }
            ++i;
        }
    }
}

void Jardim::mostra() const {
    if (!solo) return;

    cout << "\n";
    cout << ' ' << ' ';
    for (int regua_col = 0; regua_col < dimCol; regua_col++)
        cout << static_cast<char>('A' + regua_col) << ' ';
    cout << endl;

    // Imprime a regua em cada linha e imprime o jardim. Usa offset para não mostrar o mesmo elemento repetido.
    for (int regua_lin = 0; regua_lin < dimLin; regua_lin++) {
        cout << static_cast<char>('A' + regua_lin) << ' ';
        for (int j = 0; j < dimCol; j++) {
            // Ordem das ferramentas
            if (jard.getEstaNoJardim() && jard.getPosLin() == regua_lin && jard.getPosCol() == j) {
                cout << Jardineiro::getSimbolo() << ' ';
            } else {
                const Bloco &b = solo[regua_lin * dimCol + j];

                Planta *p = b.getPlanta();
                Ferramenta *f = b.getFerramenta();

                if (p != nullptr) {
                    cout << p->Simbolo() << ' ';
                } else if (f != nullptr) {
                    cout << f->getTipo() << ' ';
                } else {
                    cout << "  ";
                }
            }
        }
        cout << endl;
    }
}


void Jardim::listFerrJardineiro() const {
    auto lista = jard.listarFerramentas();
    if (lista.empty()) {
        cout << "O jardineiro não possui ferramentas no inventário.\n";
        return;
    }
    for (auto &s: lista)
        cout << s << "\n";
}

bool Jardim::comprarFerrJardineiro(char tipoFerr) {
    return jard.comprarFerramenta(tipoFerr);
}

bool Jardim::pegarFerrJardineiro(int numSerie) {
    return jard.pegarFerramenta(numSerie);
}

bool Jardim::largarFerrJardineiro() {
    return jard.largarFerramenta();
}

bool Jardim::plantar(int l, int c, char tipo) {
    // verificar limite de plantações por turno
    if (!jard.podePlantar())
        return false;

    Bloco &b = getBloco(l, c);

    // posição já tem planta → falha
    if (b.getPlanta() != nullptr)
        return false;

    Planta *nova = nullptr;

    switch (tipo) {
        case 'c':
            nova = new Cacto();
            break;
        case 'r':
            nova = new Roseira();
            break;
        case 'e':
            nova = new ErvaDaninha();
            break;
        case 'x':
            nova = new Exotica();
            break;
        default:
            return false;
    }

    b.setPlanta(nova);
    jard.registaPlantacao();
    return true;
}

bool Jardim::colher(int l, int c) {
    // verifica limites de colher
    if (!jard.podeColher())
        return false;

    Bloco &b = getBloco(l, c);
    Planta *p = b.getPlanta();

    // não há planta nessa posição
    if (p == nullptr)
        return false;

    delete p;
    b.setPlanta(nullptr);
    jard.registaColheita();
    return true;
}

// “Sempre que uma ferramenta é apanhada, aparece ‘por magia’ outra, aleatória, numa posição aleatória.”
void Jardim::novaFerramentaPosRandom() const {
    int tentativas = 1000;

    while (tentativas--) {
        int pos = rand() % tamJardim; // NOLINT(cert-msc50-cpp)
        if (solo[pos].getFerramenta() == nullptr) {
            switch (rand() % 3 + 1) { // NOLINT(cert-msc50-cpp)
                case 1: solo[pos].setFerramenta(new Adubo());
                    break;
                case 2: solo[pos].setFerramenta(new Regador());
                    break;
                case 3: solo[pos].setFerramenta(new Tesoura());
                    break;
                default: solo[pos].setFerramenta(new Adubo());
                    break;
            }
            return;
        }
    }
}

void Jardim::apanhaFerrAutomatico(int l, int c) {
    Bloco &b = getBloco(l, c);
    if (b.getFerramenta() != nullptr) {
        jard.apanharFerramenta(b.getFerramenta());
        b.setFerramenta(nullptr);
        novaFerramentaPosRandom(); // spawn “por magia”
    }
}

// jardineiro atualiza apenas posicoes na sua classe, usado na funcao Jardim::mostra
// para mostrar a posicao onde se encontra
bool Jardim::entraJardineiro(int l, int c) {
    if (!jard.entrar(l, c))
        return false;

    apanhaFerrAutomatico(l, c);
    return true;
}

bool Jardim::saiJardineiro() {
    if (jard.getEstaNoJardim())
        return jard.sair();

    return false;
}

bool Jardim::moveJardineiro(const string &dir) {
    if (jard.getEstaNoJardim()) {
        char mov = dir[0];
        int lin = jard.getPosLin();
        int col = jard.getPosCol();

        switch (mov) {
            case 'e':
                col--;
                break;
            case 'd':
                col++;
                break;
            case 'c':
                lin--;
                break;
            case 'b':
                lin++;
                break;
            default: break;
        }
        // Wrap horizontal
        if (lin < 0) lin = dimLin - 1;
        else if (lin >= dimLin) lin = 0;

        // Wrap vertical
        if (col < 0) col = dimCol - 1;
        else if (col >= dimCol) col = 0;
        // apanha ferramenta automaticamente
        apanhaFerrAutomatico(lin, col);

        return jard.atualizaPos(lin, col);
    }
    return false;
}

bool Jardim::avancar(int n) {
    if (n <= 0) return false;

    for (int i = 0; i < n; ++i) {
        ++instantes;

        if (jard.getEstaNoJardim()) {
            Ferramenta *f = jard.getFerramentaAtiva();
            if (f != nullptr) {
                int l = jard.getPosLin();
                int c = jard.getPosCol();

                Bloco &b = getBloco(l, c);
                bool viva = f->aplicaEfeito(b);
                if (!viva) {
                    jard.FerrDestruida();
                }
            }
        }

        // 2) Todas as plantas atuam (um passo de tempo para cada)
        for (int l = 0; l < dimLin; ++l) {
            for (int c = 0; c < dimCol; ++c) {
                Bloco &b = getBloco(l, c);
                Planta *p = b.getPlanta();
                if (p != nullptr) {
                    bool viva = p->passo(*this, l, c, b);
                    if (!viva) {
                        delete p;
                        b.setPlanta(nullptr);
                    }
                }
            }
        }

        jard.reiniciaContadores();
    }
    return true;
}
