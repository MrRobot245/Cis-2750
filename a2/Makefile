Path1 =/usr/lib/jvm/java-1.6.0-openjdk/include
Path2 =/usr/lib/jvm/java-1.6.0-openjdk/include/linux

all: Object Dialogc Run Clean

Object:
	gcc -std=c99  -fPIC -I$(Path1) -I$(Path2) -Iinclude src/ParameterManager.c -o ParameterManager.o -c
	gcc -std=c99  -fPIC -I$(Path1) -I$(Path2) -Iinclude src/JNICALLS.c -o JNICALLS.o -c
	gcc -I$(Path1) -I$(Path2) ParameterManager.o JNICALLS.o -shared -Wl,-soname,libDialog.so -o libDialog.so

Dialogc: Object
	javac src/Dialogc.java
	javah -classpath src/ -jni Dialogc

Run: Dialogc
	export LD_LIBRARY_PATH=:.
	java -cp src/ Dialogc

Clean:
	rm -rf src/*.class
	rm -rf *.o
	rm -rf *.log
