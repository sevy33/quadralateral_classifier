
test: main.o ClassifierTest.o
	g++ main.o ClassifierTest.o -o test

main.o: ./assignment3/assignment3/main.cpp
	g++ -c ./assignment3/assignment3/main.cpp

ClassifierTest.o: ./assignment3/assignment3/ClassifierTest.cpp
	g++ -c ./assignment3/assignment3/ClassifierTest.cpp

clean:
	rm *.o test
