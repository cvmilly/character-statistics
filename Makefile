hw1.x: proj1.o
	g++ -o hw1.x proj1.o

proj1.o: proj1.cpp
	g++ -std=c++11 -c proj1.cpp

clean:
	-rm *.o hw1.x
