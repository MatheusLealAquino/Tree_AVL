#include <stdio.h>
#include <stdlib.h>
#include "avl.h"
                 //Done by: Matheus Leal
                //June at 2017

avl_node_t * criaAvl(int valor){
    avl_node_t * aux = (avl_node_t*)malloc(sizeof(avl_node_t));
    aux->right = aux->left = NULL;
    aux->dado = valor;
    aux->height = 1;
    return aux;
}

int max(int a, int b){
    if(a > b) return a;
    return b;
}

int getHeight(avl_node_t * root){
    if(root == NULL) return 0;
    return root->height;
}

int maxHeight(avl_node_t * root){
	return max(getHeight(root->left), getHeight(root->right));
}

avl_node_t * insert(avl_node_t * root, int valor){
    if(root == NULL)
        return criaAvl(valor);
    else if(valor < root->dado)
        root->left = insert(root->left,valor);
    else if(valor > root->dado)
        root->right = insert(root->right,valor);
    else{
        return root;
    }
    root->height = maxHeight(root)+1;
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
avl_node_t * delete(avl_node_t * root, int valor){
    if(root == NULL)
        return NULL;
    else if(root->dado > valor) root->left = delete(root->left,valor);
    else if(root->dado < valor) root->right = delete(root->right,valor);
    else{
        if(root->dado== valor && root->left == NULL && root->right == NULL){
            free(root);
            root = NULL;
        }else if(root->left == NULL){
            avl_node_t * temp = root;
            root = root->right;
            free(temp);
        }else if(root->right == NULL){
            avl_node_t * temp = root;
            root = root->left;
            free(temp);
        }else{
            avl_node_t * temp = root->left;
            while(temp->right != NULL)
                temp = temp->right;
            root->dado = temp->dado;
            temp->dado = valor;
            root->left = delete(root->left,valor);
        }
    }
    if(root != NULL){
        root->height = maxHeight(root)+1;
        int b = fatorBalanceamento(root);
        if(b > 1){
            if(b >= 0){
               return rotacaoLeft(root);
            }else{
                return rotacaoRightLeft(root);
            }
        }
        if(b < -1){
            if(b <=0){
                return rotacaoRight(root);
            }else{
                return rotacaoLeftRight(root);
            }
        }
    }
    return root;
}
avl_node_t * search(avl_node_t * root, int valor){
    if(root == NULL){
        printf("Valor nao esta na arvore.\n");
        return root;
    }else{
        if(root->dado > valor){
            search(root->left,valor);
        }else if(root->dado < valor){
            search(root->right,valor);
        }else{
            printf("Valor na arvore.\n");
            return root;
        }
    }
}
avl_node_t * destroyTree(avl_node_t * root){
    if(root != NULL){
        root->left = destroyTree(root->left);
        root->right = destroyTree(root->right);
        free(root);
    }
    return NULL;
}
int fatorBalanceamento(avl_node_t * root){
    if(root != NULL) return getHeight(root->right)-getHeight(root->left);
    return 0;
}

int altura(avl_node_t * root){
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

avl_node_t * rotacaoLeft(avl_node_t * root){ //Roda para a esquerda
    avl_node_t * aux;
    aux = root->right;
    root->right = aux->left;
    aux->left = root;
    root->height = maxHeight(root)+1;
	aux->height = maxHeight(aux)+1;
    return aux;
}
avl_node_t * rotacaoRight(avl_node_t * root){ //Roda para a direita
    avl_node_t * aux;
    aux = root->left;
    root->left = aux->right;
    aux->right = root;
    root->height = maxHeight(root)+1;
	aux->height = maxHeight(aux)+1;
    return aux;
}
avl_node_t * rotacaoRightLeft(avl_node_t * root){
    root->right = rotacaoRight(root->right);
    return rotacaoLeft(root);
}
avl_node_t * rotacaoLeftRight(avl_node_t * root){
    root->left = rotacaoLeft(root->left);
    return rotacaoRight(root);
}

/* PRINT  */

void printTreeOrder(avl_node_t* root){
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
void printLevel(avl_node_t *arvore, int level, int n){
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
void printElements(avl_node_t * arvore){
    int i;
    int height = altura(arvore);

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
void printElementsTraco(avl_node_t * arvore){
    int i;
    int height = altura(arvore);

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
