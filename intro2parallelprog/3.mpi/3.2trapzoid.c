// TODO Make process 0 handle INPUT OUTPUT

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "mpi.h"
#include "math.h"

typedef double(*func)(double);

int myrank, size, count;

double x(double x){
	return x;
}

double trapezoid(double l,double r, int block, func f){
	int i;
	double sum, a, b, delta;
   
	delta = (r - l) / block;
	//printf("myrank=%d, l=%lf, r=%lf, block=%d\n",myrank, l, r, block);

	for (i=0;i<block;i++){
		a = delta * i;
		b = delta * (i+1);
		//printf("a = %lf\tb = %lf\n",l+a,l+b);
		sum += (f(l+a) + f(l+b)) * delta * 0.5;
	}
	return sum;
}

double l, r;
void get_input(){
	FILE* config_fd;
	if (myrank == 0){
		config_fd = fopen("config", "r");
		fscanf(config_fd, "l=%lf,r=%lf,count=%d", &l, &r, &count);
	}
	MPI_Bcast(&l, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Bcast(&r, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Bcast(&count, 1, MPI_INT, 0, MPI_COMM_WORLD);
}

int main(int argc, char* argv[]){
	double local, interval, reduced = 0;
	int block;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

	get_input();

	if (size > count){
		MPI_Finalize();
		return 1;
	}
	
	interval = (r-l)/size;
	block = count / size;

	func myfunc = sin;

	if (count - block*(myrank+1) > 0 && count - block*(myrank+1) < block)
		local = trapezoid(myrank*interval, (myrank+1)*interval, count - block*myrank, myfunc);
	else
		local = trapezoid(myrank*interval, (myrank+1)*interval, block, myfunc);

	MPI_Reduce(&local, &reduced, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

	if (myrank == 0){
		printf("%lf\n", reduced);
	}

	MPI_Finalize();
	return 0;
}
