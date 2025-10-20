//
// Created by Filipe Gomes on 20/10/2025.
//

#include "Comandos.h"

bool Executa_Comandos(istream& msg, Retangulo& x){
    string comando;

    if(!(msg >> comando)) return true; // se linha vazia ou EOF pa files

    bool temJardim = (x.solo != nullptr); // false se null, true se existir jardim
    // só aceitamos 'jardim <L> <C>' ou 'executa <ficheiro>'
    if (!temJardim && comando != std::string(cmd::JARDIM) && comando != std::string(cmd::EXECUTA)) {
        std::cout << "erro: o primeiro comando deve ser 'jardim <L> <C>' ou 'executa <ficheiro>'\n";
        return true;
    }

    if(comando == cmd::FIM){
        delete[] x.solo;
        x.solo = nullptr;
        return false;
    }
    else if(comando == string(cmd::JARDIM)) {
        if (temJardim) {
            std::cout << "Já existe 1 jardim\n";
            return true;
        }
        int L=0, C=0; // inicializa valores com 0
        if (!(msg >> L >> C)) { // lê aqui os valores
            std::cout << "erro: uso correto: jardim <L> <C>\n";
            return true;
        }
        if (L < 1 || L > 26 || C < 1 || C > 26) {
            std::cout << "linhas e colunas têm de estar entre 1 e 26\n";
            return true;
        }
        CriaJardim(L, C, x);
        return true;
    }
    else if(comando == cmd::EXECUTA){
        string file;
        if(!(msg >> file)){ cout << "formato correto: executa <nomeFile>\n"; return true;}

        ifstream f(file);
        if(!f){cout << "n consegue abrir file"; return true;}

        string f1;
        while (getline(f,f1)){
            istringstream fline(f1);
            if(!Executa_Comandos(fline,x)) return false;
        }
        return true;
    }
    else if(comando == cmd::AVANCA){
        cout << "validado\n";
        return true;
    }
    else{
        cout << "comando invalido, digita outro\n";
        return true;
    }

}



