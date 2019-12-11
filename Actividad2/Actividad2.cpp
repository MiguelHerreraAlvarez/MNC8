#include <omp.h>
#include <cstdio>

void execute() {
	double op1 = 7.0;
	for (double i = 1.0; i < 1e9; i++)
	{
		double aux = i * 1.000001;
		op1 *= aux;
	}
}


void main()
{
	printf("[COMIENZO]\n");
#pragma omp parallel num_threads(4)
	{
		int id = omp_get_thread_num();
		int num = omp_get_num_threads();
		double tinicial = omp_get_wtime();
		execute();
		double tfinal = omp_get_wtime();
		double tiempo = tfinal - tinicial;

		printf("Hola desde el hilo %d. El tiempo de ejecucion es %f.\n", id, tiempo);
	}
	printf("[FINAL]\n");
	std::getchar();
	return;
}