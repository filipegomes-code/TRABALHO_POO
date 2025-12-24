#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
#include "Jardim/Jardim.h"
#include "Comandos/Comandos.h"

using namespace std;

int main() {
    srand(time(nullptr)); // NOLINT(cert-msc51-cpp)
    Jardim mapa;

    cout << "========= BEM-VINDO AO SIMULADOR DE JARDIM =========" << endl;
    cout << "Comece por criar o jardim: jardim <linhas> <colunas>" << endl;

    while (true) {
        string comando;
        cout << "\n> ";

        if (!getline(cin, comando)) break; // erro ou EOF

        if (comando.empty()) continue;

        istringstream one(comando); // transforma essa linha e separa pelos espaços
        if (!ProcessarComandos(one, mapa)) break; // 'fim' devolve false
    }

    return 0;
}
