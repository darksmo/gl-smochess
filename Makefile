INC = -I./src -I./src/lib/chess_smoengine/headers
LDFLAGS = $(INC) -L/usr/X11R6/lib -L./src/lib -lGL -lGLU -lglut -lm -lchess_smoengine
CC = gcc

main: clean
	$(CC) src/*.c $(LDFLAGS) -o chessboard

clean:
	rm -rf chessboard
