CFLAGS = -Wextra -Wall -Wshadow -Werror

bin/hw_01: obj/main.o obj/bmp.o obj/stego.o | directories
	gcc $(CFLAGS) -o bin/hw_01 obj/*.o

obj/main.o: src/main.c | directories
	gcc $(CFLAGS) -I include -o obj/main.o -c src/main.c

obj/bmp.o: src/bmp.c | directories
	gcc $(CFLAGS) -I include -o obj/bmp.o -c src/bmp.c

obj/stego.o: src/stego.c | directories
	gcc $(CFLAGS) -I include -o obj/stego.o -c src/stego.c

clean:
	rm -r -f obj bin hw_01

directories:
	mkdir -p bin
	mkdir -p obj
