all: Object ParameterManager Tester

Object:
	gcc -std=c99 -c src/ParameterManager.c  src/ParameterManager.h

ParameterManager: Object
	rm -rf libpm.a
	ar rvs libpm.a ParameterManager.o

Tester: ParameterManager 
	gcc -o test1 src/tester.c libpm.a  -std=c99
	gcc -o test2 src/a1example.c libpm.a -std=c99
