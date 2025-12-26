#include "Planta.h"
#include "iostream"

int Planta::qtd_plantas = 0;

// usei move(b) pq aparecia warning a dizer para usar -> transfere a string do b para beleza, n cria cópia, b fica vazio
Planta::Planta(int n, int a, std::string b) : nutrientes(n), agua(a), beleza(std::move(b)){}

Planta::~Planta()= default;


