all:
	gcc -g -Wall *.c -lm -lglut -lGL

clean:
	rm -f *.o a.out
