INC = -I./src
LDFLAGS = $(INC) -L/usr/X11R6/lib -lGL -lGLU -lglut -lm
CC = gcc

main: clean
	$(CC) src/placer.h src/placer.c src/table.h src/table.c src/main.c src/glm.h src/glm.c src/pawn.h src/pawn.c src/chessboard.h src/chessboard.c src/viewer.h src/viewer.c $(LDFLAGS) -o chessboard

clean:
	rm -rf chessboard
