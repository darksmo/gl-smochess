INC = -I./src
LDFLAGS = $(INC) -L/usr/X11R6/lib -lGL -lGLU -lglut -lm
CC = gcc

main: clean
	$(CC) src/main.c src/pawn.h src/pawn.c src/chessboard.h src/chessboard.c src/viewer.h src/viewer.c $(LDFLAGS) -o chessboard

clean:
	rm -rf chessboard
