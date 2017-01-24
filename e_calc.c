#include "mpi.h"
#include <math.h>

static int factorial(int x)
{
	int r = 1;
	for (int i = 2; i <= x; ++i)
		r *=i;
	return r;
}

int main(argc,argv)
	int argc;
	char *argv[];
{
	int n, myid, numprocs, i;
	double e_num_const = 2.71828182845904523536;
	double my_e, e, h, sum, x, a;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	while (1) 
	{
		if (myid == 0) {
			printf("Enter the number of intervals: (0 quits) ");
			scanf("%d",&n);
		}
		MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
		if (n == 0) break;
		sum = 0.0;
		x = 1.0;
		for (i = myid + 1; i <= n; i += numprocs) 
		{
			x *= 1.0 / factorial(i);
			sum += x;
		}
		
		printf("sum = %.16f\n", sum);
		
		my_e = sum;
		if (myid == 0)
			my_e += 1.0; // 0!
	
		MPI_Reduce(&my_e, &e, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
		if (myid == 0)
			printf("e is approximately %.16f, Error is %.16f\n", e, fabs(e - e_num_const));
	}
	MPI_Finalize();
}
