#include "Ferramenta.h"

int Ferramenta::contadorNumSerie = 0;

Ferramenta::Ferramenta() : numSerie(++contadorNumSerie) {
}
