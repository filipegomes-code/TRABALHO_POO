#include "Regador.h"
#include "Settings.h"
#include "Jardim/Jardim.h"

using namespace std;

Regador::Regador() : Ferramenta(), capacidadeAgua(Settings::Regador::capacidade) {
}

Ferramenta *Regador::duplicar() const {
    return new Regador(*this);
}

bool Regador::aplicaEfeito(Bloco &b) {
    if (capacidadeAgua <= 0)
        return false;

    int dose = Settings::Regador::dose;
    if (capacidadeAgua < dose)
        dose = capacidadeAgua;

    b.setAgua(b.getAgua() + dose);
    capacidadeAgua -= dose;

    return capacidadeAgua > 0;
}

string Regador::getDescricao() const {
    return "Regador (água = " + to_string(capacidadeAgua) + ")";
}
