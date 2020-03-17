CFLAGS = -fsanitize=undefined -fsanitize=address -Wall -Wextra -Wshadow

lab3: main.o clist.o | directories
	gcc $(CFLAGS) -o bin/lab3 obj/*.o

directories:
	mkdir -p bin
	mkdir -p obj

main.o: src/main.c | directories
	gcc $(CFLAGS) -I include -o obj/main.o -c src/main.c

clist.o: src/clist.c | directories
	gcc $(CFLAGS) -I include -o obj/clist.o -c src/clist.c

clean:
	rm -r bin obj