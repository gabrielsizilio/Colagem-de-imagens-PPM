#include<stdio.h>
#include<stdlib.h>

typedef struct{
    int r;
    int g;
    int b;
}pixel_t;

int maior_coluna(int a, int b){
    int maior;
    if(a > b){
        maior = a;
    }else
    maior = b;

    return maior;
}

int soma_linhas(int a, int b){
    int soma;
    soma = a + b;

    return soma;
}

int main(){

    int i, j;
    int C1, L1, C2, L2, M1, M2;
    char nome_arquivo1[10], nome_arquivo2[10], modelo[10];

    pixel_t**imagem;
    
    FILE * arq1;
    FILE * arq2;
    FILE * arq3;
    
    scanf("%s %s", nome_arquivo1, nome_arquivo2);
    arq1 = fopen(nome_arquivo1, "r");
    arq2 = fopen(nome_arquivo2, "r");
    arq3 = fopen("colagem_de_imagens.ppm", "w");

    fscanf(arq1, "%s", modelo);
    fscanf(arq1, "%d", &C1);
    fscanf(arq1, "%d", &L1);
    fscanf(arq1, "%d", &M1);
    
    fseek(arq2, 3, SEEK_SET);
    fscanf(arq2, "%d", &C2);
    fscanf(arq2, "%d", &L2);
    fscanf(arq2, "%d", &M2);

    fprintf(arq3, "%s\n", modelo);
    fprintf(arq3, "%d ", maior_coluna(C1, C2));
    fprintf(arq3, "%d\n", soma_linhas(L1, L2));
    fprintf(arq3, "%d\n", M1);

    /*ALOCAÇÃO DA IMAGEM RESPOSTA*/
    imagem = (pixel_t**)malloc(soma_linhas(L1, L2) * sizeof(pixel_t*));
    if(imagem == NULL){
        return 1;
    }

    for(i = 0; i < soma_linhas(L1, L2); i++){
        imagem[i] = (pixel_t*) malloc(maior_coluna(C1, C2) * sizeof(pixel_t));
        if(imagem[i] == NULL){
            return 2;
        }
    }

    /*ESCREVENDO DO ARQUIVO NO ESPAÇO ALOCADO'*/
    for(i = 0; i < L1; i++){
        for(j = 0; j < maior_coluna(C1, C2); j++){
            
            if(j < C1){
                fscanf(arq1, "%d", &imagem[i][j].r);
                fscanf(arq1, "%d", &imagem[i][j].g);
                fscanf(arq1, "%d", &imagem[i][j].b);
            }
            else{
                imagem[i][j].r = M1;
                imagem[i][j].g = M1;
                imagem[i][j].b = M1;
            }
        }
    }

    for(i = L1; i < soma_linhas(L1, L2); i++){
        for(j = 0; j < maior_coluna(C1, C2); j++){
            
            if(j < C2){
                fscanf(arq2, "%d", &imagem[i][j].r);
                fscanf(arq2, "%d", &imagem[i][j].g);
                fscanf(arq2, "%d", &imagem[i][j].b);
            }
            else{
                imagem[i][j].r = M1;
                imagem[i][j].g = M1;
                imagem[i][j].b = M1;
            }
        }
    }

    /*ESCREVENDO NO ARQUIVO*/
    for(i = 0; i < L1; i++){
        for(j = 0; j < maior_coluna(C1, C2); j++){

            fprintf(arq3, "%d\n", imagem[i][j].r);
            fprintf(arq3, "%d\n", imagem[i][j].g);
            fprintf(arq3, "%d\n", imagem[i][j].b);
            
        }
    }

    for(i = L1; i < soma_linhas(L1, L2); i++){
        for(j = 0; j < maior_coluna(C1, C2); j++){

            fprintf(arq3, "%d\n", imagem[i][j].r);
            fprintf(arq3, "%d\n", imagem[i][j].g);
            fprintf(arq3, "%d\n", imagem[i][j].b);
            
        }
    }

    for(i = 0; i < soma_linhas(L1, L2); i++){
        free(imagem[i]);
    }
    free(imagem);

    fclose(arq1);
    fclose(arq2);
    fclose(arq3);
    return 0;
}