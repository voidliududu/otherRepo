/*
	使用mpi并行计算圆周率
*/

#include <stdio.h>
#include <mpi.h>
#include <math.h>

long n = 10000000;
int process_num;
int main(int argc, char *argv[])
{
	double my_pi = 0,pi = 0;
	int my_id;
	double delta = 1.0 / (double)n;
	double x;
	MPI_Status Status;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&process_num);
	MPI_Comm_rank(MPI_COMM_WORLD,&my_id);
	for (int i = my_id + 1; i <= n; i+=process_num) {
		x = i * delta;
		my_pi += sqrt(1 - x*x);
	}
	my_pi *= delta;
	MPI_Reduce(&my_pi,&pi,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
	if (my_id == 0) {
		printf("the number of process is %d\n",process_num );
		printf("the value of pi is : %15.13f",4*pi);
	}
	MPI_Finalize();
	return 0;
}