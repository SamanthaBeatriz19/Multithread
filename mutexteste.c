#include<stdio.h> 
#include<string.h> 
#include<pthread.h> 
#include<stdlib.h> 
#include<unistd.h> 
//gcc *c -pthread

pthread_t tid[5]; 
int counter; 
pthread_mutex_t lock; 

void* trythis(void *arg) 
{ 
	pthread_mutex_lock(&lock); 

	counter += 1; 
	printf("\n Job %d has started\n", counter); 
	int a=0,dado[20];
	FILE * foo = fopen("teste.dat","r");
	while(!feof(foo)){
		fscanf(foo,"%d\n",&dado[a++]);
		printf("num= %d\n",dado[a-1]);
	}
	fclose(foo);

	printf("\n Job %d has finished\n", counter); 

	pthread_mutex_unlock(&lock); 

	return NULL; 
} 

int main(int argc, char *argv[ ]) //os argumentos do main entram na linha do prompt
{ // o argume
	int i = 0; 
	int error; 
	int numero = strtol (argv[1],NULL,10);
	printf("-%d\n",numero);
	if (pthread_mutex_init(&lock, NULL) != 0) 
	{ 
		printf("\n mutex init has failed\n"); 
		return 1; 
	} 

	while(i < numero) 
	{ 
		error = pthread_create(&(tid[i]), NULL, &trythis, NULL); 
		if (error != 0) 
			printf("\nThread can't be created :[%s]", strerror(error)); 
		i++; 
	} 
	for(int a=0;a<numero;a++){
		pthread_join(tid[a], NULL); 
	} 
	pthread_mutex_destroy(&lock); 

	return 0; 
} 

