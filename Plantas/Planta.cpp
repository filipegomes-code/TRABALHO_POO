#include "Planta.h"
#include "iostream"

using namespace std;

// usei move(b) pq aparecia warning a dizer para usar -> transfere a string do b para beleza, n cria cópia, b fica vazio
Planta::Planta(int n, int a, string b) : nutrientes(n), agua(a), beleza(std::move(b)) {
}

Planta::~Planta() = default;
