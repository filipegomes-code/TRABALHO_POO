//
// Created by Filipe Gomes on 29/10/2025.
//

#ifndef TRABALHO_CACTO_H
#define TRABALHO_CACTO_H

#include "Plantas/Planta.h"

class Cacto : public Planta{
public:
    Cacto();
    ~Cacto() override;

    char Simbolo()const override;
    void Absorve() override;
    void CheckMorte() override;


};



#endif //TRABALHO_CACTO_H
