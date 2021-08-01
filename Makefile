CC = gcc
FLAGS = -Wall -g

run: Rubiks

Rubiks: Main.o Solver.o Initial.o Idastar.o Services.o Rotations.o Heuristic.o
	$(CC) $(FLAGS) Main.o Solver.o Initial.o Idastar.o Services.o Rotations.o Heuristic.o -o Rubiks

Solver.o: Dimension.h Operator.h Node.h
	$(CC) $(FLAGS) -c Solver.c

Initial.o: Dimension.h Operator.h Node.h
	$(CC) $(FLAGS) -c Initial.c

Idastar.o: Dimension.h Operator.h Node.h Services.h
	$(CC) $(FLAGS) -c Idastar.c

Services.o: Dimension.h Operator.h Node.h Services.h Rotations.h
	$(CC) $(FLAGS) -c Services.c

Rotations.o: Dimension.h Face.h Rotations.h
	$(CC) $(FLAGS) -c Rotations.c

Heuristic.o: Dimension.h
	$(CC) $(FLAGS) -c Heuristic.c

clean:
	rm *.o Rubiks
