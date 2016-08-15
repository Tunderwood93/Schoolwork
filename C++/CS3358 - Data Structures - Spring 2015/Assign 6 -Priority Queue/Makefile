a6: Assign06Test.o DPQueue.o
	g++ Assign06Test.o DPQueue.o -o a6
Assign06Test.o: Assign06Test.cpp DPQueue.h
	g++ -Wall -ansi -pedantic -c Assign06Test.cpp
DPQueue.o: DPQueue.cpp DPQueue.h
	g++ -Wall -ansi -pedantic -c DPQueue.cpp

clean:
	@rm -rf Assign06Test.o DPQueue.o

cleanall:
	@rm -rf Assign06Test.o DPQueue.o a6
