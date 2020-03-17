CFLAGS = -fsanitize=address -fsanitize=undefined -Wextra -Wall -Wshadow -Werror

lab_05: obj/main.o lib/libpointlist.a | directories
	gcc $(CFLAGS) -o bin/lab_05 obj/main.o -L lib/ -l pointlist

obj/main.o: src/main.c | directories
	gcc $(CFLAGS) -I include -o obj/main.o -c src/main.c

obj/clist.o: src/clist.c | directories
	gcc $(CFLAGS) -I include -o obj/clist.o -c src/clist.c

obj/point_list.o: src/point_list.c | directories
	gcc $(CFLAGS) -I include -o obj/point_list.o -c src/point_list.c

lib/libpointlist.a: obj/clist.o obj/point_list.o | directories
	ar rcs lib/libpointlist.a obj/clist.o obj/point_list.o

clean:
	rm -r -f obj bin lib lab_05

directories:
	mkdir -p bin
	mkdir -p obj
	mkdir -p lib
