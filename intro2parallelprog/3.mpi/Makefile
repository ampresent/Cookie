CC = /usr/bin/mpicc
SRC = $(wildcard *.c)
OBJ = $(SRC:%.c=%.o)
EXE = $(SRC:%.c=%)
INCLUDE = -I/usr/include/openmpi
FLAGS = -L/usr/lib/openmpi -lmpi -L/lib/x86_64-linux-gnu -lm

objs: 3.mpi
	$(CC) $(OBJ) -o $(EXE) $(FLAGS) 

3.mpi:
	$(CC) $(INCLUDE) -c $(SRC)

clean:
	rm -rf $(OBJ) $(EXE)
