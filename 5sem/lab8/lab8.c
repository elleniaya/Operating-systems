#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#define ERROR -1

#define iter 1000000

struct params{
	long long numId;
	double sum;
} typedef parameters;

int countThreads;

void * countPart(void *params){
	long long i;
	double pi = 0.0;
	for (i = ((parameters *)params)->numId; i < iter ; i += countThreads) {
		pi += 1.0 / (i * 4.0 + 1.0);
		pi -= 1.0 / (i * 4.0 + 3.0);
	}
	printf("Thread %lld finished, partial sum %.16f\n", ((parameters *)params)->numId, pi);
	((parameters *)params)->sum = pi;
	return (void *) params;
}

int main(int argc, char** argv){
	double Pi = 0;
	countThreads = atol(argv[1]);
	if (countThreads < 1) { 
		printf("no count thread\n");
		return ERROR;
	}
	parameters * params = malloc(countThreads * sizeof(parameters));
	pthread_t * threads = (pthread_t*) malloc(sizeof(pthread_t) * countThreads);

	int i;
	for(i = 0; i < countThreads; i++) {
		params[i].numId = i;
		int code = pthread_create(threads + i, NULL, countPart, (void*)(params + i));
		if (code){
			printf("Error create %d: %s\n", code, strerror(code));
			return ERROR;
		}
	}

	parameters * joinRes;
	for (i = 0; i < countThreads; i++){
		int join = pthread_join(threads[i], (void**)&joinRes);
		if (join) {
        		printf("Error join %d: %s\n", join, strerror(join));
        		return ERROR;
    		}
		Pi += joinRes->sum;
	}
	Pi *= 4.0;
	printf ("Pi = %.16f\n", Pi);

    return 0;
}
