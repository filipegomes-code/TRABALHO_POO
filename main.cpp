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

    ProcessarComandos(cin, mapa);

    return 0;
}
