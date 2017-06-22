#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

No * criaAvl(No * root, int valor){
    No * aux = (No*)malloc(sizeof(No));
    aux->right = aux->left = NULL;
    aux->dado = valor;
    return aux;
}
No * rotacaoLeft(No * root){ //Roda para a esquerda
    No * aux;
    aux = root->right;
    root->right = aux->left;
    aux->left = root;
    root = aux;
    return root;
}
No * rotacaoRight(No * root){ //Roda para a direita
    No * aux;
    aux = root->left;
    root->left = aux->right;
    aux->right = root;
    root = aux;
    return root;
}

No * rotacaoRightLeft(No * root){
    root->right = rotacaoRight(root->right);
    return rotacaoLeft(root);
}

No * rotacaoLeftRight(No * root){
    root->left = rotacaoLeft(root->left);
    return rotacaoRight(root);
}

int altura(No * root){
    if(root == NULL) {
        return 0;
    }else{
        int alt1 = altura(root->left);
        int alt2 = altura(root->right);

        if(alt1 > alt2){
            return alt1+1;
        }else{
            return alt2+1;
        }
    }
}
int fatorBalanceamento(No * root){
    return altura(root->right)-altura(root->left);
}

No * insereAvl(No * root, int valor){
    if(root == NULL)
        return criaAvl(root, valor);
    else if(valor < root->dado)
        root->left = insereAvl(root->left,valor);
    else if(valor > root->dado)
        root->right = insereAvl(root->right,valor);
    else{
        return root;
    }
    int b = fatorBalanceamento(root);
    if(b > 1){
        if(root->right->dado < valor){
           return rotacaoLeft(root);
        }else{
            return rotacaoRightLeft(root);
        }
    }
    if(b < -1){
        if(root->left->dado > valor){
            return rotacaoRight(root);
        }else{
            return rotacaoLeftRight(root);
        }
    }
    return root;
}

No * removerAvl(No * root, int valor){
    if(root == NULL)
        return NULL;
    else if(root->dado > valor) root->left = removerAvl(root->left,valor);
    else if(root->dado < valor) root->right = removerAvl(root->right,valor);
    else{
        if(root->dado== valor && root->left == NULL && root->right == NULL){
            free(root);
            root = NULL;
        }else if(root->left == NULL){
            No * temp = root;
            root = root->right;
            free(temp);
        }else if(root->right == NULL){
            No * temp = root;
            root = root->left;
            free(temp);
        }else{
            No * temp = root->left;
            while(temp->right != NULL)
                temp = temp->right;
            root->dado = temp->dado;
            temp->dado = valor;
            root->left = removerAvl(root->left,valor);
        }
    }
    if(root != NULL){
        int b = fatorBalanceamento(root);
        if(b > 1){
            if(root->right->dado < valor){
               return rotacaoLeft(root);
            }else{
                return rotacaoRightLeft(root);
            }
        }
        if(b < -1){
            if(root->left->dado > valor){
                return rotacaoRight(root);
            }else{
                return rotacaoLeftRight(root);
            }
        }
    }
    return root;
}

/* PRINT  */
int treeDepth(No*raiz){
    if(raiz == NULL){
        return 0;
    }else{
        int lDepth = treeDepth(raiz->left);
        int rDepth = treeDepth(raiz->right);

        if(lDepth > rDepth){
            return (lDepth+1);
        }
        else{
            return(rDepth+1);
        }
    }
}

void printTreeOrder(No* root){
    if(root==NULL){
        return;
    }
    printTreeOrder(root->left);
    printf("%d ", root->dado);
    printTreeOrder(root->right);
}

void printaEspacos(int x){
    for (int i = 0; i < x; ++i){
        printf(" ");
    }
}

void printLevel(No *arvore, int level, int n){
    if (level == 0){
        printaEspacos(n);
        if(arvore != NULL){
            printf("%d", arvore->dado);
        }else{
            printf("-");
        }
        printaEspacos(n);
    }
    else{
        if(arvore == NULL){
            printLevel(NULL, level - 1, n);
        }else{
            printLevel(arvore->left, level - 1, n);
        }
        printf(" ");
        if(arvore == NULL){
            printLevel(NULL, level - 1, n);
        }else{
            printLevel(arvore->right, level - 1, n);
        }
    }
}
int numberOfSpaces(int x){
    int j = 1;
    for (int i = 0; i < x; ++i){
        j = j*2;
    }
    j--;
    return j;
}
void printElements(No * arvore){
    int i;
    int height = treeDepth(arvore);

    for(i = 0; i < height; i++){
        int n = numberOfSpaces(height-i);
        printLevel(arvore, i, n);
        printf("\n");
    }
}
int pw(int x, int y){
    if(y == 0){
        return 1;
    }
    int r = 1;
    for (int i = 0; i < y; ++i){
        r = r * x;
    }
    return r;
}
void printElementsTraco(No * arvore){
    int i;
    int height = treeDepth(arvore);

    for(i = 0; i < height; i++){
        int n = numberOfSpaces(height-i);
        int t = numberOfSpaces(height-i-1);
        printLevel(arvore, i, n);
        printf(" ");
        printf("\n");

        for (int j = 0; j < t; j++){
            int pw1 = pw(2,i);
            for (int k = 0; k < pw1; ++k){
                printaEspacos(n-j-1);
                printf("/");
                printaEspacos(j);
                printaEspacos(1);
                printaEspacos(j);
                printf("\\");
                printaEspacos(n-j-1);
                printf(" ");

            }
            printf("\n");
        }
    }
}
/* /PRINT  */
