#include<stdio.h> 
#include<string.h> 
#include<pthread.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include <time.h> 
#define max 30

int a[max];
int part,qtd;

void merge(int inicio, int meio, int fim) 
{ 
    int* left = new int[meio - inicio + 1]; 
    int* right = new int[fim - meio]; 
	int tam1= meio-inicio, tam2= fim-meio,i,j;
	
	for (i = 0; i < tam1; i++) 
        left[i] = a[i + inicio];
	for (i = 0; i < tam2; i++) 
        right[i] = a[i + mid + 1]; 

	int k = inicio; 
    i = j = 0; 

	while(i<tam1 && j<tam2){
		if(left[i] <= right[j])
			a[k++] = left[i++];
		else
			a[k++] = right[j++];	
	}
	
 	while (i < tam1) { 
        a[k++] = left[i++]; 
    }
	
	while (j < tam2) { 
        a[k++] = right[j++]; 
    }  
}
void mergeSort(int inicio, int fim) 
{ 
     
    int meio = inicio + (fim - inicio) / 2; 
    if (inicio < fim) { 
 
        merge_sort(inicio, meio); 
        merge_sort(meio + 1, fim); 
		merge(inicio, meio, fim); 
    } 
} 
void* merge_sort(void* arg) 
{
	int thr_part = part++
	int inicio = thread_part * (MAX / 4);
	int fim = (thread_part + 1) * (MAX / 4) - 1;
	int meio = inicio+(fim-inicio) / 2;
	if(inicio<fim){
		mergeSort(inicio,meio);
		mergeSort(meio+1,fim);
		merge(inicio,meio,fim);	
	} 
}

