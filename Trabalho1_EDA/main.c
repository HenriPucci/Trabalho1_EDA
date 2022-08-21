#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Função para realizar ação com arquivo
//Passa nome do arquivo e oq deseja fazer
FILE *carregaArquivo(char *file_name, char *a){

    FILE *arquivo;

    arquivo = fopen(file_name, a);

    if(arquivo != NULL){
        if(a=="r"){
            printf("Arquivo lido com sucesso!\n");
        } else if(a=="w"){
            printf("Arquivo criado com sucesso!\n");
        } else{
            printf("Arquivo localizado com sucesso!\n");
        }
        
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

int contaLinhas(FILE *file_name){
    int tam = 0, ler, x;
    char y[3];
    while(!feof(file_name)){
        ler = fscanf(file_name, "%2[^,],%d\n", y, &x);

        if(ler==2){
            tam++;
        }
    }
    fseek(file_name, 0, SEEK_SET);
    return tam;
}

typedef struct
{
    char name[2];
    int qteVoos;
    int atraso;
    int qteAtraso;
    float media;
} Airline;

//Função de ordenação BubbleSort
//ordena as médias e os nomes e quantidade de voos em função da media;
void BubbleSort(int n,Airline *x){

        printf("Iniciando BubbleSort\n");
        clock_t start_t, end_t;
        double total_t;
		int i,j;

        start_t = clock();

		for (i=n-1; i>=1;i--){
			for(j=0;j<i;j++){
				if(x[j].media>x[j+1].media){
					/*TROCA*/
					char temp[2];
                    setString(x[j].name, temp);
                    setString(x[j+1].name, x[j].name);
                    setString(temp, x[j+1].name);
					
					float aux1;
					aux1 = x[j].media;
					x[j].media = x[j+1].media;
					x[j+1].media = aux1;
					
					int aux2;
					aux2 = x[j].qteVoos;
					x[j].qteVoos = x[j+1].qteVoos;
					x[j+1].qteVoos = aux2;

                    int aux3;
					aux3 = x[j].qteAtraso;
					x[j].qteAtraso = x[j+1].qteAtraso;
					x[j+1].qteAtraso = aux3;
				}
			}
		}
        printf("Ordenado!\n");
        end_t = clock();
        total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        printf("Tempo de execucao do BubbleSort: %f segundos\n", total_t);
}


int main()
{
    FILE *VoosDelay, *mediaVoo;
    VoosDelay = carregaArquivo("VoosDelay2.csv", "r");
    mediaVoo = carregaArquivo("mediaVoo.csv", "w");
    fputs ("Airline,AverageDelay,amountDelay,amountFlight\n", mediaVoo);   //Coloca cabeçalho no arquivo gerado

    //QUANTIDADE DE LINHAS UTILIZADA:
    int dados = contaLinhas(VoosDelay);
    printf("Quantidade de dados: %d\n", dados);
    
    Airline* airline = malloc(dados*sizeof(Airline));    //Cria uma struct de 'dados' elementos

    int cont = 0;
    int ler, i,j;
    char charMedia[6], charVoo[7], charAtraso[7];

    clock_t tempo;

    //Para que a quantidade voos e atraso comece em 0;
    for (i=0; i<dados; i++){
        airline[i].qteVoos = 0;
        airline[i].qteAtraso = 0;
    }

    do{
        //Ler o nome da empresa (com 2 char) e o atraso
        ler = fscanf(VoosDelay, "%2[^,],%d\n", airline[cont].name, 
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
        //Caso alguma linha esteja em formato diferente de "XX,1"
        if (ler != 2 && !feof(VoosDelay) && cont!=0){
            printf("Formato incorreto na linha %d\n", cont);
        }
    
    } while (!feof(VoosDelay));

    //Associa o valor final de quantidade de voos e atrasos para cada empresa, independente de quando ela aparece
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

    printf("Dados lidos: %d\n", cont);

    //Ordena as médias
    BubbleSort(dados, airline);

    //Elimina as repetições e salva no arquivo
    int k =0;
    for (i=0; i<cont; i++){

        for (j=0;j<k;j++){
            if (comparaString(airline[i].name,airline[j].name)){
                break;
                }
        }

        if (j==k){
            setString(airline[i].name, airline[k].name);
            airline[k].media = airline[i].media;
            airline[k].qteVoos = airline[i].qteVoos;
            airline[k].qteAtraso = airline[i].qteAtraso;

            sprintf(charMedia, "%.3f", airline[k].media);
            sprintf(charVoo, "%d", airline[k].qteVoos);
            sprintf(charAtraso, "%d", airline[k].qteAtraso);

            fputs(airline[k].name, mediaVoo);
            fputs(",", mediaVoo);
            fputs(charMedia, mediaVoo);
            fputs(",", mediaVoo);
            fputs(charAtraso, mediaVoo);
            fputs(",", mediaVoo);
            fputs(charVoo, mediaVoo);
            fputs("\n", mediaVoo);
            k++;
        }

        if(i==cont-1){
            printf("Salvo em mediaVoo!\n");
        }

    }

    tempo = clock();
    printf("\nTempo de execucao total: %f segundos", (float)tempo/CLOCKS_PER_SEC);
    fclose(mediaVoo);
    fclose(VoosDelay);
    free(airline);

    return 0;
}
