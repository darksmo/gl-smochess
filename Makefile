INC = -I./src -I./src/lib/chess_smoengine/headers
LDFLAGS = $(INC) -fnested-functions -L/usr/X11R6/lib -L./src/lib -lpthread -lGL -lGLU -lglut -lm -lchess_smoengine -O3
CC = gcc

main: clean
	$(CC) src/*.c $(LDFLAGS) -o chessboard

clean:
	rm -rf chessboard
