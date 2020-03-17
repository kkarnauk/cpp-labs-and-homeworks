CFLAGS = -O2 -Wall -Werror -std=c++17 -Iinclude

EXE = hw_02
TESTEXE = test_hw_02

$(EXE): obj/Board.o obj/main.o obj/GameController.o obj/StdioBoardView.o obj/BoardTest.o obj/Test.o obj/mainTest.cpp obj/NcursesBoardView.o  | directories
	g++ $(CFLAGS) -o $(EXE) obj/Board.o obj/main.o obj/GameController.o obj/StdioBoardView.o obj/NcursesBoardView.o  -lncurses
	g++ $(CFLAGS) -o $(TESTEXE) obj/mainTest.o obj/BoardTest.o obj/Test.o obj/Board.o

obj/main.o: src/main.cpp | directories
	g++ $(CFLAGS) -o obj/main.o -c src/main.cpp

obj/Board.o: src/Board.cpp | directories
	g++ $(CFLAGS) -o obj/Board.o -c src/Board.cpp

obj/GameController.o: src/GameController.cpp | directories
	g++ $(CFLAGS) -o obj/GameController.o -c src/GameController.cpp

obj/StdioBoardView.o: src/StdioBoardView.cpp | directories
	g++ $(CFLAGS) -o obj/StdioBoardView.o -c src/StdioBoardView.cpp

obj/NcursesBoardView.o: src/NcursesBoardView.cpp | directories
	g++ $(CFLAGS) -o obj/NcursesBoardView.o -c src/NcursesBoardView.cpp

obj/BoardTest.o: test/BoardTest.cpp | directories
	g++ $(CFLAGS) -o obj/BoardTest.o -c test/BoardTest.cpp

obj/Test.o: test/Test.cpp | directories
	g++ $(CFLAGS) -o obj/Test.o -c test/Test.cpp

obj/mainTest.cpp: test/mainTest.cpp | directories
	g++ $(CFLAGS) -o obj/mainTest.o -c test/mainTest.cpp

clean:
	rm -rf obj $(EXE) $(TESTEXE)

directories:
	mkdir -p obj

.PHONY: clean all
