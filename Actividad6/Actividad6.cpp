#include <omp.h>
#include <cstdio>
#include <cstdlib>

void main()
{
	double* v1 = (double*)malloc(100 * sizeof(double*));
	double* v2 = (double*)malloc(100 * sizeof(double*));
	double* v3 = (double*)malloc(100 * sizeof(double*));
	double* v4 = (double*)malloc(100 * sizeof(double*));

	for (int i = 0; i < 100; i++)
	{
		v1[i] = i;
		v2[i] = i * 2.0;
		v3[i] = 0;
		v4[i] = 0;
	}

	printf("[COMIENZO]\n");

#pragma omp parallel num_threads(4) 
	{
		int id = omp_get_thread_num();
		int num = omp_get_num_threads();
		

	#pragma omp sections nowait 
		{

		#pragma omp section 
			{
				for (int i = 0; i < 50; i++) {
					v3[i] = v1[i] + v2[i];
					printf("El hilo %d ha modificado v3[%d]\n", id, i);
				}
			}

		#pragma omp section 
			{
				for (int i = 0; i < 50; i++) {
					v4[i] = v1[i] * v2[i];
					printf("El hilo %d ha modificado v4[%d]\n", id, i);
				}
			}

		#pragma omp section 
			{
				for (int i = 50; i < 100; i++) {
					v3[i] = v1[i] + v2[i];
					printf("El hilo %d ha modificado v3[%d]\n", id, i);
				}
			}

		#pragma omp section 
			{
				for (int i = 50; i < 100; i++) {
					v4[i] = v1[i] * v2[i];
					printf("El hilo %d ha modificado v4[%d]\n", id, i);
				}
			}
		}

		printf("Hola desde el hilo %d.\n", id);
	}

	printf("[FINAL]\n\n");
	free(v1);
	free(v2);

	printf("v3 = [ ");
	for (int i = 0; i < 100; i++)
	{
		printf("%lf ", v3[i]);
	}
	printf("]\n\n");

	printf("v4 = [ ");
	for (int i = 0; i < 100; i++)
	{
		printf("%lf ", v4[i]);
	}
	printf("]");

	free(v3);
	free(v4);

	return;
}