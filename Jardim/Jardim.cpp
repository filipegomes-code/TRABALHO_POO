#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Jardim.h"
#include "../Settings.h"
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

int Jardim::instantes = 0;

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

std::string Jardim::listaAllPlantas() const {
    std::ostringstream oss;

    bool encontrou = false;

    for (int l = 0; l < dimLin; ++l) {
        for (int c = 0; c < dimCol; ++c) {
            const Bloco& b = getBloco(l, c);
            Planta* p = b.getPlanta();

            if (p != nullptr) {
                encontrou = true;

                char lc_lin = (char)('a' + l);
                char lc_col = (char)('a' + c);

                oss << "posição " << lc_lin << lc_col
                    << " - tipo='" << p->Simbolo() << "'"
                    << " | planta: agua=" << p->getAgua()
                    << ", nutr=" << p->getNutrientes()
                    << ", beleza=\"" << p->getBeleza() << "\""
                    << " | solo: agua=" << b.getAgua()
                    << ", nutr=" << b.getNutri()
                    << "\n";
            }
        }
    }

    if (!encontrou)
        oss << "Nao ha plantas no jardim.\n";

    return oss.str();
}

std::string Jardim::lista1Planta(int l, int c) const{
    std::ostringstream oss;

    const Bloco& b = getBloco(l,c);
    Planta* p = b.getPlanta();

    if(!b.getPlanta()){
        oss << "N tem planta nessa posicao\n";
        return oss.str();
    }

    char lc_lin = (char)('a' + l);
    char lc_col = (char)('a' + c);

    oss << "posição " << lc_lin << lc_col
        << " - tipo='" << p->Simbolo() << "'"
        << " | planta: agua=" << p->getAgua()
        << ", nutr=" << p->getNutrientes()
        << ", beleza=\"" << p->getBeleza() << "\""
        << " | solo: agua=" << b.getAgua()
        << ", nutr=" << b.getNutri()
        << "\n";

    return oss.str();
}

std::string Jardim::listaArea() const {
    std::ostringstream oss;

    bool encontrou = false;

    for (int l = 0; l < dimLin; ++l) {
        for (int c = 0; c < dimCol; ++c) {
            const Bloco& b = getBloco(l, c);

            bool temPlanta = (b.getPlanta());
            bool temFerr   = (b.getFerramenta());
            bool temJard   = (jard.getEstaNoJardim() &&
                              jard.getPosLin() == l &&
                              jard.getPosCol() == c);

            // posição totalmente vazia = ignora
            if (!temPlanta && !temFerr && !temJard)
                continue;

            encontrou = true;

            char lc_lin = (char)('a' + l);
            char lc_col = (char)('a' + c);

            oss << "posicao " << lc_lin << lc_col
                << " | solo: agua=" << b.getAgua()
                << ", nutr=" << b.getNutri();

            // jardineiro
            if (temJard)
                oss << " | jardineiro: *";

            // planta
            if (temPlanta) {
                const Planta* p = b.getPlanta();
                oss << " | planta: tipo='" << p->Simbolo() << "'"
                    << ", agua=" << p->getAgua()
                    << ", nutr=" << p->getNutrientes()
                    << ", beleza=\"" << p->getBeleza() << "\"";
            }

            // ferramenta
            if (temFerr) {
                const Ferramenta* f = b.getFerramenta();
                oss << " | ferramenta: tipo='" << f->getTipo() << "'";
            }

            oss << "\n";
        }
    }

    if (!encontrou)
        oss << "Nao ha nenhuma posicao com conteudo no jardim.\n";

    return oss.str();
}

// se a pessoa n definir raio [n], apenas mostra info do bloco nessa posicao
std::string Jardim::listaAreaIndicada(int l, int c) const {
    std::ostringstream oss;

    const Bloco& b = getBloco(l, c);
    char lc_lin = (char)('a' + l);
    char lc_col = (char)('a' + c);


    bool temPlanta = (b.getPlanta());
    bool temFerr   = (b.getFerramenta());
    bool temJard   = (jard.getEstaNoJardim() &&
                        jard.getPosLin() == l &&
                        jard.getPosCol() == c);

    oss << "posicao " << lc_lin << lc_col
        << " | solo: agua=" << b.getAgua()
        << ", nutr=" << b.getNutri();

    if (!temPlanta && !temFerr && !temJard) {
        oss << " | vazia\n";
        return oss.str();
    }

    if(temPlanta || temFerr || temJard){
        // jardineiro
        if (temJard)
            oss << " | jardineiro: *";

        // planta
        if (temPlanta) {
            const Planta* p = b.getPlanta();
            oss << " | planta: tipo='" << p->Simbolo() << "'"
                << ", agua=" << p->getAgua()
                << ", nutr=" << p->getNutrientes()
                << ", beleza=\"" << p->getBeleza() << "\"";
            }

        // ferramenta
        if (temFerr) {
            const Ferramenta* f = b.getFerramenta();
            oss << " | ferramenta: tipo='" << f->getTipo() << "'";
        }

        oss << "\n";
    }
    return oss.str();
}

// se a pessoa definir raio [n], mostra info dos blocos com raio [n] a partir do bloco atual (l,c)
std::string Jardim::listaAreaRaio(int l, int c, int n)const{
    std::ostringstream oss;

    // ja mostra a info na posicao atual (l,c) -> centro
    oss << listaAreaIndicada(l,c);

    for (int i = -n; i <= n ; ++i) {
        for (int j = -n; j<=n ; ++j) {
            // n queremos que i e j sejam 0, senao isso é o centro que já foi tratado antes
            if (i == 0 && j == 0) continue;

            int linNovaVizRaio = l+i;
            int colNovaVizRaio = c+j;

            // segurança: não sair fora do jardim
            if (linNovaVizRaio < 0 || linNovaVizRaio >= dimLin ||
                colNovaVizRaio < 0 || colNovaVizRaio >= dimCol)
                continue;

            oss << listaAreaIndicada(linNovaVizRaio,colNovaVizRaio);
        }
    }

    return oss.str();
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
    ferramentaPosRandom();
}

void Jardim::ferramentaPosRandom(){
    // 3 ferr aleatórias
    for (int i = 0; i < 3; ) {
        int pos = rand() % tamJardim;

        if (solo[pos].getFerramenta() == nullptr) {
            int numRand = rand() % 3 + 1;
            // no futuro podes randomizar entre Roseira/Cacto/ErvaDaninha/etc.
            switch (numRand) {
                case 1: solo[pos].setFerramenta(new Adubo()); break;
                case 2: solo[pos].setFerramenta(new Regador()); break;
                case 3: solo[pos].setFerramenta(new Tesoura()); break;
                default: solo[pos].setFerramenta(new Adubo()); break; // se de qql maneira n calhar um daqueles numeros, cria na msm.
            }
            ++i;
        }
    }
}

void Jardim::plantaPosRandom() {
    // 3 plantas aleatórias
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


void Jardim::listFerrJardineiro() const{
    auto lista = jard.listarFerramentas();
    if (lista.empty()) {
        std::cout << "Sem ferramentas\n";
        return;
    }
    for (auto& s : lista)
        std::cout << s << "\n";
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

    Bloco& b = getBloco(l, c);

    // posição já tem planta → falha
    if (b.getPlanta() != nullptr)
        return false;

    Planta* nova = nullptr;

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
        case 'z':
            // nova = new Exotica();
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

    Bloco& b = getBloco(l, c);
    Planta* p = b.getPlanta();

    // não há planta nessa posição
    if (p == nullptr)
        return false;

    delete p;
    b.setPlanta(nullptr);
    jard.registaColheita();
    return true;
}

// “Sempre que uma ferramenta é apanhada, aparece ‘por magia’ outra, aleatória, numa posição aleatória.”
void Jardim::novaFerramentaPosRandom() {
    int tentativas = 1000;

    while (tentativas--) {
        int pos = rand() % tamJardim;
        if (solo[pos].getFerramenta() == nullptr) {
            int numRand = rand() % 3 + 1;
            switch (numRand) {
                case 1: solo[pos].setFerramenta(new Adubo());   break;
                case 2: solo[pos].setFerramenta(new Regador()); break;
                case 3: solo[pos].setFerramenta(new Tesoura()); break;
                default: solo[pos].setFerramenta(new Adubo());  break;
            }
            return;
        }
    }
}

void Jardim::apanhaFerrAutomatico(int l, int c) {
    Bloco& b = getBloco(l, c);
    if (b.getFerramenta() != nullptr) {
        jard.apanharFerramenta(b.getFerramenta());
        b.setFerramenta(nullptr);
        novaFerramentaPosRandom(); // spawn “por magia”
    }
}

// jardineiro atualiza apenas posicoes na sua classe, usado na funcao Jardim::mostra
// para mostrar a posicao onde se encontra
bool Jardim::entraJardineiro(int l, int c) {
    if(!jard.entrar(l,c))
        return false;
    //
    apanhaFerrAutomatico(l,c);
    return true;
}

bool Jardim::saiJardineiro() {
    if(jard.getEstaNoJardim()){
        return jard.sair();
    }
    return false;
}

bool Jardim::moveJardineiro(string dir){
    if(jard.getEstaNoJardim()) {
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
        if(lin < 0) lin = dimLin-1;
        else if (lin >= dimLin) lin = 0;

        // Wrap vertical
        if(col < 0) col = dimCol-1;
        else if(col >= dimCol) col = 0;
        // apanha ferramenta automaticamente
        apanhaFerrAutomatico(lin,col);

        return jard.atualizaPos(lin, col);
    }
    return false;
}

bool Jardim::avancar(int n) {
    if (n <= 0) return false;

    for (int i = 0; i < n; ++i) {
        ++instantes;

        if (jard.getEstaNoJardim()) {
            Ferramenta* f = jard.getFerramentaAtiva();
            if (f != nullptr) {
                int l = jard.getPosLin();
                int c = jard.getPosCol();

                Bloco& b = getBloco(l, c);
                bool viva = f->aplicaEfeito(b);
                if (!viva) {
                    jard.FerrDestruida();
                }
            }
        }

        // 2) Todas as plantas atuam (um passo de tempo para cada)
        for (int l = 0; l < dimLin; ++l) {
            for (int c = 0; c < dimCol; ++c) {
                Bloco& b = getBloco(l, c);
                Planta* p = b.getPlanta();
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






