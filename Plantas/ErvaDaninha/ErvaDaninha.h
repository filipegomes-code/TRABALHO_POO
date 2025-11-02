
#ifndef TRABALHO_ERVADANINHA_H
#define TRABALHO_ERVADANINHA_H

#include "Plantas/Planta.h"

class ErvaDaninha : public Planta{
public:
    ErvaDaninha();
    ~ErvaDaninha() override;

    char Simbolo()const override;
    void Absorve() override;
    void CheckMorte() override;

};



#endif //TRABALHO_ERVADANINHA_H
