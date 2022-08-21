#include <stdio.h>
#include <stdlib.h>


FILE *carregaArquivo(char *file_name, char *a){

    FILE *arquivo;

    arquivo = fopen(file_name, a);

    if(arquivo != NULL){
        printf("Arquivo lido com sucesso!\n");
        return arquivo;
    }else{
        printf("Erro ao carregar o arquivo!\n");
    }

    return 0;
}

int main()
{
    FILE *voo, *mediaVoo;
    
    voo = fopen("Airlines.csv", "r");
    mediaVoo = fopen("VoosDelay.csv", "w");
    
    int i, dados, k = 0, cont = 0;;
    char valor1[100], *pt;

    printf("Quer tratar quantas linhas?\n");
    scanf("%d", &dados);

    if(dados<=0){
        printf("Erro!\n");
        return 0;
    }

    while(fscanf(voo, "%s", valor1) != EOF){
        i = 0;
        
        pt = strtok(valor1, ",");
        if(cont!=0){
            fputs("\n", mediaVoo);
        }
        while(pt) {
            if(i==1){
                fputs(pt, mediaVoo);
                fputs(",", mediaVoo);
            } else if (i == 8) {
                fputs(pt, mediaVoo);
            }
            i++;
            pt = strtok(NULL, ",");
        }
        k++;
        if(k==dados+1){
            break;
        }
        cont++;
    }

    fclose(voo);
    fclose(mediaVoo);  
    printf("\nVoosDelay gerado com %d linhas", cont);
    return 0;
}