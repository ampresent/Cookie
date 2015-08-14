CC = /usr/bin/mpicc
SRC = $(wildcard *.c)
OBJ = $(SRC:%.c=%.o)
EXE = $(SRC:%.c=%)
INCLUDE = /usr/include/mpi
FLAGS = -L/usr/lib/mpi -lmpi

objs: 3.mpi
	$(CC) $(FLAGS) $(OBJ) -o $(EXE)

3.mpi:
	$(CC) -I$(INCLUDE) -c $(SRC)
