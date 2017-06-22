#ifndef AVL_H
#define AVL_H

                //Done by: Matheus Leal
                //June at 2017

typedef struct no{
    int dado;
    struct no * right;
    struct no * left;
}No;

No * criaAvl(No * root, int valor);
No * insereAvl(No * root, int valor);
No * removerAvl(No * root, int valor);
int fatorBalanceamento(No * root);
int altura(No * root);
No * rotacaoRight(No * root);
No * rotacaoLeft(No * root);
No * rotacaoLeftRight(No * root);
No * rotacaoRightLeft(No * root);

#endif // AVL_H
