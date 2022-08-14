#include<stdio.h>
#include<stdlib.h>

// C program for implementation of Bubble sort

typedef struct {
    char nome[2];
    int atraso;
} AIRLINE;

//Bubble Sort

void bubbleSort(int vet[], int tam){
  int i,j, temp;
  for(i=tam-1; i>0; i--){
    for(j=0; j < i; j++) //Faz trocas até posição i
      if( vet[j] > vet[j+1] ){
        temp = vet[j];
        vet[j] = vet[j+1];
        vet[j+1] = temp;
      }
  }
}

int main()
{    
    FILE *arquivo; // Ponteiro do arquivo
    AIRLINE a;
    char aleatorio[50];
    char *pt;
    int i=1;


    if(arquivo = fopen("mediaVoo.csv", "r")) { // Abre o arquivo para leitura
        fseek(arquivo, 0, SEEK_SET); // Posiciona o ponteiro no inicio do arquivo

        while(!feof(arquivo)) { // A funcao feof retorna 0 quando o ponteiro atinge o final do arquivo

            fscanf(arquivo, "%[^;]s", a.nome);
            fseek(arquivo, +1, SEEK_CUR);
            fscanf(arquivo, "%d[^\n]", &a.atraso);

            printf("%s|%d", a.nome, a.atraso);


        }
        fclose(arquivo);
    } else {
        printf("\nErro ao abrir arquivo\n");
        getch();
    }
    return 0;


}


// switch (a.nome)
// {
// case "AS":
//     /* code */
//     break;
// case "AA":
//     /* code */
//     break;
// case "AC":
//     /* code */
//     break;
// case "AM":
//     /* code */
//     break;
// case "CO":
//     /* code */
//     break;
// case "DL":
//     /* code */
//     break;
// case "FX":
//     /* code */
//     break;
// case "HA":
//     /* code */
//     break;
// case "NW":
//     /* code */
//     break;
// case "PO":
//     /* code */
//     break;
// case "SW":
//     /* code */
//     break;
// case "UA":
//     /* code */
//     break;
// case "5X":
//     /* code */
//     break;
// case "VS"::
//     /* code */
//     break;
// case "VB"::
//     /* code */
//     break;
// case "WS"::
//     /* code */
//     break;
// }

