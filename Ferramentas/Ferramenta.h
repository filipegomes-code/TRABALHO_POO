#ifndef TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_FERRAMENTA_H
#define TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_FERRAMENTA_H

#include <string>

class Bloco;

class Ferramenta {
public:
    Ferramenta();

    virtual ~Ferramenta() = default;

    [[nodiscard]] virtual Ferramenta *duplicar() const = 0;

    virtual bool aplicaEfeito(Bloco &b) = 0;

    [[nodiscard]] int getNumSerie() const { return numSerie; }

    [[nodiscard]] virtual char getTipo() const = 0;

    [[nodiscard]] virtual std::string getDescricao() const = 0;

protected:
    int numSerie; // número de série de cada ferramenta

private:
    static int contadorNumSerie; // contador estático para atribuir números de série únicos
};

#endif //TP_PROGRAMACAO_ORIENTADA_A_OBJETOS_FERRAMENTA_H
