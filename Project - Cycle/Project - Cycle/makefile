kompilator=g++
standard=-std=c++20
optymalizacja=-O3
errors=-pedantic-errors

# debug=-g
debug=

__ : main
	./main
	./main -g edges.txt -c cycles

#	valgrind --leak-check=yes ./main

functions.o : functions.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(errors) -c -o $@ $^
Project-Cycle.o : Project-Cycle.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(errors) -c -o $@ $^

main : functions.o Project-Cycle.o 
	$(kompilator) $(standard) $(debug) $(optymalizacja) $(errors) -o $@ $^

