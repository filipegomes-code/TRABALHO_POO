cmake_minimum_required(VERSION 3.27)
project(Trabalho)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(.)

add_executable(SimuladorJardim
        Jardim/jardim.cpp
        main.cpp
        Comandos/Comandos.cpp
        Plantas/Planta.cpp
        Plantas/Cacto/Cacto.cpp
        Plantas/Roseira/Roseira.cpp
        Plantas/ErvaDaninha/ErvaDaninha.cpp
        Plantas/Exotica/Exotica.cpp
        Jardineiro/Jardineiro.cpp
        Ferramentas/Ferramenta.cpp
        Ferramentas/Regador/Regador.cpp
        Ferramentas/Tesoura/Tesoura.cpp
        Ferramentas/Adubo/Adubo.cpp
        Ferramentas/FerramentaZ/FerramentaZ.cpp)
