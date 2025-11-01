#include "jardim.h"
#include "Comandos/Comandos.h"
#include "Settings.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Plantas/Roseira/Roseira.h"
#include "Plantas/Cacto/Cacto.h"
#include "Plantas/ErvaDaninha/ErvaDaninha.h"

using namespace std;

// gera posições aleatórias para pôr as 3 primeiras plantas sempre que se cria um jardim.
void Planta_posRandom(Retangulo& jardim_plantas){
    // 3 posições aleatórias
    for (int i = 0; i < 3 ; ) {
        int pos_random = rand() % jardim_plantas.tam_jardim; // gera pos de 0-dimLin*dimCol
        // se estiver vazio, insere planta
        if(jardim_plantas.solo[pos_random].planta == nullptr){
            // futuramente fazer um if ou switch com rand para escolher roseira, cacto ou outros..
            jardim_plantas.solo[pos_random].planta = new Roseira();
            i++;
        }

    }
}

// apenas atribui a cada bloco(pos. jardim) as caracteristicas
void inicializa(Retangulo& x){

    // ainda ta sem plantas, ferramentas, etc ... inicializa vazio
    for (int i = 0; i < x.tam_jardim; i++) {
            // x.solo[i].planta; planta já é null nem é preciso inicializar pq já está
            x.solo[i].agua = rand() % (Settings::Jardim::agua_max - Settings::Jardim::agua_min + 1) +
                             Settings::Jardim::agua_min; // rand() % -> quantidade de numeros possiveis + -> limite minimo
            x.solo[i].nutri = rand() % (Settings::Jardim::nutrientes_max - Settings::Jardim::nutrientes_min + 1) +
                              Settings::Jardim::nutrientes_min; // 40 - 50
            x.solo[i].temJard = false;
    }

    Planta_posRandom(x);
}

void MostraJardim(Retangulo& z){

    cout << ' ' << ' ';
    for (int regua_col = 0; regua_col < z.dimCol ; regua_col++)
        cout << char('A' + regua_col) << ' ';
    cout << endl;

    // imprime a regua em cada linha e imprime o jardim. Usa offset para não mostrar o mesmo elemento repetido.
    for (int regua_lin = 0; regua_lin < z.dimLin; regua_lin++) {
        cout << char('A'+ regua_lin) << ' ';
        for (int j = 0; j < z.dimCol ; j++) {
            if(z.solo[regua_lin * z.dimCol + j].planta != nullptr ) {
                cout << z.solo[regua_lin * z.dimCol + j].planta->Simbolo() << ' ';
            }else
                cout << "  ";
        }
        cout << endl;
    }
}

void CriaJardim(int L, int C ,Retangulo& x){
    if (L <= 26 && C <= 26) {
        x.dimLin = L;
        x.dimCol = C;
        x.tam_jardim = L * C;
        x.solo = new bloco[L * C]; // cria array 1D dinâmico
        inicializa(x);
        MostraJardim(x);
    }
}



