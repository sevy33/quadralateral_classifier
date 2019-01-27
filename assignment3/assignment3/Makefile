
test: main.o ClassifierTest.o
	g++ main.o ClassifierTest.o -o test

main.o: main.cpp
	g++ -c main.cpp

ClassifierTest.o: ClassifierTest.cpp
	g++ -c ClassifierTest.cpp

clean:
	rm *.o test
