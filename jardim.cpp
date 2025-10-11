#include "jardim.h"

void inicializa(Retangulo& x){

    // ainda ta sem plantas, ferramentas, etc ... inicializa vazio
    for (int i = 0; i < dimLin ; i++) {
        for (int j = 0 ; j < dimCol ; j++) {
            x.soloJardim[i][j] = ". ";
        }
    }
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
            for (int i = dimCol; i > 0; i--) {
                cout << z.soloJardim[regua_x][i];
            }
        }

        cout << endl;
    }

}

