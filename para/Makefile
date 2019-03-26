all:
	mpiCC calcPi.c -o calcPi
run:
	mpirun --oversubscribe -n 4 ./calcPi
clean:
	rm calcPi