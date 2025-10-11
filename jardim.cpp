#include "jardim.h"
#include "Settings.h"


// gera posições aleatórias para pôr as 3 primeiras plantas sempre que se cria um jardim.
// Às vezes imprime 2 "c" em vez de 3.
void Planta_posRandom(Retangulo& jardim_plantas){

    // 3 posições aleatórias
    for (int i = 0; i < 3 ; ) {
        int linha_planta = rand() % dimLin;
        int col_planta = rand() % dimCol;

        if(jardim_plantas.soloJardim[linha_planta][col_planta].planta == ". ") {
            jardim_plantas.soloJardim[linha_planta][col_planta].planta = "c ";
            i++;
        }

    }
}

void inicializa(Retangulo& x){

    // ainda ta sem plantas, ferramentas, etc ... inicializa vazio
    for (int i = 0; i < dimLin ; i++) {
        for (int j = 0 ; j < dimCol ; j++) {
                x.soloJardim[i][j].planta = ". ";
                x.soloJardim[i][j].agua = rand() % (Settings::Jardim::agua_max - Settings::Jardim::agua_min + 1)+ Settings::Jardim::agua_min; // rand() % -> quantidade de numeros possiveis + -> limite minimo
                x.soloJardim[i][j].nutri = rand() % (Settings::Jardim::nutrientes_max - Settings::Jardim::nutrientes_min + 1)+ Settings::Jardim::nutrientes_min; // 40 - 50
                x.soloJardim[i][j].temJard = false;
        }
    }

    Planta_posRandom(x);
}

void MostraJardim(const Retangulo& z){

    // Ta confuso? ta, mas funciona
    for (int regua_x = 0; regua_x < dimLin ; regua_x++) {
        if(regua_x == 0) cout << ' ' << ' ';
        else cout << char('A' + regua_x -1) << ' ';

        for (int regua_y = 0; regua_y < dimCol; regua_y++) {
            if(regua_x == 0)
            cout << char('A' + regua_y) << ' ';
        }

        // para não imprimir na 1ª linha os pontos
        if(regua_x != 0) {
            for (int i = dimCol-1; i >= 0; i--) {
                cout << z.soloJardim[regua_x][i].planta;
            }
        }

        cout << endl;
    }
}

