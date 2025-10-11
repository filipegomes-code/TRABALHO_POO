#include "jardim.h"


int main(){
    srand(time(nullptr)); // gera semente

    Retangulo dimJardim;
    inicializa(dimJardim);
    MostraJardim(dimJardim);

    return 0;
}

