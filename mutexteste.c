#include<stdio.h> 
#include<string.h> 
#include<pthread.h> 
#include<stdlib.h> 
#include<unistd.h> 

pthread_t tid[2]; 
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
		printf("num= %d\n",counter,dado[a-1]);
	}
	fclose(foo);

	printf("\n Job %d has finished\n", counter); 

	pthread_mutex_unlock(&lock); 

	return NULL; 
} 

int main(int argc, char *argv[ ]) //os argumentos do main entram na linha do prompt
{ 
	int i = 0; 
	int error; 

	if (pthread_mutex_init(&lock, NULL) != 0) 
	{ 
		printf("\n mutex não iniciou\n"); 
		return 1; 
	} 

	while(i < 2) 
	{ 
		error = pthread_create(&(tid[i]), NULL, &trythis, NULL); 
		if (error != 0) 
			printf("\nThread deu erro :[%s]", strerror(error)); 
		i++; 
	} 

	pthread_join(tid[0], NULL); 
	pthread_join(tid[1], NULL); 
	pthread_mutex_destroy(&lock); 

	return 0; 
} 

