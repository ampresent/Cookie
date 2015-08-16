// TODO Make process 0 handle INPUT OUTPUT

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "mpi.h"
#include "math.h"

//GLOBAL
int myrank, size;

void build_my_type(double *l, double *r, int *count, MPI_Datatype* newtype){
	int array_of_blocklengths[3] = {1,1,1};
	MPI_Datatype array_of_types[3] = {MPI_DOUBLE, MPI_DOUBLE, MPI_INT};
	MPI_Aint l_addr, r_addr, count_addr;
	MPI_Aint array_of_displacements[3] = {0};

	MPI_Get_address(count, &count_addr);
	MPI_Get_address(l, &l_addr);
	MPI_Get_address(r, &r_addr);
	printf("%p %p %p\n",count,l,r);
	array_of_displacements[1] = l_addr - count_addr;
	array_of_displacements[2] = r_addr - l_addr;
	MPI_Type_create_struct(3, array_of_blocklengths,
			array_of_displacements, array_of_types, newtype);
	MPI_Type_commit(newtype);
}

typedef double(*func)(double);

int count;
double l, r;

double x(double x){
	return x;
}


double trapezoid(double l,double r, int block, func f){
	int i;
	double sum, a, b, delta;
   
	delta = (r - l) / block;

	for (i=0;i<block;i++){
		a = delta * i;
		b = delta * (i+1);
		sum += (f(l+a) + f(l+b)) * delta * 0.5;
	}
	return sum;
}

void get_input(){
	FILE *config_fd;
	MPI_Datatype newtype;
	if (myrank == 0){
		config_fd = fopen("config", "r");
		fscanf(config_fd, "l=%lf,r=%lf,count=%d", &l, &r, &count);
	}
	build_my_type(&l, &r, &count, &newtype);
	MPI_Bcast(&count, 1, newtype, 0, MPI_COMM_WORLD);
	MPI_Type_free(&newtype);
}

int main(int argc, char* argv[]){
	//LOCAL
	double local, interval, reduced = 0;
	int block;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

	get_input();
	printf("myrank=%d\nl=%lf\tr=%lf\tcount=%d\n", myrank,l,r,count);

	if (size > count){
		MPI_Finalize();
		return 1;
	}
	
	interval = (r-l)/size;
	block = count / size;

	func myfunc = sin;

	if (block == 0){
		local = 0;
	}else{
		if (count - block*(myrank+1) > 0 && count - block*(myrank+1) < block)
			local = trapezoid(myrank*interval, (myrank+1)*interval, count - block*myrank, myfunc);
		else
			local = trapezoid(myrank*interval, (myrank+1)*interval, block, myfunc);
	}

	printf("myrank=%d\tdone", myrank);
	MPI_Reduce(&local, &reduced, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

	if (myrank == 0){
		printf("%lf\n", reduced);
	}

	MPI_Finalize();
	return 0;
}
