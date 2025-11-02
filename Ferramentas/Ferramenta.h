
#ifndef TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_FERRAMENTA_H
#define TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_FERRAMENTA_H

#include <string>

class Jardim;

class Ferramenta {
public:
    Ferramenta();
    Ferramenta(char c);
    virtual ~Ferramenta() = default;

    virtual bool aplicaEfeito(Jardim* j, int l, int c) = 0;

    int getNumSerie() const { return numSerie; }
    char getCharTipo() const { return tipo; }
    virtual std::string getTipo() const = 0;

    virtual std::string getDescricao() const = 0;
private:
    static int contadorNumSerie; // contar estático para atribuir números de série únicos
protected:
    int numSerie; // número de série de cada ferramenta
    char tipo; // tipo da ferramenta: 'r' regador, 'a' adubo, etc
};


#endif //TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_FERRAMENTA_H