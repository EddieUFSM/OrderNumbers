//Compilado em Linux.Sujeito a mudanças caso outro sistema seja utilizado.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct bucket{
    int topo;
    int* balde;
}Bucket;

void bubble(int v[],int parametro1);

void bucket_sort(void (*func_ptr)(int*, int), int* vet, int tam) {
    int i, j, k, clas;
    clas = (int) ceill(1 + 3.3 * log10((double) tam));
    Bucket *b[clas];
    for (i = 0; i < clas; i++){

        b[i] = malloc(sizeof(Bucket));
        b[i]->topo = 0;
        b[i]->balde = malloc(sizeof(int) * tam);
    }

    for(i=0;i<tam;i++){                          //verifica em que balde o elemento deve ficar
        j=(clas)-1;
        while(1){
            if(j<0)
                break;
            if(vet[i]>=j*10){
                int aux = b[j]->topo;
                b[j]->balde[aux]=vet[i];
                (b[j]->topo)++;
                break;
            }
            j--;
        }
    }

    for(i=0;i<clas;i++)                     //ordena os baldes
        if(b[i]->topo)
            func_ptr(b[i]->balde, b[i]->topo);

    i=0;

    for(j=0;j<clas;j++){                    //põe os elementos dos baldes de volta no vetor
        for(k=0;k<b[j]->topo;k++){
            vet[i]=b[j]->balde[k];
            i++;
        }
    }
}

void bubble(int v[], int tam){
    int i,j,temp,flag;
    if(tam)
        for(j=0;j<tam-1;j++){
            flag=0;
            for(i=0;i<tam-1;i++){
                if(v[i+1]<v[i]){
                    temp=v[i];
                    v[i]=v[i+1];
                    v[i+1]=temp;
                    flag=1;
                }
            }
            if(!flag)
                break;
        }
}


void aleatorio(int* vet, int quant){
    {
        srand(100);
        for (int i = 0; i < quant; i++) {
            vet[i] = rand() % 100;
        }
    }
}

void imprimeVetor(int* vet, int tam){
    for (int i = 0; i < tam; i++) {
        printf("[%d] ", vet[i]);
        int jump = i+1;
        if(jump%10 == 0){
            printf("\n");
        }
    }
}

void analizeSort(void (*func_ptr)(int*, int), int* vet, int tam){
    clock_t start = clock();
    bucket_sort(func_ptr, vet,tam);
    //imprimeVetor(vet,tam);
    clock_t stop = clock();
    double elapsed = (double) (stop - start) / CLOCKS_PER_SEC;
    printf("\nTime elapsed: %.5f\n", elapsed);
}


void insertSort(int *vetor, int tam){
    int cont, cont2, cont3, aux;

    for(cont=1; cont < tam; cont++){
        for(cont2=0; cont2<cont; cont2++){
            if(vetor[cont2] > vetor[cont]){
                aux = vetor[cont];
                for(cont3=cont; cont3>cont2; cont3--){
                    vetor[cont3]=vetor[cont3-1];
                }
                vetor[cont2]=aux;
                break;
            }
        }
    }
}



void shellSort(int *vet, int tam){
    int i, j, k=0, temp;
    int gaps[8]={701,301,132,57,23,10,4,1};
    while (gaps[k] > ((tam/2)-1))
        k++;
    while( gaps[k] >= 1 ){
        for(i = gaps[k]; i<tam; i++){
            temp = vet[i];
            j = i - gaps[k];
            while( j >= 0 && temp < vet[j]){
                vet[j+gaps[k]] = vet[j];
                j -= gaps[k];
            }
            vet[j+gaps[k]] = temp;
        }
        k++;
    }
}



void heapsort(int a[], int n) {

    int i = n / 2, pai, filho, t;

    for (;;) {
        if (i > 0) {
            i--;
            t = a[i];
        } else {
            n--;
            if (n == 0) return;
            t = a[n];
            a[n] = a[0];
        }

        pai = i;

        //Primeiro será feita a comparação com o filho da esquerda.
        filho = i * 2 + 1;

        while (filho < n) {

            //Se o filho da esquerda for menor do que o filho da direita,então será feita a troca do filho que será comparado.
            if ((filho + 1 < n)  &&  (a[filho + 1] > a[filho]))
                filho++;
            if (a[filho] > t) {
                a[pai] = a[filho];
                pai = filho;
                filho = pai * 2 + 1;
            } else {
                break;
            }
        }
        a[pai] = t;
    }
}

void main(){
    int quant = 10000000;
    int* vet = malloc(sizeof(int)* quant);

    aleatorio(vet, quant);
    //analizeSort(&shellSort, vet, quant);
    //analizeSort(&heapsort, vet, quant);
    //analizeSort(&bubble, vet, quant);
    analizeSort(&insertSort, vet, quant);


    free(vet);
}
