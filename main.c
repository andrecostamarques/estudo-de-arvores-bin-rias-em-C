#include <stdio.h>
#include <stdlib.h>

typedef struct NoArvore{

    struct NoArvore* left;   //aponta para o nó da esquerda da arvore
    struct NoArvore* right;  //aponta para o nó da direita da arvore
    int info;   //informação salva naquele nó da arvore

}No;

typedef struct Arvore{

    No* raiz; //aponta para o nó mais ao topo da arvore (ele não é filho de ninguém)

}Arv;

Arv* criaArvore(){
    Arv* aux;
    aux = (Arv*)malloc(sizeof(Arv)); //liberando espaço na mem suficiente para salvar um nó inteiro, que aponta para nulo.
    aux->raiz = NULL; //enviando 
    return aux;
}

No* aux_insere(No* aux, int input){

    int flag;
    No* pai;    //cria um ponteiro para o pai
    No* novo = (No*) malloc(sizeof(No));    //aloca memoria e cria um ponteiro p o filho
    novo->info = input;
    novo->left = NULL;  //ambas folhas apontam para nulo (nao tem nada la ainda)
    novo->right = NULL;

    if(aux==NULL){ //ou seja, se o nó recebido da função apontar pra nada (vazio)
        return novo; //se nao tiver nada no nó que foi inserido, retorna o ponteiro para o nó criado
    }
    else{   //ou seja, o nó aponta para algum lugar (ele tem filhos)
        pai = aux; //o ponteiro pai aponta para o no que a gnt recebeu
        flag = 0; //flag para comparação dos while
        while(flag == 0){
            if(pai->info<input){ //se a informação do pai for menor que o input -> o input vai ser comparada com a subarvore da direita

                if(pai->right==NULL){   //se a subarvore da direita está vazia, o novo vai ser lá
                    pai->right = novo;  
                    flag = 1;           //o codigo para de rodar
                }
                else{
                    pai=pai->right; //se a direita tiver algum item, o pai atualiza para rodar o codigo até achar o local do novo
                }

            }
            else{
                if(pai->info>input){    //se a informação salva em pai for maior que o input, o input vai ser comparado com a subarvore da esquerda
                    if(pai->left==NULL){
                        pai->left=novo; //o novo é jogado para a subarvore da esquerda , já que ela nao aponta pra nada
                        flag = 1; //finaliza o while
                    }
                    else{
                        pai=pai->left; //atualiza o valor do pai para a subarvore da esquerda
                    }
                }
            } 
        }
    }

    return aux; //retorna o ponteiro da subarvore/arvore recebida
}

void insereArvore(Arv* arvIn, int input){

    arvIn -> raiz = aux_insere(arvIn->raiz, input); //puxando a função de inserir o valor na arvore
    //raiz (que é um nó) ta apontando pra o retorno dessa função 

}

//retorna 1 para se tem, 0 para se não tem
int binaryTreeSearch(No* aux, int num){

    No* pai = aux;

    if(pai == NULL){        //se o pai apontar pra nada então retorna 0 -> o item nao foi encontrado
        return 0;}
    if(num == pai->info){   //se o pai for oq estamos procurando, retornar 1
        return 1;}
    if(num > pai->info){    //se o item for maior, chamar função novamente para o pai sendo a direita dele
        return binaryTreeSearch(pai->right, num);}
    if(num < pai->info){    //se o item for maior, chamar função novamente para o pai sendo a esquerda dele
        return binaryTreeSearch(pai->left, num);} 

    return 2; //ocorreu algum erro
}

void printTreePreOrder(No* aux){

    No* pai = aux;
    printf("\n%d", pai->info);
    if(pai->right != NULL){printTreePreOrder(pai->right);}
    if(pai->left != NULL){printTreePreOrder(pai->left);} 

}

void printTreePostOrder(No* aux){

    No* pai = aux;
    if(pai->right != NULL){printTreePostOrder(pai->right);}
    if(pai->left != NULL){printTreePostOrder(pai->left);} 
    printf("\n%d", pai->info);

}

void printTreeInOrder(No* aux){

    No* pai = aux;
    if(pai->right != NULL){printTreeInOrder(pai->right);}
    printf("\n%d", pai->info);
    if(pai->left != NULL){printTreeInOrder(pai->left);} 
    
}

No* removerAux(No* pai, int num){

        if(pai == NULL){    //se o pai não aponta pra nada 
            printf("arvore não existe");
        } 
        else if(num > pai->info){    //se o numero a ser retirado é maior que o pai, ele vai comparar com a subarvore a direita dele
            pai->right = removerAux(pai->right,num); //<- ele vai executar a função até encontrar o nó que ele quer retirar
        }
        else if (num < pai->info){ //se o numero é menor que o pai, ele vai comparar com a subarvore da esquerda
            pai->left = removerAux(pai->left,num); //<- recursivamente até encontrar o no a ser retirado
        }
            else    //achou o nó a ser removido
            {
                if(pai->right == NULL && pai->left == NULL){    //CASO 1 - O NÓ NÃO TEM NENHUMA SUBARVORE
                    free(pai);  //libera a memoria e o pai aponta pra NULL
                    pai = NULL;
                }
                else if(pai->right == NULL){                    //CASO 2 - O NÓ TEM UMA ÚNICA SUBARVORE - ESQUERDA
                    
                    No* temp = pai; 
                    pai = pai->left;    //o nó da esquerda assume o lugar como nó pai e o nó é apagado
                    free(temp);

                }
                else if(pai->left == NULL){                     //CASO 2 - O NÓ TEM UMA ÚNICA SUBARVORE - DIREITA]

                    No* temp = pai;
                    pai= pai->right;    //o no da direita assume lugar como nó pai e o nó é apagado
                    free(temp);

                }
                else{                                           //CASO 3 - O NÓ TEM AS DUAS SUBARVORES - MAIOR VALOR DA SUBARVORE DA ESQUERDA       

                No* temp = pai->left;
                while(temp->right != NULL){ //vai o braço direito da subarvore esquerda até chegar no maior valor
                    temp=temp->right;
                }

                pai->info = temp->info; //as informações são trocadas
                temp->info = num; //deixa o valor do item a ser removido no maior valor da esquerda para ser trocado -> é chamada a função recursivamente
                pai->left = removerAux(pai->left,num);

                }

            }

    return pai;

}

Arv* remover(Arv* a, int num){

    No* aux =  a->raiz;
    if(aux-> info == num && aux->right== NULL && aux->left == NULL){    
        
        free(aux);      //se a raiz da arvore for o número que queremos e ela não tiver nenhum filho
        free(a);        //ai apagamos a arvore inteira
        return NULL;

    }

    a->raiz = removerAux(a->raiz, num); //a função removerAux vai estruturar a arvore da maneira correta e a arvore vai apontar pra ela
    return a;
}

int main(void){

    Arv* arvore1;
    arvore1 = criaArvore();
    insereArvore(arvore1,4); 
    insereArvore(arvore1,9); 
    insereArvore(arvore1,1); 
    insereArvore(arvore1,18); 
    insereArvore(arvore1,7); 

    printf("\n%d",binaryTreeSearch(arvore1->raiz,9));
    printf("\n%d",binaryTreeSearch(arvore1->raiz,2));

    printf("\n\n");
    printTreePreOrder(arvore1->raiz); 
    printf("\n\n");
    printTreePostOrder(arvore1->raiz); 
    printf("\n\n");
    printTreeInOrder(arvore1->raiz); 

    arvore1 = remover(arvore1,4);

    printf("\n\n");
    printTreePreOrder(arvore1->raiz); 

    return 0;
}