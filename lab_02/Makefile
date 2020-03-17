lab2: test.o test_str.o str.o | directories
	gcc -I include -o bin/lab2 obj/*.o

directories:
	mkdir -p bin/
	mkdir -p obj/

test.o: src/test.c | directories
	gcc -I include -o obj/test.o -c src/test.c -Wall -Wextra -Werror

test_str.o: src/test_str.c | directories
	gcc -I include -o obj/test_str.o -c src/test_str.c -Wall -Wextra -Werror

str.o: src/str.c | directories
	gcc -I include -o obj/str.o -c src/str.c -Wall -Wextra -Werror

clean:
	rm -r -f -- obj bin

 
