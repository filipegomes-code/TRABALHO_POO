#include "Tesoura.h"
#include "Jardim/Jardim.h"
#include "Plantas/Planta.h"

using namespace std;

Tesoura::Tesoura() : Ferramenta() {
}

Ferramenta *Tesoura::duplicar() const {
    return new Tesoura(*this);
}

bool Tesoura::aplicaEfeito(Bloco &b) {
    Planta *p = b.getPlanta();
    if (!p)
        return true;

    if (p->getBeleza() == "Feia") {
        delete p;
        b.setPlanta(nullptr);
    }

    return true; // tesoura nunca se gasta
}

string Tesoura::getDescricao() const {
    return "Tesoura";
}
