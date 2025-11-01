#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
#include "Jardim/Jardim.h"
#include "Comandos/Comandos.h"
#include "Plantas/Roseira/Roseira.h"

using namespace std;

int main(){
    srand(time(nullptr)); // gera semente
    Retangulo mapa = {0,0,0, nullptr};

    while (true) {
        string comando;
        cout << "> ";

        if (!getline(cin, comando)) break; // erro ou EOF

        istringstream one(comando); // transforma essa linha e separa pelos espaços
        if (!Executa_Comandos(one, mapa)) break; // 'fim' devolve false
    }

    return 0;
}

