# to run: make
# to eliminate .o files: make clean

calc: calcTst.o calc.o stack2.o list.o
	g++ -o calc calcTst.o calc.o stack2.o list.o

calcTst.o: calcTst.cpp
	g++ -c calcTst.cpp 

calc.o: calc.cpp
	g++ -c calc.cpp 

stack2.o: stack2.cpp
	g++ -c stack2.cpp 

list.o: list.cpp
	g++ -c list.cpp 

clean:
	rm -f *.o calc
