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
//ordena as médias e os nomes e quantidade de voos em função da média;
void BubbleSort(int n,Airline *x){

        clock_t start_t, end_t;
        double total_t;
		int i,j;

        start_t = clock();
        printf("Iniciando BubbleSort\n");

		for (i=n-1; i>=1;i--){
			for(j=0;j<i;j++){
				if(x[j].media>x[j+1].media){
					//Ordenas os nomes em função da média
					char temp[2];
                    setString(x[j].name, temp);
                    setString(x[j+1].name, x[j].name);
                    setString(temp, x[j+1].name);
					
                    //Ordena as médias
					float aux1;
					aux1 = x[j].media;
					x[j].media = x[j+1].media;
					x[j+1].media = aux1;
					
                    //Ordena a quantidade de voos em função da média
					int aux2;
					aux2 = x[j].qteVoos;
					x[j].qteVoos = x[j+1].qteVoos;
					x[j+1].qteVoos = aux2;

                    //Ordena a quantidade de atrasos em função da média
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
    //Variáveis para calcular tempo de execução
    clock_t start_t, end_t;
    double tempo;

    start_t = clock();
    FILE *VoosDelay, *mediaVoo;
    VoosDelay = carregaArquivo("VoosDelay.csv", "r");
    mediaVoo = carregaArquivo("mediaVoo.csv", "w");
    fputs ("Airline,AverageDelay,amountDelay,amountFlight\n", mediaVoo);   //Coloca cabeçalho no arquivo gerado

    //QUANTIDADE DE LINHAS UTILIZADA:
    int dados = contaLinhas(VoosDelay);
    printf("Quantidade de dados: %d\n", dados);
    
    Airline* airline = malloc(dados*sizeof(Airline));    //Cria uma struct de 'dados' elementos
    Airline* saida = malloc(dados*sizeof(Airline));

    int cont = 0;
    int ler, i,j;
    char charMedia[6], charVoo[7], charAtraso[7];

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
            for (i=cont-1; i>=0; i--){
                if (comparaString(airline[cont-1].name,airline[i].name)){
                    airline[cont-1].qteVoos++;  //Conta quantas vezes o nome da empresa se repetiu, logo quantos voos têm;
                    
                    if(airline[i].atraso){
                        airline[cont-1].qteAtraso++;    //Se houve atraso (1), a quantide de atraso da determinada empresa é incremetada
                    }
                    //Coloca o número total de voos e total de atrasos na primeira referência à companhia aérea i;
                    airline[i].qteVoos = airline[cont-1].qteVoos;
                    airline[i].qteAtraso = airline[cont-1].qteAtraso;
                    
                }
            }
            
        }
        //Caso alguma linha esteja em formato diferente de "XX,1"
        if (ler != 2 && !feof(VoosDelay) && cont!=0){
            printf("Formato incorreto na linha: %d\nCorrija e tente novamente!", cont+2);
            return 0;
        }
    
    } while (!feof(VoosDelay));
    printf("Dados lidos: %d\n", cont);

    //Elimna as repetições
    int k =0;

    for (i=0; i<cont; i++){

        for (j=0;j<k;j++){
            if (comparaString(airline[i].name,saida[j].name)){
                break;
                }
        }

        if (j==k){
            setString(airline[i].name, saida[k].name);
            saida[k].qteVoos = airline[i].qteVoos;
            saida[k].qteAtraso = airline[i].qteAtraso;
            
            //Calcula as médias
            saida[k].media = (float)saida[k].qteAtraso/saida[k].qteVoos;
            k++;
        }

        if(i==cont-1){
            printf("Repeticoes eliminadas!\n");
        }

    }

    //Ordena as médias
    BubbleSort(k, saida);
    
    //Salva os dados
    for(i=0;i<k;i++){
            sprintf(charMedia, "%.3f", saida[i].media);
            sprintf(charVoo, "%d", saida[i].qteVoos);
            sprintf(charAtraso, "%d", saida[i].qteAtraso);

            fputs(saida[i].name, mediaVoo);
            fputs(",", mediaVoo);
            fputs(charMedia, mediaVoo);
            fputs(",", mediaVoo);
            fputs(charAtraso, mediaVoo);
            fputs(",", mediaVoo);
            fputs(charVoo, mediaVoo);
            if(i!=(k-1)){fputs("\n", mediaVoo);}
    }
    printf("Salvo em mediaVoo!\n");
    fclose(mediaVoo);
    fclose(VoosDelay);
    free(airline);
    free(saida);
    end_t = clock();

    tempo = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("\nTempo de execucao total: %f segundos", tempo);

    return 0;
}
