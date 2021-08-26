CC = gcc
FLAGS = -Wall -g

run: Rubiks

Rubiks: Main.o Solver.o Initial.o Idastar.o Services.o Helper.o Heuristic.o
	$(CC) $(FLAGS) -o Rubiks Main.o Solver.o Initial.o Idastar.o Services.o Helper.o Heuristic.o

Solver.o: Dimension.h Operator.h Node.h
	$(CC) $(FLAGS) -c Solver.c

Initial.o: Dimension.h Operator.h Node.h
	$(CC) $(FLAGS) -c Initial.c

Idastar.o: Dimension.h Operator.h Node.h Services.h
	$(CC) $(FLAGS) -c Idastar.c

Services.o: Dimension.h Operator.h Node.h Services.h Helper.h
	$(CC) $(FLAGS) -c Services.c

Helper.o: Dimension.h Face.h Operator.h Helper.h
	$(CC) $(FLAGS) -c Helper.c

Heuristic.o: Dimension.h
	$(CC) $(FLAGS) -c Heuristic.c

clean:
	rm *.o Rubiks
