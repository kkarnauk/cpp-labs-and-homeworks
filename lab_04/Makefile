CFLAGS = -fsanitize=address -fsanitize=undefined -Wextra -Wall -Wshadow

lab_04: obj/main.o obj/mergesort.o | directories
	gcc $(CFLAGS) -o bin/lab_04 obj/*.o

obj/main.o: src/main.c | directories
	gcc $(CFLAGS) -I include -o obj/main.o -c src/main.c

obj/mergesort.o: src/mergesort.c | directories
	gcc $(CFLAGS) -I include -o obj/mergesort.o -c src/mergesort.c

clean:
	rm -r -f obj bin lab_04

directories:
	mkdir -p bin
	mkdir -p obj
