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

//Função para substituir Strings;
setString(char *a, char *b){
    int i,j;

    for (i=0; i<strlen(a); i++){
        b[i] = a[i];
    }
    b[i] = '\0';
}


typedef struct
{
    char name[2];
    int qteVoos;
    int atraso;
    int qteAtraso;
    float media;
} Airline;

void BubbleSort(int n,Airline *x){
		int i,j;
		for (i=n-1; i>=1;i--){
			for(j=0;j<i;j++){
				if(x[j].media>x[j+1].media){
					/*TROCA*/
					char temp[2];
                    setString(x[j].name, temp);
                    setString(x[j+1].name, x[j].name);
                    setString(temp, x[j+1].name);
					
					float temp1;
					temp1 = x[j].media;
					x[j].media = x[j+1].media;
					x[j+1].media = temp1;
					
					int temp2;
					temp2 = x[j].qteVoos;
					x[j].qteVoos = x[j+1].qteVoos;
					x[j+1].qteVoos = temp2;

                    int temp3;
					temp3 = x[j].qteAtraso;
					x[j].qteAtraso = x[j+1].qteAtraso;
					x[j+1].qteAtraso = temp3;
				}
			}
		}
}


int main()
{
    FILE *qteVoo, *mediaVoo;
    //voo = carregaArquivo("teste.csv", "r");
    mediaVoo = carregaArquivo("mediaVoo.csv", "r");
    qteVoo = carregaArquivo("qtdeVoo.csv", "w");
    fputs ("Airline,AverageDelay,Delay,Flight\n", qteVoo);   //Coloca cabeçalho no arquivo gerado
    
    //QUANTIDADE DE LINHAS UTILIZADA:
    int dados = 5000;
    
    Airline airline[dados];    //Cria uma struct de x elementos
    int cont = 0;
    int ler, i,j;
    char charMedia[dados*2], charVoo[dados*2], charAtraso[dados*2];

    //Para que a quantidade voos e atraso comece em 0;
    for (i=0; i<dados; i++){
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

    //Salva as médias
    for (i=0;i < cont; i++){
        airline[i].media = (float)airline[i].qteAtraso/airline[i].qteVoos;
    }
    //Ordena as médias
    BubbleSort(5000, airline);

    for (i=0;i < cont; i++){
        sprintf(charMedia, "%.3f", airline[i].media);
        sprintf(charVoo, "%d", airline[i].qteVoos);
        sprintf(charAtraso, "%d", airline[i].qteAtraso);

        fputs(airline[i].name, qteVoo);
        fputs(",", qteVoo);
        fputs(charMedia, qteVoo);
        fputs(",", qteVoo);
        fputs(charAtraso, qteVoo);
        fputs(",", qteVoo);
        fputs(charVoo, qteVoo);
        fputs("\n", qteVoo);

        printf("%s\n", airline[i].name);
    }

    fclose(mediaVoo);
    fclose(qteVoo);

    return 0;
}
