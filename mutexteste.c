#include<stdio.h> 
#include<string.h> 
#include<pthread.h> 
#include<stdlib.h> 
#include<unistd.h> 
//gcc *c -pthread

pthread_t tid[5]; 
int counter; 
pthread_mutex_t lock; 

void merge(int *vetor,int *aux,int ini,int fim, int meio){
	int iv=ini,ic=meio+1;
	for(int a=ini;a<=fim;a++){
		aux[a]=vetor[a];
	}
	printf("Merge\n");
	int a=ini;
	while((iv<=meio)&&ic<=fim){
		if(aux[iv]<aux[ic])
			vetor[a++]=aux[ic++];
		else
			vetor[a++]=aux[ic++];
	}
	while (iv <= meio) {
		vetor[a++] = aux[iv++];	
		printf("M %d\n",vetor[a]);
	}
	 while (ic <= fim) {
		vetor[a++] = aux[ic++];
	}
}

void sort(int *vetor,int *aux,int ini,int fim){
	if(ini>=fim)
		return;
	int meio=(ini+fim)/2;
	//a função chama a si mesma
	sort(vetor,aux,ini,meio);
	sort(vetor,aux,meio+1,fim);
	
	//if(vetor[meio]<=vetor[meio+1])
		//return;
	merge(vetor,aux,ini,fim,meio);
}



void* trythis(void *arr) 
{ 
	pthread_mutex_lock(&lock); 
	int *vetor = arr;
	int total;
	counter += 1; 
	printf("\n Job %d has started\n", counter); 
	//merge e sort tem q vir aki
	total=sizeof(vetor)/sizeof(vetor[0]);
	printf("total %d\n",total);
	int *aux = malloc(sizeof(int) * total);
	sort(vetor,aux,0,total-1);
	free(aux);	
	printf("\n Job %d has finished\n", counter); 
	pthread_mutex_unlock(&lock); 
	return NULL; 
} 

int array[10000];

int main(int argc, char *argv[ ]) //os argumentos do main entram na linha do prompt
{ 
	int i = 0; 
	int error; 
	int numero = strtol (argv[1],NULL,10);
	printf("->%d\n",argc);
	if (pthread_mutex_init(&lock, NULL) != 0) 
	{ 
		printf("\n mutex falhou\n"); 
		return 1; 
	} 
	//abre os arquivos
	int op=0;
	if(argc>=2){
		for(int a=2; a<argc;a++){
			printf("argv %s\n",argv[a]);
			FILE *fp = fopen(argv[a],"r");
				while(!feof(fp)){
				fscanf(fp,"%d\n",&array[op++]);
				}
			fclose(fp);
		}
	}	
	
	while(i < numero) 
	{ 
		error = pthread_create(&(tid[i]), NULL, &trythis, &array); 
		if (error != 0) 
			printf("\nThread não criada:[%s]", strerror(error)); 
		i++; 
	} 
	for(int a=0;a<numero;a++){
		pthread_join(tid[a], NULL); 
	}
	for(int a=0;a<op;a++){
		printf("num= %d\n",array[a]);
	}
	pthread_mutex_destroy(&lock); 

	return 0; 
} 

