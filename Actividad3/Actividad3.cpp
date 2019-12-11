#include <omp.h>
#include <cstdio>
#include <cstdlib>

#define CHUNK 10

void main()
{
	double* v1 = (double*) malloc(100 * sizeof(double*));
	double* v2 = (double*) malloc(100 * sizeof(double*));
	double* v3 = (double*) malloc(100 * sizeof(double*));

	for (int i = 0; i < 100; i++)
	{
		v1[i] = i;
		v2[i] = i * 2.0;
		v3[i] = 0;
	}
	
	printf("[COMIENZO]\n");
	#pragma omp parallel num_threads(4)
	{
		int id = omp_get_thread_num();
		int num = omp_get_num_threads();
		printf("Hola desde el hilo %d.\n", id);
		
		#pragma omp for schedule(dynamic,CHUNK)
		for(int i=0; i<100; i++)
		{
			v3[i] = v1[i] + v2[i];
			printf("El hilo %d ha modificado v3[%d]\n", id, i);
		}
	}
	
	printf("[FINAL]\n");
	free(v1);
	free(v2);
	printf("v3 = [ ");
	for (int i = 0; i < 100; i++)
	{
		printf("%lf ", v3[i]);
	}
	printf("]");
	free(v3);
	
	return;
}