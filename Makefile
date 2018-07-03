
run: main
	./main 0 && python results/main.py 0

1: main
	./main 1

2: main
	./main 2 && python results/main.py 2

3: main
	./main 3

main: main.o util/util.o label/label.o timeserie/timeserie.o dtw/dtw.o
	g++ main.o util/util.o label/label.o timeserie/timeserie.o dtw/dtw.o -o main

main.o: main.cpp
	g++ -c main.cpp

timeserie.o: timeserie/timeserie.cpp timeserie/timeserie.hpp
	g++ -c timeserie/timeserie.cpp -o timeserie/timeserie.o

label.o: label/label.cpp label/label.hpp
	g++ -c label/label.cpp -o label/label.o

dtw.o: dtw/dtw.cpp dtw/dtw.hpp
	g++ -c dtw/dtw.cpp -o dtw/dtw.o

util.o: util/util.cpp util/util.hpp
	g++ -c util/util.cpp -o util/util.o

clean:
	rm *.o util/*.o timeserie/*.o label/*.o dtw/*.o results/*.png results/*.txt main
