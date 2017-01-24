all:
	mpicc e_calc.c -o e_calc

run:
	mpirun -np 4 ./e_calc

clean:
	rm -f e_calc
