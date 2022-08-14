#include <stdio.h>
#include <stdlib.h>

//Função para realizar ação com arquivo
//Passa nome do arquivo e oq deseja fazer
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

//Função para comparar duas strings
int comparaString(char *a, char *b)
{
    int i;
    int resp;

    if (strlen(a) == strlen(b)) {
        for (i = 0; i < strlen(a); i++) {
            if (a[i] == b [i]) {
                resp = 1;
            } else {
                return 0;
            }
        }
    } else {
        resp = 0;
    }

    return resp;
}


typedef struct
{
    char name[2];
    int qteVoos;
    int atraso;
    int qteAtraso;
} Airline;



int main()
{
    FILE *qteVoo, *mediaVoo;
    //voo = carregaArquivo("teste.csv", "r");
    mediaVoo = carregaArquivo("mediaVoo.csv", "r");
    qteVoo = carregaArquivo("qtdeVoo.csv", "w");
    fputs ("Airline,AverageDelay\n", qteVoo);   //Coloca cabeçalho no arquivo gerado

    Airline airline[10];    //Cria uma struct de 10 elementos (o arquivo teste possui 10 voos)
    int cont = 0;
    int ler, i,j;
    float media[10];
    char charMedia[300];

    //Para que a quantidade voos e atraso comece em 0;
    for (i=0; i<10; i++){
        airline[i].qteVoos = 0;
        airline[i].qteAtraso = 0;
    }

    do{
        //Ler o nome da empresa (com 2 char) e o atraso
        ler = fscanf(mediaVoo, "%2[^,],%d\n", airline[cont].name, 
                        &airline[cont].atraso);
        
        if (ler == 2){
            cont++;
            for (i=0; i<cont; i++){
                if (comparaString(airline[cont-1].name,airline[i].name)){
                    airline[cont-1].qteVoos++;  //Conta quantas vezes o nome da empresa se repetiu, logo quantos voos têm;

                    if(airline[i].atraso){
                        airline[cont-1].qteAtraso++;    //Se houve atraso (1), a quantide de atraso da determinada empresa é incremetada
                    }
                }
            }
        }
    
    } while (!feof(mediaVoo));
    
    //Associa o valor final de quantidade de voos e atrasos para cada empresa, independente de quando ela aparece
    //PRECISA ELIMINAR A REPETIÇÃO
    for (i=cont;i >= 0; i--){
        for (j = 0; j < cont; j++){
            if(comparaString(airline[i].name,airline[j].name)){
                airline[j].qteVoos = airline[i].qteVoos;
                airline[j].qteAtraso = airline[i].qteAtraso;
            }
        }
    }

    //Imprime os valores no arquivo csv
    for (i=0;i < cont; i++){
        media[i] = (float)airline[i].qteAtraso/airline[i].qteVoos;
        printf("%s voo %d vezes e atrasou %d vez(s).Media: %.3f\n", 
        airline[i].name, airline[i].qteVoos, airline[i].qteAtraso,
        media[i]);

        sprintf(charMedia, "%.3f", media[i]);

        fputs(airline[i].name, qteVoo);
        fputs(",", qteVoo);
        fputs(charMedia, qteVoo);
        fputs("\n", qteVoo);
    }
    

    fclose(mediaVoo);
    fclose(qteVoo);

    return 0;
}