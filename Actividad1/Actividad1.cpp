#include <omp.h>
#include <cstdio>

void main()
{
	printf("[COMIENZO]\n");
#pragma omp parallel num_threads(4)
	{
		int id = omp_get_thread_num();
		int num = omp_get_num_threads();
		if (id == 0) {
			printf("Hola desde el hilo %d, somos %d\n", id, num);
		} else {
			printf("Hola desde el hilo %d\n", id);
		}
	}
	printf("[FINAL]\n");
	std::getchar();
	return;
}