#include "Comandos.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

// --- Funçóes auxiliares de Validação ---
/**
 *
 * @brief Tenta converter uma string para inteiro.
 * @return true se for um inteiro, false caso contrário.
 */
bool strParaInt(const string& s, int& out) {
    try {
        size_t pos;
        out = stoi(s, &pos);
        return pos == s.length();
    } catch (...) {
        return false;
    }
}

/**
 *
 * @brief Converte coordenadas "lc" para inteiros l e c.
 * @return true se o formato for válido, false caso contrário.
*/
bool strParaCoords(const string& s, int& l, int& c) {
    if (s.length() != 2) {
        return false;
    }
    l = s[0] - 'a'; // Converte 'a' -> 0, 'b' -> 1, ...
    c = s[1] - 'a';

    // Verifica se l e c estão dentro dos limites (0 - 25)
    if (l < 0 || l >= 26 || c < 0 || c >= 26) {
        return false;
    }
    return true;
}

/**
 * @brief Verifica se as coordenadas (l, c) estão dentro dos limites do jardim.
 * @return true se válidas, false caso contrário.
 */
bool coordsValidas(int l, int c, const Retangulo& x) {
    return (l >= 0 && l < x.dimLin && c >= 0 && c < x.dimCol);
}

/**
 * @brief Verifica se existem parâmetros extras na linha de comando.
 * @return true se houver lixo (erro), false se estiver tudo ok.
 */
bool verificaLixo(istream& msg, const string& comando) {
    string lixo;
    if (msg >> lixo) {
        cout << "Erro: comando '" << comando << "' tem parâmetros extra: '" << lixo << "'\n";
        return true;
    }
    return false;
}

bool Executa_Comandos(istream& msg, Retangulo& x){
    string comando;

    if(!(msg >> comando)) return true; // se linha vazia ou EOF pa files

    bool temJardim = (x.solo != nullptr); // false se null, true se existir jardim
    // só aceitamos 'jardim <L> <C>' ou 'executa <ficheiro>'
    if (comando == cmd::JARDIM) {
        if (temJardim) {
            cout << "Erro: já existe um jardim criado." << endl;
            return true;;
        }
        string p1, p2;
        int L, C;
        if (!(msg >> p1 >> p2)) {
            cout << "Erro: Sintaxe incorreta. Uso: jardim <L> <C>" << endl;
            return true;
        }
        if (!strParaInt(p1, L) || !strParaInt(p2, C)) {
            cout << "Erro: Dimensoes devem ser numeros inteiros." << endl;
            return true;
        }
        if (L < 1 || L > 26 || C < 1 || C > 26) {
            cout << "Erro: Linhas e colunas devem estar entre 1 e 26." << endl;
            return true;
        }
        if (verificaLixo(msg, "jardim <L> <C>")) {
            return true;
        }
        cout << "[META 1] Comando 'jardim " << L << " " << C << "' validado." << endl;
        CriaJardim(L, C, x);
        return true;
    } else if (comando == cmd::EXECUTA) {
        string file;
        if (!(msg >> file)) {
            cout << "Erro: Sintaxe incorreta. Uso: executa <nomeFicheiro>" << endl;
            return true;
        }
        if (verificaLixo(msg, "executa <nomeFicheiro>")) {
            return true;
        }
        cout << "[META 1] Comando 'executa " << file << "' validado." << endl;
        ifstream f(file);
        if (!f) {
            cout << "Erro: Nao foi possivel abrir o ficheiro '" << file << "'." << endl;
            return true;
        }
        string f1;
        while (getline(f, f1)) {
            if (f1.empty()) {
                continue; // salta linhas vazias
            }
            cout << "> " << f1 << endl;
            istringstream fline(f1);
            if (!Executa_Comandos(fline, x)) {
                return false; // encontrou 'fim' no ficheiro
            }
        }
        cout << "[META 1] Fim do ficheiro '" << file << "'." << endl;
        return true;
    } else if (comando == cmd::FIM) {
        if (verificaLixo(msg, "fim")) {
            return true;
        }
        cout << "[META 1] Comando 'fim' validado. A terminar e a libertar recursos..." << endl;
        delete[] x.solo;
        x.solo = nullptr;
        return false;
    }

    // --- A partir daqui todos os comandos exigem que o jardim já existe ---
    if (!temJardim) {
        cout << "Erro: O primeiro comando deve ser 'jardim <L> <C>' ou 'executa <nomeFicheiro>'" << endl;
        return true;
    }

    if (comando == cmd::AVANCA) {
        string p1;
        int n = 1;
        if (msg >> p1) {
            if (!strParaInt(p1, n) || n <= 0) {
                cout << "Erro: 'n' deve ser um inteiro positivo." << endl;
                return true;
            }
        }
        if (verificaLixo(msg, "avanca [n]")) {
            return true;
        }
        cout << "[META 1] Comando 'avanca " << n << "' validado." << endl;
        return true;
    } else if (comando == cmd::LPLANTAS) {
        if (verificaLixo(msg, "lplantas")) {
            return true;
        }
        cout << "[META 1] Comando 'lplantas' validado." << endl;
        return true;
    } else if (comando == cmd::LPLANTA) {
        string p1;
        int l, c;
        if (!(msg >> p1)) {
            cout << "Erro: Sintaxe incorreta. Uso: lplanta <l><c>" << endl;
            return true;
        }
        if (!strParaCoords(p1, l, c)) {
            cout << "Erro: Coordenadas invalidas (ex: 'aa', 'ce')." << endl;
            return true;
        }
        if (!coordsValidas(l, c, x)) {
            cout << "Erro: Coordenadas fora dos limites do jardim." << endl;
            return true;
        }
        if (verificaLixo(msg, "lplanta <l><c>")) {
            return true;
        }
        cout << "[META 1] Comando 'lplanta " << p1 << "' validado." << endl;
        return true;
    } else if (comando == cmd::LAREA) {
        if (verificaLixo(msg, "larea")) {
            return true;
        }
        cout << "[META 1] Comando 'larea' validado." << endl;
        return true;
    } else if (comando == cmd::LSOLO) {
        string p1, p2;
        int l, c, n = 0;
        bool temN = false;
        if (!(msg >> p1)) {
            cout << "Erro: Sintaxe incorreta. Uso: lsolo <l><c> [n]" << endl;
            return true;
        }
        if (!strParaCoords(p1, l, c)) {
            cout << "Erro: Coordenadas invalidas (ex: 'aa', 'ce')." << endl;
            return true;
        }
        if (!coordsValidas(l, c, x)) {
            cout << "Erro: Coordenadas fora dos limites do jardim." << endl;
            return true;
        }
        if (msg >> p2) {
            temN = true;
            if (!strParaInt(p2, n) || n < 0) {
                cout << "Erro: 'n' (raio) deve ser um numero inteiro positivo ou zero.\n";
                return true;
            }
        }
        if (verificaLixo(msg, "lsolo <l><c> [n]")) {
            return true;
        }
        cout << "[META 1] Comando 'lsolo " << p1 << (temN ? " " + p2 : "") << "' validado." << endl;
        return true;
    } else if (comando == cmd::LFERR){
        if (verificaLixo(msg, "lferr")) {
            return true;
        }
        cout << "[META 1] Comando 'lferr' validado." << endl;
        return true;
    } else if (comando == cmd::COLHE) {
        string p1;
        int l, c;
        if (!(msg >> p1)) {
            cout << "Erro: Sintaxe incorreta. Uso: colhe <l><c>" << endl;
            return true;
        }
        if (!strParaCoords(p1, l, c)) {
            cout << "Erro: Coordenadas invalidas (ex: 'aa', 'ce')." << endl;
            return true;
        }
        if (!coordsValidas(l, c, x)) {
            cout << "Erro: Coordenadas fora dos limites do jardim." << endl;
            return true;
        }
        if (verificaLixo(msg, "colhe <l><c>")) {
            return true;
        }
        cout << "[META 1] Comando 'colhe " << p1 << "' validado." << endl;
        return true;
    } else if (comando == cmd::PLANTA) {
        string p1, p2;
        int l, c;
        if (!(msg >> p1 >> p2)) {
            cout << "Erro: Sintaxe incorreta. Uso: planta <l><c> <tipo>" << endl;
            return true;
        }
        if (!strParaCoords(p1, l, c)) {
            cout << "Erro: Coordenadas invalidas (ex: 'aa', 'ce')." << endl;
            return true;
        }
        if (!coordsValidas(l, c, x)) {
            cout << "Erro: Coordenadas fora dos limites do jardim." << endl;
            return true;
        }
        if (p2.length() != 1 || (p2[0] != 'c' && p2[0] != 'r' && p2[0] != 'e' && p2[0] != 'x')) {
            cout << "Erro: Tipo de planta invalido. Use 'c', 'r', 'e' ou 'x'." << endl;
            return true;
        }
        if (verificaLixo(msg, "planta <l><c> <tipo>")) {
            return true;
        }
        cout << "[META 1] Comando 'planta " << p1 << " " << p2 << "' validado." << endl;
        return true;
    } else if (comando == cmd::LARGA) {
        if (verificaLixo(msg, "larga")) {
            return true;
        }
        cout << "[META 1] Comando 'larga' validado." << endl;
        return true;
    } else if (comando == cmd::PEGA) {
        string p1;
        int n;
        if (!(msg >> p1)) {
            cout << "Erro: Sintaxe incorreta. Uso: pega <n>" << endl;
            return true;
        }
        if (!strParaInt(p1, n) || n <= 0) {
            cout << "Erro: 'n' (numero de serie) deve ser um inteiro positivo." << endl;
            return true;
        }
        if (verificaLixo(msg, "pega <n>")) {
            return true;
        }
        cout << "[META 1] Comando 'pega " << n << "' validado." << endl;
        return true;
    } else if (comando == cmd::COMPRA) {
        string p1;
        if (!(msg >> p1)) {
            cout << "Erro: Sintaxe incorreta. Uso: compra <c>" << endl;
            return true;
        }
        if (p1.length() != 1 || (p1[0] != 'g' && p1[0] != 'a' && p1[0] != 't' && p1[0] != 'z')) {
            cout << "Erro: Tipo de ferramenta invalido. Use 'g', 'a', 't' ou 'z'." << endl;
            return true;
        }
        if (verificaLixo(msg, "compra <c>")) {
            return true;
        }
        cout << "[META 1] Comando 'compra " << p1 << "' validado." << endl;
        return true;
    } else if (comando == cmd::mov::ESQ) {
        if (verificaLixo(msg, "e")) {
            return true;
        }
        cout << "[META 1] Comando 'e' (esquerda) validado." << endl;
        return true;
    } else if (comando == cmd::mov::DIR) {
        if (verificaLixo(msg, "d")) {
            return true;
        }
        cout << "[META 1] Comando 'd' (direita) validado." << endl;
        return true;
    } else if (comando == cmd::mov::CIMA) {
        if (verificaLixo(msg, "c")) {
            return true;
        }
        cout << "[META 1] Comando 'c' (cima) validado." << endl;
        return true;
    } else if (comando == cmd::mov::BAIXO) {
        if (verificaLixo(msg, "b")) {
            return true;
        }
        cout << "[META 1] Comando 'b' (baixo) validado." << endl;
        return true;
    } else if (comando == cmd::ENTRA) {
        string p1;
        int l, c;
        if (!(msg >> p1)) {
            cout << "Erro: Sintaxe incorreta. Uso: entra <l><c>" << endl;
            return true;
        }
        if (!strParaCoords(p1, l, c)) {
            cout << "Erro: Coordenadas invalidas (ex: 'aa', 'ce')." << endl;
            return true;
        }
        if (!coordsValidas(l, c, x)) {
            cout << "Erro: Coordenadas fora dos limites do jardim." << endl;
            return true;
        }
        if (verificaLixo(msg, "entra <l><c>")) {
            return true;
        }
        cout << "[META 1] Comando 'entra " << p1 << "' validado." << endl;
        return true;
    } else if (comando == cmd::SAI) {
        if (verificaLixo(msg, "sai")) {
            return true;
        }
        cout << "[META 1] Comando 'sai' validado." << endl;
        return true;
    } else {
        cout << "Erro: Comando '" << comando << "' desconhecido." << endl;
        return true;
    }
}