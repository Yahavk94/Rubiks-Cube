CC = gcc
FLAGS = -Wall -g

run: Rubiks

Rubiks: Main.o Solver.o Initial.o Idastar.o Services.o Helper.o Rotations.o Heuristic.o
	$(CC) $(FLAGS) -o Rubiks Main.o Solver.o Initial.o Idastar.o Services.o Helper.o Rotations.o Heuristic.o

Solver.o: Dimension.h Operator.h Node.h
	$(CC) $(FLAGS) -c Solver.c

Initial.o: Dimension.h Operator.h Node.h
	$(CC) $(FLAGS) -c Initial.c

Idastar.o: Dimension.h Operator.h Node.h Services.h
	$(CC) $(FLAGS) -c Idastar.c

Services.o: Dimension.h Operator.h Node.h Services.h Helper.h Rotations.h
	$(CC) $(FLAGS) -c Services.c

Helper.o: Operator.h Helper.h
	$(CC) $(FLAGS) -c Helper.c

Rotations.o: Dimension.h Face.h Rotations.h
	$(CC) $(FLAGS) -c Rotations.c

Heuristic.o: Dimension.h
	$(CC) $(FLAGS) -c Heuristic.c

clean:
	rm *.o Rubiks
