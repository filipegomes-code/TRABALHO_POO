
#ifndef TRABALHO_CACTO_H
#define TRABALHO_CACTO_H

#include "Plantas/Planta.h"

class Cacto : public Planta{
private:
    int contaAguaAlta = 0;
    int contaSemNutrientes = 0;
    int aguaAbsVida = 0;
    int nutrAbsVida = 0;

    // helpers privados para multiplicação
    void tentaMultiplicar(Jardim& j, int l, int c);

protected:
    void Absorve(Bloco& b) override;
    bool CheckMorte() override;

public:
    Cacto();
    ~Cacto() override;

    char Simbolo()const override {return 'c';}
    bool passo(Jardim& j, int l, int c, Bloco& b) override;

};



#endif //TRABALHO_CACTO_H
