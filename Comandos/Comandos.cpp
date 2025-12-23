#include "Comandos.h"
#include "Jardim/Jardim.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

// UTILITÁRIOS (Namespace anónimo para funções auxiliares locais)
namespace {
    // converte uma string para inteiro - return true se for valido, false caso contrário
    bool strParaInt(const string& s, int& out) {
        try {
            size_t pos;
            out = stoi(s, &pos); // este &pos guarda a posição do 1 caractere que não é um número.
            return pos == s.length();
        } catch (...) {
            return false;
        }
    }

    // Converte coordenadas "lc" para inteiros l e c (0-indexed) - true se válido, false caso contrário
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

    // verifica se as coordenadas (l, c) estão dentro dos limites do jardim - true se válidas, false caso contrário
    bool coordsValidas(int l, int c, const Jardim& x) {
        return (l >= 0 && l < x.getDimLin() && c >= 0 && c < x.getDimCol());
    }
}

// CLASSES DE COMANDOS CONCRETOS
// --- JARDIM ---
class CmdJardim : public Comando {
public:
    bool executar(Jardim& jardim, const vector<string>& args) override {
        if (jardim.existe()) {
            cout << "Erro: já existe um jardim criado." << endl;
            return true;
        }
        if (args.size() != 2) {
            cout << "Erro: Síntaxe incorreta. Uso: jardim <L> <C>" << endl;
            return true;
        }

        int l, c;
        if (!strParaInt(args[0], l) || !strParaInt(args[1], c)) {
            cout << "Erro: Dimensões devem ser números inteiros." << endl;
            return true;
        }
        if (l < 1 || l > 26 || c < 1 || c > 26) {
            cout << "Erro: Linhas e colunas devem estar entre 1 e 26." << endl;
            return true;
        }

        jardim.cria(l, c);
        cout << "Jardim " << l << "x" << c << " criado com sucesso." << endl;
        return true;
    }
};

// --- AVANCA ---
class CmdAvanca : public Comando {
public:
    bool executar(Jardim& jardim, const vector<string>& args) override {
        if (!jardim.existe()) {
            cout << "Erro: Jardim não existe." << endl;
            return true;
        }

        int n = 1;
        if (!args.empty()) {
            if (args.size() > 1 || !strParaInt(args[0], n) || n <= 0) {
                cout << "Erro: 'n' deve ser um inteiro positivo." << endl;
                return true;
            }
        }
        if (jardim.avancar(n)) {
            cout << "Avançou " << n << " instantes." << endl;
        }
        return true;
    }
};

// --- FIM ---
class CmdFim : public Comando {
public:
    bool executar(Jardim &jardim, const vector<string> &args) override {
        if (!args.empty()) {
            cout << "Erro: 'fim' não aceita argumentos." << endl;
            return true;
        }
        cout << "A terminar simulação..." << endl;
        jardim.destroi();
        return false;
    }
};

// --- EXECUTA (FICHEIROS) ---
class CmdExecuta : public Comando {
public:
    bool executar(Jardim &jardim, const vector<string> &args) override {
        if (args.size() != 1) {
            cout << "Erro: Uso: executa <nome_ficheiro>" << endl;
            return true;
        }
        ifstream f(args[0]);
        if (!f) {
            cout << "Erro: Não abriu ficheiro '" << args[0] << "'" << endl;
            return true;
        }
        cout << "--- Início execução ficheiro: " << args[0] << " ---" << endl;
        // Chama o processador principal passando o ficheiro como stream - Recursivo
        if (!ProcessarComandos(f, jardim)) {
            return false; // se encontrar o comando 'fim' dentro do ficheiro, propaga o false
        }
        cout << "--- Fim execução ficheiro: " << args[0] << " ---" << endl;
        return true;
    }
};

// --- COMANDOS DE LISTAGEM ---
class CmdLPlantas : public Comando {
public:
    bool executar(Jardim& jardim, const vector<string>& args) override {
        if (!args.empty()) {
            cout << "Erro: lplantas não aceita argumentos." << endl;
            return true;
        }
        cout << jardim.listaAllPlantas();
        return true;
    }
};

class CmdLArea : public Comando {
public:
    bool executar(Jardim& j, const vector<string>& args) override {
        if (!args.empty()) {
            cout << "Erro: larea não aceita argumentos." << endl;
            return true;
        }
        cout << j.listaArea();
        return true;
    }
};

class CmdLFerr : public Comando {
public:
    bool executar(Jardim &jardim, const vector<string> &args) override {
        if (!args.empty()) {
            cout << "Erro: lferr não aceita argumentos." << endl;
            return true;
        }
        jardim.listFerrJardineiro();
        return true;
    }
};

class CmdLPlanta : public Comando {
public:
    bool executar(Jardim& jardim, const vector<string>& args) override {
        if (args.size() != 1) {
            cout << "Erro: Uso: lplanta <l><c>" << endl;
            return true;
        }
        int l, c;
        if (!strParaCoords(args[0], l, c) || !coordsValidas(l, c, jardim)) {
            cout << "Erro: Coordenadas inválidas." << endl;
            return true;
        }
        cout << jardim.lista1Planta(l, c);
        return true;
    }
};

class CmdLSolo : public Comando {
public:
    bool executar(Jardim& j, const vector <string>& args) override {
        if (args.size() < 1 || args.size() > 2) {
            cout << "Erro: Uso: lsolo <l><c> [n]" << endl;
            return true;
        }
        int l, c;
        if (!strParaCoords(args[0], l, c) || !coordsValidas(l, c, j)) {
            cout << "Erro: Coordenadas inválidas." << endl;
            return true;
        }

        if (args.size() == 2) {
            int n;
            if (!strParaInt(args[1], n) || n < 0) {
                cout << "Erro: raio deve ser inteiro >= 0." << endl;
                return true;
            }
            cout << j.listaAreaRaio(l, c, n);
        } else {
            cout << j.listaAreaIndicada(l, c);
        }
        return true;
    }
};

// --- AÇÕES DO JARDINEIRO ---
class CmdColhe : public Comando {
public:
    bool executar(Jardim& j, const vector<string>& args) override {
        if (args.size() != 1) {
            cout << "Erro: Uso: colhe <l><c>" << endl;
            return true;
        }
        int l, c;
        if (!strParaCoords(args[0], l, c) || !coordsValidas(l, c, j)) {
            cout << "Erro: Coordenadas inválidas." << endl;
            return true;
        }
        if (j.colher(l, c)) {
            cout << "Planta colhida." << endl;
        } else {
            cout << "Não foi possível colher (vazio ou limite atingido)." << endl;
        }
        j.mostra();
        return true;
    }
};

class CmdPlanta : public Comando {
public:
    bool executar(Jardim& j, const vector<string>& args) override {
        if (args.size() != 2) {
            cout << "Erro: Uso: planta <l><c> <tipo>" << endl;
            return true;
        }
        int l, c;
        if (!strParaCoords(args[0], l, c) || !coordsValidas(l, c, j)) {
            cout << "Erro: Coordenadas inválidas." << endl;
            return true;
        }

        string tipoStr = args[1];
        if (tipoStr.length() != 1) {
            cout << "Erro: Tipo deve ser 1 caracter." << endl;
            return true;
        }
        char tipo = tolower(tipoStr[0]);
        if (tipo != 'c' && tipo != 'r' && tipo != 'e' && tipo != 'x') {
            cout << "Erro: Tipo inválido (c, r, e, x)." << endl;
            return true;
        }

        if (j.plantar(l, c, tipo)) {
            cout << "Plantou " << tipo << "." << endl;
        } else {
            cout << "Não foi possível plantar (ocupado ou limite atingido." << endl;
        }
        j.mostra();
        return true;
    }
};

class CmdLarga : public Comando {
public:
    bool executar(Jardim& j, const vector<string>& args) override {
        if (!args.empty()) {
            cout << "Erro: larga não aceita argumentos." << endl;
            return true;
        }
        if (j.largarFerrJardineiro()) {
            cout << "Ferramenta largada." << endl;
        } else {
            cout << "Não tem ferramenta na mão." << endl;
        }
        return true;
    }
};

class CmdPega : public Comando {
public:
    bool executar(Jardim& j, const vector<string>& args) override {
        if (args.size() != 1) {
            cout << "Erro: Uso: pega <id>" << endl;
            return true;
        }
        int id;
        if (!strParaInt(args[0], id) || id <= 0) {
            cout << "Erro: ID deve ser inteiro positivo." << endl;
            return true;
        }
        if (j.pegarFerrJardineiro(id)) {
            cout << "Pegou na ferramenta " << id << "." << endl;
        } else {
            cout << "Ferramenta não encontrada na mochila." << endl;
        }
        return true;
    }
};

class CmdCompra : public Comando {
public:
    bool executar(Jardim& j, const vector<string>& args) override {
        if (args.size() != 1) {
            cout << "Erro: Uso: compra <tipo>" << endl;
            return true;
        }
        string t = args[0];
        if (t.length() != 1) {
            cout << "Erro: Tipo deve ser 1 caracter." << endl;
            return true;
        }
        char tipo = tolower(t[0]);
        if (tipo != 'g' && tipo != 'a' && tipo != 't' && tipo != 'z') {
            cout << "Erro: Tipo inválido (g, a, t, z)." << endl;
            return true;
        }

        if (j.comprarFerrJardineiro(tipo)) {
            cout << "Comprou ferramenta " << tipo << "." << endl;
        } else {
            cout << "Não foi possível comprar." << endl;
        }
        return true;
    }
};

// --- MOVIMENTO E ESTADO DO JARDINEIRO ---
class CmdEntra : public Comando {
public:
    bool executar(Jardim& j, const vector<string>& args) override {
        if (args.size() != 1) {
            cout << "Erro: Uso: entra <l><c>" << endl;
            return true;
        }
        int l, c;
        if (!strParaCoords(args[0], l, c) || !coordsValidas(l, c, j)) {
            cout << "Erro: Coordenadas inválidas." << endl;
            return true;
        }
        if (j.entraJardineiro(l, c)) {
            cout << "Jardineiro entrou em " << args[0] << "." << endl;
            j.mostra();
        } else {
            cout << "Não foi possível entrar (já dentro ou limite atingido)." << endl;
        }
        return true;
    }
};

class CmdSai : public Comando {
public:
    bool executar(Jardim &jardim, const std::vector<std::string> &args) override {
        if (!args.empty()) {
            cout << "Erro: sai não aceita argumentos." << endl;
            return true;
        }
        if (jardim.saiJardineiro()) {
            cout << "Jardineiro saiu do jardim." << endl;
            jardim.mostra();
        } else {
            cout << "Não pode sair (não está no jardim ou limite atingido)." << endl;
        }
        return true;
    }
};

// Classe genérica para movimento (E, D, C, B)
class CmdMovimento : public Comando {
public:
    CmdMovimento(string dir) : direcao(dir) {}

    bool executar(Jardim& j, const vector<string>& args) override {
        if (!args.empty()) {
            cout << "Erro: movimento não aceita argumentos." << endl;
            return true;
        }
        if (j.moveJardineiro(direcao)) {
            cout << "Moveu-se para: " << direcao << endl;
            j.mostra();
        } else {
            cout << "Não pode mover (fora limites, não está no jardim ou sem movimentos)." << endl;
        }
        return true;
    }
private:
    string direcao;
};

// --- COMANDOS DE PERSISTÊNCIA ---
class CmdGrava : public Comando {
public:
    bool executar(Jardim& jardim, const vector<string>& args) override {
        if (args.size() != 1) {
            cout << "Erro: Uso: grava <nome>" << endl;
            return true;
        }

        if (Jardim::salvarJogo(args[0], jardim)) {
            cout << "Jogo gravado com sucesso com o nome '" << args[0] << "'." << endl;
        } else {
            cout << "Erro ao gravar (Jardim não existe ou erro de memória)." << endl;
        }
        return true;
    }
};

class CmdRecupera : public Comando {
public:
    bool executar(Jardim &jardim, const std::vector<std::string> &args) override {
        if (args.size() != 1) {
            cout << "Erro: Uso: recupera <nome>" << endl;
            return true;
        }

        if (Jardim::recuperarJogo(args[0], jardim)) {
            cout << "Jogo '" << args[0] << "' recuperado com sucesso." << endl;
        } else {
            cout << "Erro: Save com o nome '" << args[0] << "' não encontrado." << endl;
        }
        return true;
    }
};

class CmdApaga : public Comando {
public:
    bool executar(Jardim &jardim, const std::vector<std::string> &args) override {
        if (args.size() != 1) {
            cout << "Erro: Uso: apaga <nome>" << endl;
            return true;
        }

        if (Jardim::apagarJogo(args[0])) {
            cout << "Save '" << args[0] << "' apagado da memória." << endl;
        } else {
            cout << "Erro: Save não encontrado." << endl;
        }
        return true;
    }
};

// FACTORY IMPLEMENTATION
std::unique_ptr<Comando> ComandoFactory::criar(const string &nome) {
    if (nome == cmd_keys::JARDIM) return make_unique<CmdJardim>();
    if (nome == cmd_keys::AVANCA) return make_unique<CmdAvanca>();
    if (nome == cmd_keys::FIM) return make_unique<CmdFim>();
    if (nome == cmd_keys::EXECUTA) return make_unique<CmdExecuta>();

    // Listagens
    if (nome == cmd_keys::LPLANTAS) return make_unique<CmdLPlantas>();
    if (nome == cmd_keys::LPLANTA) return make_unique<CmdLPlanta>();
    if (nome == cmd_keys::LAREA) return make_unique<CmdLArea>();
    if (nome == cmd_keys::LSOLO) return make_unique<CmdLSolo>();
    if (nome == cmd_keys::LFERR) return make_unique<CmdLFerr>();

    // Ações
    if (nome == cmd_keys::COLHE) return make_unique<CmdColhe>();
    if (nome == cmd_keys::PLANTA) return make_unique<CmdPlanta>();
    if (nome == cmd_keys::LARGA) return make_unique<CmdLarga>();
    if (nome == cmd_keys::PEGA) return make_unique<CmdPega>();
    if (nome == cmd_keys::COMPRA) return make_unique<CmdCompra>();

    // Jardineiro
    if (nome == cmd_keys::ENTRA) return make_unique<CmdEntra>();
    if (nome == cmd_keys::SAI) return make_unique<CmdSai>();

    // Movimento
    if (nome == cmd_keys::ESQ) return make_unique<CmdMovimento>(string(cmd_keys::ESQ));
    if (nome == cmd_keys::DIR) return make_unique<CmdMovimento>(string(cmd_keys::DIR));
    if (nome == cmd_keys::CIMA) return make_unique<CmdMovimento>(string(cmd_keys::CIMA));
    if (nome == cmd_keys::BAIXO) return make_unique<CmdMovimento>(string(cmd_keys::BAIXO));

    // Persistência
    if (nome == cmd_keys::GRAVA) return make_unique<CmdGrava>();
    if (nome == cmd_keys::RECUPERA) return make_unique<CmdRecupera>();
    if (nome == cmd_keys::APAGA) return make_unique<CmdApaga>();

    return nullptr;
}

// PROCESSAR COMANDOS
bool ProcessarComandos(istream& in, Jardim& jardim) {
    string linha;
    while (getline(in, linha)) {
        if (linha.empty()) {
            continue;
        }

        istringstream iss(linha);
        string nomeCmd;
        if (!(iss >> nomeCmd)) {
            continue;
        }

        vector<string> args;
        string arg;
        while (iss >> arg) {
            args.push_back(arg);
        }

        if (!jardim.existe() && nomeCmd != cmd_keys::JARDIM && nomeCmd != cmd_keys::EXECUTA && nomeCmd != cmd_keys::FIM) {
            cout << "Erro: O primeiro comando deve ser 'jardim' ou 'executa'." << endl;
            continue;
        }

        auto cmd = ComandoFactory::criar(nomeCmd);
        if (cmd) {
            if (!cmd->executar(jardim, args)) {
                return false;
            }
        } else {
            cout << "Erro: Comando desconhecido '" << nomeCmd << "'" << endl;
        }
    }
    return true;
}