// TODO Make process 0 handle INPUT OUTPUT

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "mpi.h"

typedef double(*func)(double);

double x(double x){
	return x;
}

double trapezoid(int l,int r, func f){
	return (f(r) + f(l)) * (r - l) * 0.5;
}

int main(int argc, char* argv[]){
	int myrank, size;
	double *sum, interval, reduced = 0;
	int l, r;
	FILE* config_fd;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

	config_fd = fopen("config", "r");
	fscanf(config_fd, "%d%d", &l, &r);

	sum = (double*)malloc(sizeof (double) * size);
	memset(sum, 0, sizeof(double) * size);
	interval = (double)(r-l)/size;
	sum[myrank] = trapezoid(myrank*interval, (myrank+1)*interval, x);

	MPI_Reduce(sum, &reduced, size, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

	if (myrank == 0){
		printf("%lf\n", reduced);
	}

	free(sum);
	MPI_Finalize();
	return 0;
}
