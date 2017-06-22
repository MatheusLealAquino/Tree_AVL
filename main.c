#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

int main(){
    No * p = criaAvl(p,5);
    p = insereAvl(p,6);
    p = insereAvl(p,9);
    p = insereAvl(p,10);
    p = insereAvl(p,7);
    p = removerAvl(p,9);

    printElementsTraco(p);
    return 0;
}
